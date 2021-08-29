#pragma once
#include <iostream>
#include <optional>
#include <unordered_map>
#include <functional>

#include "..\SharedUtilities\MultiThreadFIFO.h"

class __declspec(dllexport) KeyboardInfo
{
public:
	//KeyboardInfo
	using Command = std::function<void()>;
	KeyboardInfo() noexcept = default;
	KeyboardInfo(std::shared_ptr< MultiThreadFIFO<char>> keyboardState);
	KeyboardInfo(const KeyboardInfo&) = delete;
	KeyboardInfo& operator=(const KeyboardInfo&) = delete;
	void SetKeyboard(std::shared_ptr< MultiThreadFIFO<char>> keyboardState);
	void AddCommand(char button, Command command);
	void ProccessCommands();


private:
	std::unordered_map<char, Command> commands;
	std::shared_ptr<MultiThreadFIFO<char>> clickedButtons;
};

