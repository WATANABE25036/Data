//====================================================
//�ۑ�CP18 ��09(�l�[���o�g���[)
//main.cpp
//�����:�n� �C ���t:2022/12/16
//====================================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "conioex.h"

//----------------------------------------------------
//�}�N����`
//----------------------------------------------------
#define MAP_WIDTH		30		//�}�b�v�̉��̒���
#define MAP_HIGHT		30		//�}�b�v�̏c�̍���
#define ENTITY_MAX		10		//�}�b�v�ɕ\������G���e�B�e�B(�^�C��)�̎��
#define PLAYER_SPEED	4000	//�v���C���[�̃X�s�[�h(�������قǑ���)

//----------------------------------------------------
//�񋓑̐錾
//----------------------------------------------------
enum//�^�C����
{
	TILE_AIR = 0,
	TILE_PLAYER,
	TILE_ENEMY,
	TILE_ENEMY_DETECTION_RED,
	TILE_ENEMY_DETECTION_YELLOW,
	TILE_TREASURE,
	TILE_WALL,
};

//----------------------------------------------------
//�\���̐錾
//----------------------------------------------------
typedef struct//���ׂẴ^�C���̔ԍ��ƌ�����
{
	int number;
	char visual[64];
}OBJECT;

typedef struct//�v���C���[��G�l�~�[�Ȃǂ̍��W
{
	int x;
	int y;
	int oldX;
	int oldY;
}OBJECT_MOVE;

typedef struct//�v���C������̃v���C���[�̃X�R�A������
{
	int score;
	char name[20];
}SCORE;

//----------------------------------------------------
//�O���[�o���ϐ�
//----------------------------------------------------
int map[MAP_HIGHT][MAP_WIDTH] =
{//   1           5              10             15             20             25             30             35             40             45             50
 //   |           |              |              |              |              |              |              |              |              |              | 
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 1 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 5 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 10 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 15 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 20 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 25 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 30 */
};

char uiFrame[30][41] =
{
	//  1 2 3 4 5 6 7 8 91011121314151617181920
	// ����������������������������������������
	{ "���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\��"},/* 1 */
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},/* 5 */
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},/* 10 */
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},/* 15 */
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},/* 20 */
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},/* 25 */
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "��                                    ��"},
	{ "���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\��"},/* 30 */
};

char uiWeapon[10][10] =//���g�p
{
	//  1 2 3 4 5 6 7 8 91011121314151617181920
	// ����������������������������������������
	{ "�c����"},/* 1 */
	{ "�_�ȃm"},
	{ " /=��"},
	{ "�� �܄�"},
	{ "��| Є�"},/* 5 */
	{ "��| Є�"},
	{ "��: ���"},
	{ " ́��"},
	{ "  ��"},
};

char uiTreasur[6][30] =
{
	//  1 2 3 4 5 6 7 8 91011121314151617181920
	// ����������������������������������������
	{ "    _�Q___�Q"},/* 1 */
	{ "  �^ \"\"\"\"���܁_"},
	{ " //_____/___=Є�"},
	{ "�� ;�� |��|���Є�"},
	{ "�� ;_�Q|�� |_ �Є�"},/* 5 */
	{ "������������ ������������ ��"},
};
	
char uiExplosionRange[7][16] =//���g�p
{
	//  1 2 3 4 5 6 7 8 91011121314151617181920
	// ����������������������������������������
	{ "�Q�^�_�ȁ^�_�Q"},/* 1 */
	{ "�_�@�@�@�@�@�^"},
	{ "�^�@�^�Ɂ_�@�_"},
	{ "���@���@���@��"},
	{ "�_�@�_�ȁ^�@�^"},/* 5 */
	{ "�^�@�@�@�@�@�_"},
	{ "�P�_�^�Ɂ_�^�P"},
};

/*
����������������������|
������������������������
������  ������  ������
�Q�P�a�u�v=����ߎO_
�����������������R�S�T�U�L�M�_�^
.�N��":;_/���|~^@#[]{}()=_
�݁����t�s�փw̓~Ё^/���mɃ\��Y���c�ڇ��Ɂ�
����������������������������������
�{�|�}�~�������߁������������
������ځہ܁݁�聈��w�x�y�z()�k�l{}�q�r�u�v
�ȁɁʁˁ́́΁����ށ�����������������������������������������񁋁���
�������������������������������������������������������ÃăŃƃǃȃɃʃ˃̃̓΃σЃу҃ӃԃՃ�
�C�e�����ғ������������҃ǃƃЃσq���W���������ݎO�C
�ꉚ�����v�Ѝ���M�O�R�m�Y�\�`��������l�S�p�ΐ����������ʓ���������
�S�m���ї[�����������������X�Y�c�k�q�{�������������ęʙؙڙٚ�~����O�T�c�e��h�V�W�l

    _�Q___�Q
  �^ """"���܁_
 //_____/___=Є�
��;�� |��|���Є�
��;_�Q|��|__�Є�
������ ������ ��


  �c����
  �_�ȃm
   /=��
  ���܄�
  ��|Є�
  ��|Є�
  ��:���
   ́��
	��

*/

//----------------------------------------------------
//�v���g�^�C�v�錾
//----------------------------------------------------
void screenSize(int x, int y);
void createMap(OBJECT* pEntity, int color, int seed);
void inputKey(int* pMoveKey);
void inputMouse(int* pMoveMouse);
bool moveDalay(int moveKey, int oldMoveKey);
void randomMapCreate(int roomNumMax, int roomNumMin, int roomScaleMax, int roomScaleMin, int* pSeed);
void playerSet(int* playerX, int* playerY);
void mapTileRandomSet(int tileName, int tileNumMax, int tileNumMin);
void gameover(SCORE* pPlayerScore);
void uiSetWeapon(int x, int y, int num, int space);
void uiSetTreasure(int x, int y, int num, int space);
void uiSetFrame(void);
void savePlayerScore(SCORE* pPlayerScore);
void roadPlayerScore(void);
void mainGame(int seed);

//----------------------------------------------------
//���C���֐�
//----------------------------------------------------
int main()
{
	int seed = 0;
	OBJECT tile[ENTITY_MAX];//�ŏ��̉�ʃ^�C������

	//�ŏ��̉�ʃ^�C���ݒ�
	for (int i = 0; i < ENTITY_MAX; i++)
	{
		tile[i].number = i;
		if (tile[i].number == TILE_AIR)
		{
			strcpy(tile[i].visual, "�@");
		}

		if (tile[i].number == TILE_PLAYER)
		{
			strcpy(tile[i].visual, "��");
		}

		if (tile[i].number == TILE_ENEMY)
		{
			strcpy(tile[i].visual, "�d");
		}

		if (tile[i].number == TILE_ENEMY_DETECTION_RED)
		{
			strcpy(tile[i].visual, "�n");
		}

		if (tile[i].number == TILE_ENEMY_DETECTION_YELLOW)
		{
			strcpy(tile[i].visual, "��");
		}

		if (tile[i].number == TILE_TREASURE)
		{
			strcpy(tile[i].visual, "��");
		}

		if (tile[i].number == TILE_WALL)
		{
			strcpy(tile[i].visual, "��");
		}
	}

	//�ŏ��̉�ʐF
	int color = TILE_AIR;

	screenSize(100, 31);//��ʃT�C�Y(X, Y)

	while (true)
	{
		//�V�[�h�l���͉��
		createMap(tile, color, 0);//�S��ʓh��Ԃ����߂ɕ\��
		clrscr();
		createMap(tile, color, 0);//�V�[�h���͎��̃}�b�v��ʕ\��
		uiSetFrame();//�t���[���\��
		randomMapCreate(30, 5, 8, 2, &seed);//�V�[�h�l����͂��ă}�b�v���쐬

		//�Q�[�����
		clrscr();
		mainGame(seed);
		roadPlayerScore();//�Q�[���I�[�o�[�ɂȂ����Ƃ��̃X�R�A�\��
	}
	
	//���͑҂�
	rewind(stdin);//���̓o�b�t�@�������߂�
	getchar();//Enter�̓��͑҂�
}

//----------------------------------------------------
//��ʃT�C�Y�ύX
//----------------------------------------------------
void screenSize(int x, int y)
{
	//��ʃT�C�Y���
	const COORD window_size = { x, y }; //��ʃT�C�Y�̒�`
	SMALL_RECT console_screen_rect;   //�R���\�[����ʂ̃T�C�Y�ݒ�p
	console_screen_rect.Top = 0;
	console_screen_rect.Bottom = window_size.Y - 1;
	console_screen_rect.Left = 0;
	console_screen_rect.Right = window_size.X - 1;

	//�o�b�t�@�T�C�Y�̕ύX
	const HANDLE h_console_output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(h_console_output, window_size);

	//�X�N���[���T�C�Y�̕ύX
	CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
	GetConsoleScreenBufferInfo(h_console_output, &console_screen_buffer_info);
	SetConsoleWindowInfo(h_console_output, TRUE, &console_screen_rect);
}

//----------------------------------------------------
//�}�b�v�쐬 & �X�V
//----------------------------------------------------
void createMap(OBJECT* pEntity, int color, int seed)
{
	srand(seed);
	int colorTheme = 0;

	if (seed != 0)
	{
		colorTheme = rand() % 10;
	}

	gotoxy(1, 1);

	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (colorTheme == 0)textattr(0xFF);
			else if (colorTheme == 1)textattr(0xCC);
			else if (colorTheme == 2)textattr(0xBB);
			else if (colorTheme == 3)textattr(0x66);
			else if (colorTheme == 4)textattr(0x00);
			else if (colorTheme == 5)textattr(0x44);
			else if (colorTheme == 6)textattr(0xFF);
			else if (colorTheme == 7)textattr(0x11);
			else if (colorTheme == 8)textattr(0xDD);
			else if (colorTheme == 9)textattr(0x0A);

			if (color == TILE_ENEMY) textattr(0x00);
			if (color == TILE_ENEMY_DETECTION_RED) textattr(0x00);
			if (color == TILE_ENEMY_DETECTION_YELLOW) textattr(0x88);

			if (map[i][j] == (pEntity + TILE_AIR)->number)//��
			{
				if (color == TILE_ENEMY) textattr(0x00);
				if (color == TILE_ENEMY_DETECTION_RED) textattr(0x00);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textattr(0x88);
				
				printf("%s", (pEntity + TILE_AIR)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_PLAYER)->number)//�v���C���[
			{
				textcolor(0xC);
				if (colorTheme == 1)textcolor(0x4);
				else if (colorTheme == 6)textcolor(0x0);
				else if (colorTheme == 8)textcolor(0xA);
				else if (colorTheme == 9)textcolor(0xA);

				if (color == TILE_ENEMY) textcolor(0x4);
				if (color == TILE_ENEMY_DETECTION_RED) textcolor(0xC);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textcolor(0xC);

				printf("%s", (pEntity + TILE_PLAYER)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_ENEMY)->number)//�G�l�~�[
			{
				if (colorTheme == 9)textcolor(0x0);
				if (color == TILE_ENEMY) textcolor(0xC);
				if (color == TILE_ENEMY_DETECTION_RED) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textcolor(0x8);

				printf("%s", (pEntity + TILE_ENEMY)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_ENEMY_DETECTION_RED)->number)//�G�l�~�[���m(��)
			{
				if (colorTheme == 9)textcolor(0x0);
				if (color == TILE_ENEMY) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_RED) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textcolor(0x8);

				printf("%s", (pEntity + TILE_ENEMY_DETECTION_RED)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_ENEMY_DETECTION_YELLOW)->number)//�G�l�~�[���m(��)
			{
				if (colorTheme == 9)textcolor(0x0);
				if (color == TILE_ENEMY) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_RED) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textcolor(0x8);

				printf("%s", (pEntity + TILE_ENEMY_DETECTION_YELLOW)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_TREASURE)->number)//��
			{
				textattr(0xE0);
				if (colorTheme == 6)textattr(0x0F);
				else if (colorTheme == 7)textattr(0x1F);
				else if (colorTheme == 8)textattr(0xAD);
				else if (colorTheme == 9)textattr(0xA0);

				if (color == TILE_ENEMY) textattr(0xF0);
				if (color == TILE_ENEMY_DETECTION_RED) textattr(0x40);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textattr(0x67);
				
				printf("%s", (pEntity + TILE_TREASURE)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_WALL)->number)//��
			{
				textattr(0x87);
				if (colorTheme == 6)textattr(0x00);
				else if (colorTheme == 7)textattr(0xFC);
				else if (colorTheme == 8)textattr(0xAD);
				else if (colorTheme == 9)textattr(0xA0);

				if (color == TILE_ENEMY) textattr(0x0F);
				if (color == TILE_ENEMY_DETECTION_RED) textattr(0x04);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textattr(0x86);

				printf("%s", (pEntity + TILE_WALL)->visual);
			}
		}
		printf("\n");
	}
}

//----------------------------------------------------
//�L�[���͊m�F
//----------------------------------------------------
void inputKey(int* pMoveKey)
{
	int moveY = inport(PK_W) - inport(PK_S);
	int moveX = inport(PK_A) - inport(PK_D);

	if (moveX == 1)
	{
		*pMoveKey = 3;
	}

	if (moveX == -1)
	{
		*pMoveKey = 4;
	}

	if (moveY == 1)
	{
		*pMoveKey = 1;
	}

	if (moveY == -1)
	{
		*pMoveKey = 2;
	}

	if (moveY == 0 && moveX == 0)
	{
		*pMoveKey = 0;//�~
	}
}

//----------------------------------------------------
//�ړ��̃f�B���C
//----------------------------------------------------
bool moveDalay(int moveKey, int oldMoveKey)
{
	int moveDalayCou = 0;
	bool result = false;

	if (oldMoveKey == moveKey && moveKey != 0)//���������ɘA���Ői��ł��邩�A�~�܂��Ă��Ȃ�
	{
		while (true)
		{
			moveDalayCou++;
			oldMoveKey = moveKey;
			inputKey(&moveKey);//�L�[���͊m�F

			if (PLAYER_SPEED < moveDalayCou)
			{
				result = true;
				break;
			}
			if (oldMoveKey != moveKey || moveKey == 0)
			{
				break;
			}
		}
	}
	else
	{
		result = true;
	}

	return result;
}

//----------------------------------------------------
//�����_���Ƀ}�b�v�𐶐�
//----------------------------------------------------
void randomMapCreate(int roomNumMax, int roomNumMin, int roomScaleMax, int roomScaleMin, int* pSeed)
{
	char mapSeed[255];
	int seed = 0;
	int roomNum;
	int randomX[255] = { 0 };
	int randomY[255] = { 0 };
	int scaleSelect = 0;

	//�}�b�v��ǂŖ��ߐs����
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			map[i][j] = TILE_WALL;
		}
	}

	gotoxy(71, 5);
	printf("�}�b�v�𐶐����܂�");
	gotoxy(68, 7);
	printf("�V�[�h�l�����Ă�������");
	gotoxy(70, 10);
	printf("�P�P�P�P�P�P�P�P�P�P");
	gotoxy(70, 9);
	setcursortype(SOLIDCURSOR);
	scanf("%s", &mapSeed);
	setcursortype(NOCURSOR);

	int len = strlen(mapSeed);

	//�V�[�h�l�v�Z
	for (int i = 0; i < len; i++)
	{
		if (i % 3 == 0)
		{
			if (i % 2 == 0)
			{
				seed += mapSeed[i];
			}
			else
			{
				seed += mapSeed[i] * 2;
			}
		}

		if (i % 3 == 1)
		{
			if (i % 2 == 1)
			{
				seed += mapSeed[i] * 3;
			}
			else
			{
				seed += mapSeed[i] * 4;
			}
		}

		if (i % 3 == 2)
		{
			if (i % 2 == 0)
			{
				seed += mapSeed[i] * 5;
			}
			else
			{
				seed += mapSeed[i] * 6;
			}
		}
	}
	
	srand(seed);
	*pSeed = seed;

	//�����̐���
	roomNum = rand() % (roomNumMax - roomNumMin + 1) + roomNumMin;//�����̐�
	for (int i = 0; i < roomNum; i++)
	{
		randomX[i] = rand() % MAP_WIDTH;
		randomY[i] = rand() % MAP_HIGHT;

		for (int j = 0; j < rand() % (roomScaleMax - roomScaleMin + 1) + roomScaleMin; j++)//�����̏c�̒���
		{
			for (int k = 0; k < rand() % (roomScaleMax - roomScaleMin + 1) + roomScaleMin; k++)//�����̉��̒���
			{
				if ((randomY[i] + j >= 0) && (randomY[i] + j < MAP_HIGHT) && (randomX[i] + k >= 0) && (randomX[i] + k < MAP_WIDTH))//�}�b�v�O�ɂ͐������Ȃ�
				{
					map[randomY[i] + j][randomX[i] + k] = TILE_AIR;
				}
			}
		}
	}

	//�L���̐���
	for (int i = 0; i < roomNum + 1; i++)//�����������[�v(�ŏ��̕����ƍŌ�̕������Ȃ��邽�� +1)
	{
		int targetRoom = i + 1;//�Ȃ���̕���
		int randomXUpdate = 0;

		if (roomNum < targetRoom)//�ŏ��̕����ƍŌ�̕������Ȃ���
		{
			targetRoom = 0;
		}
		
		if (randomX[i] < randomX[targetRoom])
		{
			for (int j = 0; j < abs(randomX[i] - randomX[targetRoom]); j++)
			{
				map[randomY[i]][randomX[i] + j + 1] = TILE_AIR;
				randomXUpdate = randomX[i] + j + 1;//�ŏIx���W����
			}
		}
		else if (randomX[i] > randomX[targetRoom])
		{
			for (int j = 0; j < abs(randomX[i] - randomX[targetRoom]); j++)
			{
				map[randomY[i]][randomX[i] - j - 1] = TILE_AIR;
				randomXUpdate = randomX[i] - j - 1;//�ŏIx���W����
			}
		}
		else
		{
			randomXUpdate = randomX[i];//�ŏIx���W����
		}

		if (randomY[i] < randomY[targetRoom])
		{
			for (int j = 0; j < abs(randomY[i] - randomY[targetRoom]); j++)
			{
				if (j <= MAP_HIGHT)
				{
					map[randomY[i] + j + 1][randomXUpdate] = TILE_AIR;
				}
			}
		}
		else if (randomY[i] > randomY[targetRoom])
		{
			for (int j = 0; j < abs(randomY[i] - randomY[targetRoom]); j++)
			{
				map[randomY[i] - j- 1][randomXUpdate] = TILE_AIR;
			}
		}
	}
}

//----------------------------------------------------
//�v���C���[��z�u
//----------------------------------------------------
void playerSet(int* playerX, int* playerY)
{
	bool playerCheck = false;
	int airCou = 0;
	int loopCou = 0;
	srand((unsigned int)time(0));//seed�l�̃Z�b�g

	//��̃^�C�������v�Z
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j] == TILE_AIR)
			{
				airCou++;
			}
		}
	}

	//�v���C���[�z�u
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (playerCheck == false && map[i][j] == TILE_AIR)
			{
				if (rand() % (airCou - loopCou) == 0)//�}�b�v���ɕK���v���C���[��z�u����
				{
					*playerX = j;
					*playerY = i;
					map[*playerY][*playerX] = TILE_PLAYER;
					playerCheck = true;
				}
				else
				{
					loopCou++;
				}
			}
		}
	}
}

//----------------------------------------------------
//�`�̃^�C����z�u
//----------------------------------------------------
void mapTileRandomSet(int tileName, int tileNumMax, int tileNumMin)
{
	{
		bool treasureCheck = false;
		int airCou = 0;
		int loopCou = 0;
		srand((unsigned int)time(0));//seed�l�̃Z�b�g

		//��̃^�C�������v�Z
		for (int i = 0; i < MAP_HIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j] == TILE_AIR)
				{
					airCou++;
				}
			}
		}

		//�z�u
		for (int k = 0; k < rand() % (tileNumMax - tileNumMin + 1) + tileNumMin; k++)
		{
			treasureCheck = false;
			loopCou = 0;
			for (int i = 0; i < MAP_HIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (treasureCheck == false && map[i][j] == TILE_AIR)
					{
						if (rand() % (airCou - loopCou) == 0)//�}�b�v���ɕK���z�u����
						{
							map[i][j] = tileName;
							treasureCheck = true;
						}
						else
						{
							loopCou++;
						}
					}
				}
			}
		}
	}
}

//----------------------------------------------------
//�Q�[���I�[�o�[(���O����)
//----------------------------------------------------
void gameover(SCORE* pPlayerScore)
{
	char name[64];

	uiSetFrame();
	while (true)
	{
		setcursortype(SOLIDCURSOR);//�u���b�N�J�[�\��
		strcpy(pPlayerScore->name, "-UNKNOWN-");

		textcolor(0xF);//��
		gotoxy(76, 5);
		printf("�` %d �`", pPlayerScore->score);

		gotoxy(70, 8);
		printf("���O�����Ă�������");

		gotoxy(74, 11);
		printf("�P�P�P�P�P�P");

		gotoxy(74, 10);
		scanf("%s", name);

		int len = strlen(name);

		if (len > 12)//12�o�C�g�ȏ�͓��͍ē���
		{
			uiSetFrame();
			gotoxy(71, 9);
			textcolor(0x4);//��
			printf("�����O���������ł�");
		}
		else
		{
			strcpy(pPlayerScore->name, name);
			setcursortype(NOCURSOR);//�J�[�\����\��
			break;
		}
	}
}

//----------------------------------------------------
//����UI�\��
//----------------------------------------------------
void uiSetWeapon(int x, int y, int num, int space)
{
	int wideSpace = 0;
	for (int k = 0 ; k < num; k++, wideSpace += space)
	{
		for (int i = 0; i < 10; i++)
		{
			gotoxy(61 + x + wideSpace, 1 + y + i);
			for (int j = 0; j < 10; j++)
			{
				printf("%c", uiWeapon[i][j]);
			}
		}
	}
}

//----------------------------------------------------
//��UI�\��
//----------------------------------------------------
void uiSetTreasure(int x, int y, int num, int space)
{
	int wideSpace = 0;
	for (int k = 0; k < num; k++, wideSpace += space)
	{
		for (int i = 0; i < 6; i++)
		{
			gotoxy(61 + x + wideSpace, 1 + y + i);
			for (int j = 0; j < 30; j++)
			{
				printf("%c", uiTreasur[i][j]);
			}
		}
	}
}

//----------------------------------------------------
//UI�t���[���\��
//----------------------------------------------------
void uiSetFrame(void)
{
	textattr(0x8F);
	for (int i = 0; i < 30; i++)
	{
		gotoxy(60 + 1, i + 1);
		for (int j = 0; j < 40; j++)
		{
			printf("%c", uiFrame[i][j]);
		}
	}
}

//----------------------------------------------------
//�X�R�A�̃Z�[�u
//----------------------------------------------------
void savePlayerScore(SCORE* pPlayerScore)
{
	FILE* fp; //�t�@�C���|�C���^�[

	//�o�C�i���������݃��[�h�Ńt�@�C���I�[�v��
	fp = fopen("score.sav", "ab");

	//��������
	fwrite(pPlayerScore, sizeof(SCORE), 1, fp);

	pPlayerScore = 0;

	//�t�@�C���N���[�Y
	fclose(fp);
}

//----------------------------------------------------
//�X�R�A�̕\��
//----------------------------------------------------
void roadPlayerScore(void)
{
	SCORE score[99];
	SCORE tmp;

	uiSetFrame();

	for (int i = 0; i < 99; i++)
	{
		score[i].score = 0;
		strcpy(score[i].name, "       ");
	}

	FILE* fp; //�t�@�C���|�C���^�[

	//�o�C�i���������݃��[�h�Ńt�@�C���I�[�v��
	fp = fopen("score.sav", "rb");

	//�ǂݍ���
	if (fp != NULL)
	{
		fread(score, sizeof(SCORE), 99, fp);
	}

	//�X�R�A���\�[�g
	for (int i = 0; i < 99; i++)
	{
		for (int j = 0; j < 99 - i; j++)
		{
			if (score[i].score < score[i + j].score)
			{
				tmp = score[i];
				score[i] = score[i + j];
				score[i + j] = tmp;
			}
		}
	}
	
	gotoxy(68, 4);
	printf("�� �f�`�l�d�@�n�u�d�q ��");
	gotoxy(82, 29);
	printf("R �� Continue�c");
	gotoxy(72, 7);
	printf("�m�`�l�d");
	gotoxy(87, 7);
	printf("�r�b�n�q�d");

	for (int i = 0; i < 20; i++)
	{
		gotoxy(63, 8 + i);
		printf("RANK %d", i + 1);

		gotoxy(72, 8 + i);
		printf("%s", score[i].name);

		if (999999 < score[i].score)
		{
			gotoxy(87, 8 + i);
			printf("999999+");
		}
		else
		{
			gotoxy(87, 8 + i);
			printf("%d", score[i].score);
		}
	}
	//�t�@�C���N���[�Y
	fclose(fp);

	gotoxy(1, 31);

	reinport();
	while (inport(PK_R) == false);
}

//----------------------------------------------------
//�Q�[���{��
//----------------------------------------------------
void mainGame(int seed)
{
	OBJECT_MOVE player;//�v���C���[���W����
	//������
	player.x = 0;
	player.y = 0;
	player.oldX = 0;
	player.oldY = 0;

	OBJECT_MOVE enemy[64];//�G�l�~�[���W����
	//������
	for (int i = 0; i < 64; i++)
	{
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].oldX = 0;
		enemy[i].oldY = 0;
	}

	OBJECT_MOVE treasure[64];//����W����
	//������
	for (int i = 0; i < 64; i++)
	{
		treasure[i].x = 0;
		treasure[i].y = 0;
		treasure[i].oldX = 0;
		treasure[i].oldY = 0;
	}

	uiSetFrame();
	
	textcolor(0xF);
	gotoxy(67, 3);
	textcolor(0xC);
	printf("��");
	textcolor(0xF);
	printf(" �� �v�`�r�c �ňړ�����");

	gotoxy(67, 5);
	textattr(0xE0);
	printf("��");
	textattr(0x8F);
	printf(" ����������W�߂܂��傤");

	gotoxy(67, 7);
	printf("�����Ȃ� �G �ɂ͗v����");

	gotoxy(67, 8);
	printf("�F���ς�����Ƃ��̓L�P��!");

	gotoxy(67, 9);
	printf("�߂��ɂ��邩��...");

	playerSet(&player.x, &player.y);

	mapTileRandomSet(TILE_TREASURE, 5, 3);
	mapTileRandomSet(TILE_ENEMY, 3, 3);

	OBJECT tile[ENTITY_MAX];//�^�C������

	//�^�C���ݒ�
	for (int i = 0; i < ENTITY_MAX; i++)
	{
		tile[i].number = i;
		if (tile[i].number == TILE_AIR)
		{
			strcpy(tile[i].visual, "�@");
		}

		if (tile[i].number == TILE_PLAYER)
		{
			strcpy(tile[i].visual, "��");
		}

		if (tile[i].number == TILE_ENEMY)
		{
			strcpy(tile[i].visual, "�d");
		}

		if (tile[i].number == TILE_ENEMY_DETECTION_RED)
		{
			strcpy(tile[i].visual, "�n");
		}

		if (tile[i].number == TILE_ENEMY_DETECTION_YELLOW)
		{
			strcpy(tile[i].visual, "��");
		}

		if (tile[i].number == TILE_TREASURE)
		{
			strcpy(tile[i].visual, "��");
		}

		if (tile[i].number == TILE_WALL)
		{
			strcpy(tile[i].visual, "��");
		}
	}

	//�F
	int color = TILE_AIR;
	//�L�[�{�[�h�֌W
	int moveKey = 0;
	int oldMoveKey = 0;
	//�}�E�X�J�[�\���֌W
	int x, y;
	int oldX, oldY;
	int mouseLeft, oldMouseLeft;
	int cou = 0;
	bool response = true;
	x = y = 0;
	oldX = oldY = 0;
	mouseLeft = 0;
	oldMouseLeft = 0;
	//��̏�����
	SCORE playerScore;
	playerScore.score = 0;
	int oldScore = playerScore.score;
	strcpy(playerScore.name, "UNKNOWN");

	setcursortype(NOCURSOR);//�J�[�\��������

	createMap(tile, color, seed);//����}�b�v�\��

	reinport();

	while (true)
	{
		player.oldX = player.x;
		player.oldY = player.y;
		oldMoveKey = moveKey;

		inputKey(&moveKey);//�L�[���͊m�F

		//�v���C���[�ړ�
		if (moveDalay(moveKey, oldMoveKey) == true)//�ړ��̃f�B���C
		{
			switch (moveKey)
			{
			case 1:
				player.y--;
				break;
			case 2:
				player.y++;
				break;
			case 3:
				player.x--;
				break;
			case 4:
				player.x++;
				break;
			}

			//�}�b�v�O�ƕǂɍs���Ȃ��悤�ɂ���
			if ((player.y) > (MAP_HIGHT - 1) || (player.x) > (MAP_WIDTH - 1) ||
				(player.y) < 0 || (player.x) < 0 ||
				map[player.y][player.x] == TILE_WALL)//�ړ��悪��
			{
				player.x = player.oldX;
				player.y = player.oldY;
			}

		}

		//�}�b�v�̃G�l�~�[�̏ꏊ��enemy.x, y�ɓ����
		int enmeyCou = 0;

		for (int i = 0; i < MAP_HIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j] == TILE_ENEMY)
				{
					enemy[enmeyCou].x = j;
					enemy[enmeyCou].y = i;
					enmeyCou++;
				}
			}
		}

		//�}�b�v�̕�̏ꏊ��treasure.x, y�ɓ����
		int treasureCou = 0;

		for (int i = 0; i < MAP_HIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j] == TILE_TREASURE)
				{
					treasure[treasureCou].x = j;
					treasure[treasureCou].y = i;
					treasureCou++;
				}
			}
		}

		if (player.oldX != player.x || player.oldY != player.y)//�v���C���[���ړ������ꍇ
		{
			map[player.oldY][player.oldX] = TILE_AIR;//�O�̃v���C���[���󔒂ɏ㏑��

			//�O�̃G�l�~�[���m�폜
			for (int i = 0; i < MAP_HIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (map[i][j] == TILE_ENEMY_DETECTION_RED || map[i][j] == TILE_ENEMY_DETECTION_YELLOW)
					{
						map[i][j] = TILE_AIR;
					}
				}
			}

			//�G�l�~�[�ړ�
			srand((unsigned int)time(0));//seed�l�̃Z�b�g
			int randomMove;

			for (int i = 0; i < enmeyCou; i++)
			{
				randomMove = rand() % 10;

				enemy[i].oldX = enemy[i].x;
				enemy[i].oldY = enemy[i].y;

				if (randomMove == 1)
				{
					enemy[i].y--;
				}
				else if (randomMove == 2)
				{
					enemy[i].y++;
				}
				else if (randomMove == 3)
				{
					enemy[i].x--;
				}
				else if (randomMove == 4)
				{
					enemy[i].x++;
				}
				else
				{
				}

				//�}�b�v�O�ƕǂɍs���Ȃ��悤�ɂ���
				if ((enemy[i].y) > (MAP_HIGHT - 1) || (enemy[i].x) > (MAP_WIDTH - 1) ||
					(enemy[i].y) < 0 || (enemy[i].x) < 0 ||
					map[enemy[i].y][enemy[i].x] == TILE_WALL ||//�ړ��悪��
					map[enemy[i].y][enemy[i].x] == TILE_ENEMY ||//�z�u�悪�G�l�~�[
					map[enemy[i].y][enemy[i].x] == TILE_TREASURE ||//�z�u�悪��
					map[enemy[i].y][enemy[i].x] == TILE_PLAYER)//�z�u�悪�v���C���[
				{
					enemy[i].x = enemy[i].oldX;
					enemy[i].y = enemy[i].oldY;
				}
				map[enemy[i].oldY][enemy[i].oldX] = TILE_AIR;//�O�̃G�l�~�[���󔒂ɏ㏑��
				map[enemy[i].y][enemy[i].x] = TILE_ENEMY;//�G�l�~�[�z�u
				//�G�l�~�[���m��z�u

				//�G�l�~�[���m�z�u(��)
				for (int k = 0; k < 7; k++)
				{
					for (int l = 0; l < 7; l++)
					{
						if (!((l == 0 && k == 0) || (l == 1 && k == 0) || (l == 0 && k == 1) ||
							(l == 5 && k == 0) || (l == 6 && k == 0) || (l == 6 && k == 1) ||
							(l == 0 && k == 5) || (l == 0 && k == 6) || (l == 1 && k == 6) ||
							(l == 6 && k == 5) || (l == 5 && k == 6) || (l == 6 && k == 6)))
						{
							//�}�b�v�O���͕ǂłȂ���Δz�u
							if (!((enemy[i].y - 3 + k) > (MAP_HIGHT - 1) || (enemy[i].x - 3 + l) > (MAP_WIDTH - 1) ||
								(enemy[i].y - 3 + k) < 0 || (enemy[i].x - 3 + l) < 0 ||
								map[enemy[i].y - 3 + k][enemy[i].x - 3 + l] == TILE_WALL ||//�z�u�悪��
								map[enemy[i].y - 3 + k][enemy[i].x - 3 + l] == TILE_ENEMY))//�z�u�悪�G�l�~�[
							{
								map[enemy[i].y - 3 + k][enemy[i].x - 3 + l] = TILE_ENEMY_DETECTION_YELLOW;
							}
						}
					}
				}

				//�G�l�~�[���m�z�u(��)
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						//�}�b�v�O���͕ǂłȂ���Δz�u
						if (!((enemy[i].y - 1 + k) > (MAP_HIGHT - 1) || (enemy[i].x - 1 + l) > (MAP_WIDTH - 1) ||
							(enemy[i].y - 1 + k) < 0 || (enemy[i].x - 1 + l) < 0 ||
							map[enemy[i].y - 1 + k][enemy[i].x - 1 + l] == TILE_WALL ||//�z�u�悪��
							map[enemy[i].y - 1 + k][enemy[i].x - 1 + l] == TILE_ENEMY))//�z�u�悪�G�l�~�[
						{
							map[enemy[i].y - 1 + k][enemy[i].x - 1 + l] = TILE_ENEMY_DETECTION_RED;
						}
					}
				}
			}

			//���z�u
			for (int i = 0; i < treasureCou; i++)
			{
				map[treasure[i].y][treasure[i].x] = TILE_TREASURE;
			}

			//�^�C�����d�Ȃ������̏���
			if (map[player.y][player.x] == TILE_AIR)
			{
				color = TILE_AIR;
			}
			else if (map[player.y][player.x] == TILE_ENEMY)
			{
				color = TILE_ENEMY;
				createMap(tile, color, seed);
				gameover(&playerScore);
				savePlayerScore(&playerScore);
				break;
			}
			else if (map[player.y][player.x] == TILE_ENEMY_DETECTION_YELLOW)
			{
				color = TILE_ENEMY_DETECTION_YELLOW;
			}
			else if (map[player.y][player.x] == TILE_ENEMY_DETECTION_RED)
			{
				color = TILE_ENEMY_DETECTION_RED;
			}
			else if (map[player.y][player.x] == TILE_TREASURE)
			{
				color = TILE_AIR;
				playerScore.score++;

				if (playerScore.score % 2 == 0)
				{
					mapTileRandomSet(TILE_TREASURE, 4, 2);
				}

				if (playerScore.score % 5 == 0)
				{
					mapTileRandomSet(TILE_ENEMY, 1, 1);
				}

				if (playerScore.score % 10 == 0)
				{
					mapTileRandomSet(TILE_ENEMY, 1, 0);
				}
			}

			map[player.y][player.x] = TILE_PLAYER;//�v���C���[�z�u

			createMap(tile, color, seed);//�}�b�v�X�V

			if (playerScore.score != 0)
			{
				if (oldScore < playerScore.score)
				{
					//UI�󔠐F�ύX
					textattr(0x88);
					int per = 5;
					if (playerScore.score <= per * 1)textcolor(0x0);
					else if (playerScore.score <= per * 2)textcolor(0x7);
					else if (playerScore.score <= per * 3)textcolor(0xF);
					else if (playerScore.score <= per * 4)textcolor(0x2);
					else if (playerScore.score <= per * 5)textcolor(0xA);
					else if (playerScore.score <= per * 6)textcolor(0x3);
					else if (playerScore.score <= per * 7)textcolor(0x9);
					else if (playerScore.score <= per * 8)textcolor(0x5);
					else if (playerScore.score <= per * 9)textcolor(0xD);
					else if (playerScore.score <= per * 10)textcolor(0x1);
					else if (playerScore.score <= per * 11)textcolor(0x9);
					else if (playerScore.score <= per * 12)textcolor(0x4);
					else if (playerScore.score <= per * 13)textcolor(0xC);
					else if (playerScore.score <= per * 14)textcolor(0x6);
					else if (playerScore.score <= per * 15)textcolor(0xE);
					
					//UI�󔠕\��
					if (playerScore.score % per == 1)uiSetTreasure(4, 23, 1, 0);
					else if (playerScore.score % per == 2)uiSetTreasure(19, 23, 1, 0);
					else if (playerScore.score % per == 3)uiSetTreasure(4, 17, 1, 0);
					else if (playerScore.score % per == 4)uiSetTreasure(19, 17, 1, 0);
					else if (playerScore.score % per == 0)uiSetTreasure(12, 11, 1, 0);
				}
			}
		}
	}
}