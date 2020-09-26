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
		Tworzy pakiet kt�ry zostanie dodany do buffora
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
		Bufor pakiet�w
	*/
	std::queue <Package*> packagesBuffer;

	/**
		Status nadajnika 
		WAIT_FOR_ACK - oczekuje na powr�t ack
		RETRASMISSION - Retrasmituje ostatni pakiet
		WAIT_FOR_JOB - oczekiwuje na prac�
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
		MAKSYMALNA ILO�� RETRASMISJI
	*/
	const int R_MAX_;

	/**
		Obecna pr�ba retrasmisji
	*/
	int currentlyRetransmissionStep;

	/**
		Czas do rozpocz�cia retrasmisji
	*/
	int timeWaitForRetrasmissions;

	/**
		kiedy wchodzi w stan czekaj na ack czeka dop�ki czas na powr�t 
		nie sko�czy si� lub do momentu a� flaga z powrotem ack zmieni si� na true
	*/
	bool flagAck = false;

private:

	/**
		obs�uga statusu wait for job 
	*/
	void HandleWaitForJob(int currentTime, Medium* medium);

	/**
		obs�uga status retransmisji
	*/
	void HandleRetrasmission(int currentTime, Medium* medium);

	/**
		obs�uga statusu WAIT FOR ACK
	*/
	void HandleWaitForAck(int currentTime, Medium* medium);

	/**
		zwraca czas po jakim ma doj�� do retrasmisji
	*/
	int getRetrasmissionsTime(int currentTime);

};

#endif /* SIMULATOR_SIMULATOR_H_ */