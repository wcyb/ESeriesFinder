/*
 Name:		ESeriesFinder.cpp
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#include "pch.h"
#include "ESeriesFinder.h"
#include "eSeries.h"

int main()
{
	float val = 0;

	std::cout.setf(std::ios::fixed);
	std::cout << "E series finder v1.0" << std::endl;
	std::cout << "(c) 2019 Wojciech Cybowski. All rights reserved." << std::endl << std::endl;
	std::cout << "Enter 0 to exit." << std::endl << std::endl;
	while (true)
	{
		std::cout << "Enter value: ";
		std::cin >> val;
		if (val <= 0) return 0;//exit
		findClosestValues(val);
		clearInput();
	}
	return 0;
}

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void findClosestValues(float value)
{
	float divider = 1.0f;
	double closestValue = std::numeric_limits<double>::max();
	double lastClosestValue = std::numeric_limits<double>::max();
	short closestValuePosition = 0;
	short lastClosestValuePosition = 0;

	short valueSeries = 6; //starting val series
	float seriesTolerance = 20.0f;
	short const* currentSeriesArray = nullptr;

	if (value < 10.0f) divider = 0.01f;  //divide by 100 to change scale of values, to change ranges only divider needs to change
	else if (value < 100.0f) divider = 0.1f;
	else if (value > 10000.0f) divider = 100.0f;
	else if (value > 1000.0f) divider = 10.0f;

	while (valueSeries <= 192)
	{
		switch (valueSeries)
		{
		case 6:
			currentSeriesArray = e6;
			break;
		case 12:
			currentSeriesArray = e12;
			break;
		case 24:
			currentSeriesArray = e24;
			break;
		case 48:
			seriesTolerance = 2.0f;
			currentSeriesArray = e48;
			break;
		case 96:
			currentSeriesArray = e96;
			break;
		case 192:
			currentSeriesArray = e192;
			break;
		}

		for (int i = 0; i < valueSeries; i++)
		{
			double tmp = std::abs((static_cast<double>(currentSeriesArray[i]) * divider) - value); //get difference between value from array and calculated

			if (tmp < closestValue)
			{
				lastClosestValue = closestValue; //save latest closest value
				closestValue = tmp; //save new closest value
				lastClosestValuePosition = closestValuePosition; //save position of latest closest value in array
				closestValuePosition = i; //save position of new closest value in array
			}
		}

		std::cout << "E" << valueSeries << "(+-" << std::setprecision(1) << seriesTolerance << "%) first closest value : " << std::setprecision(2)
			<< (currentSeriesArray[closestValuePosition] * divider) << std::endl << "(" << std::setprecision(1)
			<< ((closestValue / value) * 100) << "% difference from calculated value)" << std::endl;
		if (((lastClosestValue / value) * 100) < 50)//show second value only if difference is less than 50%
		{
			std::cout << "E" << valueSeries << "(+-" << std::setprecision(1) << seriesTolerance << "%) second closest value: " << std::setprecision(2)
				<< (currentSeriesArray[lastClosestValuePosition] * divider) << std::endl << "(" << std::setprecision(1)
				<< ((lastClosestValue / value) * 100) << "% difference from calculated value)" << std::endl << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}

		valueSeries *= 2;
		seriesTolerance /= 2;
		closestValue = std::numeric_limits<double>::max();
		lastClosestValue = std::numeric_limits<double>::max();
		closestValuePosition = 0;
		lastClosestValuePosition = 0;//reset vars
	}
}
