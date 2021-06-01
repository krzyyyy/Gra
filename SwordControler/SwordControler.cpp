#include "pch.h"
#include "SwordControler.h"
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include "..\Core\StreamOperators.h"
#include "..\glm\gtc\matrix_transform.hpp"

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
    std::cout << globalPosition << std::endl;
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
    auto basicDirection = glm::vec3(0., 0., 1.);
    glm::vec3 rotationAxis = glm::cross(basicDirection, orientationVector);
    float teta = glm::dot(basicDirection, orientationVector);
    auto globalPosition = glm::mat4(1);
    globalPosition = glm::rotate(globalPosition, teta, rotationAxis);
    std::cout << orientationVector << std::endl;
    return globalPosition;
}
