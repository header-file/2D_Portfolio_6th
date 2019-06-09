#include "Game.h"
#include "ProgressBar.h"



ProgressBar::ProgressBar()
{
}


ProgressBar::~ProgressBar()
{
}

bool ProgressBar::Init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(_x, _y, width, height);

	_progressBarTop = IMAGEMANAGER->AddImage(TEXT("FrontBar"), TEXT("Image/hpBarTop.bmp"), x, y, width, height, true, COLOR_M);
	_progressBarBottom = IMAGEMANAGER->AddImage(TEXT("BackBar"), TEXT("Image/hpBarBottom.bmp"), x, y, width, height, true, COLOR_M);

	_width = _progressBarTop->GetWidth();

	return true;
}

bool ProgressBar::Init(string strTop, string strBack, int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(_x, _y, width, height);

	_progressBarTop = IMAGEMANAGER->FindImage(strTop);
	assert(_progressBarTop != NULL);
	_progressBarBottom = IMAGEMANAGER->FindImage(strBack);
	assert(_progressBarBottom != NULL);

	_width = _progressBarTop->GetWidth();

	return false;
}

void ProgressBar::Release()
{
}

void ProgressBar::Update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->GetWidth(), _progressBarTop->GetHeight());
}

void ProgressBar::Render(HDC hdc)
{
	_progressBarBottom->Render(hdc, _rcProgress.left + _progressBarBottom->GetWidth() / 2, _y + _progressBarBottom->GetHeight() / 2,
		0, 0, _progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());

	_progressBarTop->Render(hdc, _rcProgress.left + _progressBarTop->GetWidth() / 2, _y + _progressBarTop->GetHeight() / 2,
		0, 0, _width, _progressBarTop->GetHeight());
}

void ProgressBar::Render(HDC hdc, const POINT * pt)
{
	_progressBarBottom->Render(hdc, _rcProgress.left + _progressBarBottom->GetWidth() / 2 - pt->x, _y + _progressBarBottom->GetHeight() / 2 - pt->y,
		0, 0, _progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());

	_progressBarTop->Render(hdc, _rcProgress.left + _progressBarTop->GetWidth() / 2 - pt->x, _y + _progressBarTop->GetHeight() / 2 - pt->y,
		0, 0, _width, _progressBarTop->GetHeight());
}

void ProgressBar::SetGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->GetWidth();
}
