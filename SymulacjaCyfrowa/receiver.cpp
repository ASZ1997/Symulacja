#include "receiver.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

Receiver::Receiver(int id): ID_(id)
{

}

Receiver::~Receiver() 
{

}

bool Receiver::ConnectToReceiver()
{
	int value = rand() % 101;
	if (value > (this->T * 100))
	{
		// Nie uda�o si� obs�uzy�
		return false;
	}
	else
	{
		// ud��o si� obs�u�y�
		return true;
	}
}