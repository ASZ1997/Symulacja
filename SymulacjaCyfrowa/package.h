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
		Id nadajnika sk¹d zosta³ wys³¹ny pakiet
	*/
	const int FROM_ID_;

	/**
		Id odbiornika do kótrego zmierza pakiet
	*/
	const int TO_ID_;

	/**
		Czas utworzenia pakietu (dodanie do buffora nadajnika)	
	*/
	double createTime;

	/**
		Czas w którym dosta³a siê do medium
	*/
	int timeGotAccessToTheMedium;

	/**
		Czas po kótrym dostanie siê do odbiornika
		CTP
	*/
	int ctp;

private:

	/**
		Zwraca czas po którym ma siê dostaæ do odbiornika
		ctp
		
		"zmienna losowa o rozk³adzie jednostajnym w przedziale {1, 2, …, 10} ms"
		
	*/
	int getCTP();
};

#endif /* SIMULATOR_SIMULATOR_H_ */