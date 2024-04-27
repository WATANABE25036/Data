//===================================================
//�^�C��(tile.h)
//Auhor:�n� �C	Date:2023.8.26
//===================================================
#pragma once

#include <list>
#include <array>
#include <vector>
#include "main.h"
#include "renderer.h"

class Player;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAPCHIP_SIZE (DEFAULT_TILE_SIZE) //�}�b�v�`�b�v�T�C�Y
#define MAP_SIZE_X (500) //1�}�b�v(1���)��12�L�����N�^�[ ��g_MapSizeX�Ɠ����ɂ���
#define MAP_SIZE_Y (14) //1�}�b�v(1���)�c7�L�����N�^�[ ��g_MapSizeY�Ɠ����ɂ���
#define MAP_WIDTH_PATTERN (4)
#define MAP_HEIGHT_PATTERN (7)
#define MAP_FRAME_MAX (MAP_WIDTH_PATTERN * MAP_HEIGHT_PATTERN)//�t���[����
#define MAP_SPAWN_TIME (60 * 15)	//�G�o���Ԋu
#define STAGE_SIZE  (MAP_SIZE_X * MAPCHIP_SIZE)
#define MAP_MAX (15)
#define TILE_INIT_SPEED (1)

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum MAPATTRIB //�}�b�v�̃A�g���r���[�g(����)
{//�ǉ�������^�C���擾�֐����X�V���Ȃ��Ə����ђʂ���
	MAP_ATTRIB_NONE = 0,	//�ʉ߉\(�`�悳��Ȃ��̂Œ���)
	MAP_ATTRIB_STOP,		//�i���s��
	MAP_ATTRIB_NATURE,		//���R
	MAP_ATTRIB_SLOW,		//���x�ቺ
	MAP_ATTRIB_ERROR
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct MAP_DATA_T //�^�C����ނ��Ƃ̃f�[�^
{
	D3DXVECTOR2 uv;		//�e�N�X�`���̍�����W
	MAPATTRIB attrib;	//���̃}�b�v�`�b�v��������
	bool spawn;			//�G�����̃u���b�N�ʒu�ɗN�����ǂ���
};

struct TILE_DATA //�^�C�����Ƃ̃f�[�^
{
	D3DXVECTOR2 uv;
	D3DXVECTOR2 pos;	//���S���W
	MAPATTRIB attrib;	//���̃}�b�v�`�b�v��������
	bool spawn;			//�G�����̃u���b�N�ʒu�ɗN�����ǂ���
	int groupId;			//�O���[�v���ʗp
	D3DXCOLOR color;
	float spd; //�ړ��X�s�[�h
	D3DXVECTOR2 move; //�ړ���
	D3DXVECTOR2 initPos;	//���S���W
	MAPATTRIB initAttrib;	//���̃}�b�v�`�b�v��������
	D3DXVECTOR2 XYId;//X�̉��Ԗڂ���Y�̉��Ԗڂ�
	bool fadeOut;//�t�F�[�h�A�E�g���Ă邩�ǂ���
};

struct POLYGON
{
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		spd;	//���x�x�N�g��
	D3DXCOLOR		color;	//���_�J���[
};

struct DIRECTION
{
	bool right;
	bool down;
	bool up;
	bool left;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTile(void);
void UninitTile(void);
void UpdateTile(void);
void DrawTile(void);
float GetTileU(int index);
float GetTileV(int index);
D3DXVECTOR2 GetTileUV(int index);
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos);//���W�����̃}�b�v����Ԃ�
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos, D3DXVECTOR2 size);
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight);
void ChangeTile(std::vector<std::vector<int>>& map1, std::vector<std::vector<int>> map2, int group);
void CatTile(float minPosX, float maxPosX);
std::vector<std::vector<int>> combineArrays(const std::vector<std::vector<int>>& arr1, const std::vector<std::vector<int>>& arr2);//�}�b�v������
void SetTilePlayer(Player* player);
D3DXVECTOR2 GetMapSize();
