/*==============================================================================

   �v���C���[(�h��) [Player.h]
														 Author : �n� �C
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

//�O���錾
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

	//�J�[�\���֌W
	float m_MouseSensi = 0.0f;		//�}�E�X���x�X�P�[�����O�l
	float m_MouseSensiMax = 0.006f;	//�}�E�X���x�X�P�[�����O�l�̍ő�
	float m_MouseSensiInit = 0.003f;//�}�E�X���x�����l
	float m_MouseSensiAdd = 0.001f;	//�}�E�X���x������
	float m_MouseSensiCou = 0.0f;
	float m_ItemGetRange = 20.0f;	//�A�C�e���擾�͈�
	int m_SoundEchoValue = 50;		//�����̑傫��

	float m_MaxHp = 3;
	float m_Hp = m_MaxHp;//�̗�
	int m_InvincibleTime = 0;//���G����
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

	//��
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




