// PatientSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <string>

#include "PatientManagementSystem.h"
#include "PatientFileAdapter.h"

int main()
{
	auto loader_type = std::make_unique<PatientFileAdapter>();
	auto pms = std::make_unique<PatientManagementSystem>(std::move(loader_type));

	pms->init();
	pms->run();

	return 0;
}
