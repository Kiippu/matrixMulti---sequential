#pragma once
#include "GlobalTimer.h"
#include <string>
#include <chrono>
#include <map>
#include <vector>
#include <iostream>

/*

Class:			GlobalTimer
Description:	timer clkass for measuring matric speed and providing a metric for threaded multiplication to come.

*/

/// typedef to reduce type pollution in code
using TIME_REGISTER_PAIR = std::pair< std::string, std::chrono::time_point<std::chrono::steady_clock> >;
using TIME_REGISTER = std::map < std::string, std::chrono::time_point<std::chrono::steady_clock>>;
using TIME_VECTOR_PAIR = std::pair<std::string, long long>;
using TIME_VECTOR = std::vector<TIME_VECTOR_PAIR>;

/// enum to register how ids are timed
enum class TIME_MEASURMENT {
	Nano,
	Milli,
	Second
};

class GlobalTimer
{
public:
	GlobalTimer() {};
	~GlobalTimer() {};

	/// add timer to register map
	void addStartTime(std::string id, TIME_MEASURMENT timeFrame)
	{
		// place timer id i  to correct measurment catagory
		auto startTimer = std::chrono::high_resolution_clock::now();
		m_beginTimerList.insert(std::make_pair(id, startTimer));
		if (timeFrame == TIME_MEASURMENT::Nano)
			m_finalTimerSheetNs.push_back(TIME_VECTOR_PAIR(id, 0));
		if (timeFrame == TIME_MEASURMENT::Milli)
			m_finalTimerSheetMs.push_back(TIME_VECTOR_PAIR(id, 0));
		if (timeFrame == TIME_MEASURMENT::Second)
			m_finalTimerSheetSec.push_back(TIME_VECTOR_PAIR(id, 0));
	};
	/// register a time has finished
	void addFinishTime(std::string id)
	{
		auto finishTimer = std::chrono::high_resolution_clock::now();
		m_finishTimerList.insert(std::make_pair(id, finishTimer));
	};

	// iterate through maps and get all finished timers
	void printFinalTimeSheet()
	{
		for (auto obj : m_finalTimerSheetSec)
		{
			auto differenceInTime = m_finishTimerList[obj.first] - m_beginTimerList[obj.first];
			obj.second = std::chrono::duration_cast<std::chrono::seconds>(differenceInTime).count();
			std::cout << obj.first << ": " << std::to_string(obj.second) << "sec to execute" << std::endl;
		}
		for (auto obj : m_finalTimerSheetMs)
		{
			auto differenceInTime = m_finishTimerList[obj.first] - m_beginTimerList[obj.first];
			obj.second = std::chrono::duration_cast<std::chrono::milliseconds>(differenceInTime).count();
			std::cout << obj.first << ": " << std::to_string(obj.second) << "ms to execute" << std::endl;
		}
		for (auto obj : m_finalTimerSheetNs)
		{
			auto differenceInTime = m_finishTimerList[obj.first] - m_beginTimerList[obj.first];
			obj.second = std::chrono::duration_cast<std::chrono::nanoseconds>(differenceInTime).count();
			std::cout << obj.first << ": " << std::to_string(obj.second) << "ns to execute" << std::endl;
		}
	};

private:

	TIME_REGISTER m_beginTimerList;
	TIME_REGISTER m_finishTimerList;
	TIME_VECTOR m_finalTimerSheetSec;
	TIME_VECTOR m_finalTimerSheetMs;
	TIME_VECTOR m_finalTimerSheetNs;
};