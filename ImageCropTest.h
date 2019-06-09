#pragma once
#include "GameNode.h"

class ImageCropTest : public GameNode
{
private:
	Image * _background;
	int		_offsetX, _offsetY;

public:
	ImageCropTest();
	~ImageCropTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

