#include "Game.h"
#include "MainGame.h"
#include "StartScene.h"
#include "Room1.h"
#include "Room2.h"
#include "Room3.h"
#include "Room4.h"
#include "Room5.h"
#include "Room6.h"
#include "Room7.h"
#include "Room8.h"
#include "Room9.h"
#include "Room10.h"
#include "Room11.h"
#include "Room12.h"
#include "Room13.h"
#include "GameOver.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

bool MainGame::Init()
{
	GameNode::Init(true);			//GameNode가 가상 클래스이기에 명시적으로 호출해야 한다.

	/*=====초 기 화=====*/

	//이미지 매니저 초기화
	IMAGEMANAGER->Init();

	//이미지 추가
	IMAGEMANAGER->AddFrameImage(TEXT("StartBackground"), TEXT("Image/main.bmp"), WINSIZEX * 2, WINSIZEY, 2, 1, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("NewGame"), TEXT("Image/newgame.bmp"), 200, 96, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("LoadGame"), TEXT("Image/loadgame.bmp"), 200, 96, true, COLOR_M);

	IMAGEMANAGER->AddImage(TEXT("Sky"), TEXT("Image/background.bmp"), WINSIZEX + 25, WINSIZEY + 10, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Castle"), TEXT("Image/castle.bmp"), WINSIZEX, 3085, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Wall"), TEXT("Image/wall.bmp"), 7600, WINSIZEY, true, COLOR_M);

	IMAGEMANAGER->AddImage(TEXT("Room1"), TEXT("Image/room/room1.bmp"), 2320, 2640, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room2"), TEXT("Image/room/room2.bmp"), 6400, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room3"), TEXT("Image/room/room3.bmp"), 2560, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room4"), TEXT("Image/room/room4.bmp"), 1200, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room5"), TEXT("Image/room/room5.bmp"), 2560, 2075, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room6"), TEXT("Image/room/room6.bmp"), 1200, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room7"), TEXT("Image/room/room7.bmp"), 3840, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room8"), TEXT("Image/room/room8.bmp"), 2560, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room9"), TEXT("Image/room/room9.bmp"), 1200, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room10"), TEXT("Image/room/room10.bmp"), 1200, 2075, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room11"), TEXT("Image/room/room11.bmp"), 1200, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room12"), TEXT("Image/room/room12.bmp"), 1380, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room13"), TEXT("Image/room/room13.bmp"), 1200, 4115, true, RGB(0, 255, 0));

	IMAGEMANAGER->AddImage(TEXT("Room1pixel"), TEXT("Image/room/pixelroom1.bmp"), 2320, 2640, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room2pixel"), TEXT("Image/room/pixelroom2.bmp"), 6400, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room3pixel"), TEXT("Image/room/pixelroom3.bmp"), 2560, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room5pixel"), TEXT("Image/room/pixelroom5.bmp"), 2560, 2075, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room6pixel"), TEXT("Image/room/pixelroom6.bmp"), 1200, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room7pixel"), TEXT("Image/room/pixelroom7.bmp"), 3840, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room8pixel"), TEXT("Image/room/pixelroom8.bmp"), 2560, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room9pixel"), TEXT("Image/room/pixelroom9_2.bmp"), 1200, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room10pixel"), TEXT("Image/room/pixelroom10.bmp"), 1200, 2075, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room11pixel"), TEXT("Image/room/pixelroom11.bmp"), 1200, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room12pixel"), TEXT("Image/room/pixelroom12.bmp"), 1380, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddImage(TEXT("Room13pixel"), TEXT("Image/room/pixelroom13.bmp"), 1200, 4115, true, RGB(0, 255, 0));

	IMAGEMANAGER->AddFrameImage(TEXT("Merchant"), TEXT("Image/yoko.bmp"), 170, 170, 2, 1, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("ShopMenu"), TEXT("Image/shopMenu.bmp"), 1200, 800, true, RGB(0, 255, 0));
	IMAGEMANAGER->AddFrameImage(TEXT("MenuNumber"), TEXT("Image/menuNumber.bmp"), 160, 14, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("SelArrow"), TEXT("Image/selectArrow.bmp"), 24, 36, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("ATK"), TEXT("Image/atk.bmp"), 42, 16, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("DEF"), TEXT("Image/def.bmp"), 42, 16, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Gold"), TEXT("Image/gold.bmp"), 12, 16, true, COLOR_M);

	IMAGEMANAGER->AddFrameImage(TEXT("Candle1"), TEXT("Image/candle1.bmp"), 150, 135, 3, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Candle2"), TEXT("Image/candle2.bmp"), 240, 85, 3, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Candle3"), TEXT("Image/candle3.bmp"), 240, 140, 3, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Candle4"), TEXT("Image/candle4.bmp"), 240, 195, 3, 1, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Candle4Down"), TEXT("Image/candle4_2.bmp"), 80, 195, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("CandleLight"), TEXT("Image/candlelight.bmp"), 300, 150, 2, 1, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Coin"), TEXT("Image/coin2.bmp"), 48, 40, true, COLOR_M);

	IMAGEMANAGER->AddImage(TEXT("DaggerIcon"), TEXT("Image/dagger_icon.bmp"), 45, 45, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("LongSwordIcon"), TEXT("Image/sword_icon.bmp"), 45, 45, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("SpearIcon"), TEXT("Image/spear_icon.bmp"), 45, 45, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("AxeIcon"), TEXT("Image/axe_icon.bmp"), 45, 45, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("GreateSwordIcon"), TEXT("Image/greatsword_icon.bmp"), 45, 45, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("ClothesIcon"), TEXT("Image/clothes_icon.bmp"), 45, 45, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("RobeIcon"), TEXT("Image/robe_icon.bmp"), 45, 45, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("LArmorIcon"), TEXT("Image/leatherarmor_icon.bmp"), 45, 45, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("IArmorIcon"), TEXT("Image/ironarmor_icon.bmp"), 45, 45, true, COLOR_M);

	IMAGEMANAGER->AddFrameImage(TEXT("PlayerStand"), TEXT("Image/soma_stand.bmp"), 632, 144, 8, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PlayerRun"), TEXT("Image/soma_walk.bmp"), 6120, 144, 34, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PlayerJump"), TEXT("Image/soma_jump.bmp"), 2160, 144, 12, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PlayerJumpAttack"), TEXT("Image/soma_jumpattack.bmp"), 4224, 144, 24, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PlayerSit"), TEXT("Image/soma_sit.bmp"), 1800, 144, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PlayerAttack"), TEXT("Image/soma_attack.bmp"), 4320, 144, 24, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PlayerDamage"), TEXT("Image/soma_damage.bmp"), 720, 144, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PlayerDie"), TEXT("Image/soma_die.bmp"), 2160, 144, 12, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PlayerDamNumber"), TEXT("Image/playerDamage.bmp"), 160, 16, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("HPUI"), TEXT("Image/hp.bmp"), 333, 69, true, COLOR_M);

	IMAGEMANAGER->AddFrameImage(TEXT("Dagger"), TEXT("Image/knife.bmp"), 520, 16, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Sword"), TEXT("Image/sword.bmp"), 1470, 187, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Spear"), TEXT("Image/spear.bmp"), 2000, 24, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Axe"), TEXT("Image/axe.bmp"), 1350, 212, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("GreatSword"), TEXT("Image/greatsword.bmp"), 2390, 307, 10, 1, true, COLOR_M);

	IMAGEMANAGER->AddFrameImage(TEXT("ZombieRise"), TEXT("Image/zombie_rise.bmp"), 1232, 164, 14, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("ZombieMove"), TEXT("Image/zombie_move.bmp"), 704, 164, 8, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("ZombieDie"), TEXT("Image/zombie_die.bmp"), 576, 164, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BatMove"), TEXT("Image/bat_move.bmp"), 180, 38, 6, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BatStand"), TEXT("Image/bat_stand.bmp"), 40, 38, 2, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("ArcherMove"), TEXT("Image/archer_move.bmp"), 960, 144, 6, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("ArcherAttack"), TEXT("Image/archer_attack.bmp"), 960, 144, 6, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("ArcherReload"), TEXT("Image/archer_reload.bmp"), 1920, 144, 12, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("ArcherArrow"), TEXT("Image/archer_arrow.bmp"), 304, 12, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PersephoneMove"), TEXT("Image/persephone_move.bmp"), 576, 128, 8, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PersephoneBow"), TEXT("Image/persephone_bow.bmp"), 704, 128, 8, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PersephoneCombatMove"), TEXT("Image/persephone_combatmove.bmp"), 288, 128, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PersephoneAttack"), TEXT("Image/persephone_attack.bmp"), 1320, 128, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("PersephoneDie"), TEXT("Image/persephone_die.bmp"), 160, 128, 2, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("EnemyDamNumber"), TEXT("Image/enemyDamage.bmp"), 160, 16, 10, 1, true, COLOR_M);

	IMAGEMANAGER->AddFrameImage(TEXT("BossStand"), TEXT("Image/boss_stand.bmp"), 672, 206, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BossMeleeReady"), TEXT("Image/boss_meleeready.bmp"), 656, 244, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BossMelee"), TEXT("Image/boss_meleeattack.bmp"), 576, 340, 3, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BossRange"), TEXT("Image/boss_range.bmp"), 688, 222, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BossAllReady"), TEXT("Image/boss_allready.bmp"), 1016, 164, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BossAll"), TEXT("Image/boss_allattack.bmp"), 656, 212, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BossRangeBullet"), TEXT("Image/boss_rangebullet.bmp"), 824, 206, 4, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("BossAllBullet"), TEXT("Image/boss_allbullet.bmp"), 56, 122, 2, 1, true, COLOR_M);

	IMAGEMANAGER->AddImage(TEXT("MenuPage"), TEXT("Image/menupage.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("LevelNumber"), TEXT("Image/menuNumber.bmp"), 480, 42, 10, 1, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("StateNumber"), TEXT("Image/menuNumber.bmp"), 320, 28, 10, 1, true, COLOR_M);

	IMAGEMANAGER->AddImage(TEXT("MapBackground"), TEXT("Image/map/mapbackground.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room1Map"), TEXT("Image/map/room1map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room2Map"), TEXT("Image/map/room2map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room3Map"), TEXT("Image/map/room3map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room4Map"), TEXT("Image/map/room4map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room5Map"), TEXT("Image/map/room5map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room6Map"), TEXT("Image/map/room6map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room7Map"), TEXT("Image/map/room7map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room8Map"), TEXT("Image/map/room8map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room9Map"), TEXT("Image/map/room9map.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("Room10Map"), TEXT("Image/map/room10map.bmp"), 1200, 800, true, COLOR_M);

	IMAGEMANAGER->AddImage(TEXT("GameOverPage"), TEXT("Image/gameoverpage.bmp"), 1200, 800, true, COLOR_M);
	IMAGEMANAGER->AddImage(TEXT("GameOverTitle"), TEXT("Image/gameover.bmp"), 990, 160, true, COLOR_M);
	IMAGEMANAGER->AddFrameImage(TEXT("Congratulations"), TEXT("Image/congratulations.bmp"), 3248, 112, 4, 1, true, COLOR_M);


	//애니메이션 매니저 초기화
	ANIMANAGER->Init();

	//애니메이션 추가
	ANIMANAGER->AddDefAni(TEXT("Main"), TEXT("StartBackground"), 5, false, true);
	
	ANIMANAGER->AddDefAni(TEXT("MerchantAni"), TEXT("Merchant"), 1, false, true);
	
	ANIMANAGER->AddDefAni(TEXT("Candle1Ani"), TEXT("Candle1"), 5, false, true);
	ANIMANAGER->AddDefAni(TEXT("Candle2Ani"), TEXT("Candle2"), 5, false, true);
	ANIMANAGER->AddDefAni(TEXT("Candle3Ani"), TEXT("Candle3"), 5, false, true);
	ANIMANAGER->AddDefAni(TEXT("Candle4Ani"), TEXT("Candle4"), 5, false, true);
	ANIMANAGER->AddDefAni(TEXT("LightAni"), TEXT("CandleLight"), 20, false, true);

	ANIMANAGER->AddCoordAni(TEXT("PStandRAni"), TEXT("PlayerStand"), 0, 3, 5, true);
	ANIMANAGER->AddCoordAni(TEXT("PStandLAni"), TEXT("PlayerStand"), 7, 4, 5, true);
	ANIMANAGER->AddCoordAni(TEXT("PRunRAni"), TEXT("PlayerRun"), 0, 16, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("PRunLAni"), TEXT("PlayerRun"), 33, 17, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("PJumpRAni"), TEXT("PlayerJump"), 0, 5, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("PJumpLAni"), TEXT("PlayerJump"), 11, 6, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("PSitRAni"), TEXT("PlayerSit"), 0, 4, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("PSitLAni"), TEXT("PlayerSit"), 9, 5, 10, false);

	ANIMANAGER->AddCoordAni(TEXT("DaggerAttackRAni"), TEXT("PlayerAttack"), 0, 11, 20, false);
	ANIMANAGER->AddCoordAni(TEXT("DaggerAttackLAni"), TEXT("PlayerAttack"), 23, 12, 20, false);
	ANIMANAGER->AddCoordAni(TEXT("SwordAttackRAni"), TEXT("PlayerAttack"), 0, 11, 15, false);
	ANIMANAGER->AddCoordAni(TEXT("SwordAttackLAni"), TEXT("PlayerAttack"), 23, 12, 15, false);
	ANIMANAGER->AddCoordAni(TEXT("SpearAttackRAni"), TEXT("PlayerAttack"), 0, 11, 18, false);
	ANIMANAGER->AddCoordAni(TEXT("SpearAttackLAni"), TEXT("PlayerAttack"), 23, 12, 18, false);
	ANIMANAGER->AddCoordAni(TEXT("AxeAttackRAni"), TEXT("PlayerAttack"), 0, 11, 12, false);
	ANIMANAGER->AddCoordAni(TEXT("AxeAttackLAni"), TEXT("PlayerAttack"), 23, 12, 12, false);
	ANIMANAGER->AddCoordAni(TEXT("GSwordAttackRAni"), TEXT("PlayerAttack"), 0, 11, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("GSwordAttackLAni"), TEXT("PlayerAttack"), 23, 12, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("DaggerJumpAttackRAni"), TEXT("PlayerJumpAttack"), 0, 11, 20, false);
	ANIMANAGER->AddCoordAni(TEXT("DaggerJumpAttackLAni"), TEXT("PlayerJumpAttack"), 23, 12, 20, false);
	ANIMANAGER->AddCoordAni(TEXT("SwordJumpAttackRAni"), TEXT("PlayerJumpAttack"), 0, 11, 15, false);
	ANIMANAGER->AddCoordAni(TEXT("SwordJumpAttackLAni"), TEXT("PlayerJumpAttack"), 23, 12, 15, false);
	ANIMANAGER->AddCoordAni(TEXT("SpearJumpAttackRAni"), TEXT("PlayerJumpAttack"), 0, 11, 18, false);
	ANIMANAGER->AddCoordAni(TEXT("SpearJumpAttackLAni"), TEXT("PlayerJumpAttack"), 23, 12, 18, false);
	ANIMANAGER->AddCoordAni(TEXT("AxeJumpAttackRAni"), TEXT("PlayerJumpAttack"), 0, 11, 12, false);
	ANIMANAGER->AddCoordAni(TEXT("AxeJumpAttackLAni"), TEXT("PlayerJumpAttack"), 23, 12, 12, false);
	ANIMANAGER->AddCoordAni(TEXT("GSwordJumpAttackRAni"), TEXT("PlayerJumpAttack"), 0, 11, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("GSwordJumpAttackLAni"), TEXT("PlayerJumpAttack"), 23, 12, 10, false);

	ANIMANAGER->AddCoordAni(TEXT("PDamageRAni"), TEXT("PlayerDamage"), 1, 0, 5, false);
	ANIMANAGER->AddCoordAni(TEXT("PDamageLAni"), TEXT("PlayerDamage"), 2, 3, 5, false);
	ANIMANAGER->AddCoordAni(TEXT("PDieRAni"), TEXT("PlayerDie"), 0, 5, 5, false);
	ANIMANAGER->AddCoordAni(TEXT("PDieLAni"), TEXT("PlayerDie"), 11, 6, 5, false);

	ANIMANAGER->AddCoordAni(TEXT("DaggerRAni"), TEXT("Dagger"), 0, 4, 20, true);
	ANIMANAGER->AddCoordAni(TEXT("DaggerLAni"), TEXT("Dagger"), 9, 5, 20, true);
	ANIMANAGER->AddCoordAni(TEXT("SwordRAni"), TEXT("Sword"), 0, 5, 15, false);
	ANIMANAGER->AddCoordAni(TEXT("SwordLAni"), TEXT("Sword"), 9, 5, 15, false);
	ANIMANAGER->AddCoordAni(TEXT("SpearRAni"), TEXT("Spear"), 0, 4, 18, true);
	ANIMANAGER->AddCoordAni(TEXT("SpearLAni"), TEXT("Spear"), 9, 5, 18, true);
	ANIMANAGER->AddCoordAni(TEXT("AxeRAni"), TEXT("Axe"), 0, 4, 12, false);
	ANIMANAGER->AddCoordAni(TEXT("AxeLAni"), TEXT("Axe"), 9, 5, 12, false);
	ANIMANAGER->AddCoordAni(TEXT("GSwordRAni"), TEXT("GreatSword"), 0, 5, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("GSwordLAni"), TEXT("GreatSword"), 9, 5, 10, false);

	ANIMANAGER->AddCoordAni(TEXT("ZombieRiseUpRAni"), TEXT("ZombieRise"), 7, 0, 8, false);
	ANIMANAGER->AddCoordAni(TEXT("ZombieRiseUpLAni"), TEXT("ZombieRise"), 6, 13, 8, false);
	ANIMANAGER->AddCoordAni(TEXT("ZombieRiseDownRAni"), TEXT("ZombieRise"), 0, 7, 8, false);
	ANIMANAGER->AddCoordAni(TEXT("ZombieRiseDownLAni"), TEXT("ZombieRise"), 13, 6, 8, false);
	ANIMANAGER->AddCoordAni(TEXT("ZombieMoveRAni"), TEXT("ZombieMove"), 3, 0, 5, true);
	ANIMANAGER->AddCoordAni(TEXT("ZombieMoveLAni"), TEXT("ZombieMove"), 4, 7, 5, true);
	ANIMANAGER->AddCoordAni(TEXT("ZombieDieRAni"), TEXT("ZombieDie"), 1, 0, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("ZombieDieLAni"), TEXT("ZombieDie"), 2, 3, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("BatMoveRAni"), TEXT("BatMove"), 0, 3, 5, true);
	ANIMANAGER->AddCoordAni(TEXT("BatMoveLAni"), TEXT("BatMove"), 3, 5, 5, true);
	ANIMANAGER->AddCoordAni(TEXT("BatStandAni"), TEXT("BatStand"), 0, 1, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("ArcherMoveRAni"), TEXT("ArcherMove"), 2, 0, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("ArcherMoveLAni"), TEXT("ArcherMove"), 3, 5, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("ArcherAttackRAni"), TEXT("ArcherAttack"), 2, 0, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("ArcherAttackLAni"), TEXT("ArcherAttack"), 3, 5, 10, false);
	ANIMANAGER->AddCoordAni(TEXT("ArcherReloadRAni"), TEXT("ArcherReload"), 5, 0, 5, false);
	ANIMANAGER->AddCoordAni(TEXT("ArcherReloadLAni"), TEXT("ArcherReload"), 6, 11, 5, false);
	ANIMANAGER->AddCoordAni(TEXT("ArcherArrowRAni"), TEXT("ArcherArrow"), 0, 1, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("ArcherArrowLAni"), TEXT("ArcherArrow"), 3, 2, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneMoveRAni"), TEXT("PersephoneMove"), 4, 7, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneMoveLAni"), TEXT("PersephoneMove"), 3, 0, 10, true);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneBowRAni"), TEXT("PersephoneBow"), 7, 4, 5, false);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneBowLAni"), TEXT("PersephoneBow"), 0, 3, 5, false);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneCombatMoveRAni"), TEXT("PersephoneCombatMove"), 2, 4, 5, true);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneCombatMoveLAni"), TEXT("PersephoneCombatMove"), 1, 0, 5, true);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneAttackRAni"), TEXT("PersephoneAttack"), 5, 9, 8, false);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneAttackLAni"), TEXT("PersephoneAttack"), 4, 0, 8, false);
	ANIMANAGER->AddCoordAni(TEXT("PersephoneDieAni"), TEXT("PersephoneDie"), 0, 1, 5, false);

	ANIMANAGER->AddDefAni(TEXT("BossStandAni"), TEXT("BossStand"), 10, false, true);
	ANIMANAGER->AddDefAni(TEXT("BossMeleeReadyAni"), TEXT("BossMeleeReady"), 5, false, true);
	ANIMANAGER->AddDefAni(TEXT("BossMeleeAni"), TEXT("BossMelee"), 5, false, false);
	ANIMANAGER->AddDefAni(TEXT("BossRangeAni"), TEXT("BossRange"), 5, false, true);
	ANIMANAGER->AddDefAni(TEXT("BossAllReadyAni"), TEXT("BossAllReady"), 5, false, true);
	ANIMANAGER->AddDefAni(TEXT("BossAllAni"), TEXT("BossAll"), 5, false, true);
	ANIMANAGER->AddDefAni(TEXT("BossRangeBulletAni"), TEXT("BossRangeBullet"), 10, false, true);
	ANIMANAGER->AddDefAni(TEXT("BossAllBulletAni"), TEXT("BossAllBullet"), 10, false, true);

	ANIMANAGER->AddDefAni(TEXT("CongratulateAni"), TEXT("Congratulations"), 10, false, false);

	//사운드 매니저 초기화
	//SOUNDMANAGER->Init();

	//사운드 추가
	SOUNDMANAGER->AddSound(TEXT("MainBgm"), TEXT("Sound/main.wav"), true, true);
	SOUNDMANAGER->AddSound(TEXT("Bgm"), TEXT("Sound/bgm.wav"), true, true);
	SOUNDMANAGER->AddSound(TEXT("GameOverBgm"), TEXT("Sound/gameover.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Step"), TEXT("Sound/step.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("PAttackLight"), TEXT("Sound/pAttack.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("PAttackHeavy"), TEXT("Sound/pAttack2.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("OK"), TEXT("Sound/ok.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Back"), TEXT("Sound/back.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("BAttackMelee"), TEXT("Sound/bAttack.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Bow"), TEXT("Sound/bow.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Buy"), TEXT("Sound/buy.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Burn"), TEXT("Sound/burn.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Heal"), TEXT("Sound/heal.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Hit"), TEXT("Sound/hit.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("Menu"), TEXT("Sound/menu.wav"), false, false);


	//이펙트 매니저 초기화
	EFFECTMANAGER->Init();

	//이펙트 추가
	EFFECTMANAGER->AddEffect(TEXT("BurnEnemyEffect"), TEXT("Image/burneffect2.bmp"), 312, 92, 52, 92, 1, 1.f, 1, COLOR_M);
	EFFECTMANAGER->AddEffect(TEXT("BurnBossEffect"), TEXT("Image/burneffect3.bmp"), 624, 184, 104, 184, 1, 1.f, 1, COLOR_M);
	EFFECTMANAGER->AddEffect(TEXT("DustEffect"), TEXT("Image/dusteffect.bmp"), 448, 60, 64, 60, 1, 1.f, 5, COLOR_M);
	EFFECTMANAGER->AddEffect(TEXT("HealEffect"), TEXT("Image/healeffect2.bmp"), 340, 121, 85, 121, 1, 1.f, 5, COLOR_M);
	EFFECTMANAGER->AddEffect(TEXT("HitEffect"), TEXT("Image/hiteffect.bmp"), 96, 30, 32, 30, 1, 1.f, 5, COLOR_M);
	EFFECTMANAGER->AddEffect(TEXT("LevelUpEffect"), TEXT("Image/levelup.bmp"), 384, 44, 96, 44, 1, 1.f, 1, COLOR_M);


	//장비 싱글턴 초기화
	EQUIPMENT->Init();

	//플레이어 싱글턴 초기화
	PLAYER->Init();

	//메뉴 싱글턴 초기화
	MENU->Init();

	//지도 싱글턴 초기화
	MAP->Init();

	//텍스트 출력 싱글턴 초기화
	TXTDATA->Init();

	//씬매니저 초기화
	SCENEMANAGER->Init();

	//씬 추가
	SCENEMANAGER->AddScene(TEXT("Start"), new StartScene);
	SCENEMANAGER->AddScene(TEXT("R1"), new Room1);
	SCENEMANAGER->AddScene(TEXT("R2"), new Room2);
	SCENEMANAGER->AddScene(TEXT("R3"), new Room3);
	SCENEMANAGER->AddScene(TEXT("R4"), new Room4);
	SCENEMANAGER->AddScene(TEXT("R5"), new Room5);
	SCENEMANAGER->AddScene(TEXT("R6"), new Room6);
	SCENEMANAGER->AddScene(TEXT("R7"), new Room7);
	SCENEMANAGER->AddScene(TEXT("R8"), new Room8);
	SCENEMANAGER->AddScene(TEXT("R9"), new Room9);
	SCENEMANAGER->AddScene(TEXT("R10"), new Room10);
	SCENEMANAGER->AddScene(TEXT("R11"), new Room11);
	SCENEMANAGER->AddScene(TEXT("R12"), new Room12);
	SCENEMANAGER->AddScene(TEXT("R13"), new Room13);
	SCENEMANAGER->AddScene(TEXT("GameOver"), new GameOver);


	//첫 씬의 설정
	SCENEMANAGER->ChangeScene(TEXT("Start"));

	return true;
}

void MainGame::Release()
{
	GameNode::Release();

	/*=====해  제=====*/
	IMAGEMANAGER->Release();
	SCENEMANAGER->Release();
	//SOUNDMANAGER->Release();
	EFFECTMANAGER->Release();
	TXTDATA->Release();

	PLAYER->Release();
	EQUIPMENT->Release();
	MENU->Release();
	MAP->Release();

	/*if (KEYMANAGER->isToggleKey(VK_RETURN))
		SetKeyboardState(0x0D);
	if (KEYMANAGER->isToggleKey(VK_SHIFT))
		KEYMANAGER->isToggleKey(VK_SHIFT);*/
}

void MainGame::Update()
{
	GameNode::Update();
	
	/*=====상태 변화=====*/
	
	ANIMANAGER->Update();
	TIMEMANAGER->Update();
	SOUNDMANAGER->Update();
	EFFECTMANAGER->Update();

	if(KEYMANAGER->isToggleKey(VK_RETURN))
		MENU->Update();
	else if(KEYMANAGER->isToggleKey(VK_SHIFT))
		MAP->Update();
	else
	{
		PLAYER->Update();
		SCENEMANAGER->Update();
	}
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = this->GetBackBuffer()->GetMemDC();					//1. backDC 생성
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);			//2. backDC를 일단 하얗게 채움

	/*=====그 리 기=====*/
	TIMEMANAGER->Render(backDC);

	if (KEYMANAGER->isToggleKey(VK_RETURN))
		MENU->Render(backDC);
	else if (KEYMANAGER->isToggleKey(VK_SHIFT))
		MAP->Render(backDC);
	else
	{
		SCENEMANAGER->Render(backDC);
		EFFECTMANAGER->Render(backDC);
	}
	//================
	this->GetBackBuffer()->Render(hdc, 0, 0);							//5. backDC의 내용을 화면에 그림

}

