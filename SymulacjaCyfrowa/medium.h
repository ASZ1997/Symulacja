#ifndef MODEL_MEDIUM_H_
#define MODEL_MEDIUM_H_

#include<queue>

using namespace std;

class Package;
class Transmitter;
class Receiver;

struct Medium
{
	Medium();
	~Medium();

	/**
		Pakiety znajduj¹ce siê w medium
	*/
	std::queue<Package*> packagesInMedum;

	/**
		Flaga pokazuj¹ca czy w tej szczelinie czasowej zosta³ ju¿ dodany pakiet
	*/
	bool FSlotUsed;

	/**
		Dodaje pakiet do buffora jesli jest on wpasowany do szceliny
		zwraca true gdy sie dostal 
		zwraca false gdzy sie nie dostal
	*/
	bool addPackage(Package* package, int currentTime);

	/**
		Wszytsko zwi¹zane z prac¹ medium
	*/
	void working(int currentTime, Transmitter** transmitters, Receiver** receivers);




};

#endif /*MODEL_MEDIUM_H_*/