#include "Game.h"
#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::Init()
{
	img = IMAGEMANAGER->FindImage("PlayerStand");
	ani = ANIMANAGER->FindAni("PStandRAni");
	weaponImg = IMAGEMANAGER->FindImage("Axe");
	weaponAni = ANIMANAGER->FindAni("AxeRAni");
	damageNumber = IMAGEMANAGER->FindImage("EnemyDamNumber");
	hpUI = IMAGEMANAGER->FindImage("HPUI");
	number = IMAGEMANAGER->FindImage("MenuNumber");

	pos.x = PSTARTX;
	pos.y = PSTARTY;
	dir = RIGHT;
	state = STAND;

	gravity = 1;
	jumpPower = 0;

	jumped = false;

	ANIMANAGER->Start("PStandRAni");

	colBox = RectMakeCenter(pos.x, pos.y, BOXWIDTH, BOXHEIGHT);
	hitBox = RectMakeCenter(0, 0, 0, 0);

	//기본 방어구 clothes
	currentArmor = 6;
	if(!SearchItem(6))
		vInventory.push_back(6);

	//기본 무기 dagger
	currentWeapon = 1;
	if (!SearchItem(1))
		vInventory.push_back(1);

	//메뉴 테스트용
	/*vInventory.push_back(2);
	vInventory.push_back(3);
	vInventory.push_back(4);
	vInventory.push_back(5);
	vInventory.push_back(7);
	vInventory.push_back(8);
	vInventory.push_back(9);*/

	info.level = 1;
	info.maxHP = 95 + info.level * info.level * 5;
	info.hp = info.maxHP;
	info.STR = 9 + info.level;
	info.CON = 9 + info.level;
	info.ATK[0] = info.STR + 5;
	info.ATK[1] = EQUIPMENT->GetInfo(1)->atk;
	info.DEF[0] = info.CON + 2;
	info.DEF[1] = EQUIPMENT->GetInfo(6)->def;
	info.gold = 0;
	info.exp = 0;

	speed = 7;

	realDamage = 0;

	gameOver = false;
	standardTime = GetTickCount();

	for (int i = 0; i < MAXLEVEL; i++)
		expTable[i] = (i + 1) * (i + 1) * 100;
	info.leftExp = expTable[0];

	hBrush = CreateSolidBrush(RGB(255, 0, 0));

	isMovable = false;

	return true;
}

void Player::Release()
{
	vInventory.clear();
	getSingleton()->releaseSingleton();
}

void Player::Update()
{
	if (!gameOver)
	{
		WChangeTest();

		if(isMovable)
			Move();

		if (state == ATTACK || state == JUMPATTACK)
		{
			WeaponStart();

			if (ani->getFrameNum() >= 5 && ani->getFrameNum() <= 9)
				SetHitBox();

			if (!weaponAni->isPlay())
				weaponAni->setFrameNum(0);
		}
		else
			hitBox = RectMakeCenter(0, 0, 0, 0);

		if(state == DIE)
			Die();

		colBox = RectMakeCenter(pos.x, pos.y, BOXWIDTH, BOXHEIGHT);
	}
}

void Player::Render(HDC hdc)
{
	img->AniRender(hdc, pos.x - img->GetFrameWidth() / 2 - CAMERA->getPosition()->x, pos.y - img->GetFrameHeight() / 2 - CAMERA->getPosition()->y, ani);
	
	RenderHPBar(hdc);
	hpUI->Render(hdc, 10, 10);
	TXTDATA->RenderNumber(hdc, info.hp, number, 30, 30);

	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		Rectangle(hdc, colBox.left - CAMERA->getPosition()->x, colBox.top - CAMERA->getPosition()->y, 
			colBox.right - CAMERA->getPosition()->x, colBox.bottom - CAMERA->getPosition()->y);
		Rectangle(hdc, hitBox.left - CAMERA->getPosition()->x, hitBox.top - CAMERA->getPosition()->y, 
			hitBox.right - CAMERA->getPosition()->x, hitBox.bottom - CAMERA->getPosition()->y);
	}

	if (state == ATTACK || state == JUMPATTACK)
	{
		if (ani->getFrameNum() >= 5 && ani->getFrameNum() <= 9)
			WeaponRender(hdc);
	}

	if (nowTime - standardTime < 300)
		TXTDATA->RenderNumber(hdc, realDamage, damageNumber, pos.x - CAMERA->getPosition()->x, pos.y - BOXHEIGHT - CAMERA->getPosition()->y);
}

void Player::Move()
{
	if (state != ATTACK && state != DAMAGE && state != DIE)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			dir = LEFT;

			AniPause();
			if (state != JUMP)
				ChangeState(RUN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			AniPause();
			if (state != JUMP)
				ChangeState(STAND);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			dir = RIGHT;
			
			AniPause();
			if (state != JUMP)
				ChangeState(RUN);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			AniPause();
			if (state != JUMP)
				ChangeState(STAND);
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		AniPause();
		if (state != JUMP)
			ChangeState(SIT);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		AniPause();
		if (state != JUMP)
			ChangeState(STAND);
	}

	//점프
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (!jumped)
		{
			AniPause();
			ChangeState(JUMP);

			jumpPower = 24;
			gravity = 1;

			jumped = true;
		}
	}

	//공격
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		AniPause();

		if (state == JUMP)
		{
			if (jumpPower >= 0)
			{
				AniPause();
				ChangeState(JUMPATTACK);
				WeaponSet();
			}
		}
		else
			ChangeState(ATTACK);
		WeaponSet();
	}

	if (!ani->isPlay())
	{
		if (state == ATTACK || state == DAMAGE)
			ChangeState(STAND);
		else if (state == JUMPATTACK)
			ChangeState(JUMP);
	}
}

void Player::Jump()
{
	pos.y -= jumpPower;
	jumpPower -= gravity;
}

void Player::Buy(int _id, int _price)
{
	std::vector<int>::iterator it;
	int count = 0;

	for (it = vInventory.begin(); it != vInventory.end(); it++)
	{
		if ((*it) == _id)
			count++;
	}

	if (count == 0)
	{
		vInventory.push_back(_id);
		SOUNDMANAGER->Play(TEXT("Buy"), 0.5f);
		MinusGold(_price);
	}
	else
		SOUNDMANAGER->Play(TEXT("Back"), 0.5f);
}

void Player::AniPause()
{
	ANIMANAGER->Pause("PStandRAni");
	ANIMANAGER->Pause("PStandLAni");
	ANIMANAGER->Pause("PRunRAni");
	ANIMANAGER->Pause("PRunLAni");
	ANIMANAGER->Pause("PJumpRAni");
	ANIMANAGER->Pause("PJumpLAni");
}

void Player::ChangeState(PLAYER_STATE _state)
{
	state = _state;
	switch (state)
	{
	case STAND:
		switch (dir)
		{
		case RIGHT:
			img = IMAGEMANAGER->FindImage("PlayerStand");
			ani = ANIMANAGER->FindAni("PStandRAni");
			ANIMANAGER->Resume("PStandRAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("PStandRAni");
			break;
		case LEFT:
			img = IMAGEMANAGER->FindImage("PlayerStand");
			ani = ANIMANAGER->FindAni("PStandLAni");
			ANIMANAGER->Resume("PStandLAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("PStandLAni");
			break;
		}
		break;
	case RUN:
		switch (dir)
		{
		case RIGHT:
			img = IMAGEMANAGER->FindImage("PlayerRun");
			ani = ANIMANAGER->FindAni("PRunRAni");
			ANIMANAGER->Resume("PRunRAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("PRunRAni");
			break;
		case LEFT:
			img = IMAGEMANAGER->FindImage("PlayerRun");
			ani = ANIMANAGER->FindAni("PRunLAni");
			ANIMANAGER->Resume("PRunLAni");

			if (!ani->isPlay())
				ANIMANAGER->Start("PRunLAni");
			break;
		}
		break;
	case JUMP:
		switch (dir)
		{
		case RIGHT:
			img = IMAGEMANAGER->FindImage("PlayerJump");
			ani = ANIMANAGER->FindAni("PJumpRAni");
			if (!ani->isPlay())
				ANIMANAGER->Start("PJumpRAni");
			break;
		case LEFT:
			img = IMAGEMANAGER->FindImage("PlayerJump");
			ani = ANIMANAGER->FindAni("PJumpLAni");
			if (!ani->isPlay())
				ANIMANAGER->Start("PJumpLAni");
			break;
		}
		break;
	case SIT:
		switch (dir)
		{
		case RIGHT:
			img = IMAGEMANAGER->FindImage("PlayerSit");
			ani = ANIMANAGER->FindAni("PSitRAni");
			if (!ani->isPlay())
				ANIMANAGER->Start("PSitRAni");
			break;
		case LEFT:
			img = IMAGEMANAGER->FindImage("PlayerSit");
			ani = ANIMANAGER->FindAni("PSitLAni");
			if (!ani->isPlay())
				ANIMANAGER->Start("PSitLAni");
			break;
		}
		break;
	case JUMPATTACK:
		switch (dir)
		{
		case RIGHT:
			img = IMAGEMANAGER->FindImage("PlayerJumpAttack");
			break;
		case LEFT:
			img = IMAGEMANAGER->FindImage("PlayerJumpAttack");
			break;
		}
		break;
	case ATTACK:
		switch (dir)
		{
		case RIGHT:
			img = IMAGEMANAGER->FindImage("PlayerAttack");
			break;
		case LEFT:
			img = IMAGEMANAGER->FindImage("PlayerAttack");
			break;
		}
		break;
	case DAMAGE:
		switch (dir)
		{
		case RIGHT:
			img = IMAGEMANAGER->FindImage("PlayerDamage");
			ani = ANIMANAGER->FindAni("PDamageRAni");
			if (!ani->isPlay())
				ANIMANAGER->Start("PDamageRAni");
			break;
		case LEFT:
			img = IMAGEMANAGER->FindImage("PlayerDamage");
			ani = ANIMANAGER->FindAni("PDamageLAni");
			if (!ani->isPlay())
				ANIMANAGER->Start("PDamageLAni");
			break;
		}
		break;
	case DIE:
		switch (dir)
		{
		case RIGHT:
			img = IMAGEMANAGER->FindImage("PlayerDie");
			ani = ANIMANAGER->FindAni("PDieRAni");
			if (!ani->isPlay())
				ANIMANAGER->Start("PDieRAni");
			break;
		case LEFT:
			img = IMAGEMANAGER->FindImage("PlayerDie");
			ani = ANIMANAGER->FindAni("PDieLAni");
			if (!ani->isPlay())
				ANIMANAGER->Start("PDieLAni");
			break;
		}
		break;
	}
}

void Player::FinJump()
{
	ChangeState(STAND);
	jumped = false;
}

void Player::Damage(int _damage, POINT _effectPos)
{
	standardTime = GetTickCount();

	realDamage = _damage - (info.DEF[0] + info.DEF[1]);

	if (realDamage < 0)
		realDamage = 0;

	info.hp -= realDamage;

	AniPause();

	if (state == JUMP)
		FinJump();

	if (info.hp <= 0)
	{
		info.hp = 0;
		ChangeState(DIE);
		jumpPower = 8;
		gravity = 1;
	}
	else
	{
		ChangeState(DAMAGE);
		SOUNDMANAGER->Play(TEXT("Hit"), 0.5f);
		EFFECTMANAGER->Play(TEXT("HitEffect"), { _effectPos.x - CAMERA->getPosition()->x, _effectPos.y - CAMERA->getPosition()->y });
	}
}

void Player::Die()
{
	pos.x -= 3 * dir;
	pos.y -= jumpPower;
	jumpPower -= gravity;

	if (!ani->isPlay())
	{
		SOUNDMANAGER->Pause(TEXT("Bgm"));
		SOUNDMANAGER->Play(TEXT("GameOverBgm"), 0.5f);
		gameOver = true;
		SCENEMANAGER->ChangeScene(TEXT("GameOver"));
	}
}

void Player::WeaponChange()
{
	info.ATK[1] = EQUIPMENT->GetInfo(currentWeapon)->atk;
}

void Player::ArmorChange()
{
	info.DEF[1] = EQUIPMENT->GetInfo(currentArmor)->def;
}

void Player::WeaponSet()
{
	switch (currentWeapon)
	{
	case 1:
		weaponImg = IMAGEMANAGER->FindImage("Dagger");

		switch (dir)
		{
		case RIGHT:
			weaponAni = ANIMANAGER->FindAni("DaggerRAni");

			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("DaggerAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("DaggerAttackRAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("DaggerJumpAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("DaggerJumpAttackRAni");
			}
			break;
		case LEFT:
			weaponAni = ANIMANAGER->FindAni("DaggerLAni");

			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("DaggerAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("DaggerAttackLAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("DaggerJumpAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("DaggerJumpAttackLAni");
			}
			break;
		}
		break;
	case 2:
		weaponImg = IMAGEMANAGER->FindImage("Sword");

		switch (dir)
		{
		case RIGHT:
			weaponAni = ANIMANAGER->FindAni("SwordRAni");

			if (state == ATTACK)
			{	
				ani = ANIMANAGER->FindAni("SwordAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("SwordAttackRAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("SwordJumpAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("SwordJumpAttackRAni");
			}
			break;
		case LEFT:
			weaponAni = ANIMANAGER->FindAni("SwordLAni");
			
			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("SwordAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("SwordAttackLAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("SwordJumpAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("SwordJumpAttackLAni");
			}
			break;
		}
		break;
	case 3:
		weaponImg = IMAGEMANAGER->FindImage("Spear");

		switch (dir)
		{
		case RIGHT:
			weaponAni = ANIMANAGER->FindAni("SpearRAni");

			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("SpearAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("SpearAttackRAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("SpearJumpAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("SpearJumpAttackRAni");
			}
			break;
		case LEFT:
			weaponAni = ANIMANAGER->FindAni("SpearLAni");

			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("SpearAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("SpearAttackLAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("SpearJumpAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("SpearJumpAttackLAni");
			}
			break;
		}
		break;
	case 4:
		weaponImg = IMAGEMANAGER->FindImage("Axe");

		switch (dir)
		{
		case RIGHT:
			weaponAni = ANIMANAGER->FindAni("AxeRAni");

			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("AxeAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("AxeAttackRAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("AxeJumpAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("AxeJumpAttackRAni");
			}
			break;
		case LEFT:
			weaponAni = ANIMANAGER->FindAni("AxeLAni");

			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("AxeAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("AxeAttackLAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("AxeJumpAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("AxeJumpAttackLAni");
			}
			break;
		}
		break;
	case 5:
		weaponImg = IMAGEMANAGER->FindImage("GreatSword");

		switch (dir)
		{
		case RIGHT:
			weaponAni = ANIMANAGER->FindAni("GSwordRAni");

			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("GSwordAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("GSwordAttackRAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("GSwordJumpAttackRAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("GSwordJumpAttackRAni");
			}
			break;
		case LEFT:
			weaponAni = ANIMANAGER->FindAni("GSwordLAni");

			if (state == ATTACK)
			{
				ani = ANIMANAGER->FindAni("GSwordAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("GSwordAttackLAni");
			}
			else
			{
				ani = ANIMANAGER->FindAni("GSwordJumpAttackLAni");

				if (!ani->isPlay())
					ANIMANAGER->Start("GSwordJumpAttackLAni");
			}
			break;
		}
		break;
	}
}

void Player::WeaponStart()
{
	switch (currentWeapon)
	{
	case 1:
		if (ani->getFrameNum() == 5)
		{
			SOUNDMANAGER->Play(TEXT("PAttackLight"), 0.5f);
			switch (dir)
			{
			case RIGHT:
				ANIMANAGER->Start("DaggerRAni");
				break;
			case LEFT:
				ANIMANAGER->Start("DaggerLAni");
				break;
			}
		}			
		break;
	case 2:
		if (ani->getFrameNum() == 5)
		{
			SOUNDMANAGER->Play(TEXT("PAttackHeavy"), 0.5f);
			switch (dir)
			{
			case RIGHT:
				ANIMANAGER->Start("SwordRAni");
				break;
			case LEFT:
				ANIMANAGER->Start("SwordLAni");
				break;
			}
		}
		break;
	case 3:
		if (ani->getFrameNum() == 5)
		{
			SOUNDMANAGER->Play(TEXT("PAttackLight"), 0.5f);
			switch (dir)
			{
			case RIGHT:
				ANIMANAGER->Start("SpearRAni");
				break;
			case LEFT:
				ANIMANAGER->Start("SpearLAni");
				break;
			}
		}
		break;
	case 4:
		if (ani->getFrameNum() == 5)
		{
			SOUNDMANAGER->Play(TEXT("PAttackHeavy"), 0.5f);
			switch (dir)
			{
			case RIGHT:
				ANIMANAGER->Start("AxeRAni");
				break;
			case LEFT:
				ANIMANAGER->Start("AxeLAni");
				break;
			}
		}
		break;
	case 5:
		if (ani->getFrameNum() == 5)
		{
			SOUNDMANAGER->Play(TEXT("PAttackHeavy"), 0.5f);
			switch (dir)
			{
			case RIGHT:
				ANIMANAGER->Start("GSwordRAni");
				break;
			case LEFT:
				ANIMANAGER->Start("GSwordLAni");
				break;
			}
		}
		break;
	}
}

void Player::WeaponRender(HDC hdc)
{
	switch (currentWeapon)
	{
	case 1:
		switch (dir)
		{
		case RIGHT:
			weaponImg->AniRender(hdc, pos.x + DAGGERX - CAMERA->getPosition()->x, 
				pos.y - DAGGERY - CAMERA->getPosition()->y, weaponAni);
			break;
		case LEFT:
			weaponImg->AniRender(hdc, pos.x - DAGGERX - weaponImg->GetFrameWidth() - CAMERA->getPosition()->x,
				pos.y - DAGGERY - CAMERA->getPosition()->y, weaponAni);
			break;
		}
		break;
	case 2:
		switch (dir)
		{
		case RIGHT:
			weaponImg->AniRender(hdc, pos.x + SWORDX - CAMERA->getPosition()->x,
				pos.y - SWORDY - CAMERA->getPosition()->y, weaponAni);
			break;
		case LEFT:
			weaponImg->AniRender(hdc, pos.x - SWORDX - weaponImg->GetFrameWidth() - CAMERA->getPosition()->x,
				pos.y - SWORDY - CAMERA->getPosition()->y, weaponAni);
			break;
		}
		break;
	case 3:
		switch (dir)
		{
		case RIGHT:
			weaponImg->AniRender(hdc, pos.x - SPEARX - CAMERA->getPosition()->x,
				pos.y - SPEARY - CAMERA->getPosition()->y, weaponAni);
			break;
		case LEFT:
			weaponImg->AniRender(hdc, pos.x + SPEARX - weaponImg->GetFrameWidth() - CAMERA->getPosition()->x,
				pos.y - SPEARY - CAMERA->getPosition()->y, weaponAni);
			break;
		}
		break;
	case 4:
		switch (dir)
		{
		case RIGHT:
			weaponImg->AniRender(hdc, pos.x + AXEX - CAMERA->getPosition()->x,
				pos.y - AXEY - CAMERA->getPosition()->y, weaponAni);
			break;
		case LEFT:
			weaponImg->AniRender(hdc, pos.x - AXEX - weaponImg->GetFrameWidth() - CAMERA->getPosition()->x,
				pos.y - AXEY - CAMERA->getPosition()->y, weaponAni);
			break;
		}
		break;
	case 5:
		switch (dir)
		{
		case RIGHT:
			weaponImg->AniRender(hdc, pos.x + GSWORDX - CAMERA->getPosition()->x,
				pos.y - GSWORDY - CAMERA->getPosition()->y, weaponAni);
			break;
		case LEFT:
			weaponImg->AniRender(hdc, pos.x - GSWORDX - weaponImg->GetFrameWidth() - CAMERA->getPosition()->x,
				pos.y - GSWORDY - CAMERA->getPosition()->y, weaponAni);
			break;
		}
		break;
	}
}

void Player::SetHitBox()
{
	switch (currentWeapon)
	{
	case 1:
		switch (dir)
		{
		case RIGHT:
			hitBox = RectMake(pos.x + DAGGERX, pos.y - DAGGERY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		case LEFT:
			hitBox = RectMake(pos.x - DAGGERX - weaponImg->GetFrameWidth(), pos.y - DAGGERY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		}
		break;
	case 2:
		switch (dir)
		{
		case RIGHT:
			hitBox = RectMake(pos.x + SWORDX, pos.y - SWORDY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		case LEFT:
			hitBox = RectMake(pos.x - SWORDX - weaponImg->GetFrameWidth(), pos.y - SWORDY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		}
		break;
	case 3:
		switch (dir)
		{
		case RIGHT:
			hitBox = RectMake(pos.x - SPEARX, pos.y - SPEARY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		case LEFT:
			hitBox = RectMake(pos.x + SPEARX - weaponImg->GetFrameWidth(), pos.y - SPEARY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		}
		break;
	case 4:
		switch (dir)
		{
		case RIGHT:
			hitBox = RectMake(pos.x + AXEX, pos.y - AXEY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		case LEFT:
			hitBox = RectMake(pos.x - AXEX - weaponImg->GetFrameWidth(), pos.y - AXEY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		}
		break;
	case 5:
		switch (dir)
		{
		case RIGHT:
			hitBox = RectMake(pos.x + GSWORDX, pos.y - GSWORDY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		case LEFT:
			hitBox = RectMake(pos.x - GSWORDX - weaponImg->GetFrameWidth(), pos.y - GSWORDY, weaponImg->GetFrameWidth(), weaponImg->GetFrameHeight());
			break;
		}
		break;
	}
}

void Player::WChangeTest()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		PlusExp(100);
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		PlusGold(500);
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		Damage(50, pos);
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		currentWeapon = 1;
		WeaponChange();
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		currentWeapon = 2;
		WeaponChange();
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		currentWeapon = 3;
		WeaponChange();
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		currentWeapon = 4;
		WeaponChange();
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		currentWeapon = 5;
		WeaponChange();
	}
}

void Player::PlusExp(int _exp)
{
	info.exp += _exp;

	if (expTable[info.level - 1] <= info.exp)
	{
		info.leftExp = expTable[info.level] - info.exp;

		LevelUp();
		EFFECTMANAGER->Play(TEXT("LevelUpEffect"), { pos.x - CAMERA->getPosition()->x, pos.y - BOXHEIGHT - CAMERA->getPosition()->y });
	}
	else
		info.leftExp = expTable[info.level - 1] - info.exp;
}

void Player::LevelUp()
{
	info.level++;

	info.maxHP = 95 + info.level * info.level * 5;
	info.hp = info.maxHP;
	info.STR = 9 + info.level;
	info.CON = 9 + info.level;
	info.ATK[0] = info.STR + 5;
	info.DEF[0] = info.CON + 2;
}

void Player::RenderHPBar(HDC hdc)
{
	hpBar = RectMake(HPSTARTX, HPSTARTY, (float)info.hp / (float)info.maxHP * HPWIDTH, HPHEIGHT);

	Rectangle(hdc, hpBar.left, hpBar.top, hpBar.right, hpBar.bottom);
	FillRect(hdc, &hpBar, hBrush);
}

int Player::GetInventoryItem(int _i)
{
	std::vector<int>::iterator it;
	int count = 0;

	for (it = vInventory.begin(); it != vInventory.end(); it++)
	{
		if (count == _i)
			return (*it);
		else
			count++;	
	}

	return 0;
}

void Player::AddItem(int _id)
{
	std::vector<int>::iterator it;
	int count = 0;

	for (it = vInventory.begin(); it != vInventory.end(); it++)
	{
		if ((*it) == _id)
			count++;
	}

	if (count == 0)
		vInventory.push_back(_id);

}

bool Player::SearchItem(int _id)
{
	std::vector<int>::iterator it;
	int count = 0;

	for (it = vInventory.begin(); it != vInventory.end(); it++)
	{
		if ((*it) == _id)
			count++;
	}

	if (count == 0)
		return false;
	else
		return true;
}

void Player::PresetLevel(int _exp)
{
	info.exp += _exp;

	while (expTable[info.level - 1] <= info.exp)
	{
		if (expTable[info.level - 1] <= info.exp)
		{
			info.leftExp = expTable[info.level] - info.exp;

			LevelUp();
		}
		else
			info.leftExp = expTable[info.level - 1] - info.exp;
	}
}
