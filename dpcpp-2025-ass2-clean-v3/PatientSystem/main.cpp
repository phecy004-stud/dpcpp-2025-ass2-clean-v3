// PatientSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <string>

#include "PatientManagementSystem.h"
#include "PatientFileAdapter.h"
#include "PatientDatabaseLoader.h"
#include "CompositePatientLoader.h"

int main()
{
	/*auto loader_type = std::make_unique<PatientFileAdapter>();
	auto pms = std::make_unique<PatientManagementSystem>(std::make_unique<PatientFileLoader>());*/

	auto composite_loader = std::make_unique<CompositePatientLoader>();
	composite_loader->addLoader(std::make_unique<PatientDatabaseLoader>());
	composite_loader->addLoader(std::make_unique<PatientFileAdapter>());
	auto pms = std::make_unique<PatientManagementSystem>(std::move(composite_loader));

	pms->init();
	pms->run();

	return 0;
}
