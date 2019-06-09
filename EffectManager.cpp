#include "Game.h"
#include "EffectManager.h"
#include "Effect.h"



EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
}

bool EffectManager::Init()
{
	return true;
}

void EffectManager::Release()
{
	iTotalEffect it = _mTotalEffect.begin();

	for (; it != _mTotalEffect.end(); ++it)
	{
		iEffect vit = (it->second).begin();
		for (; vit != (it->second).end(); ++vit)
		{
			(*vit)->Release();
			SAFE_DELETE((*vit));
		}
		(it->second).clear();
	}
}

void EffectManager::Update()
{
	iTotalEffect it = _mTotalEffect.begin();

	for (; it != _mTotalEffect.end(); ++it)
	{
		for (auto vit : it->second)
		{
			vit->Update();
		}
	}
}

void EffectManager::Render(HDC hdc)
{
	iTotalEffect it = _mTotalEffect.begin();

	for (; it != _mTotalEffect.end(); ++it)
	{
		for (auto vit : it->second)
		{
			vit->Render(hdc);
		}
	}
}

void EffectManager::AddEffect(string effectName, const TCHAR * imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, 
								int fps, float elapsedTime, int buffer, COLORREF color)
{
	Image* img;

	iTotalEffect it = _mTotalEffect.find(effectName);
	if (it != _mTotalEffect.end())
		return;

	img = IMAGEMANAGER->FindImage(effectName);
	
	if(img == NULL)
	{
		img = IMAGEMANAGER->AddImage(effectName, imageName, imageWidth, imageHeight, true, color);
	}

	vEffect vEffectBuffer;
	for (int i = 0; i < buffer; ++i)
	{
		vEffectBuffer.push_back(new Effect);
		vEffectBuffer[i]->Init(img, effectWidth, effectHeight, fps, elapsedTime);
	}

	_mTotalEffect.insert(std::pair<string, vEffect>(effectName, vEffectBuffer));
}

void EffectManager::Play(string effectName, int x, int y)
{
	iTotalEffect it = _mTotalEffect.find(effectName);

	if (it != _mTotalEffect.end())
	{
		for (auto vit : it->second)
		{
			if (vit->GetIsRunning())
				continue;

			vit->StartEffect(x, y);
			return;
		}
	}
}

void EffectManager::Play(string effectName, POINT p)
{
	Play(effectName, p.x, p.y);
}
