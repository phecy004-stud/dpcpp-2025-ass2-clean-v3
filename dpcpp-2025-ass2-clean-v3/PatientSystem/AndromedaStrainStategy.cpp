#include "AndromedaStrainStategy.h"
#include "Vitals.h"

AlertLevel AndromedaStrainStategy::calculateAlertLevel(const std::vector<const Vitals*>& vitalsHistory) const {

    const Vitals* latest = vitalsHistory.back();

    if (latest->BP() > 140) {
        return AlertLevel::Red;
    }
    else if (latest->BP() > 130) {
        return AlertLevel::Orange;
    }
    else if (latest->BP() > 110) {
        return AlertLevel::Yellow;
    }
    return AlertLevel::Green;
}
