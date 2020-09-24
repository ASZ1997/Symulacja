#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>

class Logger
{
public:
	/**
		Typy logów
	*/
	enum LogType { LOG_ERROR, LOG_WARNING, LOG_INFO };

	/**
		Poziom szczegó³owoœci logów
	*/
	enum LogVerbosity { L1 = 1, L2, L3, L4 };

	/**
		Wyœwietl wiadmoœæ w logach
	*/
	void Print(const std::string text, LogVerbosity logVerb = L1, LogType logType = LOG_INFO);

	/**
		Ustaw poziom szczegó³owowœci logów
	*/
	void SetLogVerbosity(LogVerbosity lv);

	/**
		Zwraca poziom szczegó³owowœci logów
	*/
	LogVerbosity GetLogVerbosity();

	/**
		Zwraca instancje obiektu
	*/
	static Logger* GetInstance();

protected:
	
	Logger();

	virtual ~Logger();

	/**
		Przecowuje instancje loggera
	*/
	static Logger* instance_;

	/**
		Przechowuje poziom szczegó³owoœci logera
	*/
	LogVerbosity log_verbosity_;			// Log verbosity.       
};

#endif /* LOGGER_LOGGER_H_ */