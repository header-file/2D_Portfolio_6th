#pragma once
class Action
{
	Image*	image;

	float	startX, startY;
	float	endX, endY;

	float	angle;

	float	travelRange;
	float	worldTimeCount;
	float	time;
	
	bool	isMoving;

public:
	Action();
	~Action();

	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void MoveTo(Image* _image, float _endX, float _endY, float _time);
	void Moving();

	bool GetIsMoving() { return isMoving; }
};

