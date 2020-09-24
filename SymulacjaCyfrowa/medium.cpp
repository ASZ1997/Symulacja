#include "medium.h"
#include "package.h"
#include "logger.h"
#include "transmitter.h"
#include "receiver.h"
#include <iostream>
#include <sstream>
#include <queue>



using namespace std;


Medium::Medium()
{
	this->FSlotUsed = false;
}

Medium::~Medium()
{
	
}

bool Medium::addPackage(Package* package, int currentTime)
{
	if (!this->FSlotUsed)
	{
		package->timeGotAccessToTheMedium = currentTime;
		this->packagesInMedum.push(package);
		this->FSlotUsed = true;

		stringstream ss; ss <<
			currentTime << "ms" << "\n" <<
			"---" << "\n" <<
			" Medium " << "\n" <<
			" Przyjeto pakiet w szczeline:" << "\n" <<
			"	Pakiey:" << "\n" <<
			"		- id:" << package->ID_ << "\n" <<
			"		- Nadajnik id:" << package->FROM_ID_ << "\n" <<
			"		- Odbiornik id:" << package->TO_ID_ << "\n" <<
			"		- Stworzony: " << package->createTime << " ms " << "\n" <<
			"		- Szacowny czas trasmisji do odbiornika: " << package->ctp << " ms " << "\n" <<
			"		- Szacowny czas na ACK: " << package->ctp + 1 << " ms " << "\n" <<
			"\n";
		std::string v = ss.str();
		Logger::GetInstance()->Print(v, Logger::L3);

		return true;
	}
	else 
	{
		return false;
	}
}

void Medium::working(int currentTime, Transmitter** transmitters, Receiver** receivers)
{
	for (int i = 0; i < this->packagesInMedum.size(); i++)
	{
		if ((this->packagesInMedum.front()->timeGotAccessToTheMedium + this->packagesInMedum.front()->ctp) == currentTime)
		{
			Package* pack = this->packagesInMedum.front();
			int fromTo = pack->TO_ID_;
			if (receivers[fromTo]->ConnectToReceiver())
			{
				//uda sie wyslac ack
				transmitters[fromTo]->flagAck = true;

				stringstream ss; ss <<
					currentTime << "ms" << "\n" <<
					"---" << "\n" <<
					" Odbiornik:" << "\n" <<
					"	- id: "<< fromTo << "\n" <<
					" Pomyslnie odebral i obsluzyl pakiet" << "\n" <<
					" Wysyla ACK" << "\n" <<
					"	Pakiet:" << "\n" <<
					"		- id:" << pack->ID_ << "\n" <<
					"		- Od nadajnika o id:" << pack->FROM_ID_ << "\n" <<
					"\n";
				std::string v = ss.str();
				Logger::GetInstance()->Print(v, Logger::L3);

			}
			else
			{
				//nie uda sie wyslac ack
				stringstream ss; ss <<
					currentTime << "ms" << "\n" <<
					"---" << "\n" <<
					" Odbiornik:" << "\n" <<
					"	- id: " << fromTo << "\n" <<
					" Nieudana obsluga pakietu" << "\n" <<
					" Nie wysle ACK" << "\n" <<
					"	Pakiet:" << "\n" <<
					"		- id:" << pack->ID_ << "\n" <<
					"		- Od nadajnika o id:" << pack->FROM_ID_ << "\n" <<
					"\n";
				std::string v = ss.str();
				Logger::GetInstance()->Print(v, Logger::L3, Logger::LOG_WARNING);
			}

			this->packagesInMedum.pop();
		}
		else
		{
			Package* pack = this->packagesInMedum.front();
			this->packagesInMedum.pop();
			this->packagesInMedum.push(pack);
		}
	}
}
