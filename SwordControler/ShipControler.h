#pragma once
#include "..\Core\IShipControler.h"
#include "../glm/glm.hpp"

//#include <boost/array.hpp>
//#include <boost/asio/ts/buffer.hpp>
//#include <boost/asio/ts/internet.hpp>
//#include <boost/beast/http.hpp>
#include <memory>
#include <optional>

#include <GLFW/glfw3.h>

class __declspec (dllexport) ShipControler : public IShipControler
{
public:
	ShipControler() noexcept;
	ShipControler(std::shared_ptr<glm::vec2> mausePosition, std::shared_ptr<std::optional<char>> button) noexcept;
	// Inherited via IShipControler
	virtual void GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition) override;
	virtual glm::vec3 GetNextDirection() const override;
	virtual void SetCameraParameters(ICamera& camera) const override;

private:
	void ActualizeShipDirection(glm::mat4& globalPosition);
	void ActualizeShipPosition(std::chrono::duration<double> duration);
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float lastX = 400, lastY = 300;
	bool firstMouse = true;
	double yaw = 0;
	double pitch = 0;
	std::shared_ptr<glm::vec2> mausePosition_;
	std::shared_ptr<std::optional<char>> button_;



	// Inherited via IShipControler
	virtual bool IsShoting() const override;

};
//class __declspec (dllexport) ShipControler: public ISwordControler
//{
//public:
//	ShipControler();
////
////	// Inherited via ISwordControler
//	virtual bool Start() override;
////
//	virtual glm::mat4 ActualizePosition() override;
//	virtual void Close() override;
//	virtual ~ShipControler();
//private:
//
//	//IO variables
//	boost::asio::io_context io_context;
//	boost::asio::ip::udp::socket socket;
//	boost::asio::ip::udp::endpoint remoteEndpoint;
//	std::array<char, 200> reciveBuffer;
//
//
//	//background thread variables
//	std::thread reciveThread;
//	std::mutex mutex;
//	std::atomic<bool> done;
//	
//
//	//bufor variable
//	glm::mat4 globalPosition;
//
//	std::array<glm::vec3, 6> samples;
//	
////	//tool method 
//	glm::mat4 ParseInput(const std::string& inputData);
//
//	glm::vec3 ComputeMeanValue();
////	glm::mat4 swordPosition;
////	//void k
////	// Inherited via ISwordControler
//	
//};

