//===================================================
//ゲーム画面(game.cpp)
//Auhor:渡邉 修	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "GameEntity/Player/player.h"
#include "GameEntity/Enemy/EnemySpawn.h"
#include "GameEntity/Enemy/EnemybulletSpawn.h"
#include "GameEntity/Enemy/KumoBoss.h"
#include "GameEntity/EntityManager.h"
#include "game.h"
#include "dead.h"
#include "fade.h"
#include "sound.h"
#include "tile.h"
#include "camera.h"
#include "gun.h"
#include "bullet.h"
#include "hit_spark.h"
#include "back_ground.h"
#include "text_create.h"
#include "particle.h"
#include "minimap.h"
#include "icon.h"
#include "score.h"
#include "item.h"
#include "textDW.h"
#include "range_select.h"
#include "GameEntity/Enemy/PepperEnemy.h"

#include "GameEntity/MapObject/Tree.h"
#include "GameEntity/Player/paperGuardian.h"
#include "Alpaca.h"

#include "GameEntity/MapObject/EnemyCastle.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static int g_Field;
static Player* g_player;
static KumoBoss* gBoss;
static EnemyCastle* gEnemyCastle;

static Alpaca* gAlpaca;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitGame()
{
	// マウスを非表示にする
	//ShowCursor(FALSE);
	
	char tilem[] =
	{
		"data\\BGM\\Field.wav"
	};
	g_Field = LoadSound(&tilem[0]);
	PlaySound(g_Field, -1, 0.4f);

	//int texTree = LoadTexture((char*)"data/TEXTURE/Tree.png");
	//Spawner::Instance()->SetFor<Tree>({ 2000,200 }, texTree);


	Spawner::Instance()->Init();
	EnemyBulletSpawn::Instance()->Init();
	
	//char tilem[] =
	//{
	//	"data\\TILEM\\nc296708.wav"
	//};
	//g_TILEM = LoadSound(&tilem[0]);
	//PlaySound(g_TILEM, -1);
	InitTile();  //背景がプレイヤーよりも後ろにくるように
	InitBackGround();
	InitGun();
	InitBullet();
	InitHitSpark();
	InitItem();
	//InitTile();
	//InitBackGround();

	InitDead();
	InitCamera();
	InitTextCreate();
	InitParticle();
	InitIcon();
	InitMinimap();
	InitScore();
	InitTextDW();
	InitRangeSelect();
	SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
	SetFadeTime(240.0f);//time:何フレームでフェード処理を完了したいか？

	//int texSpikeTree = LoadTexture((char*)"data/TEXTURE/SpikeTree.png");
	//Spawner::Instance()->SetFor<EnemyCastle>({ 10000, 200}, texSpikeTree);

	int texPepper = LoadTexture((char*)"data/TEXTURE/paperenemy.png");
	//Spawner::Instance()->SetFor<PepperEnemy>({ 4000,2000 }, texPepper, 1.0);
	//Spawner::Instance()->SetFor<PepperEnemy>({ 4500,2000 }, texPepper, 1.5);
	//Spawner::Instance()->SetFor<PepperEnemy>({ 5000,2000 }, texPepper, 2.0);
	//Spawner::Instance()->SetEnemy({ 4500, 2000 });
	//Spawner::Instance()->SetEnemy({ 4500, 2000 });
	//Spawner::Instance()->SetEnemy({ 5600, 2000 });

	int texPaperGuardian = LoadTexture((char*)"data/TEXTURE/paperGuardian.png");
	//Spawner::Instance()->SetFor<PaperGuardian>({ 2000,2000 }, texPaperGuardian, 1.0);
	//Spawner::Instance()->SetFor<PaperGuardian>({ 2200,2000 }, texPaperGuardian, 1.0);
	//Spawner::Instance()->SetFor<PaperGuardian>({ 2400,2000 }, texPaperGuardian, 1.0);

	//gEnemyCastle = new EnemyCastle();
	gBoss = new KumoBoss();
	g_player = new Player();

	//EntityManager::Instance()->RegisterEntity(gEnemyCastle);
	EntityManager::Instance()->RegisterEntity(gBoss);
	EntityManager::Instance()->RegisterEntity(g_player);
	gAlpaca = new Alpaca();
	EntityManager::Instance()->RegisterEntity(gAlpaca);
	//SetTilePlayer(g_player);


	Spawner::Instance()->Init();
	EnemyBulletSpawn::Instance()->Init();
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateGame()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
		SetFadeTime(30.0f);//time:何フレームでフェード処理を完了したいか？
		SetFade(FADE_STATE_IN);
	}
	UpdateCamera();
	UpdateBackGround();
	UpdateTile();
	EntityManager::Instance()->Update();
	UpdateGun();
	UpdateHitSpark();
	UpdateBullet();
	UpdateItem();
	UpdateDead();
	UpdateTextCreate();
	UpdateParticle();
	UpdateIcon();
	UpdateMinimap();
	UpdateScore();
	UpdateTextDW();
	UpdateRangeSelect();
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawGame()
{
	DrawBackGroundLow();
	DrawParticle();
	DrawTile();
	DrawItem();
	EntityManager::Instance()->Draw();
	DrawGun();
	DrawBullet();
	DrawHitSpark();
	DrawDead();
	DrawBackGroundHigh();
	//DrawCamera();//デバッグ用
	//DrawTextCreate();
	//DrawIcon();
	//DrawMinimap();
	DrawScore();
	DrawTextDW();
	DrawRangeSelect();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitGame()
{
	UninitRangeSelect();
	UninitMinimap();
	UninitIcon();
	UninitTextCreate();
	UninitParticle();
	UninitDead();
	UninitItem();
	UninitBackGround();
	UninitTile();
	UninitHitSpark();
	UninitBullet();
	EntityManager::Instance()->CleanAll();
	UninitGun();
	UninitCamera();
	UninitScore();
	UninitTextDW();
	StopSoundAll();
}
