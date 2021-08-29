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

enum class ShipActions
{
	PitchUp = 0,
	PitchDown,
	YawUp,
	YawDown,
	Foreward,
	Shot
};
class __declspec (dllexport) ShipControler : public IShipControler
{
public:
	ShipControler() noexcept;
	ShipControler(std::shared_ptr<glm::vec2> mausePosition) noexcept;
	// Inherited via IShipControler
	virtual void GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition) override;
	virtual glm::vec3 GetNextDirection() const override;
	// Inherited via IShipControler
	virtual std::optional<glm::vec3> IsShoting() override;
	void SetAction(ShipActions shipRotation);


private:
	void ActualizeShipDirection(glm::mat4& globalPosition);
	void ResetMoveParams();
	glm::vec3 currentFrontVector;
	glm::vec3 currentPosition;
	float xoffset;
	float yoffset;
	float moveSensitive;
	bool shoted;

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

