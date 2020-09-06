#ifndef MODEL_ODBIORNIK_H_
#define MODEL_ODBIORNIK_H_

class Pakiet;

class Odbiornik
{
public:
	Odbiornik();
	~Odbiornik();

	bool IsEmpty();
	void AssignPakiet(Pakiet* c);
	Pakiet* RemovePakiet();

private:
	Pakiet* obsl_pakiet;
};
//void odbierzPakiet();
//void wyslijACK();
#endif /*MODEL_ODBIORNIK_H_*/