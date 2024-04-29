/*==============================================================================

   �Q�[������ [Game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Game.h"
#include "Main.h"
#include "Input.h"
#include "Collision.h"
#include "Sound.h"
#include "Shadow.h"
#include "Polyline.h"
#include "SceneManager.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Game::Game(SceneManager* sceneManager)
	: Scene(sceneManager)
{
}

Game::~Game()
{
}

//=============================================================================
// ������
//=============================================================================
void Game::Init(void)
{
	m_GameSystem.Init();

	SetLightEnable(true);

	SetAlphaTestEnable(true);

	m_BGM_Sewer = LoadSound((char*)"data/BGM/Sewer.wav");

	PlaySound(m_BGM_Sewer, -1, 0.2f);//���y�Đ�

	ShowCursor(false);//�}�E�X���\��
}

//=============================================================================
// �I������
//=============================================================================
void Game::Uninit()
{
	StopSoundAll();
	//�������Ƃ͋t���ɏI���������s��
	UninitPolyLine();
	UninitShadow();
	m_GameSystem.Uninit();
	ShowCursor(true);//�}�E�X�\��
}

//=============================================================================
// �X�V����
//=============================================================================
void Game::Update(void)
{
	m_GameSystem.Update();

	// �e�̍X�V����
	UpdateShadow();

	// �|�����C���̍X�V����
	UpdatePolyLine();

	//�J�[�\�����E�B���h�E����o�Ȃ��悤�ɂ���
	HWND* hWnd = GethWnd();
	if (GetForegroundWindow() == *hWnd)//�E�B���h�E���A�N�e�B�u�Ȃ���s
	{
		WindowClipCursor();
	}
	m_pSceneManager->SetInventory(m_GameSystem.GetInventory());//�C���x���g���̃|�C���^��n��

		//���U���g��ʂֈڍs
	if (m_GameSystem.GetPlayer()->GetResultRequest())
	{
		if (m_GameSystem.GetPlayer()->GetComplete())
		{
			m_pSceneManager->SetComplete(true);
		}
		m_pSceneManager->SetScene(SCENE_RESULT);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Game::Draw(void)
{
	m_GameSystem.Draw();

	// �|�����C���̕`�揈��
	DrawPolyLine();

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);
}

GameSystem Game::GetGameSystem()
{
	return m_GameSystem;
}
