#pragma once
#include "IAlertLevelStrategy.h"

class AndromedaStrainStategy : public IAlertLevelStrategy {

public:
    AlertLevel calculateAlertLevel(const std::vector<const Vitals*>& vitalsHistory) const override;
};

