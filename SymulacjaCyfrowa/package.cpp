#include "package.h"
#include <iostream>
#include <cstdlib>


using namespace std;


Package::Package(int id, int FromTo, double createTime):
	ID_(id), FROM_ID_(FromTo), TO_ID_(FromTo)
{
	this->createTime = createTime;
	ctp = this->getCTP();
}

Package::~Package()
{

}

int Package::getCTP()
{
	return rand() % 10 + 1;
}
