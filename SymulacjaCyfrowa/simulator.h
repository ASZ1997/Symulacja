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
		Ustawia czas po k�trym dana symulacja si� zako�czy
		Ustawia ilo�� nadajnik�w i odbiornik�w b�dzie w danej symulacji
	*/
	Simulator(double stopTime, int amountOfDevices);

	~Simulator();

	/**
		Ustawia czy symulacja ma si� wykonywa� krok po kroku
		Ustawia szczeg�owo�� wy�wietlanych informacji
	*/
	void Initialize(bool stepByStep, Logger::LogVerbosity verb);

	/**
		Wystartowanie symulacji
	*/
	void Start();

private:

	/**
		Wykonaj prac� nadajnik�w
	*/
	void transmittersJobs();

	/*
		Medium trasmisyjne
	*/
	Medium* medium;

	/**
		Lista odbiornik�w 
	*/
	Receiver* * receivers;

	/**
		Lista nadajnik�w
	*/
	Transmitter* * transmitters;
	
	/*
		Czas po kt�rym zatrzymie si� symulacja
	*/
	const double STOP_TIME_;

	/*
		Ilo�� odbiornik�w/nadajnik�w
	*/
	const int AMOUNTS_OF_DEVICES_ ;

	/*
		Aktualny czas
	*/
	double currentTime;

	/*
		Czy zosta�a ustawiona opcja krok po kroku
	*/
	bool STEP_BY_STEP_;

};

#endif /* SIMULATOR_SIMULATOR_H_ */