#ifndef MODEL_PAKIET_H_
#define MODEL_PAKIET_H_


class Pakiet
{
public:
	Pakiet();
	~Pakiet();
	int getID() const;
private:
	static int global_id_;
	const int kID_;
};

#endif /*MODEL_PAKIET_H_*/