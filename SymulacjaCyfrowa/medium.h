#ifndef MODEL_MEDIUM_H_
#define MODEL_MEDIUM_H_

#include<queue>
using namespace std;

class Pakiet;
class Odbiornik;

struct Medium
{
	const int kLiczbaOdbiorników;
	Medium(int nr_of_sds);
	~Medium();

	queue<Pakiet*> pakiet;
	vector<Odbiornik*> odbiornik;

};

#endif /*MODEL_MEDIUM_H_*/