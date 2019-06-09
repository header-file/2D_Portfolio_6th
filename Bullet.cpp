#include "Game.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

bool Bullet::Init(Bullet_Type _type)
{
	type = _type;

	switch (type)
	{
	case ARCHER_ARROW:
		img = IMAGEMANAGER->FindImage("ArcherArrow");
		ani = ANIMANAGER->FindAni("ArcherArrowLAni");

		pos.x = 0;
		pos.y = 0;

		collision = RectMakeCenter(pos.x, pos.y, ARROWWIDTH, ARROWHEIGHT);

		speed = 7;
		dir = LEFT;

		isFire = false;
		break;
	case BOSS_RANGEBULLET:
		img = IMAGEMANAGER->FindImage("BossRangeBullet");
		ani = ANIMANAGER->FindAni("BossRangeBulletAni");
		ANIMANAGER->Start("BossRangeBulletAni");

		pos.x = 0;
		pos.y = 0;
		standardPos.x = 0;
		standardPos.y = 0;

		collision = RectMakeCenter(pos.x, pos.y, RANGEWIDTH, RANGEHEIGHT);

		speed = 5;
		
		rangeCount = 0;

		isFire = false;
		AniPause();
		break;
	case BOSS_ALLBULLET:
		img = IMAGEMANAGER->FindImage("BossAllBullet");
		ani = ANIMANAGER->FindAni("BossAllBulletAni");
		ANIMANAGER->Start("BossAllBulletAni");
		
		pos.x = 0;
		pos.y = 0;

		collision = RectMakeCenter(pos.x, pos.y, ALLWIDTH, ALLHEIGHT);

		speed = 5;

		isFire = false;
		isMove = false;
		AniPause();
		break;
	}
	return true;
}

void Bullet::Release()
{
}

void Bullet::Update()
{
	if (isFire)
	{
		switch (type)
		{
		case ARCHER_ARROW:
			pos.x += speed * dir;

			if (pos.x <= -img->GetFrameWidth() / 2 || pos.x >= PLAYER->GetX() + WINSIZEX / 2 + img->GetFrameWidth() / 2)
				isFire = false;

			collision = RectMakeCenter(pos.x, pos.y, ARROWWIDTH, ARROWHEIGHT);
			break;
		case BOSS_RANGEBULLET:
			if (rangeCount <= RANGECOUNT)
			{		
				pos.x += cosf(angle) * speed;
				pos.y += -sinf(angle) * speed;

				if (pos.y >= WINSIZEY + RANGEHEIGHT || pos.y <= -RANGEHEIGHT)
				{
					SetAngle();
					rangeCount++;
				}
				else if(pos.x >= PLAYER->GetX() + WINSIZEX / 2 + RANGEWIDTH || pos.x <= PLAYER->GetX() - WINSIZEX / 2 - RANGEWIDTH)
				{
					SetAngle();
					rangeCount++;
				}
			}
			else
				isFire = false;

			collision = RectMakeCenter(pos.x, pos.y, RANGEWIDTH, RANGEHEIGHT);
			break;
		case BOSS_ALLBULLET:
			if (isMove)
			{
				pos.y += speed;

				if (pos.y >= WINSIZEY + ALLHEIGHT / 2)
				{
					isMove = false;
					isFire = false;
				}
			}

			collision = RectMakeCenter(pos.x, pos.y, ALLWIDTH, ALLHEIGHT);
			break;
		}
	}
}

void Bullet::Render(HDC hdc)
{
	if (isFire)
	{
		img->AniRender(hdc, pos.x - img->GetFrameWidth() / 2 - CAMERA->getPosition()->x,
			pos.y - img->GetFrameHeight() / 2 - CAMERA->getPosition()->y, ani);

		if (KEYMANAGER->isToggleKey(VK_F3))
			Rectangle(hdc, collision.left - CAMERA->getPosition()->x, collision.top - CAMERA->getPosition()->y,
				collision.right - CAMERA->getPosition()->x, collision.bottom - CAMERA->getPosition()->y);
	}
}

void Bullet::AniPause()
{
	switch (type)
	{
	case ARCHER_ARROW:
		ANIMANAGER->Pause("ArcherArrowRAni");
		ANIMANAGER->Pause("ArcherArrowLAni");
		break;
	case BOSS_RANGEBULLET:
		ANIMANAGER->Pause("BossRangeBulletAni");
		break;
	case BOSS_ALLBULLET:
		ANIMANAGER->Pause("BossAllBulletAni");
		break;
	}
}

void Bullet::SetAngle()
{
	standardPos.x = PLAYER->GetX();
	standardPos.y = PLAYER->GetY();
	angle = UTIL::getAngle(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(standardPos.x), static_cast<float>(standardPos.y));
}

void Bullet::SetFire(POINT _pos)
{
	if (!isFire)
		isFire = true;

	switch (type)
	{
	case ARCHER_ARROW:
		AniPause();

		switch (dir)
		{
		case RIGHT:
			ani = ANIMANAGER->FindAni("ArcherArrowRAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("ArcherArrowRAni");

			pos.x = _pos.x + 10;
			pos.y = _pos.y - 20;
			break;
		case LEFT:
			ani = ANIMANAGER->FindAni("ArcherArrowLAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("ArcherArrowLAni");

			pos.x = _pos.x - 10;
			pos.y = _pos.y - 20;
			break;
		}
		break;
	case BOSS_RANGEBULLET:
		ani = ANIMANAGER->FindAni("BossRangeBulletAni");
		ANIMANAGER->Resume("BossRangeBulletAni");

		pos.x = _pos.x;
		pos.y = _pos.y;

		SetAngle();
		break;
	case BOSS_ALLBULLET:
		ani = ANIMANAGER->FindAni("BossAllBulletAni");
		ANIMANAGER->Resume("BossAllBulletAni");

		pos.x = _pos.x;
		pos.y = _pos.y;
		break;
	}
}
