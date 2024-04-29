/*==============================================================================

   �L�����N�^�[(�I�u�W�F�N�g) [ObjCharacter.h]
														 Author : �n� �C
														 Date   : 2023/02/14
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "Collision.h"
class Map;

class ObjCharacter : public Object
{
public:
	ObjCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map);
	~ObjCharacter() override;

	void HitJudge();//�ǂƂ̓����蔻�菈��
	void WallSlidingMove(D3DXVECTOR3& out, D3DXVECTOR3 normal);
	void RipplesSet(ORDER_TAG tag, int ownerCou);

	bool GetRipplesSE() const { return m_RipplesSE; }

protected:
	Collision m_Collision;
	Map* m_pMap = nullptr;
	D3DXVECTOR3 m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O�̕\�����W
	D3DXVECTOR2 m_ArrayPos = D3DXVECTOR2(0.0f, 0.0f);			//�}�b�v�̍s��ԍ�
	D3DXVECTOR2 m_OldArrayPos = D3DXVECTOR2(0.0f, 0.0f);		//�O�̃}�b�v�̍s��ԍ�
	D3DXVECTOR3 m_StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�X�^�[�g���̈ʒu
	D3DXVECTOR3 m_NormaMoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_RipplesRange = 8;			//�\�����̂΂��
	int m_RipplesSpan = 18;			//�g�䂪�o��Ԋu
	int m_RipplesDeleteSpan = 20;	//�g������t���[����ɏ�����
	int m_RipplesPoint = 0;			//�J�E���^�[
	int m_RipplesDeleteCou = 0;		//�J�E���^�[
	int m_RipplesDeleteNum = 0;		//�g��̐�
	int m_RipplesMax = 5;			//�g��ő吔
	bool m_RipplesSE = false;
};

