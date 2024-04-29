//===================================================
//�Q�[�����(game.cpp)
//Auhor:�n� �C	Date:2023.8.4
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
//�O���[�o���ϐ�
//---------------------------------------------------
static int g_Field;
static Player* g_player;
static KumoBoss* gBoss;
static EnemyCastle* gEnemyCastle;

static Alpaca* gAlpaca;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitGame()
{
	// �}�E�X���\���ɂ���
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
	InitTile();  //�w�i���v���C���[�������ɂ���悤��
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
	SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
	SetFadeTime(240.0f);//time:���t���[���Ńt�F�[�h�������������������H

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
//�X�V
//---------------------------------------------------
void UpdateGame()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
		SetFadeTime(30.0f);//time:���t���[���Ńt�F�[�h�������������������H
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
//�`��
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
	//DrawCamera();//�f�o�b�O�p
	//DrawTextCreate();
	//DrawIcon();
	//DrawMinimap();
	DrawScore();
	DrawTextDW();
	DrawRangeSelect();
}

//---------------------------------------------------
//�I������
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
