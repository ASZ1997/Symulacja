#include "odbiornik.h"

#include "pakiet.h"

Odbiornik::Odbiornik(): obsl_pakiet(nullptr)
{
}


Odbiornik::~Odbiornik()
{
	if (obsl_pakiet != nullptr)
		delete obsl_pakiet;
}
bool Odbiornik::IsEmpty()
{
	return (obsl_pakiet == nullptr);
}

void Odbiornik::AssignPakiet(Pakiet* c)
{
	obsl_pakiet = c;
}

Pakiet* Odbiornik::RemovePakiet()
{
	Pakiet* c = obsl_pakiet;
	obsl_pakiet = nullptr;
	return c;
}
