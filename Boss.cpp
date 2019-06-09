#include "Game.h"
#include "Boss.h"
#include "Bullet.h"


Boss::Boss()
{
}

Boss::~Boss()
{
}

bool Boss::Init()
{
	img = IMAGEMANAGER->FindImage("BossStand");
	ani = ANIMANAGER->FindAni("BossStandAni");
	damageNumber = IMAGEMANAGER->FindImage("PlayerDamNumber");

	pos.x = 0;
	pos.y = 0;

	collision = RectMakeCenter(pos.x, pos.y, BOSSWIDTH, BOSSHEIGHT);
	speed = 5;
	dir = 1;

	state = E_STAND;

	hp = 50;
	atk = 50;
	def = 0;

	for(int i = 0; i < MAXBULLET; i++)
	{
		bullet[i] = new Bullet;
		if (i < MAXALL)
			bullet[i]->Init(BOSS_ALLBULLET);
		else
			bullet[i]->Init(BOSS_RANGEBULLET);

	}

	isAlive = true;
	isStart = false;

	standardTime = GetTickCount();
	realDamage = 0;

	return true;
}

void Boss::Release()
{
}

void Boss::Update()
{
	if(isAlive && isStart)
		Move();

	for (int i = 0; i < MAXBULLET; i++)
		bullet[i]->Update();

	collision = RectMakeCenter(pos.x, pos.y, BOSSWIDTH, BOSSHEIGHT);
}

void Boss::Render(HDC hdc)
{
	if (isAlive)
	{
		img->AniRender(hdc, pos.x - img->GetFrameWidth() / 2 - CAMERA->getPosition()->x,
			pos.y - img->GetFrameHeight() / 2 - CAMERA->getPosition()->y, ani);

		if (KEYMANAGER->isToggleKey(VK_F3))
			Rectangle(hdc, collision.left - CAMERA->getPosition()->x, collision.top - CAMERA->getPosition()->y,
				collision.right - CAMERA->getPosition()->x, collision.bottom - CAMERA->getPosition()->y);

		for (int i = 0; i < MAXBULLET; i++)
			bullet[i]->Render(hdc);

		nowTime = GetTickCount();
		if (nowTime - damTime < 300)
			TXTDATA->RenderNumber(hdc, realDamage, damageNumber, pos.x - CAMERA->getPosition()->x, pos.y - BOSSHEIGHT - CAMERA->getPosition()->y);
	}
}

void Boss::Move()
{
	switch (state)
	{
	case E_STAND:
		if (CheckTime())
		{
			int pattern = RAND->getInt(3);

			switch (pattern)
			{
			case 0:
				ChangeState(BOSS_MELEE_READY);
				break;
			case 1:
				ChangeState(BOSS_RANGE);
				break;
			case 2:
				ChangeState(BOSS_ALL_READY);
				break;
			}
		}
		break;
	case BOSS_MELEE_READY:
		pos.y -= speed;

		if (CheckTime())
			ChangeState(BOSS_MELEE);
		break;
	case BOSS_MELEE:
		if (pos.y + BOSSHEIGHT / 2 < 720)
			pos.y += speed;
		else
		{
			EFFECTMANAGER->Play(TEXT("DustEffect"), { pos.x + 5 - CAMERA->getPosition()->x, pos.y + BOSSHEIGHT / 2 - CAMERA->getPosition()->y });
			EFFECTMANAGER->Play(TEXT("DustEffect"), { pos.x - 5 - DUSTWIDTH - CAMERA->getPosition()->x, pos.y + BOSSHEIGHT / 2 - CAMERA->getPosition()->y });
			ChangeState(E_STAND);
		}
		break;
	case BOSS_RANGE:
		if (!bullet[MAXBULLET - 1]->GetisFire())
			ChangeState(E_STAND);
		break;
	case BOSS_ALL_READY:
		if (CheckTime())
			ChangeState(BOSS_ALL);
		break;
	case BOSS_ALL:
		int count = 0;
		for (int i = 0; i < MAXALL; i++)
		{
			if (bullet[i]->GetisFire())
				continue;
			count++;
		}
		if (count == MAXALL)
			ChangeState(E_STAND);
		break;
	}
}

void Boss::ChangeState(Enemy_State _state)
{
	state = _state;

	switch (state)
	{
	case E_STAND:
		AniPause();
		img = IMAGEMANAGER->FindImage("BossStand");
		ani = ANIMANAGER->FindAni("BossStandAni");
		ANIMANAGER->Resume("BossStandAni");

		pos.x = PLAYER->GetX() + BOSSWIDTH * 3;
		pos.y = BOSSDEFAULTY;
		speed = 1;
		standardTime = GetTickCount();
		break;
	case BOSS_MELEE_READY:
		AniPause();
		img = IMAGEMANAGER->FindImage("BossMeleeReady");
		ani = ANIMANAGER->FindAni("BossMeleeReadyAni");
		ANIMANAGER->Resume("BossMeleeReadyAni");

		pos.x = PLAYER->GetX();
		pos.y = PLAYER->GetY() - BOSSHEIGHT * 3;
		speed = 1;
		standardTime = GetTickCount();
		break;
	case BOSS_MELEE:
		AniPause();
		img = IMAGEMANAGER->FindImage("BossMelee");
		ani = ANIMANAGER->FindAni("BossMeleeAni");

		if (!ani->isPlay())
			ANIMANAGER->Start("BossMeleeRAni");

		speed = 10;
		SOUNDMANAGER->Play(TEXT("BAttackMelee"), 0.5f);
		break;
	case BOSS_RANGE:
		AniPause();
		img = IMAGEMANAGER->FindImage("BossRange");
		ani = ANIMANAGER->FindAni("BossRangeAni");
		ANIMANAGER->Resume("BossRangeAni");

		pos.x = PLAYER->GetX() + BOSSWIDTH * 4;
		pos.y = BOSSDEFAULTY;

		bullet[MAXBULLET - 1]->SetFire(pos);
		break;
	case BOSS_ALL_READY:
		AniPause();
		img = IMAGEMANAGER->FindImage("BossAllReady");
		ani = ANIMANAGER->FindAni("BossAllReadyAni");
		ANIMANAGER->Resume("BossAllReadyAni");

		pos.x = PLAYER->GetX();
		pos.y = PLAYER->GetY() - BOSSWIDTH * 3;

		for (int i = 0; i < MAXALL; i++)
			bullet[i]->SetFire({ PLAYER->GetX() - WINSIZEX / 2 + 150 * i, ALLHEIGHT });
		standardTime = GetTickCount();
		break;
	case BOSS_ALL:
		AniPause();
		img = IMAGEMANAGER->FindImage("BossAll");
		ani = ANIMANAGER->FindAni("BossAllAni");
		ANIMANAGER->Resume("BossAllAni");
		
		for (int i = 0; i < MAXALL; i++)
			bullet[i]->SetisMove(true);
		break;
	}
}

void Boss::AniPause()
{
	ANIMANAGER->Pause("BossStandAni");
	ANIMANAGER->Pause("BossMeleeReadyAni");
	ANIMANAGER->Pause("BossMeleeAni");
	ANIMANAGER->Pause("BossRangeAni");
	ANIMANAGER->Pause("BossAllReadyAni");
	ANIMANAGER->Pause("BossAllAni");
}

void Boss::Damage(int _damage)
{
	damTime = GetTickCount();

	realDamage = _damage - def;

	if (realDamage < 0)
		realDamage = 0;

	hp -= realDamage;

	if (hp <= 0)
	{
		isAlive = false;
		isStart = false;
		SOUNDMANAGER->Play(TEXT("Burn"), 0.5f);
		EFFECTMANAGER->Play(TEXT("BurnBossEffect"), { pos.x - CAMERA->getPosition()->x, pos.y - CAMERA->getPosition()->y });
	}
}

bool Boss::CheckTime()
{
	nowTime = GetTickCount();

	if (nowTime - standardTime >= 3000)
		return true;
	else
		return false;
}
