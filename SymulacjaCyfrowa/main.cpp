#include <iostream>
#include "simulator.h"
#include "logger.h"

int main()
{
	printf("------------------------------------------------------------------------\n");
	printf("                           INITIALIZATION\n");
	printf("------------------------------------------------------------------------\n");

	Simulator* simulator = new Simulator(100, 4);

	bool step_by_step = true; 
	int logger_verb;
	printf("Choose simulation mode (1 - step by step, 0 - continous): ");
	std::cin >> step_by_step;
	do
	{
		printf("Choose logger verbosity level (1-4): ");
		std::cin >> logger_verb;
	} while (logger_verb < 1 || logger_verb > 4);

	simulator->Initialize(step_by_step, static_cast<Logger::LogVerbosity>(logger_verb));

	printf("------------------------------------------------------------------------\n");
	printf("                           SIMULATION\n");
	printf("------------------------------------------------------------------------\n");

	simulator->Start();

	printf("------------------------------------------------------------------------\n");
	printf("                           FINISHED\n");
	printf("------------------------------------------------------------------------\n");

	delete simulator;

	system("Pause");
}
