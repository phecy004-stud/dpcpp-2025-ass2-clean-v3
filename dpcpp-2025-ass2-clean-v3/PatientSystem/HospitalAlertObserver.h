#pragma once

#include "IAlertObserver.h"

class HospitalAlertObserver : public IAlertObserver {
    public:
        
		HospitalAlertObserver(HospitalAlertSystemFacade* facade) : _facade(facade) {} // Constructor that takes a HospitalAlertSystemFacade pointer

        void update(Patient* patient) override {
            _facade->sendAlertForPatient(patient);
        }

    protected:
        HospitalAlertSystemFacade* _facade;
};
