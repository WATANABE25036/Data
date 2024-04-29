/*==============================================================================

   �V�[���Ǘ� [SceneManager.cpp]
														 Author : �n� �C
														 Date   : 2023/12/29
--------------------------------------------------------------------------------

==============================================================================*/
#include "SceneManager.h"
#include "Fade.h"
#include "Input.h"


//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
SceneManager::SceneManager()
	: m_Title(this), m_Game(this), m_Result(this)
{
	m_pFade = new Fade();
}

SceneManager::~SceneManager()
{
	delete m_pFade;
}

//=============================================================================
// ������
//=============================================================================
HRESULT SceneManager::Init(SCENE_INDEX index)
{
	m_SceneIndex = m_SceneNextIndex = index;

	switch (m_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		m_Title.Init();
		break;

	case SCENE_GAME:
		m_Game.Init();
		break;

	case SCENE_RESULT:
		m_Result.Init();
		break;
	}

	HRESULT hr = S_OK;
	hr = m_pFade->Init();
	if (FAILED(hr))	// �����������s
	{
		DebugPrint("�t�F�[�h���������s");
		return E_ABORT;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void SceneManager::Uninit()
{
	switch (m_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		m_Title.Uninit();
		break;

	case SCENE_GAME:
		m_Game.Uninit();
		break;

	case SCENE_RESULT:
		m_Result.Uninit();
		break;
	}
	m_pFade->Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void SceneManager::Update()
{
	m_pFade->Update();

	switch( m_SceneIndex ) 
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		m_Title.Update();
		break;

	case SCENE_GAME:
		m_Game.Update();
		break;

	case SCENE_RESULT:
		m_Result.Update();
		break;
	}
	
	m_pPlayer = m_Game.GetGameSystem().GetPlayer();

	CheckScene();//�V�[�����؂�ւ�������Ď�
}

//=============================================================================
// �`�揈��
//=============================================================================
void SceneManager::Draw()
{
	switch( m_SceneIndex )
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		m_Title.Draw();
		break;

	case SCENE_GAME:
		m_Game.Draw();
		break;

	case SCENE_RESULT:
		m_Result.Draw();
		break;
	}
	m_pFade->Draw();
}

//=============================================================================
// �V�[���J�ڂ�v��
//=============================================================================
void SceneManager::SetScene(SCENE_INDEX index)
{
	//�J�ڐ�V�[����ݒ肷��
	m_SceneNextIndex = index;
}

//=============================================================================
// �V�[���J�ڂ��Q�b�g
//=============================================================================
SCENE_INDEX SceneManager::GetNextIndex() const
{
	return m_SceneNextIndex;
}

//=============================================================================
// �J�ڂ�v��������ꍇ�ɃV�[����؂�ւ���
//=============================================================================
void SceneManager::CheckScene()
{
	//���݂̃V�[���ƑJ�ڐ�V�[��������Ă�����
	if( m_SceneIndex != m_SceneNextIndex )
	{
		if (m_pFade->GetFadeState() == FADE_OUT_COMP)
		{
			//���݂̃V�[�����I��������
			Uninit();
			//�J�ڐ�V�[���̏������������s��
			Init(m_SceneNextIndex);
			m_pFade->FadeIn();
		}
		else
		{
			m_pFade->FadeOut();
		}

	}
}
