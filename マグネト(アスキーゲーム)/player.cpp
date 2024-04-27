//===================================================
//プレイヤー制御[player.cpp]
//Author:渡邉 修	Date:2023.1.13
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
//グローバル変数
//===================================================
PLAYER g_player; //実体
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
//初期化
//===================================================
void InitializePlayer(void)
{
	//値の初期化
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
//更新
//===================================================
void UpdatePlayer(void)
{
	if (g_player.isUse)
	{
		SCENE scene = GetScene();

		//死んでいるとき
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

			//残機があれば復活
			if (g_standbyDeadCnt >= RESPAWN_TIMER && (g_player.remain >= 0 || scene == SCENE_TITLE))
			{
				g_player.dead = false;
				g_player.respawn = true;
				g_standbyDeadCnt = 0;
			}
			//残機がない場合
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

		//生きているとき
		if (!g_player.dead)
		{
			//前フレームの情報を格納
			g_player.oldXPos = g_player.xPos;
			g_player.oldYPos = g_player.yPos;
			g_player.oldState = g_player.state;

			//スピードリセット
			g_player.ySpeed = g_player.ySpeed * DEC_Y;

			//重力
			if (g_ground)
			{
				g_player.gravity = 0;
			}
			else
			{
				g_player.gravity += GRAVITY;
				g_petaSeTrigger = false;
			}

			//マイナスブロックにくっついたときすべらないようにする
			if (g_player.minusBlock && !g_ySpeedZeroTrigger)
			{
				g_player.ySpeed = 0;
				g_ySpeedZeroTrigger = true;
			}
			else if(!g_player.minusBlock)
			{
				g_ySpeedZeroTrigger = false;
			}

			//プレイヤー操作
			if (scene != SCENE_TITLE && !g_player.goal)
			{
				g_inportRight = false;
				g_inportLeft = false;
				g_inportJump = false;
				g_inportSquat = false;
				g_inportSwitch = false;
				g_inportDeath = false;

				//操作受付(キーボード)
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

				//操作受付(コントローラー)
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

			//自動操作
			if (scene == SCENE_TITLE)
			{
				//移動
				if (!g_inportRight && !g_inportLeft)
				{
					g_randomControl = rand() % 50;

					//右移動
					if (g_randomControl == 0)
					{
						g_inportRight = true;
					}
					//左移動
					else if (g_randomControl == 1)
					{
						g_inportLeft = true;
					}
					//ストップ
					else
					{
						g_inportRight = false;
						g_inportLeft = false;
					}
				}
				else if (g_inportRight)
				{
					g_randomControl = rand() % 300;

					//ストップ
					if (g_randomControl == 0)
					{
						g_inportRight = false;
						g_inportLeft = false;
					}
					//左移動
					else if (g_randomControl == 1)
					{
						g_inportLeft = true;
					}
					//右移動
					else
					{
						g_inportRight = true;
					}
				}
				else if (g_inportLeft)
				{
					g_randomControl = rand() % 300;

					//ストップ
					if (g_randomControl == 0)
					{
						g_inportRight = false;
						g_inportLeft = false;
					}
					//右移動
					else if (g_randomControl == 1)
					{
						g_inportRight = true;
					}
					//左移動
					else
					{
						g_inportLeft = true;
					}
				}

				//しゃがみ
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

				//ジャンプ
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

				//磁力切り替え
				g_randomControl = rand() % 300;
				if (g_randomControl == 1)
				{
					g_player.inportSwitch = true;
				}

				if (g_randomControl == 0)
				{
					g_player.inportSwitch = false;
				}

				//自滅
				g_randomControl = rand() % 1500;
				if (g_randomControl == 0)
				{
					g_player.dead = true;
				}
			}


			//移動
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
				g_player.xSpeed = g_player.xSpeed * DEC_X;//減速
			}

			//ジャンプ処理
			if (!g_player.minusBlock)
			{
				//キーを押している間跳ぶ
				if (g_inportJump && g_jumpCnt < JUMP_MAX)
				{
					g_jumpCnt = g_jumpStartPos - g_player.yPos;

					g_player.ySpeed -= JUMP_POWER;

					if (g_jumpSeTrigger)
					{
						g_player.ySpeed -= 0.3;//少し押したときもある程度ジャンプするように
						playsound(g_jumpSe, 0);
						g_jumpSeTrigger = false;
					}
				}

				//地面についてキーを離したら
				if (!g_inportJump && g_ground)
				{
					g_jumpStartPos = g_player.yPos;
					g_jumpCnt = 0.0f;
					g_jumpSeTrigger = true;
				}

				//ジャンプ中は再ジャンプ不可 + 地面がなくなっても多少の間ならジャンプ可
				if (!g_inportJump && (int)g_jumpStartPos > (int)g_player.yPos)
				{
					g_jumpCnt = JUMP_MAX;
				}
			}
			//マイナスブロックにくっついているとき
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

			//切り替え操作処理
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

			//自滅
			if (g_inportDeath)
			{
				g_player.dead = true;
			}

			//磁力処理
			COLLISION collisionTopP = GetCollisionTopP();
			COLLISION collisionUnderP = GetCollisionUnderP();
			COLLISION collisionRightP = GetCollisionRightP();
			COLLISION collisionLeftP = GetCollisionLeftP();

			for (int i = 0; i < MAX_COLLISION_Y; i++)
			{
				for (int j = 0; j < MAX_COLLISION_X; j++)
				{
					//S極
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
					//N極
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
			//プラス磁力の影響を受けていなかったら
			if (g_magnetCnt == MAX_COLLISION_Y * MAX_COLLISION_X)
			{
				g_player.plusBlock = false;
			}

			g_magnetCnt = 0;

			//動く床処理
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
										//横のブロック当たり判定
										if ((int)(g_player.xPos + g_player.xSpeed) == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j])
										{
											g_player.xSpeed = 0.0f;
										}

										//-ブロックの隣の時
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

									//スタート地点に移動(リスポーン)
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

									//ゴールに触れたら
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

			//ゴールしたときの処理
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
			

			//スピード適用
			g_player.ySpeed += g_player.gravity;
			g_player.xPos += g_player.xSpeed;
			g_player.yPos += g_player.ySpeed;

			//床処理
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
									//下にあるブロックに貫通したら
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j] && g_player.oldYPos <= (pBlock + i)->yPos[j])
									{
										g_player.yPos = g_player.oldYPos;
										//ブロックと同じ座標になったら
										if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos) + 1 != (int)(pBlock + i)->yPos[j])
										{
											g_player.yPos = (pBlock + i)->yPos[j] - 1;//ブロックのひとつ上の座標に移動
										}
									}

									//上にあるブロックに貫通したら
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)g_player.yPos == (int)(pBlock + i)->yPos[j] && g_player.oldYPos >= (pBlock + i)->yPos[j])
									{
										g_player.yPos = g_player.oldYPos;
										//ブロックと同じ座標になったら
										if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos) - 1 != (int)(pBlock + i)->yPos[j])
										{
											g_player.yPos = (pBlock + i)->yPos[j] + 1;//ブロックのひとつ下の座標に移動
										}

										g_jumpCnt = JUMP_MAX;

										if ((pBlock + i)->mode != BLOCK_MAGNET_MINUS)
										{
											g_player.ySpeed += 1.5f;
											playsound(g_blockHitSe, 0);
										}
									}

									//縦に移動するブロックに乗るための処理
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos) + 2 == (int)(pBlock + i)->yPos[j] &&
										(pBlock + i)->topBlock[j] && (pBlock + i)->yPos[j] > (pBlock + i)->oldYPos[j] && !inport(PK_W) && (pBlock + i)->mode != BLOCK_MAGNET_PLUS)
									{
										g_player.yPos++;
									}
									//下がブロックの時の処理
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && ((int)(g_player.yPos) + 1 == (int)(pBlock + i)->yPos[j]) && !g_moveBlockTrigger)
									{
										g_ground = true;
										g_player.ySpeed = 0;

										g_player.xPos += (pBlock + i)->xPos[k] - (pBlock + i)->oldXPos[k];
										g_player.yPos += (pBlock + i)->yPos[j] - (pBlock + i)->oldYPos[j];
										g_moveBlockTrigger = true;//ブロックに乗ると滑ってしまうのを阻止
									}

									//上が-ブロックの時の処理
									if ((int)g_player.xPos == (int)(pBlock + i)->xPos[k] && (int)(g_player.yPos) - 1 == (int)(pBlock + i)->yPos[j] &&
										(pBlock + i)->mode == BLOCK_MAGNET_MINUS && !g_moveBlockTrigger)
									{
										g_ground = true;
										g_player.ySpeed = 0;
										g_player.xPos += (pBlock + i)->xPos[k] - (pBlock + i)->oldXPos[k];
										g_player.yPos += (pBlock + i)->yPos[j] - (pBlock + i)->oldYPos[j];
										g_moveBlockTrigger = true;//ブロックに乗ると滑ってしまうのを阻止
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

			//被弾処理
			BULLET* pBullet = GetBullet();
			for (int i = 0; i < MAX_BULLET; i++)
			{
				if ((pBullet + i)->isUse && (int)(pBullet + i)->xPos == (int)g_player.xPos && (int)(pBullet + i)->yPos == (int)g_player.yPos)
				{
					g_player.dead = true;
				}
			}

			//モーション
			if (g_player.state != g_player.oldState)//モーションのカウントを0にする
			{
				g_player.motionCnt = 0;
			}

			//下降モーション
			if (((g_player.yPos > g_player.oldYPos) && !g_ground) || (g_inportSquat && g_ground))
			{
				g_player.state = FALL;
			}
			//上昇モーション
			else if (g_player.yPos < g_player.oldYPos && !g_ground || g_player.plusBlock)
			{
				g_player.state = RISE;
			}
			//歩きモーション
			else if (g_player.xSpeed > 0.1f || g_player.xSpeed < -0.1f)
			{
				g_player.state = WALK;
				g_player.motionCnt++;

				if (g_player.motionCnt >= MOTIONFRAME_PLAYER_WALK * MOTIONFRAME_MAX_PLAYER_WALK)
				{
					g_player.motionCnt = 0;
				}
			}
			//待機モーション
			else
			{
				g_player.state = IDLE;
				g_player.motionCnt++;

				if (g_player.motionCnt >= MOTIONFRAME_PLAYER_IDLE * MOTIONFRAME_MAX_PLAYER_IDLE)
				{
					g_player.motionCnt = 0;
				}
			}

			//磁力でくっついているとき
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

			//アピールモーション
			if (g_player.goal)
			{
				g_player.state = APPEAL;
				g_player.motionCnt++;

				if (g_player.motionCnt >= MOTIONFRAME_PLAYER_APPEAL * MOTIONFRAME_MAX_PLAYER_APPEAL)
				{
					g_player.motionCnt = 0;
				}
			}

			//端処理
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
//描画
//===================================================
void DrawPlayer(void)
{

}

//===================================================
//終了処理
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
//プレイヤーのセット(セッター)
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
								//スタート地点に移動
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
//プレイヤー取得
//===================================================
PLAYER GetPlayer(void)
{
	return g_player;
}