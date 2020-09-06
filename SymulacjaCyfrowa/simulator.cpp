#include <cstdlib>
#include <ctime>
#include "simulator.h"

#include <iostream>
#include <sstream>
#include "logger.h"
#include <iso646.h>

#include "medium.h"
#include "pakiet.h"
#include "odbiornik.h"

Simulator::Simulator(double stop_time, int nrof_service) : kStopTime_(stop_time),
kNrofOdbiornik_(nrof_service)
{
	medium_ = nullptr;
	pakiet_arrived_time_ = -1;

	for (int i = 0; i < kNrofOdbiornik_; i++)
		service_completion_time_.push_back(-1);
}

Simulator::~Simulator()
{
	delete medium_;
}

void Simulator::Initialize(bool step_by_step, Logger::LogVerbosity verb)
{
	medium_ = new Medium(kNrofOdbiornik_);
	current_time_ = 0;
	step_by_step_ = step_by_step;
	pakiet_arrived_time_ = 0;
	Logger::GetInstance()->SetLogVerbosity(static_cast<Logger::LogVerbosity>(verb));

}

bool Simulator::RunTimeEvents()
{
	bool state_changed = false;

	if (pakiet_arrived_time_ == current_time_)
	{
		HandleNewPakietArrivedTEvent();
		state_changed = true;
	}
	for (int i = 0; i < medium_->odbiornik.size(); i++)
	{
		if (service_completion_time_[i] == current_time_)
		{
			HandleServiceCompletionTEvent(i);
			state_changed = true;
			service_completion_time_[i] = -1;
		}
	}
	return state_changed;
}

bool Simulator::RunConditionalEvents()
{
	bool state_changed = false;

	for (int i = 0; i < medium_->odbiornik.size(); i++)
	{
		if (medium_->odbiornik[i]->IsEmpty() && !medium_->pakiet.empty())
		{
			HandleStartServiceCEvent(i);
			state_changed = true;
		}
	}
	return state_changed;
}

void Simulator::Start()
{
	// simulation loop
	while (current_time_ <= kStopTime_)
	{
		Logger::GetInstance()->Print(("\n----------------------------------------------------------------------\n"), Logger::L3);
		Logger::GetInstance()->Print(("CLOCK = " + std::to_string(current_time_) + "\n"), Logger::L3);

		bool state_changed = true;

		while (state_changed)
		{
			state_changed = false;

			state_changed = state_changed or RunTimeEvents();

			state_changed = state_changed or RunConditionalEvents();
		}

		// Find the closest time event
		double closest_event = pakiet_arrived_time_;
		double eps = 0.00000001;

		for (int i = 0; i < medium_->odbiornik.size(); i++)
		{
			//Not equal && from the future && smaller than current the smallest
			if (abs(service_completion_time_[i] - current_time_) > eps && service_completion_time_[i] > current_time_ && service_completion_time_[i] < closest_event)
				closest_event = service_completion_time_[i];
		}
		current_time_ = closest_event;

		if (step_by_step_)
		{
			std::cout << "Press ENTER to continue...";
			std::string l; getline(std::cin, l);
		}
	}
}

void Simulator::HandleNewPakietArrivedTEvent()
{
	Logger::GetInstance()->Print("HandleNewPakietArrivedTEvent()", Logger::L2);
	auto new_pakiet = new Pakiet();
	medium_->pakiet.push(new_pakiet);
	pakiet_arrived_time_ = current_time_ + rand() % 50 + 1;

	std::stringstream ss; ss << "New Process: ID = " << new_pakiet->getID()
		<< ", arrived at = " << current_time_
		<< " s, next process will arrive at " << pakiet_arrived_time_ << " s." << std::endl;
	std::string descp = ss.str();
	Logger::GetInstance()->Print(descp, Logger::L3);
}

void Simulator::HandleServiceCompletionTEvent(int service_idx)
{
	Logger::GetInstance()->Print("HandleServiceCompletionTEvent()", Logger::L2);

	auto pakiet = medium_->odbiornik[service_idx]->RemovePakiet();
	stringstream ss; ss << "Service finished at = " << current_time_ << " s, " << service_idx << "-th service desk finished serving " << pakiet->getID() << "-th pakiet" << endl;
	string descp = ss.str();
	Logger::GetInstance()->Print(descp, Logger::L3);
	delete pakiet;
}

void Simulator::HandleStartServiceCEvent(int service_idx)
{
	Logger::GetInstance()->Print("HandleStartServiceCEvent()", Logger::L2);

	auto first_pakiet = medium_->pakiet.front();
	medium_->pakiet.pop();

	medium_->odbiornik[service_idx]->AssignPakiet(first_pakiet);
	service_completion_time_[service_idx] = current_time_ + rand() % 20 + 1;

	stringstream ss; ss << "Service started at = " << current_time_ << " s, " << first_pakiet->getID()
		<< "-th customer was assigned to " << service_idx << "-th service desk, service will stop at "
		<< service_completion_time_[service_idx] << " s" << endl;
	string descp = ss.str();
	Logger::GetInstance()->Print(descp, Logger::L3);
}
