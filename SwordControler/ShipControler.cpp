#include "pch.h"
#include <numeric>
#include <numbers>
#include "ShipControler.h"
//#include <boost/asio.hpp>
//#include <boost/algorithm/string.hpp>
#include "..\Core\StreamOperators.h"
#include "..\glm\gtc\matrix_transform.hpp"
#include "..\glm\gtc\type_ptr.hpp"
#include "..\glm/gtx/matrix_decompose.hpp"

//#include "SwordControler.h"
//
//
//
//
//namespace http = boost::beast::http;
//
//ShipControler::ShipControler() :
//    io_context(),
//    socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 13)),
//    reciveThread(),
//    mutex(),
//    done(false)
//{
//    reciveThread = std::thread([this]()
//        {
//            Start();
//            io_context.run();
//        });
//    auto initializeSample = glm::vec3(0., 1., 0.);
//    std::for_each(samples.begin(), samples.end(), [initializeSample](glm::vec3& element)
//        {
//            element = initializeSample;
//        });
//    
//}
//
//bool ShipControler::Start()
//{
//    socket.async_receive_from(
//        boost::asio::buffer(reciveBuffer), remoteEndpoint,
//        [this](const boost::system::error_code& error, // Result of operation.
//            std::size_t bytesTransferred)
//        {
//            if ((!error || error == boost::asio::error::message_size)&& (!done))
//            {
//            auto inputData = std::string(reciveBuffer.begin(), reciveBuffer.begin() + bytesTransferred);
//            glm::mat4 globalPosition = ParseInput(inputData);
//            mutex.lock();
//            this->globalPosition = globalPosition;
//            mutex.unlock();
//            Start();
//            }
//        }
//    );
//    return true;
//}
//
//glm::mat4 ShipControler::ActualizePosition()
//{
//    std::scoped_lock csoped_lock(mutex);
//    return globalPosition;
//}
//
//void ShipControler::Close()
//{
//}
//
//ShipControler::~ShipControler()
//{
//    done = true;
//    reciveThread.join();
//}
//
//glm::mat4 ShipControler::ParseInput(const std::string& inputData)
//{
//    static int i = 0;
//    if(i% 10 ==0)
//        std::cout << inputData <<std::endl;
//    ++i;
//    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    glm::vec3 orientationVector = glm::vec3(0, 0, 0);
//    auto numberList = std::vector<double>();
//    std::vector<std::string> stringList = std::vector<std::string>();
//    boost::split(stringList, inputData, [](char c)
//        {
//            return c == ',';
//    });
//    std::transform(stringList.cbegin(), stringList.cend(),std::back_inserter(numberList), [](const std::string& element)
//        {
//            return std::stod(element);
//        }
//    );
//    if (numberList.size() > 4)
//    {
//        double time = numberList[0];
//        double index = numberList[1];
//        orientationVector = glm::vec3(numberList[2], numberList[3], numberList[4]);
//    }
//    orientationVector = glm::normalize(orientationVector);
//    auto basicDirection = glm::vec3(0., 1., 0.);
//    //glm::vec3 rotationAxis = std::accumulate(samples.cbegin(), samples.cend(), glm::vec3(0, 0, 0)) / float(samples.size());
//    float rcos = glm::dot(basicDirection, orientationVector);
//    auto crossProduct = glm::cross(basicDirection, orientationVector);
//    float rsin = glm::length(crossProduct);
//    float u = crossProduct.x;
//    float v = crossProduct.y;
//    float w = crossProduct.z;
//    float matrixData[] = {rcos + (u * u * (1 - rcos)), w * rsin + v * u * (1 - rcos), -v * rsin + w * u * (1 - rcos),0 ,
//                          -w * rsin + u * v * (1 - rcos) , rcos + v * v * (1 - rcos) , u * rsin + w * v * (1 - rcos) , 0,
//                          v * rsin + u * w * (1 - rcos) , -u * rsin + v * w * (1 - rcos) , rcos + w * w * (1 - rcos) , 0 ,
//                            0, 0, 0, 1};
//    globalPosition = glm::make_mat4(matrixData);
//    //std::cout << orientationVector << std::endl;
//    return globalPosition;
//}
//
//glm::vec3 ShipControler::ComputeMeanValue()
//{
//    auto averageValue = std::accumulate(samples.cbegin(), samples.cend(), glm::vec3(0, 0, 0))/float( samples.size());
//    return averageValue;
//}

ShipControler::ShipControler() noexcept:
currentFrontVector(0.f, 0.f, 1.f),
currentPosition(0.f, 0.f, 1.f),
yaw(0),
pitch(0),
mausePosition_(nullptr),
button_(nullptr)
{
}

ShipControler::ShipControler(std::shared_ptr<glm::vec2> mausePosition, std::shared_ptr<std::optional<char>> button) noexcept :
    currentFrontVector(0.f, 0.f, 1.f),
    currentPosition(0.f, 0.f, 1.f),
    yaw(0),
    pitch(0),
    mausePosition_(mausePosition),
    button_(button)
{
}



void ShipControler::ActualizeShipDirection(glm::mat4& globalPosition)
{

    float xoffset = 0;
    float yoffset = 0;
    auto objectDirection = glm::vec3(0.f, 0.f, 1.f);
    auto rotateAxisPitch = glm::vec3(1.f, 0.f, 0.f);
    auto rotateAxisYaw = glm::vec3(0., 1., 0.);
    float moveSensitive = 0.f;
    if (auto pressedButton = button_.get())
    {
        if (*pressedButton == 'w')
            xoffset =0.01;
        else if (*pressedButton == 's')
            xoffset = -0.01;
        else if (*pressedButton == 'a')
            yoffset = 0.01;
        else if (*pressedButton == 'd')
            yoffset = -0.01;
        else if (*pressedButton == 'r')
            moveSensitive = 0.1f;
        else if (*pressedButton == 'f')
            moveSensitive = -0.1f;
    }
    pitch += yoffset;
    yaw += xoffset;

    if(xoffset != 0.f)
        globalPosition = glm::rotate(globalPosition, -xoffset, rotateAxisPitch);
    if (yoffset != 0.f)
		globalPosition = glm::rotate(globalPosition, -yoffset, rotateAxisYaw);

    currentFrontVector =  globalPosition * glm::vec4(objectDirection, 0.f);
    glm::vec3 movementVector = currentFrontVector * moveSensitive;

    globalPosition[3].x += movementVector.x;
    globalPosition[3].y += movementVector.y;
    globalPosition[3].z += movementVector.z;
    currentPosition = glm::vec3(globalPosition[3].x, globalPosition[3].y, globalPosition[3].z);
    //std::cout << globalPosition << std::endl;

    

    
}

std::optional<glm::vec3> ShipControler::IsShoting() const
{
    if (auto pressedButton = button_.get())
    {
        if (*pressedButton == 'k')
        {
            auto currentFrontVectorNormal = glm::normalize(currentFrontVector);
            return std::make_optional(currentPosition + (currentFrontVectorNormal * 10.f));
        }
    }
    return std::nullopt;
}

void ShipControler::GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition)
{
    ActualizeShipDirection( globalPosition);/*
    ActualizeShipPosition(duration);*/
}

glm::vec3 ShipControler::GetNextDirection() const
{
    return glm::vec3();
}

