#ifndef Package_h_
#define Package_h_

using namespace std;

/**
	Pakiet
*/
class Package
{
public:

	Package(int id, int FromTo, double createTime);
	
	~Package();

	/**
		Id pakietu
	*/
	const int ID_;

	/**
		Id nadajnika sk�d zosta� wys��ny pakiet
	*/
	const int FROM_ID_;

	/**
		Id odbiornika do k�trego zmierza pakiet
	*/
	const int TO_ID_;

	/**
		Czas utworzenia pakietu (dodanie do buffora nadajnika)	
	*/
	double createTime;

	/**
		Czas w kt�rym dosta�a si� do medium
	*/
	int timeGotAccessToTheMedium;

	/**
		Czas po k�trym dostanie si� do odbiornika
		CTP
	*/
	int ctp;

private:

	/**
		Zwraca czas po kt�rym ma si� dosta� do odbiornika
		ctp
		
		"zmienna losowa o rozk�adzie jednostajnym w przedziale {1, 2, �, 10} ms"
		
	*/
	int getCTP();
};

#endif /* SIMULATOR_SIMULATOR_H_ */