#ifndef Receiver_h_
#define Receiver_h_

#include <queue>

using namespace std;

/**
	Odbiornik
*/
class Receiver
{
public:

	Receiver(int id);

	~Receiver();

	/**
		Id odbiornika
	*/
	const int ID_;

	/**
		Szansa na poprawn¹ obs³ugê pakietu
	*/
	const float T = 0.8;
	
	/**
		Zwraca czy pakiet zosta³ pomyœlnie obs³uzony
		jesli tak to ustaiwa w nadjaniku flagê ack na true
	*/
	bool ConnectToReceiver();
};

#endif /* SIMULATOR_SIMULATOR_H_ */