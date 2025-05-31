#pragma once  
#include <vector>  
#include "PatientAlertLevels.h"  
#include "Vitals.h"  

class Patient;  

class IAlertLevelStrategy {  
public:  
virtual ~IAlertLevelStrategy() = default;  
virtual AlertLevel calculateAlertLevel(const std::vector<const Vitals*>& vitalsHistory) const = 0;  
virtual void setPatient(const Patient* patient) {}  
};
