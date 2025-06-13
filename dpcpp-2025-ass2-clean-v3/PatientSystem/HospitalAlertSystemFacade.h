#pragma once

#include "Patient.h"
#include "IAlertObserver.h"

class HospitalAlertSystemFacade
{
public:
	HospitalAlertSystemFacade();
	virtual ~HospitalAlertSystemFacade();

	void sendAlertForPatient(Patient* p);

};

