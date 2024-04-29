/*==============================================================================

   �}�b�v [Map.cpp]
														 Author : �n� �C
														 Date   : 2024/01/18
--------------------------------------------------------------------------------

==============================================================================*/
#include <vector>
#include "Map.h"
#include "Library.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Map::Map(GameWorld* gameWorld)
	:m_pGameWorld(gameWorld)
{

}

Map::~Map()
{
}

//=============================================================================
// �X�V����
//=============================================================================
void Map::Update()
{
	D3DXVECTOR3 playerPos = m_pGameWorld->GetPlayer()->GetPos();
	D3DXVECTOR2 playerArray = GetArrayPos(playerPos);
	
	//�v���C���[�̈ʒu���L�^
	if (
		playerArray.x >= 0 && playerArray.x < MAX_TILE_X &&
		playerArray.y >= 0 && playerArray.y < MAX_TILE_Y
		)
	{
		m_Map[int(m_PlayerOldArrayPos.y)][int(m_PlayerOldArrayPos.x)].Player = false;//�O�̃v���C���[�ʒu��������
		m_Map[int(playerArray.y)][int(playerArray.x)].Player = true;

		if (playerPos != m_PlayerOldPos)//�v���C���[���ړ�����
		{
			for (auto& it : m_TileHistory)
			{
				it->TileState = TILE_STATE_NONE;
			}
			m_TileHistory.clear();
			//m_pGameWorld->DestroyObject("ClearBoxGreen");//�f�o�b�O�p


			SoundEcho(playerArray);
			for (auto& it : m_TileHistory)
			{
				SoundEcho(it->arrayPos);
				if (m_TileHistory.size() > m_pGameWorld->GetPlayer()->GetSoundEchoValue())break;
 			}

			for (auto& it : m_TileHistory)
			{
				it->TileState = HEAR_SOUND;
				//m_pGameWorld->CreateClearBoxGreen(D3DXVECTOR3(it->pos.x, it->pos.y + 2.0f, it->pos.z));//�f�o�b�O�p
			}
			m_PlayerNoMoveCou = 120;

		}
		else//�v���C�[���~�܂��Ă���
		{
			m_PlayerNoMoveCou--;
			if (m_PlayerNoMoveCou <= 0)
			{
				m_pGameWorld->DestroyObject("ClearBoxGreen");
			}
		}
	}

	//�ߋ��L�^�X�V
	m_PlayerOldPos = playerPos;
	m_PlayerOldArrayPos = playerArray;
}


//=============================================================================
// �^�C���̃p�^�[�������߂�
//=============================================================================
void Map::CreateMap()
{
	int ran = 0;
	std::vector<D3DXVECTOR2> playerSpawnList;

	for (int i = 1; i < MAX_TILE_Y - 1; i++)
	{
		for (int j = 1; j < MAX_TILE_X - 1; j++)
        {
			m_Map[i][j].ItemAttribute = ITEM_ATTRIBUTE_NONE;

            switch (m_Map[i][j].TileAttribute)
            {
            case AIR://�������ʍs�\
				//�A�C�e���z�u
				//�ׂ荇����3�ӂ��ǂ�������A�C�e��
				if ((m_Map[i][j + 1].TileAttribute == STOP && m_Map[i][j - 1].TileAttribute == STOP) &&
					m_Map[i - 1][j].TileAttribute == STOP) {
					m_Map[i][j].ItemAttribute = ITEM_SET;
				}
				else if ((m_Map[i + 1][j].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP) &&
					m_Map[i][j - 1].TileAttribute == STOP) {
					m_Map[i][j].ItemAttribute = ITEM_SET;
				}
				else if ((m_Map[i][j + 1].TileAttribute == STOP && m_Map[i][j - 1].TileAttribute == STOP) &&
					m_Map[i + 1][j].TileAttribute == STOP) {
					m_Map[i][j].ItemAttribute = ITEM_SET;
				}
				else if ((m_Map[i + 1][j].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP) &&
					m_Map[i][j + 1].TileAttribute == STOP) {
					m_Map[i][j].ItemAttribute = ITEM_SET;
				}
				else
				{
					if ((m_Map[i][j + 1].TileAttribute != STOP && m_Map[i][j - 1].TileAttribute != STOP) &&
						(m_Map[i + 1][j].TileAttribute != STOP && m_Map[i - 1][j].TileAttribute != STOP))
					{
						//�v���C���[�X�|�[�����n�Ƃ���
						playerSpawnList.push_back(D3DXVECTOR2(float(j), float(i)));
					}
				}

            case STOP://�������ʍs�s��
				//���Ŗ��߂�
				m_Map[i][j].TilePattern = TILE_PATTERN_NONE;
				m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//�ǂ����̕ӂ��󂾂������
				if (m_Map[i + 1][j].TileAttribute == AIR || m_Map[i - 1][j].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				if (m_Map[i][j + 1].TileAttribute == AIR || m_Map[i][j - 1].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
				}
				//�㉺�����E2�ӂ��󂾂������
				if (m_Map[i + 1][j].TileAttribute == AIR && m_Map[i - 1][j].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				if (m_Map[i][j + 1].TileAttribute == AIR && m_Map[i][j - 1].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
				}

				//3�ӂ��󂾂�����ǒ[
				if ((m_Map[i][j + 1].TileAttribute == AIR && m_Map[i][j - 1].TileAttribute == AIR) &&
					m_Map[i - 1][j].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL_END;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				if ((m_Map[i + 1][j].TileAttribute == AIR && m_Map[i - 1][j].TileAttribute == AIR) &&
					m_Map[i][j - 1].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL_END;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
				}
				if ((m_Map[i][j + 1].TileAttribute == AIR && m_Map[i][j - 1].TileAttribute == AIR) &&
					m_Map[i + 1][j].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL_END;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(180.0f), 0.0f, 0.0f);
				}
				if ((m_Map[i + 1][j].TileAttribute == AIR && m_Map[i - 1][j].TileAttribute == AIR) &&
					m_Map[i][j + 1].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL_END;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(270.0f), 0.0f, 0.0f);
				}

				//4�ӂ��󂾂����璌
				if ((m_Map[i][j + 1].TileAttribute == AIR && m_Map[i][j - 1].TileAttribute == AIR) &&
					(m_Map[i + 1][j].TileAttribute == AIR && m_Map[i - 1][j].TileAttribute == AIR)) {
					m_Map[i][j].TilePattern = PILLAR;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				//�ׂ荇����2�ӂ��ǂ�������p
				if (m_Map[i][j + 1].TileAttribute == STOP && m_Map[i + 1][j].TileAttribute == STOP) {
					m_Map[i][j].TilePattern = CORNER;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(180.0f), 0.0f, 0.0f);
				}
				if (m_Map[i][j - 1].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP) {
					m_Map[i][j].TilePattern = CORNER;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				if (m_Map[i][j + 1].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP) {
					m_Map[i][j].TilePattern = CORNER;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(270.0f), 0.0f, 0.0f);
				}
				if (m_Map[i][j - 1].TileAttribute == STOP && m_Map[i + 1][j].TileAttribute == STOP) {
					m_Map[i][j].TilePattern = CORNER;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
				}

				//�ׂ荇����3�ӂ��ǂ�������T��
				if ((m_Map[i][j + 1].TileAttribute == STOP && m_Map[i][j - 1].TileAttribute == STOP) &&
					m_Map[i - 1][j].TileAttribute == STOP) {
					m_Map[i][j].TilePattern = T;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				if ((m_Map[i + 1][j].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP) &&
					m_Map[i][j - 1].TileAttribute == STOP) {
					m_Map[i][j].TilePattern = T;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
				}
				if ((m_Map[i][j + 1].TileAttribute == STOP && m_Map[i][j - 1].TileAttribute == STOP) &&
					m_Map[i + 1][j].TileAttribute == STOP) {
					m_Map[i][j].TilePattern = T;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(180.0f), 0.0f, 0.0f);
				}
				if ((m_Map[i + 1][j].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP) &&
					m_Map[i][j + 1].TileAttribute == STOP) {
					m_Map[i][j].TilePattern = T;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(270.0f), 0.0f, 0.0f);
				}

				//�S�ӂ��ǂ�������\��
				if ((m_Map[i][j + 1].TileAttribute == STOP && m_Map[i][j - 1].TileAttribute == STOP) &&
					(m_Map[i + 1][j].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP)) {
					m_Map[i][j].TilePattern = CROSS;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				//�����Ȃ��Ƃ���ɂ����
				if ((m_Map[i][j + 1].TileAttribute == STOP && m_Map[i][j - 1].TileAttribute == STOP) &&
					(m_Map[i + 1][j].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP) &&
					(m_Map[i + 1][j + 1].TileAttribute == STOP && m_Map[i + 1][j - 1].TileAttribute == STOP) &&
					(m_Map[i - 1][j + 1].TileAttribute == STOP && m_Map[i - 1][j - 1].TileAttribute == STOP)) {
					m_Map[i][j].TilePattern = TILE_PATTERN_NONE;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				if (m_Map[i][j].TilePattern == TILE_PATTERN_NONE)m_Map[i][j].TileAttribute = OUT_RANGE;

                break;

            default:
                break;
            }
        }
    }

	//�z�u
	//�v���C���[�z�u�ꏊ�����߂�
	int spawnRan = GetRandomInt(0, int(playerSpawnList.size()) - 1);
	D3DXVECTOR2 playerSpawnArray = playerSpawnList[spawnRan];

	m_PlayerSpawnPos = GetXYPos(playerSpawnArray);
	m_PlayerSpawnPos.y = 50.0f;

	m_pGameWorld->GetPlayer()->SetPos(m_PlayerSpawnPos);

	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			m_Map[i][j].arrayPos = D3DXVECTOR2(float(j), float(i));//�z��ʒu���擾
			m_Map[i][j].pos = GetXYPos(D3DXVECTOR2(float(j), float(i)));//�ʒu���擾

			//�A�C�e���z�u
			switch (m_Map[i][j].ItemAttribute)
			{
			case ITEM_SET:
				if (!(j >= m_PlayerSpawnPos.x - 10 && j <= m_PlayerSpawnPos.x + 10 && i >= m_PlayerSpawnPos.y - 10 && i <= m_PlayerSpawnPos.y + 10))//�v���C���[���X�|�[���߂�����Ȃ����
				{
					switch (RandomPercent(60, 30, 10))
					{
					case 1:
						m_pGameWorld->CreateCoinGold(D3DXVECTOR3(TILE_OFFSET * j, 10.5f, TILE_OFFSET * i));

						break;
					case 2:
						m_pGameWorld->CreateCoinGold(D3DXVECTOR3(TILE_OFFSET * j, 10.5f, TILE_OFFSET * i));
						m_pGameWorld->CreateEnemy(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), D3DXVECTOR3(0.0f, 0.0f, 0.0f), this);
						break;
					case 3:
						m_pGameWorld->CreateEnemy(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), D3DXVECTOR3(0.0f, 0.0f, 0.0f), this);
						break;
					default:
						break;
					}
				}
				break;

			default:
				break;
			}

			//�^�C���z�u
			switch (m_Map[i][j].TileAttribute)
			{
			case OUT_RANGE://�����Ȃ�
				m_pGameWorld->CreateClearBoxRed(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i));
				break;

			case AIR://�������ʍs�\
				m_pGameWorld->CreateClearBoxWater(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i));
				m_pGameWorld->CreateAisle(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i));

				if (!(j >= playerSpawnArray.x - 10 && j <= playerSpawnArray.x + 10 && i >= playerSpawnArray.y - 10 && i <= playerSpawnArray.y + 10))//�v���C���[���X�|�[���߂�����Ȃ����
				{
					ran = RandomPercent(3.0f, 0.8f);

					if (ran == 1)m_pGameWorld->CreateCoinGold(D3DXVECTOR3(TILE_OFFSET * j, 10.5f, TILE_OFFSET * i));
					if (ran == 2)m_pGameWorld->CreateEnemy(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), D3DXVECTOR3(0.0f, 0.0f, 0.0f), this);
				}

				break;

			case STOP://�������ʍs�s��

				if (m_Map[i][j].TilePattern == WALL)m_pGameWorld->CreateWall(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), m_Map[i][j].Dir);
				if (m_Map[i][j].TilePattern == WALL_END) m_pGameWorld->CreateWallEnd(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), m_Map[i][j].Dir);
				if (m_Map[i][j].TilePattern == PILLAR) m_pGameWorld->CreatePillar(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), m_Map[i][j].Dir);
				if (m_Map[i][j].TilePattern == CORNER) m_pGameWorld->CreateCorner(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), m_Map[i][j].Dir);
				if (m_Map[i][j].TilePattern == T) m_pGameWorld->CreateT(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), m_Map[i][j].Dir);
				if (m_Map[i][j].TilePattern == CROSS) m_pGameWorld->CreateCross(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), m_Map[i][j].Dir);

				//m_pGameWorld->CreateClearBoxRed(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i));
				break;

			default:
				break;
			}
		}
	}
}

//=============================================================================
// ����̃^�C������Ԃ�
// �� 1 ��  �o ����
// 4 P 2  1,2,3,4 �̏���Ԃ�	
// �� 3 ��  �͈͊O�ł͏����擾���Ȃ��̂Œ���
//=============================================================================
AROUND_TILE Map::GetAroundTile(D3DXVECTOR3 pos) const
{
	D3DXVECTOR2 ArrayPos = GetArrayPos(pos);
	AROUND_TILE aroundTile{};

	//�͈͊O�ł͏����擾���Ȃ�
	if (
		ArrayPos.x < 0 || ArrayPos.x > MAX_TILE_X ||
		ArrayPos.y < 0 || ArrayPos.y > MAX_TILE_Y
		)return aroundTile = AROUND_TILE{};

	int tempPos = 0;
	//��(1)���擾
	tempPos = int(ArrayPos.y) + 1;
	if (tempPos < MAX_TILE_Y)
		aroundTile.Top = m_Map[tempPos][int(ArrayPos.x)];
	else aroundTile.Top.TileAttribute = OUT_RANGE;
	//�E(2)���擾
	tempPos = int(ArrayPos.x) + 1;
	if (tempPos < MAX_TILE_X)
		aroundTile.Right = m_Map[int(ArrayPos.y)][tempPos];
	else aroundTile.Right.TileAttribute = OUT_RANGE;
	//��(3)���擾
	tempPos = int(ArrayPos.y) - 1;
	if (tempPos >= 0)
		aroundTile.Under = m_Map[tempPos][int(ArrayPos.x)];
	else aroundTile.Under.TileAttribute = OUT_RANGE;
	//��(4)���擾
	tempPos = int(ArrayPos.x) - 1;
	if (tempPos >= 0)
		aroundTile.Left = m_Map[int(ArrayPos.y)][tempPos];
	else aroundTile.Left.TileAttribute = OUT_RANGE;
	 
	return aroundTile;
}

AROUND_TILE Map::GetAroundTile(D3DXVECTOR2 pos) const
{
	AROUND_TILE aroundTile{};

	//�͈͊O�ł͏����擾���Ȃ�
	if (
		pos.x < 0 || pos.x > MAX_TILE_X ||
		pos.y < 0 || pos.y > MAX_TILE_Y
		)return aroundTile = AROUND_TILE{};

	int tempPos = 0;
	//��(1)���擾
	tempPos = int(pos.y) + 1;
	if (tempPos < MAX_TILE_Y)
		aroundTile.Top = m_Map[tempPos][int(pos.x)];
	else aroundTile.Top.TileAttribute = OUT_RANGE;
	//�E(2)���擾
	tempPos = int(pos.x) + 1;
	if (tempPos < MAX_TILE_X)
		aroundTile.Right = m_Map[int(pos.y)][tempPos];
	else aroundTile.Right.TileAttribute = OUT_RANGE;
	//��(3)���擾
	tempPos = int(pos.y) - 1;
	if (tempPos >= 0)
		aroundTile.Under = m_Map[tempPos][int(pos.x)];
	else aroundTile.Under.TileAttribute = OUT_RANGE;
	//��(4)���擾
	tempPos = int(pos.x) - 1;
	if (tempPos >= 0)
		aroundTile.Left = m_Map[int(pos.y)][tempPos];
	else aroundTile.Left.TileAttribute = OUT_RANGE;

	return aroundTile;
}



//=============================================================================
// �|�W�V�����̃^�C�����擾
//=============================================================================
TILE Map::GetTile(D3DXVECTOR3 pos) const
{
	D3DXVECTOR2 ArrayPos = GetArrayPos(pos);
	return m_Map[int(ArrayPos.y)][int(ArrayPos.x)];
}

//=============================================================================
// �|�W�V�������}�b�v�̍s��ԍ��ɕϊ�
//=============================================================================
D3DXVECTOR2 Map::GetArrayPos(D3DXVECTOR3 pos) const
{
	D3DXVECTOR2 Pos = D3DXVECTOR2(pos.x + TILE_OFFSET_HALF, pos.z + TILE_OFFSET_HALF);
	D3DXVECTOR2 ArrayPos = Pos / TILE_OFFSET;

	ArrayPos.x = std::floor(ArrayPos.x);
	ArrayPos.y = std::floor(ArrayPos.y);

	return D3DXVECTOR2(ArrayPos.x, ArrayPos.y);
}

//=============================================================================
// �}�b�v�̍s��ԍ����|�W�V�����ɕϊ�
//=============================================================================
D3DXVECTOR3 Map::GetXYPos(D3DXVECTOR2 arrayPos) const
{
	D3DXVECTOR2 Pos = arrayPos * TILE_OFFSET;

	return D3DXVECTOR3(Pos.x, 0.1f, Pos.y);
}

//=============================================================================
//�����_���Ƀ}�b�v�𐶐�
//=============================================================================
void Map::RandomMapCreate(int roomNumMax, int roomNumMin, int roomScaleMax, int roomScaleMin)
{
	TILE_ATTRIBUTE attribute[ATTRIBUTE_Y][ATTRIBUTE_X]{};//�����ǂɂ��邽�ߎ���𔲂����}�b�v���쐬
	int roomNum;
	int randomX[255] = { 0 };
	int randomY[255] = { 0 };
	int scaleSelect = 0;

	//�}�b�v��ǂŖ��ߐs����
	for (int i = 0; i < ATTRIBUTE_Y; i++)
	{
		for (int j = 0; j < ATTRIBUTE_X; j++)
		{
			attribute[i][j] = STOP;
		}
	}

	//�����̐���
	roomNum = rand() % (roomNumMax - roomNumMin + 1) + roomNumMin;//�����̐�
	for (int i = 0; i < roomNum; i++)
	{
		randomX[i] = GetRandomInt(0, ATTRIBUTE_X - 1);
		randomY[i] = GetRandomInt(0, ATTRIBUTE_Y - 1);

		for (int j = 0; j < rand() % (roomScaleMax - roomScaleMin + 1) + roomScaleMin; j++)//�����̏c�̒���
		{
			for (int k = 0; k < rand() % (roomScaleMax - roomScaleMin + 1) + roomScaleMin; k++)//�����̉��̒���
			{
				if ((randomY[i] + j >= 1) && (randomY[i] + j < ATTRIBUTE_Y - 1) && (randomX[i] + k >= 1) && (randomX[i] + k < ATTRIBUTE_X - 1))//�}�b�v�O�ɂ͐������Ȃ�
				{
					attribute[randomY[i] + j][randomX[i] + k] = AIR;
				}
			}
		}
	}

	//�L���̐���
	for (int i = 0; i < roomNum + 1; i++)//�����������[�v(�ŏ��̕����ƍŌ�̕������Ȃ��邽�� +1)
	{
		int targetRoom = i + 1;//�Ȃ���̕���
		int randomXUpdate = 0;

		if (roomNum < targetRoom)//�ŏ��̕����ƍŌ�̕������Ȃ���
		{
			targetRoom = 0;
		}

		if (randomX[i] < randomX[targetRoom])
		{
			for (int j = 0; j < abs(randomX[i] - randomX[targetRoom]); j++)
			{
				attribute[randomY[i]][randomX[i] + j + 1] = AIR;
				randomXUpdate = randomX[i] + j + 1;//�ŏIx���W����
			}
		}
		else if (randomX[i] > randomX[targetRoom])
		{
			for (int j = 0; j < abs(randomX[i] - randomX[targetRoom]); j++)
			{
				attribute[randomY[i]][randomX[i] - j - 1] = AIR;
				randomXUpdate = randomX[i] - j - 1;//�ŏIx���W����
			}
		}
		else
		{
			randomXUpdate = randomX[i];//�ŏIx���W����
		}

		if (randomY[i] < randomY[targetRoom])
		{
			for (int j = 0; j < abs(randomY[i] - randomY[targetRoom]); j++)
			{
				int newY = randomY[i] + j + 1;
				if (newY < ATTRIBUTE_Y)
				{
					attribute[newY][randomXUpdate] = AIR;
				}
			}
		}
		else if (randomY[i] > randomY[targetRoom])
		{
			for (int j = 0; j < abs(randomY[i] - randomY[targetRoom]); j++)
			{
				attribute[randomY[i] - j - 1][randomXUpdate] = AIR;
			}
		}
	}

	//����̕ǂ�����}�b�v�ɑ��
	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			//���ׂĂɑ���A�ŏI�I�Ɉ�Ԓ[�����R���ɂȂ�
			m_Map[i][j].TileAttribute = OUT_RANGE;

			//�����������͕ǂɂ���
			if ((i == 1 || j == 1 || i == MAX_TILE_Y - 2 || j == MAX_TILE_X - 2) && 
				(i != 0 && j != 0 && i != MAX_TILE_Y - 1 && j != MAX_TILE_X - 1))
			{
				m_Map[i][j].TileAttribute = STOP;
			}

			if (i > 1 && j > 1 && i < MAX_TILE_Y - 2 && j < MAX_TILE_X - 2)
			{
				m_Map[i][j].TileAttribute = attribute[i - 2][j - 2];
			}
		}
	}
}

void Map::SoundEcho(D3DXVECTOR2 arrayPos)
{
	AROUND_TILE aroundTile = GetAroundTile(D3DXVECTOR2(float(arrayPos.x), float(arrayPos.y)));//�v���C���[�̎���̃^�C�����擾
	TILE tile[4] = { aroundTile.Top, aroundTile.Right, aroundTile.Under, aroundTile.Left };


	for (size_t i = 0; i < 4; i++)
	{
		if (
			tile[i].arrayPos.x >= 0 && tile[i].arrayPos.x < MAX_TILE_X &&
			tile[i].arrayPos.y >= 0 && tile[i].arrayPos.y < MAX_TILE_Y
			)
		{
			if (tile[i].TileAttribute != STOP && tile[i].TileAttribute != OUT_RANGE)
			{
				m_TileHistory.push_back(&m_Map[int(tile[i].arrayPos.y)][int(tile[i].arrayPos.x)]);//�����Ɏc��
			}
		}
	}
}