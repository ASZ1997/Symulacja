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
		// Nie uda³o siê obs³uzyæ
		return false;
	}
	else
	{
		// ud¹³o siê obs³u¿yæ
		return true;
	}
}