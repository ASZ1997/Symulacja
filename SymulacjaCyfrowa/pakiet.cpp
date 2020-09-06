#include "pakiet.h"


int Pakiet::global_id_ = 0;

Pakiet::Pakiet() :kID_(global_id_++)
{
}


Pakiet::~Pakiet()
{
}

int Pakiet::getID() const
{
	return kID_;
}
