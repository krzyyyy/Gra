#include "pch.h"
#include <numeric>
#include <numbers>
#include "ShipControler.h"
//#include <boost/asio.hpp>
//#include <boost/algorithm/string.hpp>
#include "..\SharedUtilities\StreamOperators.h"
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
xoffset(0.f),
yoffset(0.f),
moveSensitive(0.f),
shoted(false)
{
}

ShipControler::ShipControler(std::shared_ptr<glm::vec2> mausePosition) noexcept :
    currentFrontVector(0.f, 0.f, 1.f),
    currentPosition(0.f, 0.f, 1.f),
    xoffset(0.f),
    yoffset(0.f),
    moveSensitive(0.f),
    shoted(false)
{
}



void ShipControler::ActualizeShipDirection(glm::mat4& globalPosition)
{
    auto objectDirection = glm::vec3(0.f, 0.f, 1.f);
    auto rotateAxisPitch = glm::vec3(1.f, 0.f, 0.f);
    auto rotateAxisYaw = glm::vec3(0.f, 1.f, 0.f);

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
    ResetMoveParams();
}

void ShipControler::ResetMoveParams()
{
    xoffset = 0.f;
    yoffset = 0.f;
    moveSensitive = 0.f;
}

std::optional<glm::vec3> ShipControler::IsShoting() 
{

	if (shoted)
	{
        shoted = false;
		auto currentFrontVectorNormal = glm::normalize(currentFrontVector);
		return std::make_optional(currentPosition + (currentFrontVectorNormal * 10.f));
	}
    return std::nullopt;
}

void ShipControler::SetAction(ShipActions shipRotation)
{
    if (shipRotation == ShipActions::PitchUp)
        xoffset = 0.01f;
    else if (shipRotation == ShipActions::PitchDown)
        xoffset = -0.01f;
    else if (shipRotation == ShipActions::YawUp)
        yoffset = 0.01f;
    else if (shipRotation == ShipActions::YawDown)
        yoffset = -0.01f;
    else if (shipRotation == ShipActions::Foreward)
        moveSensitive = 0.1f;
    else if (shipRotation == ShipActions::Foreward)
        moveSensitive = 0.1f;
    else if (shipRotation == ShipActions::Shot)
        shoted = true;


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

