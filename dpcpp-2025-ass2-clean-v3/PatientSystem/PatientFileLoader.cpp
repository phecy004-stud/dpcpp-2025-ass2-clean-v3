#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Patient.h"
#include "Vitals.h"

using namespace std;


std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& file)
{
	vector<Patient*> patients{};
    std::ifstream fileName(file);

    if (fileName.is_open()) {

        std::string line;

		while (getline(fileName, line)) { // Read each line in the file

			std::istringstream lineStream(line); // Create a stream from the line
			std::string id, name, dobStr, diagnosis, vitalsStr;

			// Each line read in parts
			if (!getline(lineStream, id, '|') || // Read the ID in that line
				!getline(lineStream, name, '|') || // Read the name in that line
				!getline(lineStream, dobStr, '|') || // Read the date of birth in that line
				!getline(lineStream, diagnosis, '|')) // Read the diagnosis in that line
                continue; // Skip line IF any part except vitals is missing

			getline(lineStream, vitalsStr); // Read the vitals in that line (Some line, vitals can be empty)

			// Split the name into first and last names
			auto commaPos = name.find(','); // Find the comma in the name
			std::string lastName = name.substr(0, commaPos); // Extract the last name
			std::string firstName = name.substr(commaPos + 1); // Extract the first name
	
			// Parse the date of birth
			std::tm birthday{}; // Create a tm structure to hold the date string
			std::istringstream(dobStr) >> std::get_time(&birthday, "%d-%m-%Y"); // Parse the date string into the tm structure

			// Create a new Patient object and add the diagnosis
			Patient* patient = new Patient(firstName, lastName, birthday); // Create a new Patient object
			patient->addDiagnosis(diagnosis); // Add the diagnosis to the Patient object

			std::istringstream vitalsStream(vitalsStr); // Create a stream from the vitals string
			std::string singleReading; // Variable to hold each reading

			while (getline(vitalsStream, singleReading, ';')) { // Read each reading in the vitals string

				std::istringstream readingStream(singleReading); // Create a stream from the single reading
				float temperature;
				int bloodPressure, heartRate, respiratoryRate; // Variables to hold the vitals
				char comma1, comma2, comma3; // Variable to hold the comma

				// Read all the four values of the vitals from the stream separated by commas
				if (readingStream >> temperature >> comma1 >> bloodPressure >> comma2 >> heartRate >> comma3 >> respiratoryRate && comma1 == ',' && comma2 == ',' && comma3 == ',')
				{
					patient->addVitals(new Vitals(temperature, bloodPressure, heartRate, respiratoryRate)); // Add the vitals to the Patient object
				}
			}
			patients.push_back(patient); // Add the Patient object to the vector of patients
		}
		fileName.close();
	}
    return patients;
}
