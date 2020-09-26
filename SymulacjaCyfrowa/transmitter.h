#ifndef Transmitter_h_
#define Transmitter_h_

#include <queue>

using namespace std;

class Package;
class Medium;

/**
	Nadajnik
*/
class Transmitter
{
public:
	/**
		Inicjalizacja nadajnika
	*/
	Transmitter(int id);

	/**
		Dekostrukcja nadajnika 
	*/
	~Transmitter();

	/**
		Tworzy pakiet który zostanie dodany do buffora
	*/
	void addPackage(int currentTime, int packageId);

	/**
		Pracuj nadajnikiem
	*/
	void working(int currentTime, Medium* medium);

	/**
		Id nadajnika
	*/
	const int ID_;
	
	/**
		Bufor pakietów
	*/
	std::queue <Package*> packagesBuffer;

	/**
		Status nadajnika 
		WAIT_FOR_ACK - oczekuje na powrót ack
		RETRASMISSION - Retrasmituje ostatni pakiet
		WAIT_FOR_JOB - oczekiwuje na pracê
	*/
	enum StatusType {
		WAIT_FOR_ACK,
		RETRASMISSION,
		WAIT_FOR_JOB
	};

	StatusType status;

	/**
		Oczekiwany czas na ack
	*/
	int timeWaitForAck;

	/**
		MAKSYMALNA ILOŒÆ RETRASMISJI
	*/
	const int R_MAX_;

	/**
		Obecna próba retrasmisji
	*/
	int currentlyRetransmissionStep;

	/**
		Czas do rozpoczêcia retrasmisji
	*/
	int timeWaitForRetrasmissions;

	/**
		kiedy wchodzi w stan czekaj na ack czeka dopóki czas na powrót 
		nie skoñczy siê lub do momentu a¿ flaga z powrotem ack zmieni siê na true
	*/
	bool flagAck = false;

private:

	/**
		obs³uga statusu wait for job 
	*/
	void HandleWaitForJob(int currentTime, Medium* medium);

	/**
		obs³uga status retransmisji
	*/
	void HandleRetrasmission(int currentTime, Medium* medium);

	/**
		obs³uga statusu WAIT FOR ACK
	*/
	void HandleWaitForAck(int currentTime, Medium* medium);

	/**
		zwraca czas po jakim ma dojœæ do retrasmisji
	*/
	int getRetrasmissionsTime(int currentTime);

};

#endif /* SIMULATOR_SIMULATOR_H_ */