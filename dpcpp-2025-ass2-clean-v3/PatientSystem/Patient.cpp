#include "Patient.h"

#include "CordycepsBrainInfectionStategy.h"
#include "KepralsSyndromeStategy.h"
#include "AndromedaStrainStategy.h"
#include "IAlertObserver.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Vitals.h"


using namespace std;

const std::string Diagnosis::CORDYCEPS_BRAIN_INFECTION = "Cordyceps Brain Infection";
const std::string Diagnosis::KEPRALS_SYNDROME = "Kepral's Syndrome";
const std::string Diagnosis::ANDROMEDA_STRAIN= "Andromeda Strain";


Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	Person(firstName, lastName, birthday),
	_alertLevel(AlertLevel::Green)
{
}

int Patient::age() const
{	
	// an inaccurate age estimate but fine for assignment purposes
	return 2022 - (1900 + _birthday.tm_year);
}

std::string Patient::uid() const
{
	std::stringstream ss;
	ss << (char)std::tolower(_lastName.at(0)) 
	   << (char)std::tolower(_firstName.at(0))
	   << std::setfill('0') << std::setw(2) << (_birthday.tm_mon + 1) 
	   << _birthday.tm_year;
	return ss.str();
}

std::string Patient::humanReadableID() const
{
	return "" + _lastName + ", " + _firstName + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	os << p.uid() << "|" << p._lastName << "," << p._firstName << "|" << std::put_time(&p._birthday, "%d-%m-%Y") << "|" << p.primaryDiagnosis();
	
	os << "|";
	for (int i = 0; i < p.vitals().size(); ++i) {
		auto v = p.vitals()[i];
		os << *v;
		if (i != p.vitals().size() - 1) {
			os << ";";
		}
	}
	return os;
}

void Patient::addDiagnosis(const std::string& diagnosis)
{
	_diagnosis.push_back(diagnosis);

	if (_diagnosis.size() == 1) { // Only set the alert strategy for the primary diagnosis

		if (diagnosis == Diagnosis::CORDYCEPS_BRAIN_INFECTION) {
			_alertStrategy = std::make_unique<CordycepsBrainInfectionStategy>();
		}
		else if (diagnosis == Diagnosis::KEPRALS_SYNDROME) {
			auto strategy = std::make_unique<KepralsSyndromeStategy>();
			strategy->setPatient(this);
			_alertStrategy = std::move(strategy);
		}
		else if (diagnosis == Diagnosis::ANDROMEDA_STRAIN) {
			_alertStrategy = std::make_unique<AndromedaStrainStategy>();
		}
		else {
			_alertStrategy.reset();
		}
	}
}

const std::string& Patient::primaryDiagnosis() const
{
	return _diagnosis.front();
}

void Patient::addVitals(const Vitals* v)
{
	_vitals.push_back(v);
	// TODO: calculate alert levels
	if (_alertStrategy) {
		AlertLevel newLevel = _alertStrategy->calculateAlertLevel(_vitals);
		setAlertLevel(newLevel);
	}
}

const std::vector<const Vitals*> Patient::vitals() const
{
	return _vitals;
}

void Patient::setAlertLevel(AlertLevel level)
{
	_alertLevel = level;

	if (level > AlertLevel::Green) {
		cout << "Patient: " << humanReadableID() << " has an alert level: ";
		switch (_alertLevel) {
		case AlertLevel::Yellow:
			cout << "Yellow";
			break;
		case AlertLevel::Orange:
			cout << "Orange";
			break;
		case AlertLevel::Red:
			cout << "Red";
			break;
		}
		cout << endl;

		if (level == AlertLevel::Red) {
			notifyObservers();  //Only notify observers when alert level becomes Red
		}
	}
}

void Patient::notifyObservers() { //Notify all observers (receivers like the GPs and Hospital) of the alert level change

	for (const auto& observer : _observers) {
		observer->update(this);
	}
}

void Patient::addAlertObserver(std::shared_ptr<IAlertObserver> observer) { //Add an observer to the list of observers
	_observers.push_back(observer);
}
