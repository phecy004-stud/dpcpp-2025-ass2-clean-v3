#include "CordycepsBrainInfectionStategy.h"
#include "Vitals.h"

AlertLevel CordycepsBrainInfectionStategy::calculateAlertLevel(const std::vector<const Vitals*>& vitalsHistory) const {

    const Vitals* latest = vitalsHistory.back();
    int rr = latest->RR();

    if (rr > 40) return AlertLevel::Red;
    if (rr > 30) return AlertLevel::Orange;
    if (rr > 20) return AlertLevel::Yellow;

    return AlertLevel::Green;
}
