#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

bool Enemy::Init(Enemy_Type _type)
{
	type = _type;

	switch (type)
	{
	case ZOMBIE:
		img = IMAGEMANAGER->FindImage("ZombieRise");
		ani = ANIMANAGER->FindAni("ZombieRiseUpLAni");

		pos.x = 0;
		pos.y = 0;

		collision = RectMakeCenter(pos.x, pos.y, ZOMBIEWIDTH, ZOMBIEHEIGHT);
		searchArea = RectMakeCenter(pos.x, pos.y, ZOMBIEWIDTH * 6, ZOMBIEHEIGHT);
		speed = 1;

		state = E_STAND;

		hp = 30;
		atk = 5;
		def = 20;

		exp = 10;

		isAlive = true;
		break;
	case BAT:
		img = IMAGEMANAGER->FindImage("BatStand");
		ani = ANIMANAGER->FindAni("BatStandAni");
		ANIMANAGER->Start("BatStandAni");

		pos.x = 0;
		pos.y = 0;

		collision = RectMakeCenter(pos.x, pos.y, BATWIDTH, BATHEIGHT);
		searchArea = RectMakeCenter(pos.x, pos.y, BATWIDTH * 50, BATHEIGHT * 40);
		speed = 3;

		state = E_STAND;

		hp = 10;
		atk = 15;
		def = 10;

		exp = 20;
		break;
	case ARCHER:
		img = IMAGEMANAGER->FindImage("ArcherMove");
		ani = ANIMANAGER->FindAni("ArcherMoveLAni");

		pos.x = 0;
		pos.y = 0;

		collision = RectMakeCenter(pos.x, pos.y, ARCHERWIDTH, ARCHERHEIGHT);
		searchArea = RectMakeCenter(pos.x, pos.y, ARCHERWIDTH * 50, ARCHERHEIGHT * 2);
		speed = 5;

		state = E_MOVE;
		dir = LEFT;

		hp = 50;
		atk = 20;
		def = 15;

		exp = 50;

		bullet = new Bullet;
		bullet->Init(ARCHER_ARROW);
		break;
	case PERSEPHONE:
		img = IMAGEMANAGER->FindImage("PersephoneMove");
		ani = ANIMANAGER->FindAni("PersephoneMoveLAni");
		ANIMANAGER->Start("PersephoneMoveLAni");

		pos.x = 0;
		pos.y = 0;

		collision = RectMakeCenter(pos.x, pos.y, PERSEPHONEWIDTH, PERSEPHONEHEIGHT);
		searchArea = RectMakeCenter(pos.x, pos.y, PERSEPHONEWIDTH * 20, PERSEPHONEHEIGHT * 5);
		hitBox = RectMake(pos.x - KICKWIDTH, pos.y - KICKYMODIFY, KICKWIDTH, KICKHEIGHT);
		speed = 7;

		state = E_MOVE;
		dir = LEFT;

		hp = 100;
		atk = 30;
		def = 30;

		exp = 100;
		break;
	}
	
	standardTime = GetTickCount();
	damageNumber = IMAGEMANAGER->FindImage("PlayerDamNumber");
	int realDamage = 0;

	isAlive = true;
	return true;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	if (isAlive)
	{
		if (state != E_DIE || state != E_ATTACK)
			Move();

		if (type == ARCHER)
		{
			if (bullet->GetisFire())
				bullet->Update();
		}

		switch (type)
		{
		case ZOMBIE:
			collision = RectMakeCenter(pos.x, pos.y, ZOMBIEWIDTH, ZOMBIEHEIGHT);
			searchArea = RectMakeCenter(pos.x, pos.y, ZOMBIEWIDTH * 6, ZOMBIEHEIGHT);
			break;
		case BAT:
			collision = RectMakeCenter(pos.x, pos.y, BATWIDTH, BATHEIGHT);
			searchArea = RectMakeCenter(pos.x, pos.y, BATWIDTH * 50, BATHEIGHT * 40);
			break;
		case ARCHER:
			collision = RectMakeCenter(pos.x, pos.y, ARCHERWIDTH, ARCHERHEIGHT);
			searchArea = RectMakeCenter(pos.x, pos.y, ARCHERWIDTH * 50, ARCHERHEIGHT * 2);
			break;
		case PERSEPHONE:
			collision = RectMakeCenter(pos.x, pos.y, PERSEPHONEWIDTH, PERSEPHONEHEIGHT);
			searchArea = RectMakeCenter(pos.x, pos.y, PERSEPHONEWIDTH * 25, PERSEPHONEHEIGHT * 5);

			switch (dir)
			{
			case RIGHT:
				hitBox = RectMake(pos.x, pos.y - KICKYMODIFY, KICKWIDTH, KICKHEIGHT);
				break;
			case LEFT:
				hitBox = RectMake(pos.x - KICKWIDTH, pos.y - KICKYMODIFY, KICKWIDTH, KICKHEIGHT);
				break;
			}
			break;
		}
	}
}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		img->AniRender(hdc, pos.x - img->GetFrameWidth() / 2 - CAMERA->getPosition()->x,
			pos.y - img->GetFrameHeight() / 2 - CAMERA->getPosition()->y, ani);

		if (KEYMANAGER->isToggleKey(VK_F3))
		{
			Rectangle(hdc, collision.left - CAMERA->getPosition()->x, collision.top - CAMERA->getPosition()->y,
				collision.right - CAMERA->getPosition()->x, collision.bottom - CAMERA->getPosition()->y);
			RectToLine(hdc, &searchArea, CAMERA->getPosition()->x, CAMERA->getPosition()->y);
			Rectangle(hdc, hitBox.left - CAMERA->getPosition()->x, hitBox.top - CAMERA->getPosition()->y,
				hitBox.right - CAMERA->getPosition()->x, hitBox.bottom - CAMERA->getPosition()->y);
		}

		if (type == ARCHER)
		{
			if (bullet->GetisFire())
				bullet->Render(hdc);
		}

		nowTime = GetTickCount();
		if (nowTime - standardTime < 300)
		{
			switch (type)
			{
			case ZOMBIE:
				TXTDATA->RenderNumber(hdc, realDamage, damageNumber, pos.x - CAMERA->getPosition()->x, pos.y - ZOMBIEHEIGHT - CAMERA->getPosition()->y);
				break;
			case BAT:
				TXTDATA->RenderNumber(hdc, realDamage, damageNumber, pos.x - CAMERA->getPosition()->x, pos.y - BATHEIGHT - CAMERA->getPosition()->y);
				break;
			case ARCHER:
				TXTDATA->RenderNumber(hdc, realDamage, damageNumber, pos.x - CAMERA->getPosition()->x, pos.y - ARCHERHEIGHT - CAMERA->getPosition()->y);
				break;
			case PERSEPHONE:
				TXTDATA->RenderNumber(hdc, realDamage, damageNumber, pos.x - CAMERA->getPosition()->x, pos.y - PERSEPHONEHEIGHT - CAMERA->getPosition()->y);
				break;
			}
		}
	}
}

void Enemy::Move()
{
	switch (type)
	{
	case ZOMBIE:
		switch (state)
		{
		case E_STAND:
			break;
		case ZOMBIE_RISEUP:
			if (!ani->isPlay())
				ChangeState(E_MOVE);
			break;
		case ZOMBIE_RISEDOWN:
			if (!ani->isPlay())
				ChangeState(E_STAND);
			break;
		case E_MOVE:
			switch (dir)
			{
			case RIGHT:
				pos.x += speed;
				break;
			case LEFT:
				pos.x -= speed;
				break;
			}
			break;
		case E_DIE:
			if (!ani->isPlay())
				isAlive = false;
		}
		break;
	case BAT:
		switch (state)
		{
		case E_STAND:
			break;
		case E_DIE:
			isAlive = false;
			break;
		case E_MOVE:
			CheckDir();
			ChangeState(E_MOVE);
			
			float x = static_cast<float>(PLAYER->GetX());
			float y = static_cast<float>(PLAYER->GetY());
			float angle = UTIL::getAngle(static_cast<float>(pos.x), static_cast<float>(pos.y), x, y);
			pos.x += cosf(angle) * speed;
			pos.y += -sinf(angle) * speed;
			break;
		}
		break;
	case ARCHER:
		switch (state)
		{
		case E_MOVE:
			if (abs(PLAYER->GetX() - pos.x) <= 700)
			{
				CheckDir();
				ChangeState(E_MOVE);

				if (pos.x > PLAYER->GetX() - 500)
					pos.x -= speed;
				else
					pos.x += speed;
			}
			break;
		case E_ATTACK:
			if (!ani->isPlay())
			{
				bullet->SetDir(dir);
				bullet->SetFire(pos);
				ChangeState(ARCHER_RELOAD);
			}
			break;
		case ARCHER_RELOAD:
			if (!ani->isPlay())
				ChangeState(E_MOVE);
			break;
		case E_DIE:
			isAlive = false;
			break;
		}
		break;
	case PERSEPHONE:
		switch (state)
		{
		case E_MOVE:
		pos.x += speed * dir;

			if (ani->getFrameNum() >= 4)
			{
				switch (dir)
				{
				case RIGHT:
					dir = LEFT;
					break;
				case LEFT:
					dir = RIGHT;
					break;
				}
			}
			break;
		case PERSEPHONE_BOW:
			if (!ani->isPlay())
			{
				if (pos.x >= PLAYER->GetX())
				{
					dir = LEFT;
					ChangeState(PERSEPHONE_COMBAT);
				}
				else
				{
					dir = RIGHT;
					ChangeState(PERSEPHONE_COMBAT);
				}
			}
			break;
		case PERSEPHONE_COMBAT:
			if (abs(PLAYER->GetX() - pos.x) <= 80)
			{
				CheckDir();
				ChangeState(E_ATTACK);
			}
			else
				pos.x += speed * dir;

			break;
		case E_ATTACK:
			if (!ani->isPlay())
			{
				CheckDir();
				ChangeState(PERSEPHONE_COMBAT);
			}
			break;
		case E_DIE:
			if (!ani->isPlay())
				isAlive = false;
		}
		break;
	}
}

void Enemy::ChangeState(Enemy_State _state)
{
	state = _state;

	switch (state)
	{
	case E_STAND:
		switch (type)
		{
		case ZOMBIE:
			switch (dir)
			{
			case RIGHT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ZombieRise");
				ani = ANIMANAGER->FindAni("ZombieRiseUpRAni");
				break;
			case LEFT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ZombieRise");
				ani = ANIMANAGER->FindAni("ZombieRiseUpLAni");
				break;
			}
			break;
		case BAT:
			AniPause();
			img = IMAGEMANAGER->FindImage("BatStand");
			ani = ANIMANAGER->FindAni("BatStandAni");
			ANIMANAGER->Resume("BatStandAni");
			break;
		}
		break;
	case E_MOVE:
		switch (type)
		{
		case ZOMBIE:
			switch (dir)
			{
			case RIGHT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ZombieMove");
				ani = ANIMANAGER->FindAni("ZombieMoveRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("ZombieMoveRAni");
				break;
			case LEFT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ZombieMove");
				ani = ANIMANAGER->FindAni("ZombieMoveLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("ZombieMoveLAni");
				break;
			}
			break;
		case BAT:
			switch (dir)
			{
			case RIGHT:
				AniPause();
				img = IMAGEMANAGER->FindImage("BatMove");
				ani = ANIMANAGER->FindAni("BatMoveRAni");
				ANIMANAGER->Resume("BatMoveRAni");
				break;
			case LEFT:
				AniPause();
				img = IMAGEMANAGER->FindImage("BatMove");
				ani = ANIMANAGER->FindAni("BatMoveLAni");
				ANIMANAGER->Resume("BatMoveLAni");
				break;
			}
			break;
		case ARCHER:
			switch (dir)
			{
			case RIGHT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ArcherMove");
				ani = ANIMANAGER->FindAni("ArcherMoveRAni");
				ANIMANAGER->Resume("ArcherMoveRAni");
				break;
			case LEFT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ArcherMove");
				ani = ANIMANAGER->FindAni("ArcherMoveLAni");
				ANIMANAGER->Resume("ArcherMoveLAni");
				break;
			}
			break;
		case PERSEPHONE:
			switch (dir)
			{
			case RIGHT:
				AniPause();
				img = IMAGEMANAGER->FindImage("PersephoneMove");
				ani = ANIMANAGER->FindAni("PersephoneMoveRAni");
				ANIMANAGER->Resume("PersephoneMoveRAni");

				speed = 7;
				break;
			case LEFT:
				AniPause();
				img = IMAGEMANAGER->FindImage("PersephoneMove");
				ani = ANIMANAGER->FindAni("PersephoneMoveLAni");
				ANIMANAGER->Resume("PersephoneMoveLAni");

				speed = 7;
				break;
			}
			break;
		}
		break;
	case E_ATTACK:
		switch (type)
		{
		case ARCHER:
			SOUNDMANAGER->Play(TEXT("Bow"), 0.5f);
			switch (dir)
			{
			case RIGHT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ArcherAttack");
				ani = ANIMANAGER->FindAni("ArcherAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("ArcherAttackRAni");
				break;
			case LEFT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ArcherAttack");
				ani = ANIMANAGER->FindAni("ArcherAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("ArcherAttackLAni");
				break;
			}
			break;
		case PERSEPHONE:
			switch (dir)
			{
			case RIGHT:
				AniPause();
				img = IMAGEMANAGER->FindImage("PersephoneAttack");
				ani = ANIMANAGER->FindAni("PersephoneAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("PersephoneAttackRAni");
				break;
			case LEFT:
				AniPause();
				img = IMAGEMANAGER->FindImage("PersephoneAttack");
				ani = ANIMANAGER->FindAni("PersephoneAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("PersephoneAttackLAni");
				break;
			}
			break;
		}
		break;
	case E_DIE:
		switch (type)
		{
		case ZOMBIE:
			switch (dir)
			{
			case RIGHT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ZombieDie");
				ani = ANIMANAGER->FindAni("ZombieDieRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("ZombieDieRAni");
				break;
			case LEFT:
				AniPause();
				img = IMAGEMANAGER->FindImage("ZombieDie");
				ani = ANIMANAGER->FindAni("ZombieDieLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("ZombieDieLAni");
				break;
			}
			break;
		case PERSEPHONE:
			AniPause();
			img = IMAGEMANAGER->FindImage("PersephoneDie");
			ani = ANIMANAGER->FindAni("PersephoneDieAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("PersephoneDieAni");
			break;
		}
		break;
	case ZOMBIE_RISEUP:
		switch (dir)
		{
		case RIGHT:
			AniPause();
			img = IMAGEMANAGER->FindImage("ZombieRise");
			ani = ANIMANAGER->FindAni("ZombieRiseUpRAni");

			if(!ani->isPlay())
				ANIMANAGER->Start("ZombieRiseUpRAni");
			break;
		case LEFT:
			AniPause();
			img = IMAGEMANAGER->FindImage("ZombieRise");
			ani = ANIMANAGER->FindAni("ZombieRiseUpLAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("ZombieRiseUpLAni");
			break;
		}
		break;
	case ZOMBIE_RISEDOWN:
		switch (dir)
		{
		case RIGHT:
			AniPause();
			img = IMAGEMANAGER->FindImage("ZombieRise");
			ani = ANIMANAGER->FindAni("ZombieRiseDownRAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("ZombieRiseDownRAni");
			break;
		case LEFT:
			AniPause();
			img = IMAGEMANAGER->FindImage("ZombieRise");
			ani = ANIMANAGER->FindAni("ZombieRiseDownLAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("ZombieRiseDownLAni");
			break;
		}
		break;
	case ARCHER_RELOAD:
		switch (dir)
		{
		case RIGHT:
			AniPause();
			img = IMAGEMANAGER->FindImage("ArcherReload");
			ani = ANIMANAGER->FindAni("ArcherReloadRAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("ArcherReloadRAni");
			break;
		case LEFT:
			AniPause();
			img = IMAGEMANAGER->FindImage("ArcherReload");
			ani = ANIMANAGER->FindAni("ArcherReloadLAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("ArcherReloadLAni");
			break;
		}
		break;
	case PERSEPHONE_BOW:
		switch (dir)
		{
		case RIGHT:
			AniPause();
			img = IMAGEMANAGER->FindImage("PersephoneBow");
			ani = ANIMANAGER->FindAni("PersephoneBowRAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("PersephoneBowRAni");
			break;
		case LEFT:
			AniPause();
			img = IMAGEMANAGER->FindImage("PersephoneBow");
			ani = ANIMANAGER->FindAni("PersephoneBowLAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("PersephoneBowLAni");
			break;
		}
		break;
	case PERSEPHONE_COMBAT:
		switch (dir)
		{
		case RIGHT:
			AniPause();
			img = IMAGEMANAGER->FindImage("PersephoneCombatMove");
			ani = ANIMANAGER->FindAni("PersephoneCombatMoveRAni");
			ANIMANAGER->Resume("PersephoneCombatMoveRAni");

			speed = 5;
			break;
		case LEFT:
			AniPause();
			img = IMAGEMANAGER->FindImage("PersephoneCombatMove");
			ani = ANIMANAGER->FindAni("PersephoneCombatMoveLAni");
			ANIMANAGER->Resume("PersephoneCombatMoveLAni");

			speed = 5;
			break;
		}
		break;
	}
}

void Enemy::AniPause()
{
	switch (type)
	{
	case ZOMBIE:
		switch (dir)
		{
		case RIGHT:
			ANIMANAGER->Stop("ZombieRiseUpRAni");
			ANIMANAGER->Pause("ZombieMoveRAni");
			ANIMANAGER->Stop("ZombieRiseDownRAni");
			ANIMANAGER->Stop("ZombieDieRAni");
			break;
		case LEFT:
			ANIMANAGER->Stop("ZombieRiseUpLAni");
			ANIMANAGER->Pause("ZombieMoveLAni");
			ANIMANAGER->Stop("ZombieRiseDownLAni");
			ANIMANAGER->Stop("ZombieDieLAni");
			break;
		}
		break;
	case BAT:
		switch (dir)
		{
		case RIGHT:
			ANIMANAGER->Pause("BatMoveRAni");
			ANIMANAGER->Pause("BatStandAni");
			break;
		case LEFT:
			ANIMANAGER->Pause("BatMoveLAni");
			ANIMANAGER->Pause("BatStandAni");
			break;
		}
		break;
	case ARCHER:
		switch (dir)
		{
		case RIGHT:
			ANIMANAGER->Pause("ArcherMoveRAni");
			ANIMANAGER->Pause("ArcherAttackRAni");
			ANIMANAGER->Pause("ArcherReloadRAni");
			break;
		case LEFT:
			ANIMANAGER->Pause("ArcherMoveLAni");
			ANIMANAGER->Pause("ArcherAttackLAni");
			ANIMANAGER->Pause("ArcherReloadLAni");
			break;
		}
		break;
	case PERSEPHONE:
		switch (dir)
		{
		case RIGHT:
			ANIMANAGER->Pause("PersephoneMoveRAni");
			ANIMANAGER->Pause("PersephoneBowRAni");
			ANIMANAGER->Pause("PersephoneCombatMoveRAni");
			ANIMANAGER->Pause("PersephoneAttackRAni");
			ANIMANAGER->Pause("PersephoneDieAni");
			break;
		case LEFT:
			ANIMANAGER->Pause("PersephoneMoveLAni");
			ANIMANAGER->Pause("PersephoneBowLAni");
			ANIMANAGER->Pause("PersephoneCombatMoveLAni");
			ANIMANAGER->Pause("PersephoneAttackLAni");
			ANIMANAGER->Pause("PersephoneDieAni");
			break;
		}
		break;
	}
}

void Enemy::Damage(int _damage)
{
	standardTime = GetTickCount();

	realDamage = _damage - def;

	if (realDamage < 0)
		realDamage = 0;

	hp -= realDamage;

	if (hp <= 0)
	{
		ChangeState(E_DIE);
		isAlive = false;
		PLAYER->PlusExp(exp);
		SOUNDMANAGER->Play(TEXT("Burn"), 0.5f);
		EFFECTMANAGER->Play(TEXT("BurnEnemyEffect"), { pos.x - CAMERA->getPosition()->x, pos.y - CAMERA->getPosition()->y });
	}
}

void Enemy::CheckSearch(POINT _pos)
{
	if (PtInRect(&searchArea, _pos))
	{
		switch (type)
		{
		case ZOMBIE:
			ChangeState(ZOMBIE_RISEUP);
			break;
		case BAT:
			ChangeState(E_MOVE);
			break;
		case PERSEPHONE:
			break;
		}
	}
	else
	{
		switch (type)
		{
		case ZOMBIE:
			if(state == E_MOVE)
				ChangeState(ZOMBIE_RISEDOWN);
			break;
		case PERSEPHONE:
			break;
		}
	}
}

void Enemy::CheckDir()
{
	if (PLAYER->GetX() >= pos.x)
		dir = RIGHT;
	else
		dir = LEFT;
}
