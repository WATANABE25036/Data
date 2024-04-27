//===================================================
//�^�C��(tile.cpp)
//Auhor:�n� �C	Date:2023.8.26
//===================================================
#include "tile.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "GameEntity/Player/player.h"
#include "GameEntity/Enemy/enemy.h"
#include "GameEntity/Enemy/EnemySpawn.h"
#include "GameEntity/Enemy/PepperEnemy.h"
#include "score.h"
#include "gun.h"
#include <list>
#include <array>
#include <vector>
#include <unordered_map>
#include "input.h"
#include "range_select.h"

#include "GameEntity/MapObject/Tree.h"
#include "GameEntity/MapObject/NekoCastle.h"

#include "GameEntity/MapObject/EnemyCastle.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_Ground;	//�w�i�p�̃e�N�X�`���ԍ�
static int g_Filter;
static float g_UW;
static float g_VH;
static std::vector<TILE_DATA> g_Map; //�}�b�v�̃f�[�^
static int g_SpawnTimeCou;
static int g_SpawnTime;
static int g_SpawnNum;
static int g_Wave;
int g_MapSizeX = 10; // �}�b�v���T�C�Y
int g_MapSizeY = 0; // �}�b�v�c�T�C�Y
size_t g_MapSize = 0;
Player* p_Player;
static int mapInitSizeY;
static int mapInitSizeX;

MAP_DATA_T g_MapInfo[MAP_FRAME_MAX] =
{
	//������W�ƃ}�b�v�`�b�v�����̐ݒ�
	//�ʏ�
	{ GetTileUV(0), MAP_ATTRIB_NONE, false},	//0��
	{ GetTileUV(1), MAP_ATTRIB_STOP, false},	//1�n�ʍ�
	{ GetTileUV(2), MAP_ATTRIB_STOP, false},	//2�n�ʏ�
	{ GetTileUV(3), MAP_ATTRIB_STOP, false},	//3�n�ʉE
	{ GetTileUV(4), MAP_ATTRIB_STOP, false},	//4�h��Ԃ���F
	{ GetTileUV(5), MAP_ATTRIB_STOP, false},	//5�h��Ԃ�(��������)
	{ GetTileUV(6), MAP_ATTRIB_STOP, false},	//6�h��Ԃ�
	{ GetTileUV(7), MAP_ATTRIB_STOP, false},	//7�h��Ԃ�(�傫����)
	{ GetTileUV(8), MAP_ATTRIB_STOP, false},	//8���p�E
	{ GetTileUV(9), MAP_ATTRIB_STOP, false},	//9���p��
	{ GetTileUV(10), MAP_ATTRIB_STOP, false},	//10��(�ʂ蔲���s��)
	//��
	{ GetTileUV(13), MAP_ATTRIB_STOP, true},	//11�n�ʍ�
	{ GetTileUV(14), MAP_ATTRIB_STOP, true},	//12�n�ʏ�
	{ GetTileUV(15), MAP_ATTRIB_STOP, true},	//13�n�ʉE
	{ GetTileUV(16), MAP_ATTRIB_STOP, false},	//14�h��Ԃ���F
	{ GetTileUV(17), MAP_ATTRIB_STOP, false},	//15�h��Ԃ�(��������)
	{ GetTileUV(18), MAP_ATTRIB_STOP, false},	//16�h��Ԃ�
	{ GetTileUV(19), MAP_ATTRIB_STOP, false},	//17�h��Ԃ�(�傫����)
	{ GetTileUV(20), MAP_ATTRIB_STOP, false},	//18���p�E
	{ GetTileUV(21), MAP_ATTRIB_STOP, false},	//19���p��

	//���R
	{ GetTileUV(24), MAP_ATTRIB_NATURE, false},//20��
	{ GetTileUV(25), MAP_ATTRIB_NATURE, false},//21����
	{ GetTileUV(26), MAP_ATTRIB_NATURE, false},//22�ԉ��F
	{ GetTileUV(27), MAP_ATTRIB_NATURE, false},//23���߂�
	//�}�b�v�`�b�v�̎�ޕ��쐬����
};

//�}�b�v�f�[�^�[(1��ʕ�)
const int P = 'P';	// �v���C���[
const int E = 'E';	// �G�l�~�[
const int E2 = 'E2';	// �G�l�~�[
const int T = 'T';	//�؃I�u�W�F�N�g
const int C = 'C'; //��I�u�W�F�N�g
const int �� = 1;	// �n�ʏ�
const int �c = 11;	// �n�ʏ�
const int �O = 10;	// �n�ʏ�
const int TT = 'TT';  //�Ƃ��Ƃ��̖�
const int �O = 0;


struct MAP_DATA
{
	std::vector<std::vector<int>> mapData;
	float rate;
};

//�e�X�̑���������
// 
//--------------------------------------------------
//�����}�b�v
std::vector<std::vector<int>> g_MapAttribDataS =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //7
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,��,��,��,��,��,��,��,��,��,��,��}}, //3
	{{�O,�O,�O,�O,��,��,��,��,��,��,��,��,��,��,��}}, //4 �قډ�ʊO
	{{�O,�O,�O,�O,��,��,��,��,��,��,��,��,��,��,��}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapDataS{ g_MapAttribDataS, 0.0f };//�r�o�m��
//--------------------------------------------------�����1�}�b�v


//--------------------------------------------------
std::vector<std::vector<int>> g_MapAttribData1 =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //7
	{{�O,�O,�O,�O,�O, T,�O,�O, E,�O}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{��,��,��,��,��,��,��,��,��,��}}, //2
	{{��,��,��,��,��,��,��,��,��,��}}, //3
	{{��,��,��,��,��,��,��,��,��,��}}, //4 �قډ�ʊO
	{{��,��,��,��,��,��,��,��,��,��}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapData1{ g_MapAttribData1, 35.0f };//�r�o�m��
//--------------------------------------------------�����1�}�b�v

std::vector<std::vector<int>> g_MapAttribData2 =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O, E, E,�O,�O,�O, E}}, //7
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,��,��,��,��,�O,�O,�O}}, //1
	{{�O,�O,��,��,��,��,��,��,��,�O}}, //2
	{{��,��,��,��,��,��,��,��,��,��}}, //3
	{{��,��,��,��,��,��,��,��,��,��}}, //4 �قډ�ʊO
	{{��,��,��,��,��,��,��,��,��,��}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapData2{ g_MapAttribData2, 35.0f };
//--------------------------------------------------�����1�}�b�v

std::vector<std::vector<int>> g_MapAttribData3 =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //7
	{{�O,�O,�O, T,�O,�O,�O,�O,�O, T}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{��,��,�O,�O,�O,��,��,��,�O,�O}}, //2
	{{��,��,��,��,��,��,��,��,��,��}}, //3
	{{��,��,��,��,��,��,��,��,��,��}}, //4 �قډ�ʊO
	{{��,��,��,��,��,��,��,��,��,��}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapData3{ g_MapAttribData3, 35.0f };
//--------------------------------------------------�����1�}�b�v

std::vector<std::vector<int>> g_MapAttribData4 =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //7
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //8
	{{�O,�O,�O,�O,�O,E2,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //3
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //4 �قډ�ʊO
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapData4{ g_MapAttribData4, 25.0f };
//--------------------------------------------------�����1�}�b�v

std::vector<std::vector<int>> g_MapAttribData5 =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O, T,�O}}, //7
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�c,�c,�O,E2,�O,�O,�O,�O}}, //0
	{{�O,�c,�c,�c,�O,�O,�O,�O,�O,�O}}, //1
	{{�c,�c,�c,�c,�O,�O,�O,�c,�c,�c}}, //2
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //3
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //4 �قډ�ʊO
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapData5{ g_MapAttribData5, 25.0f };
//--------------------------------------------------�����1�}�b�v

std::vector<std::vector<int>> g_MapAttribData6 =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O, T,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //7
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�O,�O,�O,�O}}, //0
	{{�O,�O,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�O}}, //1
	{{�O,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //2
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //3
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //4 �قډ�ʊO
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapData6{ g_MapAttribData6, 25.0f };
//--------------------------------------------------�����1�}�b�v
// 
std::vector<std::vector<int>> g_MapAttribData7 =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,E2,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,E2,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //7
	{{�O,�O,�O,�O,E2,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�O,�O,�c,�c,�c,�c,�c,�c,�c,�c,�O,�O}}, //0
	{{�O,�O,�O,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�O,�O}}, //1
	{{�O,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�O,�O}}, //2
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //3
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //4 �قډ�ʊO
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapData7{ g_MapAttribData7, 25.0f };
//--------------------------------------------------�����1�}�b�v
// 
std::vector<std::vector<int>> g_MapAttribData8 =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,E2,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //7
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�c,�c,�O,�O,�O,�O,�c,�c,�c,�c,�O,�O,�O}}, //1
	{{�O,�c,�c,�c,�c,�O,�O,�c,�c,�c,�c,�c,�c,�O,�O}}, //2
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //3
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //4 �قډ�ʊO
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapData8{ g_MapAttribData8, 25.0f };
//--------------------------------------------------�����1�}�b�v
//�{�X�}�b�v
std::vector<std::vector<int>> g_MapAttribDataG =
{ {
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //6
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //7
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,E2,E2,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //8
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,E2,E2,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //9
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //0
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //1
	{{�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //2
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //3
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //4 �قډ�ʊO
	{{�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�c,�O,�O,�O,�O,�O,�O,�O,�O,�O}}, //5 ��ʊO(�����܂ŕK�v)
} };

MAP_DATA g_MapDataG{ g_MapAttribDataG, 0.0f };
//--------------------------------------------------�����1�}�b�v



//�}�b�v���܂Ƃ߂�(�����_�������̌��)
std::unordered_map<int, MAP_DATA>g_MapDatas;


//=============================================================================
// ����������
//=============================================================================
void InitTile(void)
{
	//�w�i�e�N�X�`���̓ǂݍ���
	g_Ground = LoadTexture((char*)"data/TEXTURE/MapChip.png");
	g_Filter = LoadTexture((char*)"data/TEXTURE/Filter.png");

	g_UW = 1.0f / MAP_WIDTH_PATTERN;
	g_VH = 1.0f / MAP_HEIGHT_PATTERN;

	for (size_t i = 0; i < g_MapAttribData2.size(); i++)
	{
		for (size_t j = 0; j < g_MapAttribData2[1].size(); j++)
		{
			if (g_MapAttribData2[i][j] == 0)continue;
			g_MapAttribData2[i][j] += 6;
		}
	}
	
	// �z������̂�����
	//-------------------------------------------------------�}�b�v��ǉ������炱���ɋL��
	g_MapDatas[0] = g_MapDataS;
	g_MapDatas[1] = g_MapData1;
	g_MapDatas[2] = g_MapData2;
	g_MapDatas[3] = g_MapData3;
	g_MapDatas[4] = g_MapData4;
	g_MapDatas[5] = g_MapData5;
	g_MapDatas[6] = g_MapData6;
	g_MapDatas[7] = g_MapData7;
	g_MapDatas[8] = g_MapData8;
	//-------------------------------------------------------

	std::vector<std::vector<int>> g_MapAttribData;//map�f�[�^�������������̂�����
	g_MapAttribData = g_MapDatas[0].mapData;//�ŏ��̒n�`����
	for (size_t i = 0; i < MAP_MAX; i++)
	{
		int rate = 0;
		//-------------------------------------------------------�����Ń}�b�v�������_���ɑI��
		while (rate == 0)
		{
			//0.0f�����Ė�����菈��
			if (i <= 5)rate = RandomPercent(g_MapData1.rate, g_MapData2.rate, g_MapData3.rate);
			else if (i <= 10)rate = RandomPercent(g_MapData1.rate, g_MapData2.rate, g_MapData3.rate, g_MapData4.rate, 0.0f, 0.0f, g_MapData7.rate, g_MapData8.rate);
			else if (i <= 15)rate = RandomPercent(0.0f, 0.0f, 0.0, g_MapData4.rate, g_MapData5.rate, g_MapData6.rate, g_MapData7.rate, g_MapData8.rate);
		}
		//-------------------------------------------------------
		g_MapAttribData = combineArrays(g_MapAttribData, g_MapDatas[rate].mapData);
	}
	//�ŏI�}�b�v
	g_MapAttribData = combineArrays(g_MapAttribData, g_MapDataG.mapData);

	//�}�b�v�T�C�Y�擾
	mapInitSizeY = g_MapAttribData.size(); // �}�b�v�c�T�C�Y
	mapInitSizeX = (mapInitSizeY > 0) ? g_MapAttribData[0].size() : 0; // �}�b�v���T�C�Y�i�ŏ��̍s����łȂ��ꍇ�j

	//�����_���^�C���z�u
//-------------------------------------------------------�^�C���������炱����ύX
	//�I�[�o�[�t���[���Ȃ��悤�Ɏ����0������
	for (size_t i = 0; i < mapInitSizeY; i++)
	{
		g_MapAttribData[i].push_back(0); //X�����ǉ�
		g_MapAttribData[i].insert(g_MapAttribData[i].begin(), 0); //X�����ǉ�
	}
	
	//Y�����ǉ�
	g_MapAttribData.push_back(std::vector<int>(mapInitSizeX + 2));

	//Y�擪�ǉ�
	g_MapAttribData.insert(g_MapAttribData.begin(), std::vector<int>(mapInitSizeX + 2));

	std::vector<std::vector<int>> g_MapAttribDataCopy = g_MapAttribData;//g_MapAttribDataCopy���Q�Ƃ���g_MapAttribData�����������Ă���

	int rate = 0;//�����_��

	//����̏�񂩂�^�C���̌����ڂ�ύX
	for (int y = 1; y < mapInitSizeY; y++)
	{
		for (int x = 1; x < mapInitSizeX; x++)
		{
			//�G���e�B�e�B��z�u
			//�v���C���[
			if (g_MapAttribData[y][x] == P)
			{
				g_MapAttribData[y][x] = 0;
			}
			//�G�l�~�[
			if (g_MapAttribData[y][x] == E)
			{
				g_MapAttribData[y][x] = 0;
				Spawner::Instance()->SetEnemy({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) });
			}
			if (g_MapAttribData[y][x] == E2)
			{
				g_MapAttribData[y][x] = 0;
				int texPepper = LoadTexture((char*)"data/TEXTURE/paperenemy.png");
				Spawner::Instance()->SetFor<PepperEnemy>({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) }, texPepper, 2.0);
			}
			//��
			if (g_MapAttribData[y][x] == T)
			{
				g_MapAttribData[y][x] = 0;
				int texTree = LoadTexture((char*)"data/TEXTURE/Tree.png");
				//�؂͂ł����̂Œn�ʂɖ��܂�Ȃ��悤������ɔz�u����
				Spawner::Instance()->SetFor<Tree>({ x * static_cast<float>(MAPCHIP_SIZE), y * static_cast<float>(MAPCHIP_SIZE) - 500.0f}, texTree);
			}
			//��(����̂�)
			if (g_MapAttribData[y][x] == C)
			{
				g_MapAttribData[y][x] = 0;
				Spawner::Instance()->SetFor<Castle>({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) });

			}
			//�Ƃ��Ƃ���
			if (g_MapAttribData[y][x] == TT)
			{
				g_MapAttribData[y][x] = 0;
				int texSpikeTree = LoadTexture((char*)"data/TEXTURE/SpikeTree.png");
				//Spawner::Instance()->SetFor<EnemyCastle>({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) + 150 }, texSpikeTree);
			}


			switch (g_MapAttribDataCopy[y][x])
			{
			case 1://�n��
				if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x - 1] == 0)//�n�ʍ��[
				{
					g_MapAttribData[y][x] = 1;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x + 1] == 0)//�n�ʉE�[
				{
					g_MapAttribData[y][x] = 3;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0)//�オ��Ȃ�n�ʏ�
				{
					g_MapAttribData[y][x] = 2;
				}
				else if (g_MapAttribDataCopy[y - 1][x + 1] == 0 && g_MapAttribDataCopy[y][x + 1] == 1)//�n�ʓ��p�E
				{
					g_MapAttribData[y][x] = 8;
				}
				else if (g_MapAttribDataCopy[y - 1][x - 1] == 0 && g_MapAttribDataCopy[y][x - 1] == 1)//�n�ʓ��p�E
				{
					g_MapAttribData[y][x] = 9;
				}
				else//�h��Ԃ�
				{
					//�����_���Ŏ�ނ����߂�
					rate = RandomPercent(40, 15, 40, 5);
					if (rate == 1)g_MapAttribData[y][x] = 4;
					if (rate == 2)g_MapAttribData[y][x] = 5;
					if (rate == 3)g_MapAttribData[y][x] = 6;
					if (rate == 4)g_MapAttribData[y][x] = 7;
				}
				break;

			case 11://�n�ʐ�
				if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x - 1] == 0)//�n�ʍ��[
				{
					g_MapAttribData[y][x] = 11;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x + 1] == 0)//�n�ʉE�[
				{
					g_MapAttribData[y][x] = 13;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0)//�オ��Ȃ�n�ʏ�
				{
					g_MapAttribData[y][x] = 12;
				}
				else if (g_MapAttribDataCopy[y - 1][x + 1] == 0 && g_MapAttribDataCopy[y][x + 1] == 11)//�n�ʓ��p�E
				{
					g_MapAttribData[y][x] = 18;
				}
				else if (g_MapAttribDataCopy[y - 1][x - 1] == 0 && g_MapAttribDataCopy[y][x - 1] == 11)//�n�ʓ��p�E
				{
					g_MapAttribData[y][x] = 19;
				}
				else//�h��Ԃ�
				{
					//�����_���Ŏ�ނ����߂�
					rate = RandomPercent(40, 15, 40, 5);
					if (rate == 1)g_MapAttribData[y][x] = 14;
					if (rate == 2)g_MapAttribData[y][x] = 15;
					if (rate == 3)g_MapAttribData[y][x] = 16;
					if (rate == 4)g_MapAttribData[y][x] = 17;
				}
				break;
				break;
			case 80:

				break;
			default:
				break;
			}



		}
	}

	for (int y = 1; y < mapInitSizeY; y++)
	{
		for (int x = 1; x < mapInitSizeX; x++)
		{
			//�n�ʂł���Α��Ƃ����₷
			if (g_MapAttribData[y][x] == 0)
			{
				if (g_MapAttribData[y + 1][x] == 2)//�ʏ�n��
				{
					rate = RandomPercent(60, 5, 25, 10);
					if (rate == 1) g_MapAttribData[y][x] = 20;
					if (rate == 2) g_MapAttribData[y][x] = 21;
					if (rate == 3) g_MapAttribData[y][x] = 22;
					if (rate == 4) g_MapAttribData[y][x] = 23;
				}
				if (g_MapAttribData[y + 1][x] == 1 || g_MapAttribData[y + 1][x] == 3)//�n�ʒ[
				{
					g_MapAttribData[y][x] = 21;
				}
			}
		}
	}

	//-------------------------------------------------------

	for (int y = 1; y < mapInitSizeY; y++)
	{
		for (int x = 1; x < mapInitSizeX; x++)
		{
			//�}�b�v�f�[�^������
			TILE_DATA tileData;

			int i = x * (y + 1);
			tileData.attrib = g_MapInfo[g_MapAttribData[y][x]].attrib;
			tileData.initAttrib = tileData.attrib;
			tileData.uv = g_MapInfo[g_MapAttribData[y][x]].uv;
			tileData.XYId = D3DXVECTOR2(x, y);
			tileData.pos.x = x * MAPCHIP_SIZE + (MAPCHIP_SIZE * 0.5);
			tileData.pos.y = y * MAPCHIP_SIZE + (MAPCHIP_SIZE * 0.5);
			tileData.initPos.x = tileData.pos.x;
			tileData.initPos.y = tileData.pos.y;
			tileData.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			tileData.move = D3DXVECTOR2(0.0f, 0.0f);
			tileData.spd = TILE_INIT_SPEED;
			tileData.spawn = g_MapInfo[g_MapAttribData[y][x]].spawn;
			tileData.fadeOut = false;

			g_Map.push_back(tileData);

		}
	}

	g_SpawnTimeCou = 0;
	g_SpawnTime = MAP_SPAWN_TIME;
	g_Wave = 0;
	g_SpawnNum = g_Wave + 1; //���̃X�|�[����

	g_MapSize = g_Map.size();

	for (int i = 0; i < g_MapSize; i++)
	{
		//�G�X�|�[��
		if (g_Map[i].spawn == true)
		{
			int ran = RandomPercent(50);
			if (ran == 1)Spawner::Instance()->SetEnemy({ g_Map[i].pos.x, g_Map[i].pos.y - DEFAULT_TILE_SIZE });
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitTile(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTile(void)
{
	g_MapSize = g_Map.size();

	g_SpawnTimeCou = Counter(g_SpawnTimeCou, g_SpawnTime);

	for (int i = 0; i < g_MapSize; i++)
	{
		//�t�F�[�h�������ď���
		if (g_Map[i].fadeOut)
		{
			g_Map[i].color.a *= 0.95f;

			if (g_Map[i].color.a < 0.01f)
			{
				g_Map[i].fadeOut = false;
				g_Map[i].attrib = MAP_ATTRIB_NONE;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTile(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);//�e�N�X�`���̃t�B���^�[��OFF

	for (const auto& it : g_Map)
	{
		if (it.attrib != MAP_ATTRIB_NONE)
		{
			DrawSpriteColorRotateCamera
			(
				g_Ground,
				(int)it.pos.x,
				(int)it.pos.y,
				MAPCHIP_SIZE, MAPCHIP_SIZE,	//���A����
				it.uv.x, it.uv.y,			//����UV���W
				g_UW, g_VH,					//�e�N�X�`�����A��
				it.color.r, it.color.g, it.color.b, it.color.a,
				0.0f
			);
		}


		/*[�f�o�b�O�p]-------------------------------------------*/
		//�}�b�v�������ƂɐF�����\��
		//{
		//	switch (it.attrib)
		//	{
		//	case MAP_ATTRIB_STOP:
		//		DrawSpriteColorRotateCamera
		//		(
		//			g_Filter,
		//			it.pos.x, it.pos.y,
		//			MAPCHIP_SIZE, MAPCHIP_SIZE,
		//			0.5f, 0.5f,
		//			1, 1,
		//			0, 0, 1, 0.2f,
		//			0
		//		);

		//	default:
		//		break;
		//	}

		//	if (it.spawn)
		//	{
		//		DrawSpriteColorRotateCamera
		//		(
		//			g_Filter,
		//			it.pos.x, it.pos.y,
		//			MAPCHIP_SIZE, MAPCHIP_SIZE,
		//			0.5f, 0.5f,
		//			1, 1,
		//			1, 0, 1, 0.2f,
		//			0
		//		);
		//	}
		//}
		/*-------------------------------------------------------*/
	}
}

//=============================================================================
// U���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
float GetTileU(int index)
{
	return ((index % MAP_WIDTH_PATTERN) * (1.0f / MAP_WIDTH_PATTERN));
}

//=============================================================================
// V���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
float GetTileV(int index)
{
	return ((index / MAP_WIDTH_PATTERN) * (1.0f / MAP_HEIGHT_PATTERN));
}

//=============================================================================
// UV���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//=============================================================================
D3DXVECTOR2 GetTileUV(int index)
{
	D3DXVECTOR2 UV = D3DXVECTOR2(GetTileU(index), GetTileV(index));
	return UV;
}

//=============================================================================
// ���W�����̃}�b�v����Ԃ�
// �O�P�Q 
// �R�S�T
// �U�V�W 4�������̍��W
//=============================================================================
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos)
{
	TILE_DATA* tile = new TILE_DATA[9];

	// ���͂̃^�C���̈ʒu���v�Z
	int posX = int(pos.x / MAPCHIP_SIZE);
	int posY = int(pos.y / MAPCHIP_SIZE);

	for (int i = 0; i < 9; i++)
	{
		int offsetX = (i % 3) - 1; // ��i�����璆���ւ̃I�t�Z�b�g�j
		int offsetY = (i / 3) - 1; // �s�i�ォ�璆���ւ̃I�t�Z�b�g�j

		int checkX = posX + offsetX;
		int checkY = posY + offsetY;

		// ���E�`�F�b�N�i�}�b�v�͈̔͊O���`�F�b�N�j
		if (checkX >= 0 && checkX < g_MapSizeX && checkY >= 0 && checkY < g_MapSizeY)
		{
			int checkXY = checkY * checkX;
			tile[i] = g_Map[checkXY];
		}
		else
		{
			// �}�b�v�͈̔͊O�̏ꍇ�A�f�t�H���g�l��ݒ肷�邩�G���[�������s��
			tile[i].attrib = MAP_ATTRIB_ERROR;
			tile[i].pos = D3DXVECTOR2(-1, -1); // �}�b�v�O�̍��W�������l�Ȃ�
		}
	}

	return tile;
}

//=============================================================================
// ���W�����̃}�b�v����Ԃ�(�|�W�V�����)
//=============================================================================
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	TILE_DATA* tile = new TILE_DATA[9];
	//������
	for (size_t i = 0; i < 9; i++)
	{
		tile[i].attrib = MAP_ATTRIB_ERROR;
		tile[i].pos = D3DXVECTOR2(-1, -1); // �}�b�v�O�̍��W�������l�Ȃ�
	}

	D3DXVECTOR2 sizeH = D3DXVECTOR2(size.x * 0.5f, size.y * 0.5f);

	for (const auto& it : g_Map)
	{
		if (it.color.a < 0.5f) continue;

		if ((it.pos.x < pos.x + size.x && it.pos.x > pos.x - size.x) || (it.pos.y < pos.y + size.y && it.pos.y > pos.y - size.y))
		{
			//���̃^�C���擾
			//�E
			if (CollisionRot(pos.x + sizeH.x, pos.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[5].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[5].attrib == MAP_ATTRIB_NONE || tile[5].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[5] = it;
				}
			}
			//��
			if (CollisionRot(pos.x - sizeH.x, pos.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[3].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[3].attrib == MAP_ATTRIB_NONE || tile[3].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[3] = it;
				}
			}
			//��
			if (CollisionRot(pos.x, pos.y + sizeH.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[7].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[7].attrib == MAP_ATTRIB_NONE || tile[7].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[7] = it;
				}
			}
			//��
			if (CollisionRot(pos.x, pos.y - sizeH.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[1].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[1].attrib == MAP_ATTRIB_NONE || tile[1].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[1] = it;
				}
			}
			//����
			if (CollisionRot(pos.x, pos.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[4].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[4].attrib == MAP_ATTRIB_NONE || tile[4].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[4] = it;
				}
			}
		}
	}

	return tile;
}

//=============================================================================
// �����蔻�� [�߂�l] 1: ��, 3: ��, 5: �E, 7: ��
//=============================================================================
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight)
{
	TILE_DATA* tile = GetMapInfo(pos);
	DIRECTION dir = { false };

	for (int j = 0; j < 9; j++)
	{
		if (tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//���ɕǂ�����ꍇ
			if (CollisionRot(pos.x + hsp, pos.y, tile[j].pos.x, tile[j].pos.y, hitBoxWidth, hitBoxHeight, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (j == 3) dir.left = true;
				if (j == 5) dir.right = true;
			}

			//�c�ɕǂ�����ꍇ
			if (CollisionRot(pos.x, pos.y + vsp, tile[j].pos.x, tile[j].pos.y, hitBoxWidth, hitBoxHeight, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (j == 1) dir.up = true;
				if (j == 7) dir.down = true;
			}
		}
	}
	delete[] tile;
	return dir;
}

//=============================================================================
// �}�b�v�̃^�C���ύX [����] 1: ���̃}�b�v, 2: �㏑������}�b�v, 3: �㏑������ӏ�
//=============================================================================
void ChangeTile(std::vector<std::vector<int>>& map1, std::vector<std::vector<int>> map2, int group)
{
	int startPos = map2[0].size() * (group - 1);

	for (int i = 0; i < map2.size(); i++)
	{
		for (int j = 0; j < map2[0].size(); j++)
		{
			map1[i].insert(map1[i].begin() + j + startPos, map2[i][j]);
		}
	}
}

void CatTile(float minPosX, float maxPosX)
{

	for (size_t i = 0; i < g_MapSize; i++)
	{
		if (g_Map[i].pos.x >= minPosX && g_Map[i].pos.x <= maxPosX)
		{
			g_Map[i].fadeOut = true;
		}
	}
}

std::vector<std::vector<int>> combineArrays(const std::vector<std::vector<int>>& arr1, const std::vector<std::vector<int>>& arr2)
{
	// arr1��arr2�����Ɍ������ĐV�����z����쐬
	std::vector<std::vector<int>> combinedArray = arr1;

	for (size_t i = 0; i < arr1.size(); ++i)
	{
		combinedArray[i].insert(combinedArray[i].end(), arr2[i].begin(), arr2[i].end());
	}

	return combinedArray;
}

void SetTilePlayer(Player* player)
{
	p_Player = player;
}

D3DXVECTOR2 GetMapSize()
{
	D3DXVECTOR2 mapSize = D3DXVECTOR2(mapInitSizeX * MAPCHIP_SIZE, mapInitSizeY * MAPCHIP_SIZE);
	return mapSize;
}