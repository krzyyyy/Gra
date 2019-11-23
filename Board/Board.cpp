// Board.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "CharacterSlot.h"
#include "Button.h"
#include "IField.h"

int main()
{
	cv::namedWindow("main", cv::WINDOW_AUTOSIZE );
	cv::Mat img(800, 1500, CV_8UC3, cv::Scalar(0, 0, 0));
	//CharacterSlot chSlot(cv::Rect(200, 200, 30, 40), cv::Scalar(0.5, 0.8, 0.1));
	std::vector<std::unique_ptr<IField>> object;
	object.push_back(std::make_unique<CharacterSlot>(CharacterSlot(cv::Rect(200, 200, 300, 400), cv::Scalar(120, 20, 20),
		"C:/Resources/Galadriela")));
	object.push_back(std::make_unique<Button>(Button(cv::Rect(400, 400, 400, 300), "przycisk", cv::Scalar(100, 180, 120))));

	std::for_each(object.begin(), object.end(), [img](auto &elem)mutable {
		elem->draw(img);
	});
	cv::imshow("main", img);
	cv::waitKey();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
