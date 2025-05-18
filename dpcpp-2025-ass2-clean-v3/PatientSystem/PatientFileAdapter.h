#pragma once

#include "AbstractPatientDatabaseLoader.h"
#include "PatientFileLoader.h"

class PatientFileAdapter : public AbstractPatientDatabaseLoader
{
public:
    void initialiseConnection() override {}
    void closeConnection() override {}

    void loadPatients(std::vector<Patient*>& patients) override {
        PatientFileLoader loader;
        auto loaded = loader.loadPatientFile("patients.txt");
        patients.insert(patients.end(), loaded.begin(), loaded.end());
    }
};
