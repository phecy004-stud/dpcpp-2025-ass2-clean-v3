#pragma once

#include <vector>
#include <memory>
#include "AbstractPatientDatabaseLoader.h"

class CompositePatientLoader : public AbstractPatientDatabaseLoader 
{

private: 
    std::vector<std::unique_ptr<AbstractPatientDatabaseLoader>> _loaders;

public:

    void initialiseConnection() override {}
    void closeConnection() override {}

    void loadPatients(std::vector<Patient*>& patients) override {
		for (auto& loader : _loaders) { // For each loader in the vector
			loader->loadPatients(patients); // Load patients using the loader
        }
    }

    void addLoader(std::unique_ptr<AbstractPatientDatabaseLoader> loader) {
		_loaders.push_back(std::move(loader)); // Add the loader to the vector
    }
};
