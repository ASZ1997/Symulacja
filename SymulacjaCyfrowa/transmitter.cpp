#include "transmitter.h"
#include "package.h"
#include "medium.h"
#include "logger.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

Transmitter::Transmitter(int id) : ID_(id), R_MAX_(2)
{
	status = WAIT_FOR_JOB;
}

Transmitter::~Transmitter()
{
	
}

void Transmitter::addPackage(int currentTime, int packageId) 
{
	packagesBuffer.push(new Package(packageId, this->ID_, currentTime));
	
	stringstream ss; ss <<
		currentTime << "ms" << "\n" <<
		"---" << "\n" <<
		" Nadajnik " << "\n" <<
		"	- id:  " << this->ID_ << "\n" <<
		" Dodal pakiet:" << "\n" <<
		"	- id: " << packageId << "\n";
	std::string v = ss.str();
	Logger::GetInstance()->Print(v, Logger::L3);
}

void Transmitter::working(int currentTime, Medium* medium) 
{
	switch (this->status)
	{
	case WAIT_FOR_ACK:
		this->HandleWaitForAck(currentTime, medium);
		break;

	case RETRASMISSION:
		this->HandleRetrasmission(currentTime, medium);
		break;

	case WAIT_FOR_JOB:
		this->HandleWaitForJob(currentTime, medium);
		break;
	default:
		exit(-1);
		break;
	}
}

void Transmitter::HandleWaitForJob(int currentTime, Medium* medium)
{
	if (packagesBuffer.empty())
	{
		stringstream ss; ss <<
			currentTime << "ms" << "\n" <<
			"---" << "\n" <<
			" Nadajnik " << "\n" <<
			"	- id:  " << this->ID_ << "\n" <<
			" Pusty buffor" << "\n";
		std::string v = ss.str();
		Logger::GetInstance()->Print(v, Logger::L3);
	}
	else 
	{
		if (medium->addPackage(this->packagesBuffer.front(), currentTime))
		{
			this->status = WAIT_FOR_ACK;
			this->flagAck = false;
			this->timeWaitForAck = this->packagesBuffer.front()->ctp + 1 + currentTime;

			stringstream ss; ss <<
				currentTime << "ms" << "\n" <<
				"---" << "\n" <<
				" Nadajnik " << "\n" <<
				"	- id:  " << this->ID_ << "\n" <<
				" Wyslal pakiet do buffora" << "\n" <<
				" Pakiet:" << "\n" <<
				"	- id: " << this->packagesBuffer.front()->ID_ << "\n";
			std::string v = ss.str();
			Logger::GetInstance()->Print(v, Logger::L3);
		}
		else
		{
			this->status = RETRASMISSION;
			this->currentlyRetransmissionStep = 0;
			this->timeWaitForRetrasmissions = this->getRetrasmissionsTime(currentTime);

			stringstream ss; ss <<
				currentTime << "ms" << "\n" <<
				"---" << "\n" <<
				" Nadajnik " << "\n" <<
				"	- id:  " << this->ID_ << "\n" <<
				" Kolizja - retrasmituj" << "\n" <<
				" Pakiet:" << "\n" <<
				"	- id: " << this->packagesBuffer.front()->ID_ << "\n";
			std::string v = ss.str();
			Logger::GetInstance()->Print(v, Logger::L3, Logger::LOG_WARNING);
		}
	}
}

void Transmitter::HandleRetrasmission(int currentTime, Medium* medium)
{
	if (this->timeWaitForRetrasmissions == currentTime)
	{
		switch (this->currentlyRetransmissionStep)
		{
		case 0:
			if (medium->addPackage(this->packagesBuffer.front(), currentTime))
			{
				this->status = WAIT_FOR_ACK;
				this->flagAck = false;
				this->timeWaitForAck = this->packagesBuffer.front()->ctp + 1 + currentTime;

				stringstream ss; ss <<
					currentTime << "ms" << "\n" <<
					"---" << "\n" <<
					" Nadajnik " << "\n" <<
					"	- id:  " << this->ID_ << "\n" <<
					" Udana retrasmisja" << "\n" <<
					" Pakiet:" << "\n" <<
					"	- id: " << this->packagesBuffer.front()->ID_ << "\n";
				std::string v = ss.str();
				Logger::GetInstance()->Print(v, Logger::L3);
			}
			else
			{
				this->status = RETRASMISSION;
				this->currentlyRetransmissionStep = 1;
				this->timeWaitForRetrasmissions = this->getRetrasmissionsTime(currentTime);

				stringstream ss; ss <<
					currentTime << "ms" << "\n" <<
					"---" << "\n" <<
					" Nadajnik " << "\n" <<
					"	- id:  " << this->ID_ << "\n" <<
					" Nieudana retrasmisja - ponawianie" << "\n" <<
					" Pakiet:" << "\n" <<
					"	- id: " << this->packagesBuffer.front()->ID_ << "\n";
				std::string v = ss.str();
				Logger::GetInstance()->Print(v, Logger::L3, Logger::LOG_WARNING);
			}
			break;
		case 1:
			if (medium->addPackage(this->packagesBuffer.front(), currentTime))
			{
				this->status = WAIT_FOR_ACK;
				this->flagAck = false;
				this->timeWaitForAck = this->packagesBuffer.front()->ctp + 1 + currentTime;

				stringstream ss; ss <<
					currentTime << "ms" << "\n" <<
					"---" << "\n" <<
					" Nadajnik " << "\n" <<
					"	- id:  " << this->ID_ << "\n" <<
					" Udana retrasmisja" << "\n" <<
					" Pakiet:" << "\n" <<
					"	- id: " << this->packagesBuffer.front()->ID_ << "\n";
				std::string v = ss.str();
				Logger::GetInstance()->Print(v, Logger::L3);
			}
			else
			{
				this->status = WAIT_FOR_JOB;
				this->currentlyRetransmissionStep = 0;
				this->timeWaitForRetrasmissions = 0;

				stringstream ss; ss <<
					currentTime << "ms" << "\n" <<
					"---" << "\n" <<
					" Nadajnik " << "\n" <<
					"	- id:  " << this->ID_ <<"\n" <<
					" Nieudana retrasmisja - porzucenie pakietu" << "\n" <<
					" Pakiet Podsumowanie:" << "\n" <<
					"	- id: " << this->packagesBuffer.front()->ID_ << "\n" <<
					"	- Nadajnik id: " << this->packagesBuffer.front()->FROM_ID_<< "\n" <<
					"	- Odbiornik id: " << this->packagesBuffer.front()->TO_ID_<< "\n" <<
					"	- Stworzony: " << this->packagesBuffer.front()->createTime << " ms " << "\n" <<
					"	- Odrzucony: " << currentTime << " ms "<< "\n" <<				
					"\n";
				std::string v = ss.str();
				Logger::GetInstance()->Print(v, Logger::L3, Logger::LOG_WARNING);

				this->packagesBuffer.pop();
			}
			break;
		default:

			stringstream ss; ss <<
				currentTime << "ms" << "\n" <<
				"---" << "\n" <<
				"!!! B³ad symulatora !!!: " << "\n";
			std::string v = ss.str();
			Logger::GetInstance()->Print(v, Logger::L3, Logger::LOG_ERROR);

			std::cout << "Press ENTER to continue...";
			std::string l; getline(std::cin, l);

			exit(-1);
			break;
		}
	}
	else
	{
		stringstream ss; ss <<
			currentTime << "ms" << "\n" <<
			"---" << "\n" <<
			" Nadajnik " << "\n" <<
			"	- id:  " << this->ID_ << "\n" <<
			" Oczekuje na retrasmisje" << "\n";
		std::string v = ss.str();
		Logger::GetInstance()->Print(v, Logger::L3);
	}
}

void Transmitter::HandleWaitForAck(int currentTime, Medium* medium)
{
	if (this->flagAck && this->timeWaitForAck == currentTime)
	{
		this->flagAck = false;
		this->timeWaitForAck = 0;

		stringstream ss; ss <<
			currentTime << "ms" << "\n" <<
			"---" << "\n" <<
			" Nadajnik " << "\n" <<
			"	- id:  " << this->ID_ << "\n" <<
			" Otrzymano ACK" << "\n" <<
			" Pakiet Podsumowanie:" << "\n" <<
			"	- id: " << this->packagesBuffer.front()->ID_ << "\n" <<
			"	- Nadajnik id: " << this->packagesBuffer.front()->FROM_ID_ << "\n" <<
			"	- Odbiornik id: " << this->packagesBuffer.front()->TO_ID_ << "\n" <<
			"	- Stworzony: " << this->packagesBuffer.front()->createTime << " ms " << "\n" <<
			"	- Obsluzony przez odbiornik: " << currentTime - 1 << " ms " << "\n" <<
			"	- Zakceptowany i usuniety z nadajnika: " << currentTime << " ms " << "\n" <<
			"\n";;
		std::string v = ss.str();
		Logger::GetInstance()->Print(v, Logger::L3);


		this->packagesBuffer.pop();
		this->status = WAIT_FOR_JOB;
	}
	else
	{
		if (this->timeWaitForAck < currentTime)
		{
			this->flagAck = false;
			this->timeWaitForAck = 0;
			this->status = RETRASMISSION;
			this->currentlyRetransmissionStep = 0;
			this->timeWaitForRetrasmissions = this->getRetrasmissionsTime(currentTime);

			stringstream ss; ss <<
				currentTime << "ms" << "\n" <<
				"---" << "\n" <<
				" Nadajnik " << "\n" <<
				"	- id:  " << this->ID_ << "\n" <<
				" Nie otrzymano ACK na czas - retrasmituj" << "\n" <<
				" Pakiet:" << "\n" <<
				"	- id: " << this->packagesBuffer.front()->ID_ << "\n";
			std::string v = ss.str();
			Logger::GetInstance()->Print(v, Logger::L3, Logger::LOG_WARNING);
		}
		else
		{
			stringstream ss; ss <<
				currentTime << "ms" << "\n" <<
				"---" << "\n" <<
				" Nadajnik " << "\n" <<
				"	- id:  " << this->ID_ << "\n" <<
				" Oczekuje na ACK" << "\n";
			std::string v = ss.str();
			Logger::GetInstance()->Print(v, Logger::L3);
		}
	}
}

int Transmitter::getRetrasmissionsTime(int currentTime)
{
	double pp = pow(2, this->currentlyRetransmissionStep + 1);
	return currentTime + (rand() % int(pp) + 1);
}