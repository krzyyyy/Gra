#include "pch.h"
#include <numeric>
#include "SwordControler.h"
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include "..\Core\StreamOperators.h"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"

//#include "SwordControler.h"
//
//
//
//
namespace http = boost::beast::http;

SwordControler::SwordControler() :
    io_context(),
    socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 13)),
    reciveThread(),
    mutex(),
    done(false)
{
    reciveThread = std::thread([this]()
        {
            Start();
            io_context.run();
        });
    auto initializeSample = glm::vec3(0., 1., 0.);
    std::for_each(samples.begin(), samples.end(), [initializeSample](glm::vec3& element)
        {
            element = initializeSample;
        });
    
}

bool SwordControler::Start()
{
    socket.async_receive_from(
        boost::asio::buffer(reciveBuffer), remoteEndpoint,
        [this](const boost::system::error_code& error, // Result of operation.
            std::size_t bytesTransferred)
        {
            if ((!error || error == boost::asio::error::message_size)&& (!done))
            {
            auto inputData = std::string(reciveBuffer.begin(), reciveBuffer.begin() + bytesTransferred);
            glm::mat4 globalPosition = ParseInput(inputData);
            mutex.lock();
            this->globalPosition = globalPosition;
            mutex.unlock();
            Start();
            }
        }
    );
    return true;
}

glm::mat4 SwordControler::ActualizePosition()
{
    std::scoped_lock csoped_lock(mutex);
    return globalPosition;
}

void SwordControler::Close()
{
}

SwordControler::~SwordControler()
{
    done = true;
    reciveThread.join();
}

glm::mat4 SwordControler::ParseInput(const std::string& inputData)
{
    static int i = 0;
    if(i% 10 ==0)
        std::cout << inputData <<std::endl;
    ++i;
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    glm::vec3 orientationVector = glm::vec3(0, 0, 0);
    auto numberList = std::vector<double>();
    std::vector<std::string> stringList = std::vector<std::string>();
    boost::split(stringList, inputData, [](char c)
        {
            return c == ',';
    });
    std::transform(stringList.cbegin(), stringList.cend(),std::back_inserter(numberList), [](const std::string& element)
        {
            return std::stod(element);
        }
    );
    if (numberList.size() > 4)
    {
        double time = numberList[0];
        double index = numberList[1];
        orientationVector = glm::vec3(numberList[2], numberList[3], numberList[4]);
    }
    orientationVector = glm::normalize(orientationVector);
    auto basicDirection = glm::vec3(0., 1., 0.);
    //glm::vec3 rotationAxis = std::accumulate(samples.cbegin(), samples.cend(), glm::vec3(0, 0, 0)) / float(samples.size());
    float rcos = glm::dot(basicDirection, orientationVector);
    auto crossProduct = glm::cross(basicDirection, orientationVector);
    float rsin = glm::length(crossProduct);
    float u = crossProduct.x;
    float v = crossProduct.y;
    float w = crossProduct.z;
    float matrixData[] = {rcos + (u * u * (1 - rcos)), w * rsin + v * u * (1 - rcos), -v * rsin + w * u * (1 - rcos),0 ,
                          -w * rsin + u * v * (1 - rcos) , rcos + v * v * (1 - rcos) , u * rsin + w * v * (1 - rcos) , 0,
                          v * rsin + u * w * (1 - rcos) , -u * rsin + v * w * (1 - rcos) , rcos + w * w * (1 - rcos) , 0 ,
                            0, 0, 0, 1};
    globalPosition = glm::make_mat4(matrixData);
    //std::cout << orientationVector << std::endl;
    return globalPosition;
}

glm::vec3 SwordControler::ComputeMeanValue()
{
    auto averageValue = std::accumulate(samples.cbegin(), samples.cend(), glm::vec3(0, 0, 0))/float( samples.size());
    return averageValue;
}
