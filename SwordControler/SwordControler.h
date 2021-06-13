#pragma once
#include "..\Core\ISwordControler.h"
#include "../glm/glm.hpp"

#include <boost/array.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/beast/http.hpp>

class __declspec (dllexport) SwordControler: public ISwordControler
{
public:
	SwordControler();
//
//	// Inherited via ISwordControler
	virtual bool Start() override;
//
	virtual glm::mat4 ActualizePosition() override;
	virtual void Close() override;
	virtual ~SwordControler();
private:

	//IO variables
	boost::asio::io_context io_context;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint remoteEndpoint;
	std::array<char, 200> reciveBuffer;


	//background thread variables
	std::thread reciveThread;
	std::mutex mutex;
	std::atomic<bool> done;
	

	//bufor variable
	glm::mat4 globalPosition;

	std::array<glm::vec3, 6> samples;
	
//	//tool method 
	glm::mat4 ParseInput(const std::string& inputData);

	glm::vec3 ComputeMeanValue();
//	glm::mat4 swordPosition;
//	//void k
//	// Inherited via ISwordControler
	
};

