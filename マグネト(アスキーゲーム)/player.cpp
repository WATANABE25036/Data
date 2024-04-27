//===================================================
//�v���C���[����[player.cpp]
//Author:�n� �C	Date:2023.1.13
//===================================================
#include <time.h>
#include "player.h"
#include "bullet.h"
#include "drawing.h"
#include "gameControl.h"
#include "block.h"
#include "collision.h"
#include "explosion.h"
#include "parts.h"
#include "fade.h"
#include "main.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
PLAYER g_player; //����
bool g_shotTrigger;
bool g_releaseShot;
bool g_moveBlockTrigger;
bool g_xStackTrigger;
bool g_yStackTrigger;
bool g_ground;
float g_jumpCnt;
float g_jumpStartPos;
bool g_inportLeft;
bool g_inportRight;
bool g_inportJump;
bool g_inportSquat;
bool g_inportDeath;
bool g_jumpSeTrigger;
int g_standbyDeadCnt;
int g_jumpSe;
int g_deadSe;
int g_blockHitSe;
bool g_switchTrigger;
int g_randomControl;
int g_controller;
bool g_stageSetTrigger;
bool g_groundTrigger;
bool g_inportSwitch;
int g_changeSe;
int g_magnetCnt;
int g_petaSe;
bool g_petaSeTrigger;
bool g_ySpeedZeroTrigger;

//===================================================
//������
//===================================================
void InitializePlayer(void)
{
	//�l�̏�����
	g_player.xPos = 0.0f;
	g_player.yPos = 0.0f;
	g_player.oldXPos = 0.0f;
	g_player.oldYPos = 0.0f;
	g_player.xSpeed = 0.0f;
	g_player.ySpeed = 0.0f;
	g_player.chargCnt = 0;
	g_player.gravity = GRAVITY;
	g_player.dead = false;
	g_player.stageNum = FIRST_STAGE;
	g_player.goal = false;
	g_player.state = IDLE;
	g_player.motionCnt = 0;
	g_player.minusBlock = false;
	g_player.isUse = false;
	g_player.facing = RIGHT_FACING;
	g_player.upDownfacing = UP_FACING;
	g_player.respawn = true;
	g_player.inportSwitch = false;
	g_player.remain = REMAIN;
	g_player.plusBlock = false;

	g_moveBlockTrigger = false;
	g_shotTrigger = false;
	g_releaseShot = true;
	g_xStackTrigger = false;
	g_yStackTrigger = false;
	g_ground = false;
	g_jumpCnt = 0.0f;
	g_jumpStartPos = 0.0f;
	g_jumpSeTrigger = true;
	g_standbyDeadCnt = 0;
	srand((unsigned int)time(0));
	g_randomControl = 0;
	g_controller = 0;
	g_stageSetTrigger = false;
	g_inportLeft = false;
	g_inportRight = false;
	g_inportJump = false;
	g_inportSquat = false;
	g_inportSwitch = false;
	g_inportDeath = false;
	g_switchTrigger = false;
	g_groundTrigger = false;
	g_magnetCnt = 0;
	g_petaSeTrigger = false;
	g_ySpeedZeroTrigger = false;
	g_jumpSe = opensound("Data\\jump.mp3");
	g_deadSe = opensound("Data\\dead.mp3");
	g_blockHitSe = opensound("Data\\blockHit.mp3");
	g_changeSe = opensound("Data\\change.mp3");
	g_petaSe = opensound("Data\\peta.mp3");
}

//===================================================
//�X�V
//===================================================
void UpdatePlayer(void)
{
	if (g_player.isUse)
	{
		SCENE scene = GetScene();

		//����ł���Ƃ�
		if (g_player.dead)
		{
			if (g_standbyDeadCnt == 0)
			{
				if (scene != SCENE_TITLE || g_player.remain > 0)
				{
					g_player.remain--;
				}
				SetExplosion(g_player.xPos, g_player.yPos);
				SetExplosion(g_player.xPos + 1, g_player.yPos);
				SetExplosion(g_player.xPos - 1, g_player.yPos);
				SetExplosion(g_player.xPos, g_player.yPos + 1);
				SetExplosion(g_player.xPos, g_player.yPos - 1);
				SetPartsFever();
				playsound(g_deadSe, 0);
			}
			g_standbyDeadCnt++;

			//�c�@������Ε���
			if (g_standbyDeadCnt >= RESPAWN_TIMER && (g_player.remain >= 0 || scene == SCENE_TITLE))
			{
				g_player.dead = false;
				g_player.respawn = true;
				g_standbyDeadCnt = 0;
			}
			//�c�@���Ȃ��ꍇ
			if (g_player.remain < 0)
			{
				SetFadeOut();
				bool blacKOutTrigger = GetBlacKOutTrigger();
				if (blacKOutTrigger)
				{
					SetScene(SCENE_RESULT);
				}
			}
		}

		//�����Ă���Ƃ�
		if (!g_player.dead)
		{
			//�O�t���[���̏����i�[
			g_player.oldXPos = g_player.xPos;
			g_player.oldYPos = g_player.yPos;
			g_player.oldState = g_player.state;

			//�X�s�[�h���Z�b�g
			g_player.ySpeed = g_player.ySpeed * DEC_Y;

			//�d��
			if (g_ground)
			{
				g_player.gravity = 0;
			}
			else
			{
				g_player.gravity += GRAVITY;
				g_petaSeTrigger = false;
			}

			//�}�C�i�X�u���b�N�ɂ��������Ƃ����ׂ�Ȃ��悤�ɂ���
			if (g_player.minusBlock && !g_ySpeedZeroTrigger)
			{
				g_player.ySpeed = 0;
				g_ySpeedZeroTrigger = true;
			}
			else if(!g_player.minusBlock)
			{
				g_ySpeedZeroTrigger = false;
			}

			//�v���C���[����
			if (scene != SCENE_TITLE && !g_player.goal)
			{
				g_inportRight = false;
				g_inportLeft = false;
				g_inportJump = false;
				g_inportSquat = false;
				g_inportSwitch = false;
				g_inportDeath = false;

				//�����t(�L�[�{�[�h)
				if (inport(PJ1_XPOS) == -1)
				{
					if (inport(PK_D) || inport(PK_RIGHT))
					{
						g_inportRight = true;
					}

					if (inport(PK_A) || inport(PK_LEFT))
					{
						g_inportLeft = true;
					}

					if (inport(PK_W) || inport(PK_UP))
					{
						g_inportJump = true;
					}

					if (inport(PK_S) || inport(PK_DOWN))
					{
						g_inportSquat = true;
					}

					if (inport(PK_CTRL) || inport(PK_SP))
					{
						g_inportSwitch = true;
					}

					if (inport(PK_R))
					{
						g_inportDeath = true;
					}
				}

				//�����t(�R���g���[���[)
				else
				{
					g_controller = 0;
					g_controller = inport(PJ1_BTNS);
					if (inport(PK_D) || inport(PK_RIGHT) || inport(PJ1_XPOS) > 32767 + 10000)
					{
						g_inportRight = true;
					}

					if (inport(PK_A) || inport(PK_LEFT) || inport(PJ1_XPOS) < 32767 - 10000)
					{
						g_inportLeft = true;
					}

					if (inport(PK_W) || inport(PK_UP) || g_controller == 1 || g_controller == 2 || inport(PJ1_YPOS) < 32767 - 20000)
					{
						g_inportJump = true;
					}

					if (inport(PK_S) || inport(PK_DOWN) || inport(PJ1_YPOS) > 32767 + 20000)
					{
						g_inportSquat = true;
					}

					if (inport(PK_SP)|| inport(PK_CTRL) || g_controller == 32 || g_controller == 16)
					{
						g_inportSwitch = true;
					}

					if (inport(PK_R) || g_controller == 64)
					{
						g_inportDeath = true;
					}
				}
			}

			//��������
			if (scene == SCENE_TITLE)
			{
				//�ړ�
				if (!g_inportRight && !g_inportLeft)
				{
					g_randomControl = rand() % 50;

					//�E�ړ�
					if (g_randomControl == 0)
					{
						g_inportRight = true;
					}
					//���ړ�
					else if (g_randomControl == 1)
					{
						g_inportLeft = true;
					}
					//�X�g�b�v
					else
					{
						g_inportRight = false;
						g_inportLeft = false;
					}
				}
				else if (g_inportRight)
				{
					g_randomControl = rand() % 300;

					//�X�g�b�v
					if (g_randomControl == 0)
					{
						g_inportRight = false;
						g_inportLeft = false;
					}
					//���ړ�
					else if (g_randomControl == 1)
					{
						g_inportLeft = true;
					}
					//�E�ړ�
					else
					{
						g_inportRight = true;
					}
				}
				else if (g_inportLeft)
				{
					g_randomControl = rand() % 300;

					//�X�g�b�v
					if (g_randomControl == 0)
					{
						g_inportRight = false;
						g_inportLeft = false;
					}
					//�E�ړ�
					else if (g_randomControl == 1)
					{
						g_inportRight = true;
					}
					//���ړ�
					else
					{
						g_inportLeft = true;
					}
				}

				//���Ⴊ��
				g_randomControl = rand() % 500;
				if (!g_inportSquat)
				{
					if (g_randomControl == 100)
					{
						g_inportSquat = true;
					}
				}
				else if (g_inportSquat)
				{
					if (g_randomControl == 200)
					{
						g_inportSquat = false;
					}
				}

				//�W�����v
				g_randomControl = rand() % 50;
				if (!g_inportJump)
				{
					if (g_randomControl == 1)
					{
						g_inportJump = true;
					}
				}
				else if (g_inportJump)
				{
					if (g_randomControl == 0)
					{
						g_inportJump = false;
					}
					else
					{
						g_inportJump = true;
					}
				}

				//���͐؂�ւ�
				g_randomControl = rand() % 300;
				if (g_randomControl == 1)
				{
					g_player.inportSwitch = true;
				}

				if (g_randomControl == 0)
				{
					g_player.inportSwitch = false;
				}

				//����
				g_randomControl = rand() % 1500;
				if (g_randomControl == 0)
				{
					g_player.dead = true;
				}
			}


			//�ړ�
			if (g_inportRight)
			{
				g_player.xSpeed += ACC;
				if (g_player.xSpeed >= MAX_SPEED)
				{
					g_player.xSpeed = MAX_SPEED;
				}

				g_player.facing = RIGHT_FACING;
			}
			else if (g_inportLeft)
			{
				g_player.xSpeed -= ACC;
				if (g_player.xSpeed <= -MAX_SPEED)
				{
					g_player.xSpeed = -MAX_SPEED;
				}

				g_player.facing = LEFT_FACING;
			}
			else
			{
				g_player.xSpeed = g_player.xSpeed * DEC_X;//����
			}

			//�W�����v����
			if (!g_player.minusBlock)
			{
				//�L�[�������Ă���Ԓ���
				if (g_inportJump && g_jumpCnt < JUMP_MAX)
				{
					g_jumpCnt = g_jumpStartPos - g_player.yPos;

					g_player.ySpeed -= JUMP_POWER;

					if (g_jumpSeTrigger)
					{
						g_player.ySpeed -= 0.3;//�����������Ƃ���������x�W�����v����悤��
						playsound(g_jumpSe, 0);
						g_jumpSeTrigger = false;
					}
				}

				//�n�ʂɂ��ăL�[�𗣂�����
				if (!g_inportJump && g_ground)
				{
					g_jumpStartPos = g_player.yPos;
					g_jumpCnt = 0.0f;
					g_jumpSeTrigger = true;
				}

				//�W�����v���͍ăW�����v�s�� + �n�ʂ��Ȃ��Ȃ��Ă������̊ԂȂ�W�����v��
				if (!g_inportJump && (int)g_jumpStartPos > (int)g_player.yPos)
				{
					g_jumpCnt = JUMP_MAX;
				}
			}
			//�}�C�i�X�u���b�N�ɂ������Ă���Ƃ�
			else
			{
				if (g_inportJump)
				{
					g_player.ySpeed -= MINUS_JUMP_POWER;
					g_player.upDownfacing = UP_FACING;
				}

				if (g_inportSquat)
				{
					g_player.ySpeed += MINUS_JUMP_POWER;
					g_player.upDownfacing = DOWN_FACING;
				}
			}

			//�؂�ւ����쏈��
			if (g_inportSwitch && !g_switchTrigger)
			{
				playsound(g_changeSe, 0);
				if (g_player.inportSwitch == false)
				{
					g_player.inportSwitch = true;
				}
				else if (g_player.inportSwitch == true)
				{
					g_player.inportSwitch = false;
				}
				g_switchTrigger = true;
			}
			else if (!g_inportSwitch)
			{
				g_switchTrigger = false;
			}

			//����
			if (g_inportDeath)
			{
				g_player.dead = true;
			}

			//���͏���
			COLLISION collisionTopP = GetCollisionTopP();
			COLLISION collisionUnderP = GetCollisionUnderP();
			COLLISION collisionRightP = GetCollisionRightP();
			COLLISION collisionLeftP = GetCollisionLeftP();

			for (int i = 0; i < MAX_COLLISION_Y; i++)
			{
				for (int j = 0; j < MAX_COLLISION_X; j++)
				{
					//S��
					if (collisionTopP.magSTrigger[i][j] == true)
					{
						g_player.ySpeed -= 0.0005f;
					}

					if (collisionUnderP.magSTrigger[i][j] == true)
					{
						g_player.ySpeed += 0.0005f;
					}

					if (collisionRightP.magSTrigger[i][j] == true)
					{
						g_player.xSpeed -= 0.0005f;
					}

					if (collisionLeftP.magSTrigger[i][j] == true)
					{
						g_player.xSpeed += 0.0005f;
					}
					//N��
					if (collisionTopP.magNTrigger[i][j] == true)
					{
						g_player.ySpeed += 0.04f;
					}

					if (collisionUnderP.magNTrigger[i][j] == true)
					{
						g_player.ySpeed -= 0.04f;
					}

					if (collisionRightP.magNTrigger[i][j] == true)
					{
						g_player.xSpeed += 0.08f;
					}

					if (collisionLeftP.magNTrigger[i][j] == true)
					{
						g_player.xSpeed -= 0.08f;
					}

					if (collisionTopP.magNTrigger[i][j] || collisionUnderP.magNTrigger[i][j] || collisionRightP.magNTrigger[i][j] || collisionLeftP.magNTrigger[i][j])
					{
						g_player.gravity = 0;
						g_player.plusBlock = true;
					}
					else
					{
						g_magnetCnt++;
					}
				}
			}
			//�v���X���͂̉e�����󂯂Ă��Ȃ�������
			if (g_magnetCnt == MAX_COLLISION_Y * MAX_COLLISION_X)
			{
				g_player.plusBlock = false;
			}

			g_magnetCnt = 0;

			//����������
			BLOCK* pBlock = GetBlock();
			g_ground = false;
			g_player.minusBlock = false;

			for (int i = 0; i < MAX_BLOCK; i++)
			{
				if ((pBlock + i)->isUse)
				{
					for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
					{
						if ((pBlock + i)->isUseHeight[j])
						{
							for (int k = 0; k < MAX_BLOCK_WIDE; k++)
							{
								if ((pBlock + i)->isUseWide[k])
								{
									if (!(pBlock + i)->untouch)
									{
										//���̃u���b�N�����蔻��
										if ((int)(g_player.xPos + g_player.xSpeed) == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j])
										{
											g_player.xSpeed = 0.0f;
										}

										//-�u���b�N�ׂ̗̎�
										if (((int)(g_player.xPos + 1) == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j] ||
											(int)(g_player.xPos - 1) == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j] ||
											(int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos - 1) == (int)(pBlock + i)->yPos[j] ||
											(int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos + 1) == (int)(pBlock + i)->yPos[j]) &&
											((pBlock + i)->mode == BLOCK_MAGNET_MINUS))
										{
											g_player.minusBlock = true;
											g_player.gravity = 0.0f;
											if (!g_petaSeTrigger)
											{
												playsound(g_petaSe, 0);
												g_petaSeTrigger = true;
											}
										}
									}

									//�X�^�[�g�n�_�Ɉړ�(���X�|�[��)
									if ((pBlock + i)->mode == BLOCK_START && g_player.respawn)
									{
										g_inportLeft = false;
										g_inportRight = false;
										g_inportJump = false;
										g_inportSquat = false;
										g_inportSwitch = false;
										g_player.xSpeed = 0.0f;
										g_player.ySpeed = 0.0f;
										g_player.xPos = (pBlock + i)->xPos[k];
										g_player.yPos = (pBlock + i)->yPos[j];
										g_player.respawn = false;
									}

									//�S�[���ɐG�ꂽ��
									if ((pBlock + i)->mode == BLOCK_GOAL && (int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j] && !g_player.goal)
									{
										g_player.stageNum++;
										g_player.goal = true;

									}
								}
							}
						}
					}
				}
			}

			//�S�[�������Ƃ��̏���
			if (g_player.goal)
			{
				g_player.xSpeed = 0.0f;
				g_player.ySpeed = 0.0f;
				int stageNum = GetStageNum();
				g_stageSetTrigger = true;

				if (g_player.stageNum == stageNum && g_stageSetTrigger == true)
				{
					g_player.goal = false;
					g_player.respawn = true;
					g_stageSetTrigger = false;
				}
			}
			

			//�X�s�[�h�K�p
			g_player.ySpeed += g_player.gravity;
			g_player.xPos += g_player.xSpeed;
			g_player.yPos += g_player.ySpeed;

			//������
			g_moveBlockTrigger = false;
			g_xStackTrigger = false;
			g_yStackTrigger = false;

			for (int i = 0; i < MAX_BLOCK; i++)
			{
				if ((pBlock + i)->isUse && !(pBlock + i)->untouch)
				{
					for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
					{
						if ((pBlock + i)->isUseHeight[j])
						{
							for (int k = 0; k < MAX_BLOCK_WIDE; k++)
							{
								if ((pBlock + i)->isUseWide[k])
								{
									//���ɂ���u���b�N�Ɋђʂ�����
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j] && g_player.oldYPos <= (pBlock + i)->yPos[j])
									{
										g_player.yPos = g_player.oldYPos;
										//�u���b�N�Ɠ������W�ɂȂ�����
										if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos) + 1 != (int)(pBlock + i)->yPos[j])
										{
											g_player.yPos = (pBlock + i)->yPos[j] - 1;//�u���b�N�̂ЂƂ�̍��W�Ɉړ�
										}
									}

									//��ɂ���u���b�N�Ɋђʂ�����
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j] && g_player.oldYPos >= (pBlock + i)->yPos[j])
									{
										g_player.yPos = g_player.oldYPos;
										//�u���b�N�Ɠ������W�ɂȂ�����
										if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos) - 1 != (int)(pBlock + i)->yPos[j])
										{
											g_player.yPos = (pBlock + i)->yPos[j] + 1;//�u���b�N�̂ЂƂ��̍��W�Ɉړ�
										}

										g_jumpCnt = JUMP_MAX;

										if ((pBlock + i)->mode != BLOCK_MAGNET_MINUS)
										{
											g_player.ySpeed += 1.5f;
											playsound(g_blockHitSe, 0);
										}
									}

									//�c�Ɉړ�����u���b�N�ɏ�邽�߂̏���
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos) + 2 == (int)(pBlock + i)->yPos[j] &&
										(pBlock + i)->topBlock[j] && (pBlock + i)->yPos[j] > (pBlock + i)->oldYPos[j] && !inport(PK_W) && (pBlock + i)->mode != BLOCK_MAGNET_PLUS)
									{
										g_player.yPos++;
									}
									//�����u���b�N�̎��̏���
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && ((int)(g_player.yPos) + 1 == (int)(pBlock + i)->yPos[j]) && !g_moveBlockTrigger)
									{
										g_ground = true;
										g_player.ySpeed = 0;

										g_player.xPos += (pBlock + i)->xPos[k] - (pBlock + i)->oldXPos[k];
										g_player.yPos += (pBlock + i)->yPos[j] - (pBlock + i)->oldYPos[j];
										g_moveBlockTrigger = true;//�u���b�N�ɏ��Ɗ����Ă��܂��̂�j�~
									}

									//�オ-�u���b�N�̎��̏���
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos) - 1 == (int)(pBlock + i)->yPos[j] &&
										(pBlock + i)->mode == BLOCK_MAGNET_MINUS && !g_moveBlockTrigger)
									{
										g_ground = true;
										g_player.ySpeed = 0;
										g_player.xPos += (pBlock + i)->xPos[k] - (pBlock + i)->oldXPos[k];
										g_player.yPos += (pBlock + i)->yPos[j] - (pBlock + i)->oldYPos[j];
										g_moveBlockTrigger = true;//�u���b�N�ɏ��Ɗ����Ă��܂��̂�j�~
									}
								}
							}
						}
					}
				}
			}

			if (g_ground && !g_groundTrigger)
			{
				playsound(g_blockHitSe, 0);
				g_groundTrigger = true;
			}
			else if (!g_ground)
			{
				g_groundTrigger = false;
			}

			//��e����
			BULLET* pBullet = GetBullet();
			for (int i = 0; i < MAX_BULLET; i++)
			{
				if ((pBullet + i)->isUse && (int)(pBullet + i)->xPos == (int)g_player.xPos && (int)(pBullet + i)->yPos == (int)g_player.yPos)
				{
					g_player.dead = true;
				}
			}

			//���[�V����
			if (g_player.state != g_player.oldState)//���[�V�����̃J�E���g��0�ɂ���
			{
				g_player.motionCnt = 0;
			}

			//���~���[�V����
			if (((g_player.yPos > g_player.oldYPos) && !g_ground) || (g_inportSquat && g_ground))
			{
				g_player.state = FALL;
			}
			//�㏸���[�V����
			else if (g_player.yPos < g_player.oldYPos && !g_ground || g_player.plusBlock)
			{
				g_player.state = RISE;
			}
			//�������[�V����
			else if (g_player.xSpeed > 0.1f || g_player.xSpeed < -0.1f)
			{
				g_player.state = WALK;
				g_player.motionCnt++;

				if (g_player.motionCnt >= MOTIONFRAME_PLAYER_WALK * MOTIONFRAME_MAX_PLAYER_WALK)
				{
					g_player.motionCnt = 0;
				}
			}
			//�ҋ@���[�V����
			else
			{
				g_player.state = IDLE;
				g_player.motionCnt++;

				if (g_player.motionCnt >= MOTIONFRAME_PLAYER_IDLE * MOTIONFRAME_MAX_PLAYER_IDLE)
				{
					g_player.motionCnt = 0;
				}
			}

			//���͂ł������Ă���Ƃ�
			for (int i = 0; i < MAX_COLLISION_Y; i++)
			{
				for (int j = 0; j < MAX_COLLISION_X; j++)
				{
					if (collisionTopP.magSTrigger[i][j])
					{
						g_player.state = MAGNET_S_TOP;
					}

					else if (collisionUnderP.magSTrigger[i][j])
					{
						g_player.state = FALL;
					}

					else if (collisionLeftP.magSTrigger[i][j])
					{
						g_player.state = MAGNET_S_LEFT;
					}

					else if (collisionRightP.magSTrigger[i][j])
					{
						g_player.state = MAGNET_S_RIGHT;
					}
				}
			}

			//�A�s�[�����[�V����
			if (g_player.goal)
			{
				g_player.state = APPEAL;
				g_player.motionCnt++;

				if (g_player.motionCnt >= MOTIONFRAME_PLAYER_APPEAL * MOTIONFRAME_MAX_PLAYER_APPEAL)
				{
					g_player.motionCnt = 0;
				}
			}

			//�[����
			if (g_player.xPos <= DRAWING_WIDTHW_MIN)
			{
				g_player.xPos = DRAWING_WIDTHW_MIN;
			}

			if (g_player.xPos >= DRAWING_WIDTHW_MAX - 1)
			{
				g_player.xPos = DRAWING_WIDTHW_MAX - 1;
			}

			if (g_player.yPos <= DRAWING_HEIGHT_MIN - 5)
			{
				g_player.yPos = DRAWING_HEIGHT_MIN - 5;
			}

			if (g_player.yPos >= DRAWING_HEIGHT_MAX)
			{
				g_player.dead = true;
			}
		}
	}
}

//===================================================
//�`��
//===================================================
void DrawPlayer(void)
{

}

//===================================================
//�I������
//===================================================
void FinalizePlayer(void)
{
	closesound(g_jumpSe);
	closesound(g_deadSe);
	closesound(g_blockHitSe);
	closesound(g_changeSe);
	closesound(g_petaSe);
}

//===================================================
//�v���C���[�̃Z�b�g(�Z�b�^�[)
//===================================================
void SetPlayer(float px, float py)
{
	if (!g_player.isUse)
	{
		g_player.xPos = g_player.oldXPos = px;
		g_player.yPos = g_player.oldYPos = py;

		BLOCK* pBlock = GetBlock();

		for (int i = 0; i < MAX_BLOCK; i++)
		{
			if ((pBlock + i)->isUse)
			{
				for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
				{
					if ((pBlock + i)->isUseHeight[j])
					{
						for (int k = 0; k < MAX_BLOCK_WIDE; k++)
						{
							if ((pBlock + i)->isUseWide[k])
							{
								//�X�^�[�g�n�_�Ɉړ�
								if ((pBlock + i)->mode == BLOCK_START)
								{
									g_player.xPos = g_player.oldXPos = (pBlock + i)->xPos[k];
									g_player.yPos = g_player.oldYPos = (pBlock + i)->yPos[j];
									g_player.respawn = true;
								}
							}
						}
					}
				}
			}
		}

		g_player.isUse = true;
	}
}

//===================================================
//�v���C���[�擾
//===================================================
PLAYER GetPlayer(void)
{
	return g_player;
}