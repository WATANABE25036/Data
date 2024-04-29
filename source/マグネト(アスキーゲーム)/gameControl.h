//===================================================
//�Q�[������[gameControl.h]
//Author:�n� �C	Date:2023.1.31
//===================================================
#ifndef _GAME_CONTROL_H_ //�C���N���[�h�K�[�h(��d��`�̖h�~)
#define _GAME_CONTROL_H_
#include "drawing.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�}�N����`
//===================================================
#define GRAVITY (0.0045f)	//�d��(0�Ŗ��d��)
#define DEFAULT_STAGE_SETTING (-1)		//�Q�[���J�n���̐ݒ�
#define FIRST_STAGE (STAGE1)		//�ŏ��ɓǂݍ��ރX�e�[�W
#define FINAL_STAGE (STAGE15)		//�Ō�̃X�e�[�W
#define S (8)
#define G (9)

//===================================================
//�񋓑̐錾
//===================================================
typedef enum
{
	STAGE1 = 1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	STAGE6,
	STAGE7,
	STAGE8,
	STAGE9,
	STAGE10,
	STAGE11,
	STAGE12,
	STAGE13,
	STAGE14,
	STAGE15,
}STAGE;

//===================================================
//�\���̐錾
//===================================================
//typedef struct { //�Q�[���R���g���[���\����
//	char stage1[DRAWING_HEIGHT_MAX][DRAWING_WIDTHW_MAX];
//}GAME_CONTROL;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeGameControl(void);
void UpdateGameControl(void);
void DrawGameControl(void);
void FinalizeGameControl(void);

int GetStageNum(void);
bool GetInstructions(void);
void SetStage(char stage[DRAWING_HEIGHT_MAX][DRAWING_WIDTHW_MAX]);
//GAME_CONTROL GetGameControl(void);

#endif