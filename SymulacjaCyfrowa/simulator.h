#ifndef SIMULATOR_SIMULATOR_H_
#define SIMULATOR_SIMULATOR_H_
#include <vector>
#include "logger.h"

using namespace std;

struct Medium;

class Simulator
{
public:
	Simulator(double stop_time, int nrof_service);
	~Simulator();

	void Initialize(bool step_by_step, Logger::LogVerbosity verb);

	void Start();

private:
	/*
		Czas po kt�rym zatrzymie si� symulacja
	*/
	const double kStopTime_;

	/*
		Ilo�� odbiornik�w
	*/
	const double kNrofOdbiornik_;

	/*
		Aktualny czas
	*/
	double current_time_;

	/*
		Czy zosta�a ustawiona opcja krok po kroku
	*/
	bool step_by_step_;

	double pakiet_arrived_time_;
	vector<double> service_completion_time_;

	Medium* medium_;

	bool RunTimeEvents();
	bool RunConditionalEvents();
	void HandleNewPakietArrivedTEvent();
	void HandleServiceCompletionTEvent(int service_idx);
	void HandleStartServiceCEvent(int service_idx);
};

#endif /* SIMULATOR_SIMULATOR_H_ */