#pragma once
class PatientManagementSystem;

class IAlertObserver {

    public:
        virtual void update(Patient* patient) = 0;
        virtual ~IAlertObserver() = default;
};
