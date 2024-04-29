/*==============================================================================

   �\�����S��(���) [Object.h]
														 Author : �n� �C
														 Date   : 2023/12/12
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <d3dx9.h>
#include <list>
#include <unordered_map>
#include <string>
#include "Model.h"

class GameWorld;
class BodyParts;
enum class ORDER_TAG;

class Object
{
public:
	Object(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 hitSize, GameWorld* gameWorld);
	virtual ~Object();

	HRESULT InitAll();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void ModelLoad();

	float GetSpd() const { return m_Spd; }
	virtual D3DXVECTOR3 GetPos() { return m_Pos; }
	D3DXVECTOR3 GetRot() const { return m_Rot; }
	std::string GetTag() const { return m_Tag; }
	D3DXVECTOR3 GetHitSize() const { return m_HitSize; }
	int GetOwnerNum() const { return m_OwnerNum; }
	ORDER_TAG GetOwnerTag() const { return m_OwnerTag; }
	int GetOwnerCou() const { return m_OwnerCou; }
	virtual void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }
	void SetScl(D3DXVECTOR3 scl) { m_Scl = scl; }
	void SetHitSize(D3DXVECTOR3 hitSize) { m_HitSize = hitSize; }
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_MtxWorld = mtxWorld; }

protected:
	bool m_Use = false;
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�\�����W
	D3DXVECTOR3 m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O�̕\�����W
	D3DXVECTOR3 m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]�p�x
	D3DXVECTOR3 m_Scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�傫��
	D3DXVECTOR3 m_HitSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����蔻��傫��
	D3DXMATRIX m_MtxWorld;									//���[���h�s��
	D3DXVECTOR3	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ�����
	D3DXVECTOR3 m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	float m_Spd = 0.0f;			//�ړ��X�s�[�h
	int m_Shadow = 0;			// �e�̎��ʔԍ�
	std::string m_Tag;
	ORDER_TAG m_OwnerTag;
	int m_OwnerNum = 0;
	int m_OwnerCou = 0;

	//���f���֌W
	struct MODEL
	{
		char* ModelAddress = nullptr;
		BodyParts* Parts = nullptr;
	};
	std::unordered_map<std::string, MODEL> m_ModelMap;
	BodyParts* m_ParentParts = nullptr;
	GameWorld* m_pGameWorld = nullptr;
	DX11_MODEL m_Model;
};
