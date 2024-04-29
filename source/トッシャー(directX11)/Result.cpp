/*==============================================================================

   ���U���g��ʏ���(�h��) [Result.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Result.h"
#include "Input.h"
#include "Texture.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Sound.h"
#include "Score.h"
//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Result::Result(SceneManager* sceneManager)
	: Scene(sceneManager)
{

}

Result::~Result()
{
}

//=============================================================================
// ����������
//=============================================================================
void Result::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/Result.png");
	m_TextureNoLight = LoadTexture((char*)"data/TEXTURE/Titlelight.png");
	m_TextureNoRetry = LoadTexture((char*)"data/TEXTURE/Retry.png");
	m_TextureNoQuit = LoadTexture((char*)"data/TEXTURE/Quit.png");
	m_TextureNoCursor = LoadTexture((char*)"data/TEXTURE/Cursor.png");
	m_TextureNoCompleteText = LoadTexture((char*)"data/TEXTURE/CompleteText.png");
	m_TextureNoRest = LoadTexture((char*)"data/TEXTURE/Rest.png");

	m_SE_CursorMove = LoadSound((char*)"data/SE/CursorMove.wav");
	m_SE_Decision = LoadSound((char*)"data/SE/Decision.wav");
	m_SE_Result = LoadSound((char*)"data/SE/Result.wav");

	m_SelectX = SCREEN_WIDTH * 0.4f;//�͂��߂�̈ʒu�ɍ��킹��
	m_CursorRetry = true;//�ŏ��̃J�[�\��

	m_Cou = 0;
	m_Retry = false;
	m_Quit = false;

	m_Score.Init();

	PlaySound(m_SE_Result, 0, 0.2f);
}

//=============================================================================
// �I������
//=============================================================================
void Result::Uninit(void)
{
	StopSoundAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void Result::Update(void)
{
	m_LightMove += 0.01f;
	m_LightOffsetX = cos(m_LightMove) * 100;

	m_LeftButton = m_RightButton = m_SelectButton = false;

	if (GetKeyboardTrigger(DIK_LEFT) || GetKeyboardTrigger(DIK_A))
	{
		m_LeftButton = true;
		PlaySound(m_SE_CursorMove, 0, 0.1f);
	}

	if (GetKeyboardTrigger(DIK_RIGHT) || GetKeyboardTrigger(DIK_D))
	{
		m_RightButton = true;
		PlaySound(m_SE_CursorMove, 0, 0.1f);
	}

	if (GetKeyboardTrigger(DIK_E) || GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_RETURN))
	{
		m_SelectButton = true;
		PlaySound(m_SE_Decision, 0, 0.2f);
	}


	if (m_LeftButton)
	{
		m_SelectX = SCREEN_WIDTH * 0.4f;
		m_CursorRetry = true;
		m_CursorQuit = false;
	}
	else if (m_RightButton)
	{
		m_SelectX = SCREEN_WIDTH * 0.6f;
		m_CursorQuit = true;
		m_CursorRetry = false;
	}

	if (m_SelectButton && m_CursorRetry)
	{
		m_Retry = true;
		m_Cou = 45;

	}
	else if (m_SelectButton && m_CursorQuit)
	{
		m_Quit = true;
		m_Cou = 45;

	}

	if (m_Retry || m_Quit)m_Cou--;

	if (m_Retry && m_Cou <= 0)m_pSceneManager->SetScene(SCENE_GAME);
	if (m_Quit && m_Cou <= 0)m_pSceneManager->SetScene(SCENE_TITLE);

	//�A�C�e�����擾
	m_Inventory = *m_pSceneManager->GetInventory();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Result::Draw(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//�w�i
	DrawSpriteLeftTop(m_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	//��
	DrawSprite(m_TextureNoLight, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 5000 + m_LightOffsetX * 2.0f, 2500 + m_LightOffsetX * 2.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	//�J�[�\��
	DrawSprite(m_TextureNoCursor, m_SelectX, SCREEN_HEIGHT * 0.9f, 96 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
	
	//����
	DrawSprite(m_TextureNoRetry, SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.9f, 64 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSprite(m_TextureNoQuit, SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.9f, 48 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);

	//�A�C�e���\��
	m_Inventory.SetPos(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 450, SCREEN_HEIGHT * 0.3f));
	m_Inventory.Drow();
	//�R�C���S���莞
	if (m_pSceneManager->GetComplete())
	{
		DrawSprite(m_TextureNoCompleteText, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.15f, 80 * 3.5f, 49 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		//���ݎc�薇��
		if (m_Inventory.GetMaxCoin() != 0)
		{
			//�c��
			DrawSprite(m_TextureNoRest, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, 48 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
			//����
			int restCoin = m_Inventory.GetMaxCoin() - (int)m_Inventory.GetItemLest().size();
			m_Score.SetScore(restCoin);
			m_Score.Draw();
		}
	}
}
