// =============================================================================
// ���C�� [main.cpp]
// Author:�n� �C	Date:2023.1.13
// =============================================================================
#include "main.h"
#include "title.h"
#include "game.h"
#include "result.h"

#include "conioex.h"

// *****************************************************************************
// �}�N����`
// *****************************************************************************
#define		DEBUG_TIMER (500)	// �f�o�b�O�\���̊Ԋu 500ms

// *****************************************************************************
// �v���g�^�C�v�錾
// *****************************************************************************
#ifdef _DEBUG
	void DispFPS(void);	// �f�o�b�O���̂ݗL���Ȋ֐�
#endif

// *****************************************************************************
// �O���[�o���ϐ�
// *****************************************************************************
int g_fpsCounter;				//  FPS�J�E���^
SCENE g_scene;					//  �V�[������p

// =============================================================================
// ���C���֐�
// =============================================================================
int main(void)
{
	int execLastTime;	// �Q�[���������������ԁi�^�C�}�[�l�j
	int fpsLastTime;	// �f�o�b�O�\�����������ԁi�^�C�}�[�l�j
	int currentTime;	// ���݂̎��ԁi�^�C�}�[�l�j
	int frameCount;		// �Q�[���̏�����������

	setcaption((char*)"�}�O�l�g");

	//  �^�C�}�[����\�������x�ɐݒ�
	//  1/1000�b���Ƃ�1��������^�C�}�[���g����
	timeBeginPeriod(1);

	execLastTime = 
	fpsLastTime = timeGetTime();	// ���݂̃^�C�}�[�l�擾

	// �ϐ���0�ɏ�����
	currentTime =
	frameCount = 0;

	//  �J�[�\���\���n�e�e
	setcursortype(NOCURSOR);

	//������
	g_scene = SCENE_TITLE;
	// ==========================
	// ���̕ӂŏ������������s��
	// ==========================
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitializeTitle();
		break;
	case SCENE_GAME:
		InitializeGame();
		break;
	case SCENE_RESULT:
		InitializeResult();
		break;
	default:
		break;
	}

	//  ��������Q�[�����[�v
	do
	{
		currentTime = timeGetTime();	// ���݂̃^�C�}�[�l
		if((currentTime - fpsLastTime) >= DEBUG_TIMER)	// �^�C�}�[�̍���500ms�ȏォ�ǂ���
		{	// �����񐔂ƌo�ߎ��Ԃ���1�b�Ԃɉ��񏈗��ł��邩���v�Z
			g_fpsCounter = frameCount * 1000 / (currentTime - fpsLastTime);
			fpsLastTime = currentTime;	// ���݂̃^�C�}�[�l��ۑ�
			frameCount = 0;				// �����񐔃��Z�b�g
		}

		// �O��Q�[���������̃^�C�}�[�l�ƌ��݂̃^�C�}�[�l�̍���
		// 1/60�b(17ms)�ȏ�ɂȂ��Ă����珈�������s
		if((currentTime - execLastTime) >= (1000 / 60))
		{
			execLastTime = currentTime;// ���݂̃^�C�}�[�l�ۑ�

			// �X�V����
			switch (g_scene)
			{
			case SCENE_TITLE:
				UpdateTitle();
				break;
			case SCENE_GAME:
				UpdateGame();
				break;
			case SCENE_RESULT:
				UpdateResult();
				break;
			default:
				break;
			}

			// �`�揈��(�㏑������邽�ߏ��Ԓ���)
			switch (g_scene)
			{
			case SCENE_TITLE:
				DrawTitle();
				break;
			case SCENE_GAME:
				DrawGame();
				break;
			case SCENE_RESULT:
				DrawResult();
				break;
			default:
				break;
			}

			frameCount++;// �Q�[�������񐔃A�b�v

			//  �f�o�b�O���̂ݕ\��
			#ifdef _DEBUG
				DispFPS();
			#endif
		}
	} while( !inport(PK_ESC) ); // ESC�����܂Ń��[�v


	// ===============================
	// ���̕ӂŌ�n���������s��
	// ===============================
	switch (g_scene)
	{
	case SCENE_TITLE:
		FinalizeTitle();
		break;
	case SCENE_GAME:
		FinalizeGame();
		break;
	case SCENE_RESULT:
		FinalizeResult();
		break;
	default:
		break;
	}

	//  �J�[�\���\���n�m
	setcursortype(NORMALCURSOR);

	//  �^�C�}�[����\��߂�
	timeEndPeriod(1);

	return 0;
}

#ifdef _DEBUG
// =============================================================================
// �f�o�b�O�\��
// =============================================================================
void DispFPS(void)
{
	//  �F�ݒ�
	textattr(0x01);

	gotoxy(1, 1);	// �\���ʒu�ݒ�
	printf("FPS:%d", g_fpsCounter);// FPS�l�\��

	//  �F�ݒ�(���Ƃɖ߂�)
	textcolor(WHITE);

}
#endif

// =============================================================================
// �V�[���؂�ւ�
// =============================================================================
void SetScene(SCENE scene)
{
	//�ȑO�̃V�[���̏I���������s��
	switch (g_scene)
	{
	case SCENE_TITLE:
		FinalizeTitle();
		break;
	case SCENE_GAME:
		FinalizeGame();
		break;
	case SCENE_RESULT:
		FinalizeResult();
		break;
	default:
		break;
	}

	//�V�[���̍X�V
	g_scene = scene;

	//��ʂ̃N���A
	clrscr();

	//�X�V��̃V�[���̏��������s��
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitializeTitle();
		break;
	case SCENE_GAME:
		InitializeGame();
		break;
	case SCENE_RESULT:
		InitializeResult();
		break;
	default:
		break;
	}
}

// =============================================================================
// ���݂̃V�[�����Q�b�g
// =============================================================================
SCENE GetScene(void)
{
	return(g_scene);
}