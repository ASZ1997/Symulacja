#ifndef SIMULATOR_SIMULATOR_H_
#define SIMULATOR_SIMULATOR_H_
#include <vector>
#include "logger.h"

using namespace std;

struct Medium;
class Transmitter;
class Receiver;

/**
	Symulator
*/
class Simulator
{
public:
	/**
		Ustawia czas po kótrym dana symulacja siê zakoñczy
		Ustawia iloœæ nadajników i odbiorników bêdzie w danej symulacji
	*/
	Simulator(double stopTime, int amountOfDevices);

	~Simulator();

	/**
		Ustawia czy symulacja ma siê wykonywaæ krok po kroku
		Ustawia szczegó³owoœæ wyœwietlanych informacji
	*/
	void Initialize(bool stepByStep, Logger::LogVerbosity verb);

	/**
		Wystartowanie symulacji
	*/
	void Start();

private:

	/**
		Wykonaj pracê nadajników
	*/
	void transmittersJobs();

	/*
		Medium trasmisyjne
	*/
	Medium* medium;

	/**
		Lista odbiorników 
	*/
	Receiver* * receivers;

	/**
		Lista nadajników
	*/
	Transmitter* * transmitters;
	
	/*
		Czas po którym zatrzymie siê symulacja
	*/
	const double STOP_TIME_;

	/*
		Iloœæ odbiorników/nadajników
	*/
	const int AMOUNTS_OF_DEVICES_ ;

	/*
		Aktualny czas
	*/
	double currentTime;

	/*
		Czy zosta³a ustawiona opcja krok po kroku
	*/
	bool STEP_BY_STEP_;

};

#endif /* SIMULATOR_SIMULATOR_H_ */