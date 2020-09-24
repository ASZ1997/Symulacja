#include <cstdlib>
#include <ctime>
#include "simulator.h"

#include <iostream>
#include <sstream>
#include "logger.h"
#include <iso646.h>
#include "receiver.h"
#include "transmitter.h"
#include "medium.h"
#include <cstdlib>
#include <ctime>


/*
	Ustawia symulator 
*/
Simulator::Simulator(double stopTime, int amountOfDevices) : 
	STOP_TIME_(stopTime), AMOUNTS_OF_DEVICES_(amountOfDevices)
{
	srand(time(NULL));
	currentTime = 1;
	medium = new Medium();
	receivers = new Receiver*[AMOUNTS_OF_DEVICES_];
	transmitters = new Transmitter*[AMOUNTS_OF_DEVICES_];

	for (int i = 0; i < AMOUNTS_OF_DEVICES_; i++) 
	{
		receivers[i] = new Receiver(i);
		transmitters[i] = new Transmitter(i);
	}
}


Simulator::~Simulator()
{
	delete medium;
	delete receivers;
	delete transmitters;
	
}

/*
	Inicjalizuje ustawienia sumulatora
	step_by_step -> ustawia tryb pracy symulatora
	verb -> ustawia poziom wyœwietlanych szczegó³ów 
*/
void Simulator::Initialize(bool step_by_step, Logger::LogVerbosity verb)
{
	STEP_BY_STEP_ = step_by_step;
	Logger::GetInstance()->SetLogVerbosity(static_cast<Logger::LogVerbosity>(verb));
}

void Simulator::Start()
{
	// Nie wiem jak maj¹ byæ dodawane pakiety wiêdz dodam tu kilka na sztywno
	for (int i = 0; i < AMOUNTS_OF_DEVICES_; i++)
	{
		transmitters[i]->addPackage(this->currentTime, i);
	}
	
	this->currentTime++;

	// Normalny ci¹g synchronizacji 
	while (currentTime <= STOP_TIME_) {

		Logger::GetInstance()->Print(("\n----------------------------------------------------------------------\n"), Logger::L3);
		Logger::GetInstance()->Print(("CLOCK = " + std::to_string(this->currentTime) + "\n"), Logger::L3);
		
		// praca nadajników
		this->transmittersJobs();

		// praca medium + odbiorników 
		this->medium->working(currentTime, transmitters, receivers);


		Logger::GetInstance()->Print(("\n----------------------------------------------------------------------\n"), Logger::L3);

		if (this->STEP_BY_STEP_)
		{
			std::cout << "Press ENTER to continue...";
			std::string l;
			getline(std::cin, l);
		}

		this->medium->FSlotUsed = false;
		this->currentTime++;
	}
}

void Simulator::transmittersJobs()
{
	for (int i = 0; i < this->AMOUNTS_OF_DEVICES_; i++)
	{
		transmitters[i]->working(this->currentTime, this->medium);
	}
}


