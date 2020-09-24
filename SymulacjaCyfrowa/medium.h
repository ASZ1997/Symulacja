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
		Pakiety znajduj�ce si� w medium
	*/
	std::queue<Package*> packagesInMedum;

	/**
		Flaga pokazuj�ca czy w tej szczelinie czasowej zosta� ju� dodany pakiet
	*/
	bool FSlotUsed;

	/**
		Dodaje pakiet do buffora jesli jest on wpasowany do szceliny
		zwraca true gdy sie dostal 
		zwraca false gdzy sie nie dostal
	*/
	bool addPackage(Package* package, int currentTime);

	/**
		Wszytsko zwi�zane z prac� medium
	*/
	void working(int currentTime, Transmitter** transmitters, Receiver** receivers);




};

#endif /*MODEL_MEDIUM_H_*/