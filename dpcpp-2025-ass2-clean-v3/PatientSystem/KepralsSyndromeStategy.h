#pragma once  
#include "IAlertLevelStrategy.h"  
#include "Patient.h"

class KepralsSyndromeStategy : public IAlertLevelStrategy { 

public:  
   AlertLevel calculateAlertLevel(const std::vector<const Vitals*>& vitalsHistory) const override;  
   void setPatient(const Patient* patient) override;

protected:  
   const Patient* _patient = nullptr; 
};
