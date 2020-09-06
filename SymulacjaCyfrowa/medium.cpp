#include "medium.h"
#include <iostream>
#include "pakiet.h"
#include "odbiornik.h"

using namespace std;


Medium::Medium(int nr_of_sds):kLiczbaOdbiorników(nr_of_sds)
{
	for(int i = 0; i <kLiczbaOdbiorników; i++)
	{
		odbiornik.push_back(new Odbiornik());
	}
}

Medium::~Medium()
{
	while(!pakiet.empty())
	{
		Pakiet* p = pakiet.front();
		pakiet.pop();
		cout << "Pakiet #" << p->getID() << " deleted!\n";
		delete p;
	}
	for(auto *sd:odbiornik)
	{
		delete sd;
	}
}
