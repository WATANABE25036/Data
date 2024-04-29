/*==============================================================================

   �^�C�g����ʏ���(�h��) [Title.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Title.h"
#include "Input.h"
#include "Texture.h"
#include "Sprite.h"
#include "Sound.h"
#include "SceneManager.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Title::Title(SceneManager* sceneManager)
	: Scene(sceneManager)
{
}

Title::~Title()
{
}

//=============================================================================
// ������
//=============================================================================
void Title::Init(void)
{
	//�e�N�X�`������
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/Tosher.png");
	m_TextureNoLight = LoadTexture((char*)"data/TEXTURE/Titlelight.png");
	m_TextureNoStart = LoadTexture((char*)"data/TEXTURE/Start.png");
	m_TextureNoEnd = LoadTexture((char*)"data/TEXTURE/End.png");
	m_TextureNoCursor = LoadTexture((char*)"data/TEXTURE/Cursor.png");
	m_BGMNo1 = LoadSound((char*)"data/BGM/TitleBGM1.wav");
	m_BGMNo2 = LoadSound((char*)"data/BGM/TitleBGM2.wav");

	m_SE_CursorMove = LoadSound((char*)"data/SE/CursorMove.wav");
	m_SE_Decision = LoadSound((char*)"data/SE/Decision.wav");

	PlaySound(m_BGMNo1, -1, 0.05f);
	PlaySound(m_BGMNo2, -1, 0.05f);
	//���y���Đ�
	//255(-1)�����[�v�w�肷��Ɩ������[�v
	//PlaySound(g_BGMNo, -1);

	m_SelectX = SCREEN_WIDTH * 0.4f;//�͂��߂�̈ʒu�ɍ��킹��
	m_CursorStart = true;
	m_Cou = 0;
	m_NextScene = false;
	m_End = false;
}

//=============================================================================
// �I������
//=============================================================================
void Title::Uninit(void)
{
	StopSoundAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void Title::Update(void)
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
		m_CursorStart = true;
		m_CursorEnd = false;
	}
	else if (m_RightButton)
	{
		m_SelectX = SCREEN_WIDTH * 0.6f;
		m_CursorEnd = true;
		m_CursorStart = false;
	}

	if (m_SelectButton && m_CursorStart)
	{
		m_NextScene = true;
		m_Cou = 45;
		
	}
	else if (m_SelectButton && m_CursorEnd)
	{
		m_End = true;
		m_Cou = 45;

	}

	if (m_NextScene || m_End)m_Cou--;

	if(m_NextScene && m_Cou <= 0)m_pSceneManager->SetScene(SCENE_GAME);
	if (m_End && m_Cou <= 0)PostQuitMessage(0);//�Q�[���I��
}

//=============================================================================
// �`�揈��
//=============================================================================
void Title::Draw(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	//�^�C�g��
	DrawSpriteLeftTop(m_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	//��
	DrawSprite(m_TextureNoLight, SCREEN_WIDTH * 0.5f + m_LightOffsetX, SCREEN_HEIGHT * 0.5f, 5000 + m_LightOffsetX * 2.0f, 2500 + m_LightOffsetX * 2.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	//�J�[�\��
	DrawSprite(m_TextureNoCursor, m_SelectX, SCREEN_HEIGHT * 0.9f, 96 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);

	//����
	DrawSprite(m_TextureNoStart, SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.9f, 64 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSprite(m_TextureNoEnd, SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.9f, 48 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
}

