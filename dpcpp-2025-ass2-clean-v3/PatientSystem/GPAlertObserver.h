#pragma once

#include "IAlertObserver.h"

class GPAlertObserver : public IAlertObserver {

    public:

        GPAlertObserver(GPNotificationSystemFacade* facade) : _facade(facade) {} // Constructor that takes a GPNotificationSystemFacade pointer

		void update(Patient* patient) override { // Notify the GP about the patient's alert level change
            _facade->sendGPNotificationForPatient(patient);
        }

    protected:
        GPNotificationSystemFacade* _facade;
};