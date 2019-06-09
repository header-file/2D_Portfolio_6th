#pragma once
#include "SingletonBase.h"
#include <time.h>

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		srand(GetTickCount());			//GetTickCount�� unsigned ������ ��(4byte ������)�� �������ش�.
	}

	~RandomFunction() {}

	inline int getInt(int num) { return rand() % num; }

	inline int getFromIntoTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};