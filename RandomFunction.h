#pragma once
#include "SingletonBase.h"
#include <time.h>

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		srand(GetTickCount());			//GetTickCount는 unsigned 형태의 값(4byte 정수형)을 리턴해준다.
	}

	~RandomFunction() {}

	inline int getInt(int num) { return rand() % num; }

	inline int getFromIntoTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};