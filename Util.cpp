#include "Game.h"
#include "Util.h"

namespace UTIL
{
	float UTIL::getDistance(const float startX, const float startY, const float endX, const float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x*x + y * y);
	}

	float getAngle(const float x1, const float y1, const float x2, const float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;

			if (angle >= PI2)			//acosf의 범위 때문에 2PI가 넘으면 2PI만큼 빼줘서 예외처리
			{
				angle -= PI2;
			}
		}
		return angle;
	}
}
