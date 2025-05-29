#include "KepralsSyndromeStategy.h"
#include "Vitals.h"
#include "Patient.h"


void KepralsSyndromeStategy::setPatient(const Patient* patient) {
    _patient = patient;
}

AlertLevel KepralsSyndromeStategy::calculateAlertLevel(const std::vector<const Vitals*>& vitalsHistory) const {

    const Vitals* latest = vitalsHistory.back();

    if (_patient == nullptr) return AlertLevel::Green;

    int age = _patient->age();
    int hr = latest->HR();

    if ((age < 12 && hr > 120) || (age >= 12 && hr > 100)) {
        return AlertLevel::Red;
    }

    return AlertLevel::Green;
}
