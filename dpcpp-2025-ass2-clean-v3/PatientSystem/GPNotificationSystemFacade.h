#pragma once

#include "Patient.h"
#include "IAlertObserver.h"


class GPNotificationSystemFacade {
public:
	GPNotificationSystemFacade();
	virtual ~GPNotificationSystemFacade();

	void sendGPNotificationForPatient(Patient* p);
};

