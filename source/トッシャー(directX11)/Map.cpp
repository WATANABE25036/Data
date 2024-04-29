/*==============================================================================

   マップ [Map.cpp]
														 Author : 渡邉 修
														 Date   : 2024/01/18
--------------------------------------------------------------------------------

==============================================================================*/
#include <vector>
#include "Map.h"
#include "Library.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
Map::Map(GameWorld* gameWorld)
	:m_pGameWorld(gameWorld)
{

}

Map::~Map()
{
}

//=============================================================================
// 更新処理
//=============================================================================
void Map::Update()
{
	D3DXVECTOR3 playerPos = m_pGameWorld->GetPlayer()->GetPos();
	D3DXVECTOR2 playerArray = GetArrayPos(playerPos);
	
	//プレイヤーの位置を記録
	if (
		playerArray.x >= 0 && playerArray.x < MAX_TILE_X &&
		playerArray.y >= 0 && playerArray.y < MAX_TILE_Y
		)
	{
		m_Map[int(m_PlayerOldArrayPos.y)][int(m_PlayerOldArrayPos.x)].Player = false;//前のプレイヤー位置情報を消す
		m_Map[int(playerArray.y)][int(playerArray.x)].Player = true;

		if (playerPos != m_PlayerOldPos)//プレイヤーが移動した
		{
			for (auto& it : m_TileHistory)
			{
				it->TileState = TILE_STATE_NONE;
			}
			m_TileHistory.clear();
			//m_pGameWorld->DestroyObject("ClearBoxGreen");//デバッグ用


			SoundEcho(playerArray);
			for (auto& it : m_TileHistory)
			{
				SoundEcho(it->arrayPos);
				if (m_TileHistory.size() > m_pGameWorld->GetPlayer()->GetSoundEchoValue())break;
 			}

			for (auto& it : m_TileHistory)
			{
				it->TileState = HEAR_SOUND;
				//m_pGameWorld->CreateClearBoxGreen(D3DXVECTOR3(it->pos.x, it->pos.y + 2.0f, it->pos.z));//デバッグ用
			}
			m_PlayerNoMoveCou = 120;

		}
		else//プレイーが止まっている
		{
			m_PlayerNoMoveCou--;
			if (m_PlayerNoMoveCou <= 0)
			{
				m_pGameWorld->DestroyObject("ClearBoxGreen");
			}
		}
	}

	//過去記録更新
	m_PlayerOldPos = playerPos;
	m_PlayerOldArrayPos = playerArray;
}


//=============================================================================
// タイルのパターンを決める
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
            case AIR://属性が通行可能
				//アイテム配置
				//隣り合った3辺が壁だったらアイテム
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
						//プレイヤースポーン候補地とする
						playerSpawnList.push_back(D3DXVECTOR2(float(j), float(i)));
					}
				}

            case STOP://属性が通行不可
				//柱で埋める
				m_Map[i][j].TilePattern = TILE_PATTERN_NONE;
				m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//どこかの辺が空だったら壁
				if (m_Map[i + 1][j].TileAttribute == AIR || m_Map[i - 1][j].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				if (m_Map[i][j + 1].TileAttribute == AIR || m_Map[i][j - 1].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
				}
				//上下か左右2辺が空だったら壁
				if (m_Map[i + 1][j].TileAttribute == AIR && m_Map[i - 1][j].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
				if (m_Map[i][j + 1].TileAttribute == AIR && m_Map[i][j - 1].TileAttribute == AIR) {
					m_Map[i][j].TilePattern = WALL;
					m_Map[i][j].Dir = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
				}

				//3辺が空だったら壁端
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

				//4辺が空だったら柱
				if ((m_Map[i][j + 1].TileAttribute == AIR && m_Map[i][j - 1].TileAttribute == AIR) &&
					(m_Map[i + 1][j].TileAttribute == AIR && m_Map[i - 1][j].TileAttribute == AIR)) {
					m_Map[i][j].TilePattern = PILLAR;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				//隣り合った2辺が壁だったら角
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

				//隣り合った3辺が壁だったらT字
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

				//全辺が壁だったら十字
				if ((m_Map[i][j + 1].TileAttribute == STOP && m_Map[i][j - 1].TileAttribute == STOP) &&
					(m_Map[i + 1][j].TileAttribute == STOP && m_Map[i - 1][j].TileAttribute == STOP)) {
					m_Map[i][j].TilePattern = CROSS;
					m_Map[i][j].Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				//見えないところにある壁
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

	//配置
	//プレイヤー配置場所を決める
	int spawnRan = GetRandomInt(0, int(playerSpawnList.size()) - 1);
	D3DXVECTOR2 playerSpawnArray = playerSpawnList[spawnRan];

	m_PlayerSpawnPos = GetXYPos(playerSpawnArray);
	m_PlayerSpawnPos.y = 50.0f;

	m_pGameWorld->GetPlayer()->SetPos(m_PlayerSpawnPos);

	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			m_Map[i][j].arrayPos = D3DXVECTOR2(float(j), float(i));//配列位置を取得
			m_Map[i][j].pos = GetXYPos(D3DXVECTOR2(float(j), float(i)));//位置を取得

			//アイテム配置
			switch (m_Map[i][j].ItemAttribute)
			{
			case ITEM_SET:
				if (!(j >= m_PlayerSpawnPos.x - 10 && j <= m_PlayerSpawnPos.x + 10 && i >= m_PlayerSpawnPos.y - 10 && i <= m_PlayerSpawnPos.y + 10))//プレイヤーリスポーン近くじゃなければ
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

			//タイル配置
			switch (m_Map[i][j].TileAttribute)
			{
			case OUT_RANGE://属性なし
				m_pGameWorld->CreateClearBoxRed(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i));
				break;

			case AIR://属性が通行可能
				m_pGameWorld->CreateClearBoxWater(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i));
				m_pGameWorld->CreateAisle(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i));

				if (!(j >= playerSpawnArray.x - 10 && j <= playerSpawnArray.x + 10 && i >= playerSpawnArray.y - 10 && i <= playerSpawnArray.y + 10))//プレイヤーリスポーン近くじゃなければ
				{
					ran = RandomPercent(3.0f, 0.8f);

					if (ran == 1)m_pGameWorld->CreateCoinGold(D3DXVECTOR3(TILE_OFFSET * j, 10.5f, TILE_OFFSET * i));
					if (ran == 2)m_pGameWorld->CreateEnemy(D3DXVECTOR3(TILE_OFFSET * j, 0.1f, TILE_OFFSET * i), D3DXVECTOR3(0.0f, 0.0f, 0.0f), this);
				}

				break;

			case STOP://属性が通行不可

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
// 周りのタイル情報を返す
// □ 1 □  Ｐ 自分
// 4 P 2  1,2,3,4 の情報を返す	
// □ 3 □  範囲外では情報を取得しないので注意
//=============================================================================
AROUND_TILE Map::GetAroundTile(D3DXVECTOR3 pos) const
{
	D3DXVECTOR2 ArrayPos = GetArrayPos(pos);
	AROUND_TILE aroundTile{};

	//範囲外では情報を取得しない
	if (
		ArrayPos.x < 0 || ArrayPos.x > MAX_TILE_X ||
		ArrayPos.y < 0 || ArrayPos.y > MAX_TILE_Y
		)return aroundTile = AROUND_TILE{};

	int tempPos = 0;
	//上(1)情報取得
	tempPos = int(ArrayPos.y) + 1;
	if (tempPos < MAX_TILE_Y)
		aroundTile.Top = m_Map[tempPos][int(ArrayPos.x)];
	else aroundTile.Top.TileAttribute = OUT_RANGE;
	//右(2)情報取得
	tempPos = int(ArrayPos.x) + 1;
	if (tempPos < MAX_TILE_X)
		aroundTile.Right = m_Map[int(ArrayPos.y)][tempPos];
	else aroundTile.Right.TileAttribute = OUT_RANGE;
	//下(3)情報取得
	tempPos = int(ArrayPos.y) - 1;
	if (tempPos >= 0)
		aroundTile.Under = m_Map[tempPos][int(ArrayPos.x)];
	else aroundTile.Under.TileAttribute = OUT_RANGE;
	//左(4)情報取得
	tempPos = int(ArrayPos.x) - 1;
	if (tempPos >= 0)
		aroundTile.Left = m_Map[int(ArrayPos.y)][tempPos];
	else aroundTile.Left.TileAttribute = OUT_RANGE;
	 
	return aroundTile;
}

AROUND_TILE Map::GetAroundTile(D3DXVECTOR2 pos) const
{
	AROUND_TILE aroundTile{};

	//範囲外では情報を取得しない
	if (
		pos.x < 0 || pos.x > MAX_TILE_X ||
		pos.y < 0 || pos.y > MAX_TILE_Y
		)return aroundTile = AROUND_TILE{};

	int tempPos = 0;
	//上(1)情報取得
	tempPos = int(pos.y) + 1;
	if (tempPos < MAX_TILE_Y)
		aroundTile.Top = m_Map[tempPos][int(pos.x)];
	else aroundTile.Top.TileAttribute = OUT_RANGE;
	//右(2)情報取得
	tempPos = int(pos.x) + 1;
	if (tempPos < MAX_TILE_X)
		aroundTile.Right = m_Map[int(pos.y)][tempPos];
	else aroundTile.Right.TileAttribute = OUT_RANGE;
	//下(3)情報取得
	tempPos = int(pos.y) - 1;
	if (tempPos >= 0)
		aroundTile.Under = m_Map[tempPos][int(pos.x)];
	else aroundTile.Under.TileAttribute = OUT_RANGE;
	//左(4)情報取得
	tempPos = int(pos.x) - 1;
	if (tempPos >= 0)
		aroundTile.Left = m_Map[int(pos.y)][tempPos];
	else aroundTile.Left.TileAttribute = OUT_RANGE;

	return aroundTile;
}



//=============================================================================
// ポジションのタイルを取得
//=============================================================================
TILE Map::GetTile(D3DXVECTOR3 pos) const
{
	D3DXVECTOR2 ArrayPos = GetArrayPos(pos);
	return m_Map[int(ArrayPos.y)][int(ArrayPos.x)];
}

//=============================================================================
// ポジションをマップの行列番号に変換
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
// マップの行列番号をポジションに変換
//=============================================================================
D3DXVECTOR3 Map::GetXYPos(D3DXVECTOR2 arrayPos) const
{
	D3DXVECTOR2 Pos = arrayPos * TILE_OFFSET;

	return D3DXVECTOR3(Pos.x, 0.1f, Pos.y);
}

//=============================================================================
//ランダムにマップを生成
//=============================================================================
void Map::RandomMapCreate(int roomNumMax, int roomNumMin, int roomScaleMax, int roomScaleMin)
{
	TILE_ATTRIBUTE attribute[ATTRIBUTE_Y][ATTRIBUTE_X]{};//周りを壁にするため周りを抜いたマップを作成
	int roomNum;
	int randomX[255] = { 0 };
	int randomY[255] = { 0 };
	int scaleSelect = 0;

	//マップを壁で埋め尽くす
	for (int i = 0; i < ATTRIBUTE_Y; i++)
	{
		for (int j = 0; j < ATTRIBUTE_X; j++)
		{
			attribute[i][j] = STOP;
		}
	}

	//部屋の生成
	roomNum = rand() % (roomNumMax - roomNumMin + 1) + roomNumMin;//部屋の数
	for (int i = 0; i < roomNum; i++)
	{
		randomX[i] = GetRandomInt(0, ATTRIBUTE_X - 1);
		randomY[i] = GetRandomInt(0, ATTRIBUTE_Y - 1);

		for (int j = 0; j < rand() % (roomScaleMax - roomScaleMin + 1) + roomScaleMin; j++)//部屋の縦の長さ
		{
			for (int k = 0; k < rand() % (roomScaleMax - roomScaleMin + 1) + roomScaleMin; k++)//部屋の横の長さ
			{
				if ((randomY[i] + j >= 1) && (randomY[i] + j < ATTRIBUTE_Y - 1) && (randomX[i] + k >= 1) && (randomX[i] + k < ATTRIBUTE_X - 1))//マップ外には生成しない
				{
					attribute[randomY[i] + j][randomX[i] + k] = AIR;
				}
			}
		}
	}

	//廊下の生成
	for (int i = 0; i < roomNum + 1; i++)//部屋数分ループ(最初の部屋と最後の部屋をつなげるため +1)
	{
		int targetRoom = i + 1;//つなげ先の部屋
		int randomXUpdate = 0;

		if (roomNum < targetRoom)//最初の部屋と最後の部屋をつなげる
		{
			targetRoom = 0;
		}

		if (randomX[i] < randomX[targetRoom])
		{
			for (int j = 0; j < abs(randomX[i] - randomX[targetRoom]); j++)
			{
				attribute[randomY[i]][randomX[i] + j + 1] = AIR;
				randomXUpdate = randomX[i] + j + 1;//最終x座標を代入
			}
		}
		else if (randomX[i] > randomX[targetRoom])
		{
			for (int j = 0; j < abs(randomX[i] - randomX[targetRoom]); j++)
			{
				attribute[randomY[i]][randomX[i] - j - 1] = AIR;
				randomXUpdate = randomX[i] - j - 1;//最終x座標を代入
			}
		}
		else
		{
			randomXUpdate = randomX[i];//最終x座標を代入
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

	//周りの壁があるマップに代入
	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			//すべてに代入、最終的に一番端だけコレになる
			m_Map[i][j].TileAttribute = OUT_RANGE;

			//周りより一つ内側は壁にする
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
	AROUND_TILE aroundTile = GetAroundTile(D3DXVECTOR2(float(arrayPos.x), float(arrayPos.y)));//プレイヤーの周りのタイルを取得
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
				m_TileHistory.push_back(&m_Map[int(tile[i].arrayPos.y)][int(tile[i].arrayPos.x)]);//履歴に残す
			}
		}
	}
}