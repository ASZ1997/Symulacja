#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>

class Logger
{
public:
	/**
		Typy log�w
	*/
	enum LogType { LOG_ERROR, LOG_WARNING, LOG_INFO };

	/**
		Poziom szczeg�owo�ci log�w
	*/
	enum LogVerbosity { L1 = 1, L2, L3, L4 };

	/**
		Wy�wietl wiadmo�� w logach
	*/
	void Print(const std::string text, LogVerbosity logVerb = L1, LogType logType = LOG_INFO);

	/**
		Ustaw poziom szczeg�owow�ci log�w
	*/
	void SetLogVerbosity(LogVerbosity lv);

	/**
		Zwraca poziom szczeg�owow�ci log�w
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
		Przechowuje poziom szczeg�owo�ci logera
	*/
	LogVerbosity log_verbosity_;			// Log verbosity.       
};

#endif /* LOGGER_LOGGER_H_ */