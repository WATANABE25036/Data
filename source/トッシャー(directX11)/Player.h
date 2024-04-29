/*==============================================================================

   プレイヤー(派生) [Player.h]
														 Author : 渡邉 修
														 Date   : 2023/12/21
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <iostream>
#include <list>
#include "BodyParts.h"
#include "Renderer.h"
#include "Collision.h"
#include "ObjCharacter.h"

//前方宣言
class Inventory;

class Player : public ObjCharacter
{
public:
	Player(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map, Inventory* m_Inventory);
	~Player() override;

	void Init() override;
	void Update() override; 

	BodyParts* GetBody() const { return m_pBody; }
	BodyParts* GetHead() const { return m_pHead; }
	D3DXVECTOR3 GetStartPos() const { return m_StartPos; }
	bool GetResult() const { return m_Result; }
	void SetResult(bool Judge) { m_Result = Judge; }
	int GetSoundEchoValue() const { return m_SoundEchoValue; }
	bool GetResultRequest() const { return m_ResultRequest; }
	bool GetComplete() const { return m_Complete; }

private:
	BodyParts* m_pBody = nullptr;
	BodyParts* m_pHead = nullptr;
	BodyParts* m_pJudgeSphereBlue = nullptr;
	Inventory* m_pInventory = nullptr;
	static int m_sCou;
	bool m_GameOver = false;
	int m_ResultCou = 0;
	bool m_ResultRequest = false;

	//カーソル関係
	float m_MouseSensi = 0.0f;		//マウス感度スケーリング値
	float m_MouseSensiMax = 0.006f;	//マウス感度スケーリング値の最大
	float m_MouseSensiInit = 0.003f;//マウス感度初期値
	float m_MouseSensiAdd = 0.001f;	//マウス感度増加量
	float m_MouseSensiCou = 0.0f;
	float m_ItemGetRange = 20.0f;	//アイテム取得範囲
	int m_SoundEchoValue = 50;		//足音の大きさ

	float m_MaxHp = 3;
	float m_Hp = m_MaxHp;//体力
	int m_InvincibleTime = 0;//無敵時間
	bool m_Result = false;
	bool m_Complete = false;
	int m_MoveSECou = 0;
	int m_MoveSEChange = 0;
	int DeadFogZoom = 0;
	bool m_ItemGet = false;
	float m_LightRed = 1.0f;

	struct m_DIR8
	{
		bool Front = false;
		bool FrontRight = false;
		bool Right = false;
		bool BackRight = false;
		bool Back = false;
		bool BackLeft = false;
		bool Left = false;
		bool FrontLeft = false;
	};

	//音
	int m_SE_WaterA0 = 0;
	int m_SE_WaterAL45 = 0;
	int m_SE_WaterAL90 = 0;
	int m_SE_WaterAL135 = 0;
	int m_SE_WaterAR45 = 0;
	int m_SE_WaterAR90 = 0;
	int m_SE_WaterAR135 = 0;
	int m_SE_WaterA180 = 0;
	int m_SE_WaterB0 = 0;
	int m_SE_WaterBL45 = 0;
	int m_SE_WaterBL90 = 0;
	int m_SE_WaterBL135 = 0;
	int m_SE_WaterBR45 = 0;
	int m_SE_WaterBR90 = 0;
	int m_SE_WaterBR135 = 0;
	int m_SE_WaterB180 = 0;
	int m_SE_PlayerMoveA = 0;
	int m_SE_PlayerMoveB = 0;
	int m_SE_UnderWater = 0;
	int m_SE_Dead = 0;
	int m_SE_Miss = 0;
	int m_SE_Get = 0;
};




