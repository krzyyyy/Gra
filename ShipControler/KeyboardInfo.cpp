#include "pch.h"
#include "KeyboardInfo.h"

KeyboardInfo::KeyboardInfo(std::shared_ptr<MultiThreadFIFO<char>> keyboardState):
	clickedButtons(std::move(keyboardState))
{
	
}

void KeyboardInfo::SetKeyboard(std::shared_ptr<MultiThreadFIFO<char>> keyboardState)
{
	clickedButtons = std::move(keyboardState);
}

void KeyboardInfo::AddCommand(char button, Command command)
{
	commands[button] = command;
}

void KeyboardInfo::ProccessCommands()
{
	
	while (auto optionalValue = clickedButtons->Pop())
	{
		if (commands.find(*optionalValue) == commands.cend())
			continue;
		commands[*optionalValue]();
	}
}
