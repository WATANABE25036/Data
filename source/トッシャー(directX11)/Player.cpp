/*==============================================================================

   �v���C���[(�h��) [Player.cpp]
														 Author : �n� �C
														 Date   : 2023/12/21
--------------------------------------------------------------------------------

==============================================================================*/
#include <iostream>
#include "Input.h"
#include "Player.h"
#include "Shadow.h"
#include "GameWorld.h"
#include "Sound.h"
#include "Map.h"
#include "Library.h"
#include "Inventory.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_SPEED	3.0f
#define PLAYER_HIT_SIZE	5.0f	
#define PLAYER_SCALE	0.1f	

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************	
static LIGHT		g_DirectionalLight;	// �f�B���N�V���i�����C�g
static LIGHT		g_PointLight;		// �|�C���g���C�g

static int			g_AxisLine[3]; //�|�����C���p���ʎq

// �ÓI�����o�ϐ��̒�`
int Player::m_sCou = 0;

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Player::Player(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map, Inventory* m_Inventory)
	: ObjCharacter(pos, rot, gameWorld, map), m_pInventory(m_Inventory)
{
	m_sCou++;
	m_OwnerNum = m_sCou;
	m_OwnerTag = ORDER_TAG::PLAYER;
	m_Tag = "Player";

	m_Scl = D3DXVECTOR3(PLAYER_SCALE, PLAYER_SCALE, PLAYER_SCALE);
	m_Spd = PLAYER_SPEED;//�v���C���[�̑���
	m_HitSize = D3DXVECTOR3(PLAYER_HIT_SIZE, PLAYER_HIT_SIZE, PLAYER_HIT_SIZE);

	//���f���̐ݒ�
	m_ModelMap["Body"] = { (char*)"data/MODEL/Trolley.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this ,true) };
	m_ModelMap["Head"] = { (char*)"data/MODEL/miku_head.obj", new BodyParts(D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), this, false) };
	m_ModelMap["JudgeSphereBlue"] = { (char*)"data/MODEL/judgeSphereBlue.obj", new BodyParts(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), this, false) };
	m_ModelMap["PlayerFog"] = { (char*)"data/MODEL/PlayerFog.obj", new BodyParts(D3DXVECTOR3(0.0f, -1000.0f, 10000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 1.0f), this, false) };

	//���̏ꏊ�ł��g���Ƃ��̓|�C���^���擾����
	m_pBody = m_ModelMap["Body"].Parts;
	m_pHead = m_ModelMap["Head"].Parts;
	m_pJudgeSphereBlue = m_ModelMap["JudgeSphereBlue"].Parts;

	//�y�A�����g�̍\�z
	m_ModelMap["Body"].Parts->SetChild(m_ModelMap["Head"].Parts);
	m_ModelMap["Head"].Parts->SetChild(m_ModelMap["JudgeSphereBlue"].Parts);
	m_ModelMap["JudgeSphereBlue"].Parts->SetBros(m_ModelMap["PlayerFog"].Parts);
	//���f���̓ǂݍ���
	Object::ModelLoad();
}

Player::~Player()
{

}

//=============================================================================
// ����������
//=============================================================================
void Player::Init(void)
{
	m_Use = true;

	 //���s�����̐ݒ�i���E���Ƃ炷���j
	//g_DirectionalLight.Type = LIGHT_TYPE_DIRECTIONAL;				// ���s����
	//g_DirectionalLight.Enable = true;								// ���̃��C�g��ON
	//g_DirectionalLight.Direction = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f);// ���̌���
	//g_DirectionalLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	//SetLight(0, &g_DirectionalLight);								// ����Őݒ肵�Ă���

	// �_�����̐ݒ�
	g_PointLight.Type = LIGHT_TYPE_POINT;						// ���s����
	g_PointLight.Enable = true;									// ���̃��C�g��ON
	g_PointLight.Position = D3DXVECTOR4(-200.0f, 200.0f, -200.0f, 0.0f);// ���̍��W
	g_PointLight.Diffuse = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0f);	// ���̐F
	g_PointLight.Attenuation = 200.0f;							// ��������
	SetLight(1, &g_PointLight);									// ����Őݒ肵�Ă���
	
	// �_�����̐ݒ�
	g_PointLight.Type = LIGHT_TYPE_POINT;						// ���s����
	g_PointLight.Enable = true;									// ���̃��C�g��ON
	g_PointLight.Position = D3DXVECTOR4(-200.0f, 200.0f, -200.0f, 0.0f);// ���̍��W
	g_PointLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	g_PointLight.Attenuation = 1000.0f;							// ��������
	SetLight(2, &g_PointLight);									// ����Őݒ肵�Ă���

	// �e�̃Z�b�g�i�e�͍�����0�ɂ��ĕ\��������j
	m_Shadow = SetShadow(D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z), 80.0f);

	m_GameOver = false;

	m_SE_WaterA0 = LoadSound((char*)"data/SE/WaterA0.wav");
	m_SE_WaterAL45 = LoadSound((char*)"data/SE/WaterAL45.wav");
	m_SE_WaterAL90 = LoadSound((char*)"data/SE/WaterAL90.wav");
	m_SE_WaterAL135 = LoadSound((char*)"data/SE/WaterAL135.wav");
	m_SE_WaterAR45 = LoadSound((char*)"data/SE/WaterAR45.wav");
	m_SE_WaterAR90 = LoadSound((char*)"data/SE/WaterAR90.wav");
	m_SE_WaterAR135 = LoadSound((char*)"data/SE/WaterAR135.wav");
	m_SE_WaterA180 = LoadSound((char*)"data/SE/WaterA180.wav");
	m_SE_WaterB0 = LoadSound((char*)"data/SE/WaterB0.wav");
	m_SE_WaterBL45 = LoadSound((char*)"data/SE/WaterBL45.wav");
	m_SE_WaterBL90 = LoadSound((char*)"data/SE/WaterBL90.wav");
	m_SE_WaterBL135 = LoadSound((char*)"data/SE/WaterBL135.wav");
	m_SE_WaterBR45 = LoadSound((char*)"data/SE/WaterBR45.wav");
	m_SE_WaterBR90 = LoadSound((char*)"data/SE/WaterBR90.wav");
	m_SE_WaterBR135 = LoadSound((char*)"data/SE/WaterBR135.wav");
	m_SE_WaterB180 = LoadSound((char*)"data/SE/WaterB180.wav");
	m_SE_PlayerMoveA = LoadSound((char*)"data/SE/PlayerMoveA.wav");
	m_SE_PlayerMoveB = LoadSound((char*)"data/SE/PlayerMoveB.wav");
	m_SE_UnderWater = LoadSound((char*)"data/SE/UnderWater.wav");
	m_SE_Dead = LoadSound((char*)"data/SE/Dead.wav");
	m_SE_Miss = LoadSound((char*)"data/SE/Miss.wav");
	m_SE_Get = LoadSound((char*)"data/SE/Get.wav");
}

//=============================================================================
// �X�V����
//=============================================================================
void Player::Update(void)
{
	// �J�����̃��[�J�����W�n�ł̑O�i�������v�Z
	D3DXVECTOR3 forwardLocal(0.0f, 0.0f, 1.0f);
	// �J�����̃��[�J�����W�n�ł̑O�i���������[���h���W�n�ɕϊ�
	D3DXVECTOR3 forwardWorld;
	D3DXMATRIX mtxWorld = m_pBody->GetMtxWorld();
	D3DXVec3TransformNormal(&forwardWorld, &forwardLocal, &mtxWorld);

	//-------------------------------------------------------------
	//�����}�E�X�œ�����
	//-------------------------------------------------------------
	//�}�E�X�̈ړ��ʂ���ъ��x�̒���
	if (!m_GameOver)
	{
		D3DXVECTOR2 difMousePos;//�}�E�X�ړ���

		m_MouseSensi = max(m_MouseSensiInit, min(m_MouseSensiCou, m_MouseSensiMax));
		difMousePos.x = GetMouseX() * m_MouseSensi;
		difMousePos.y = GetMouseY() * m_MouseSensi;

		if (difMousePos.y != 0 || difMousePos.x != 0)m_MouseSensiCou += m_MouseSensiAdd;
		else {
			m_MouseSensiCou = 0.0f;
		}

		// �����_�̐���u�㉺�v
		if (difMousePos.y != 0)
		{
			m_pHead->SetRot(D3DXVECTOR3(m_pHead->GetRot().x, m_pHead->GetRot().y + difMousePos.y, m_pHead->GetRot().z));

			// ���̊p�x�ɏ����t����
			const float maxVerticalAngle = D3DXToRadian(89.0f);

			if (m_pHead->GetRot().y < -maxVerticalAngle)
			{
				m_pHead->SetRot(D3DXVECTOR3(m_pHead->GetRot().x, -maxVerticalAngle, m_pHead->GetRot().z));
			}
			else if (m_pHead->GetRot().y > maxVerticalAngle)
			{
				m_pHead->SetRot(D3DXVECTOR3(m_pHead->GetRot().x, maxVerticalAngle, m_pHead->GetRot().z));
			}
		}

		// �����_�̈ړ��u���E�v
		if (difMousePos.x != 0)
		{
			m_Rot.x += difMousePos.x;

			// �p�x��-�΂�菬�����ꍇ�A360�x�����Đ��K������i0����2�΂͈̔͂Ɏ��߂�j
			if (m_Rot.x < -D3DX_PI)
			{
				m_Rot.x += D3DX_PI * 2.0f;
			}
			else if (m_Rot.x > D3DX_PI)
			{
				m_Rot.x -= D3DX_PI * 2.0f;
			}
		}
	}
	//-------------------------------------------------------------
	//�̂��L�[�œ�����
	//-------------------------------------------------------------

	// �ړ��ʂ�������
	D3DXVECTOR3 moveVector(0.0f, 0.0f, 0.0f);
	if (!m_GameOver)
	{
		// W�L�[��������Ă���ꍇ�A�O�i�����Ɉړ�
		if (GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_UP))
		{
			moveVector += forwardWorld;
		}

		// S�L�[��������Ă���ꍇ�A��ޕ����Ɉړ�
		if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN))
		{
			moveVector -= forwardWorld;
		}

		// A�L�[��������Ă���ꍇ�A�������Ɉړ�
		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT))
		{
			// �J�����̃��[�J�����W�n�ł̉E�������v�Z
			D3DXVECTOR3 leftLocal(1.0f, 0.0f, 0.0f);
			// �J�����̃��[�J�����W�n�ł̉E���������[���h���W�n�ɕϊ�
			D3DXVECTOR3 leftWorld;
			D3DXMATRIX mtxWorld = m_pBody->GetMtxWorld();
			D3DXVec3TransformNormal(&leftWorld, &leftLocal, &mtxWorld);

			moveVector -= leftWorld;
		}

		// D�L�[��������Ă���ꍇ�A�E�����Ɉړ�
		if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT))
		{
			// �J�����̃��[�J�����W�n�ł̉E�������v�Z
			D3DXVECTOR3 rightLocal(1.0f, 0.0f, 0.0f);
			// �J�����̃��[�J�����W�n�ł̉E���������[���h���W�n�ɕϊ�
			D3DXVECTOR3 rightWorld;
			D3DXMATRIX mtxWorld = m_pBody->GetMtxWorld();
			D3DXVec3TransformNormal(&rightWorld, &rightLocal, &mtxWorld);

			moveVector += rightWorld;
		}
	}
	// ���K�����Ĉړ����x���l��
	D3DXVec3Normalize(&m_NormaMoveVec, &moveVector);
	m_Move = m_NormaMoveVec * m_Spd;//�ړ��������Z�o

	//-------------------------------------------------------------
	//�������Z�o
	//-------------------------------------------------------------
	m_Dir = GlobalToLocal(m_Pos, m_pJudgeSphereBlue->GetGlobalPos());
	D3DXVec3Normalize(&m_Dir, &m_Dir);

	//-------------------------------------------------------------
	//�ǂƂ̓����蔻��
	//-------------------------------------------------------------
	HitJudge();

	//-------------------------------------------------------------
	//�A�C�e������
	//-------------------------------------------------------------
	if (GetKeyboardTrigger(DIK_E) || IsMouseLeftTriggered())
	{
		for (auto it : m_pGameWorld->GetObjectList())
		{
			if (it->GetTag() == "Item")
			{
				D3DXVECTOR2 itemArrayPos = m_pMap->GetArrayPos(it->GetPos());
				if (//1�}�X�ׂ������ł����
					m_ArrayPos == itemArrayPos ||
					(m_ArrayPos.x + 1 == itemArrayPos.x && m_ArrayPos.y == itemArrayPos.y) ||
					(m_ArrayPos.x - 1 == itemArrayPos.x && m_ArrayPos.y == itemArrayPos.y) ||
					(m_ArrayPos.x == itemArrayPos.x && m_ArrayPos.y + 1 == itemArrayPos.y) ||
					(m_ArrayPos.x == itemArrayPos.x && m_ArrayPos.y - 1 == itemArrayPos.y) ||
					(m_ArrayPos.x + 1 == itemArrayPos.x && m_ArrayPos.y + 1 == itemArrayPos.y) ||
					(m_ArrayPos.x + 1 == itemArrayPos.x && m_ArrayPos.y - 1 == itemArrayPos.y) ||
					(m_ArrayPos.x - 1 == itemArrayPos.x && m_ArrayPos.y + 1 == itemArrayPos.y) ||
					(m_ArrayPos.x - 1 == itemArrayPos.x && m_ArrayPos.y - 1 == itemArrayPos.y)
					)
				{
					if (m_Collision.CollisionBS(m_pJudgeSphereBlue->GetGlobalPos(), it->GetPos(), m_ItemGetRange, it->GetHitSize().x))//�����蔻��
					{
						m_pInventory->AddItem(dynamic_cast<Item*>(it));
						m_pGameWorld->DestroyObject(it);
						PlaySound(m_SE_Get, 0, 0.5f);
						m_ItemGet = true;
						break;
					}
				}
			}
		}
		if (!m_ItemGet)PlaySound(m_SE_Miss, 0, 0.5f);
	}

	m_ItemGet = false;

	//-------------------------------------------------------------
	//�ړ�
	//-------------------------------------------------------------
	// �p�[�c(�e)�̈ʒu���ړ�
	m_Pos += m_Move;

	//����
	m_MoveSECou--;
	if (m_Pos != m_OldPos && m_MoveSECou <= 0)
	{
		if (m_MoveSEChange)
		{
			PlaySound(m_SE_PlayerMoveA, 0, 0.3f);
			m_MoveSEChange = 0;
		}
		else
		{
			PlaySound(m_SE_PlayerMoveB, 0, 0.3f);
			m_MoveSEChange = 1;
		}
		m_MoveSECou = 25;
	}
	//-------------------------------------------------------------
	//�G����
	//-------------------------------------------------------------
	//�G�̕����𒲂ׂ�
	float dot = 0.0f;
	float cross = 0.0f;
	for (auto it : m_pGameWorld->GetObjectList())
	{
		if (it->GetTag() != "Enemy")continue;

		if (m_Collision.CollisionBS(m_Pos, it->GetPos(), 300, 1))
		{
			D3DXVECTOR3 EnemyPosV3 = GlobalToLocal(m_Pos, it->GetPos());
			D3DXVECTOR2 EnemyPosV2 =  D3DXVECTOR2(EnemyPosV3.x, EnemyPosV3.z);
			D3DXVECTOR2	PlayerDirV2 = D3DXVECTOR2(m_Dir.x, m_Dir.z);

			D3DXVec2Normalize(&EnemyPosV2, &EnemyPosV2);

			dot = D3DXVec2Dot(&PlayerDirV2, &EnemyPosV2);

			dot = D3DXToDegree(std::acos(dot));

			// �v���C���[�̐��ʕ����ƓG�̈ʒu�̃x�N�g���̊O�ς��v�Z
			cross = PlayerDirV2.x * EnemyPosV2.y - PlayerDirV2.y * EnemyPosV2.x;

			 //�����𑪒�
			 D3DXVECTOR3 diff = m_Pos - it->GetPos();
			 float dis = D3DXVec3Length(&diff);
			 dis = 50 / dis ;


			 if (dynamic_cast<ObjCharacter*>(it)->GetRipplesSE())
			 {
				 m_DIR8 dir8 = {};

				 //�O��딻��
				 if (dot < 90)dir8.Front = true;
				 else if (dot > 90)dir8.Back = true;
				 //���E����
				 if (cross > 0)dir8.Left = true;
				 else if (cross < 0)dir8.Right = true;

				 //4����(�΂�)�̂ǂ��ɂ��邩���߂�
				 if (dir8.Front && dir8.Right) dir8.FrontRight = true;
				 else if (dir8.Front && dir8.Left)dir8.FrontLeft = true;
				 else if (dir8.Back && dir8.Right)dir8.BackRight = true;
				 else if (dir8.Back && dir8.Left)dir8.BackLeft = true;
				 //���ʉ���炷
				 int ran = GetRandomInt(0, 1);
				 if (dir8.FrontRight)
				 {
					 if(ran)PlaySound(m_SE_WaterAR45, 0, dis);
					 else PlaySound(m_SE_WaterBR45, 0, dis);
				 }
				 else if (dir8.FrontLeft)
				 {
					 if (ran)PlaySound(m_SE_WaterAL45, 0, dis);
					 else PlaySound(m_SE_WaterBL45, 0, dis);
				 }
				 else if (dir8.BackRight)
				 {
					 if (ran)PlaySound(m_SE_WaterAR135, 0, dis);
					 else PlaySound(m_SE_WaterBR135, 0, dis);
				 }
				 else if (dir8.BackLeft)
				 {
					 if (ran)PlaySound(m_SE_WaterAL135, 0, dis);
					 else PlaySound(m_SE_WaterBL135, 0, dis);
				 }
			 }
		}
	}

	//-------------------------------------------------------------
	//�G�Ƃ̓����蔻��
	//-------------------------------------------------------------
	m_InvincibleTime--;
	for (auto it : m_pGameWorld->GetObjectList())
	{
		if (it->GetTag() != "Enemy")continue;

		if (m_Collision.CollisionBS(m_Pos, it->GetPos(), m_HitSize.x, it->GetHitSize().x))
		{
			if (m_Hp && m_InvincibleTime <= 0)
			{
				m_Hp--;
				m_InvincibleTime = 120;
				PlaySound(m_SE_Dead, 0, 0.06f);
				m_pGameWorld->GetCamera()->Shake(15.0f, 10.0f);//��ʂ�h�炷
				m_LightRed = 1.0f;
			}
		}
	}

	if (m_LightRed > 0.5f)m_LightRed -= 0.05f;


	//-------------------------------------------------------------
	//�Q�[���I�[�o�[
	//-------------------------------------------------------------
	if (m_Hp <= 0)
	{
		m_GameOver = true;
	}

	if(m_GameOver)
	{
		DeadFogZoom += 5000;
		if (m_Pos.y > 25.0f)
		{
			m_pGameWorld->GetCamera()->Shake(15.0f, 10.0f);//��ʂ�h�炷
			m_Pos.y -= 4.0f;
		}

		m_pJudgeSphereBlue->SetPos(D3DXVECTOR3(m_pJudgeSphereBlue->GetPos().x, m_pJudgeSphereBlue->GetPos().y, m_pJudgeSphereBlue->GetPos().z - DeadFogZoom));//��ʂ��Â�����

		if (m_ResultCou <= 0)
		{
			m_ResultCou = 300;
			PlaySound(m_SE_UnderWater, 0, 0.5f);
		}
	}

	//���U���g�Ɉڍs
	if (m_ResultCou > 0)
	{
		m_ResultCou--;

		if (m_ResultCou <= 0)
		{
			m_ResultRequest = true;
		}
	}

	//-------------------------------------------------------------
	//�N���A����
	//-------------------------------------------------------------
	if (m_pInventory->GetItemLest().size() > 0)
	{
		if (m_pInventory->GetItemLest().size() == m_pInventory->GetItemLest().front()->GetItemCou())
		{
			m_Complete = true;
			m_ResultRequest = true;
		}
	}

	//�e�̈ʒu���X�V
	SetPositionShadow(m_Shadow, D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z));

	//���̍X�V
	g_PointLight.Position = D3DXVECTOR4(m_pJudgeSphereBlue->GetGlobalPos().x, m_pJudgeSphereBlue->GetGlobalPos().y, m_pJudgeSphereBlue->GetGlobalPos().z, 0.0f);

	SetLight(1, &g_PointLight);	
	g_PointLight.Position = D3DXVECTOR4(m_Pos.x, m_Pos.y, m_Pos.z, 0.0f);

	float hpRatio = m_Hp / m_MaxHp;
	if (hpRatio <= 1.0f / m_MaxHp  )
	{
		g_PointLight.Diffuse = D3DXCOLOR(m_LightRed, 0.2f, 0.2f, 1.0f);	// 2/3�_���[�W��H������Ƃ�
	}
	else if (hpRatio <= 2.0f / m_MaxHp)
	{
		g_PointLight.Diffuse = D3DXCOLOR(m_LightRed, 0.4f, 0.4f, 1.0f);	// 1/3�_���[�W��H������Ƃ�
	}

	SetLight(2, &g_PointLight);

	//���f���X�V
	Object::Update();

	//�O�|�W�V�����X�V
	m_OldPos = m_Pos;
	m_OldArrayPos = m_ArrayPos;

#ifdef _DEBUG	// �f�o�b�O����\������
	//SetDebugStr(0, "PosX", m_Pos.x, "PosY", m_Pos.y, "PosZ", m_Pos.z);
	//SetDebugStr(1, "DirX", m_Dir.x, "DirY", m_Dir.y, "DirZ", m_Dir.z);
	//SetDebugStr(2, "RotX", m_Rot.x, "RotY", m_Rot.y, "RotZ", m_Rot.z);
	//SetDebugStr(3, "HeadRotX", m_pHead->GetRot().x, "HeadRotY", m_pHead->GetRot().y, "HeadRotZ", m_pHead->GetRot().z);
	//SetDebugStr(4, "BodyRotX", m_pBody->GetRot().x, "BodyRotY", m_pBody->GetRot().y, "BodyRotZ", m_pBody->GetRot().z);
	//SetDebugStr(5, "ArrayPosX", m_ArrayPos.x, "ArrayPosY", m_ArrayPos.y);
	//SetDebugStr(6, "SphereBlueX", m_pJudgeSphereBlue->GetGlobalPos().x, "SphereBlueY", m_pJudgeSphereBlue->GetGlobalPos().y, "SphereBlueZ", m_pJudgeSphereBlue->GetGlobalPos().z);
	//SetDebugStr(7, "HP", m_Hp);
	//SetDebugStr(8, "MouseSensi", m_MouseSensi, "MouseSensiAdd" ,m_MouseSensiAdd);
	
	//SetDebugStr(8, "arrayX", m_ArrayPos.x, "arrayMoveX", arrayPosNext.x);
	//SetDebugStr(9, "arrayY", m_ArrayPos.y, "arrayMoveY", arrayPosNext.y);
	//SetDebugStr(10, "DirX", m_Dir.x, "DirY", m_Dir.y, "DirZ", m_Dir.z);
	//SetDebugStr(11, "MoveX", m_Move.x, "MoveY", m_Move.y, "MoveZ", m_Move.z);
	//SetDebugStr(12, "NextTile", tileNext);
	//SetDebugStr(13, "Top", aroundTile.Top, "Under", aroundTile.Under);
	//SetDebugStr(14, "Left", aroundTile.Left, "Right", aroundTile.Right);
#endif
}

