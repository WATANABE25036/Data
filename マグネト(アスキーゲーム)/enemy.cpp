//===================================================
//敵制御[enemy.cpp]
//Author:渡邉 修	Date:2023.1.17
//===================================================
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "drawing.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//グローバル変数
//===================================================
ENEMY g_enemy[MAX_ENEMY];	//実体(プーリング)
int g_timeCntEnemy;				//時間カウンター

//===================================================
//初期化
//===================================================
void InitializeEnemy(void)
{
	//値の初期化
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_enemy[i].xPos = g_enemy[i].oldXPos = 0.0f;
		g_enemy[i].yPos = g_enemy[i].oldYPos = 0.0f;
		g_enemy[i].xSpeed = 0.0f;
		g_enemy[i].ySpeed = 0.0f;
		g_enemy[i].moveTime = 0;
		g_enemy[i].isUse = false;
	}

	g_timeCntEnemy = 0;

	//SetEnemy(25.0f, 3.0f);
	//SetEnemy(25.0f, 4.0f);
	//SetEnemy(25.0f, 5.0f);
	//SetEnemy(25.0f, 6.0f);
	//SetEnemy(25.0f, 7.0f);
	//SetEnemy(25.0f, 8.0f);
	//SetEnemy(25.0f, 9.0f);
	//SetEnemy(25.0f, 10.0f);
	//SetEnemy(25.0f, 11.0f);

	//SetEnemy(28.0f, 3.0f);
	//SetEnemy(28.0f, 4.0f);
	//SetEnemy(28.0f, 5.0f);
	//SetEnemy(28.0f, 6.0f);
	//SetEnemy(28.0f, 7.0f);
	//SetEnemy(28.0f, 8.0f);
	//SetEnemy(28.0f, 9.0f);
	//SetEnemy(28.0f, 10.0f);
	//SetEnemy(28.0f, 11.0f);

	//SetEnemy(31.0f, 3.0f);
	//SetEnemy(31.0f, 4.0f);
	//SetEnemy(31.0f, 5.0f);
	//SetEnemy(31.0f, 6.0f);
	//SetEnemy(31.0f, 7.0f);
	//SetEnemy(31.0f, 8.0f);
	//SetEnemy(31.0f, 9.0f);
	//SetEnemy(31.0f, 10.0f);
	//SetEnemy(31.0f, 11.0f);

	//SetEnemy(34.0f, 3.0f);
	//SetEnemy(34.0f, 4.0f);
	//SetEnemy(34.0f, 5.0f);
	//SetEnemy(34.0f, 6.0f);
	//SetEnemy(34.0f, 7.0f);
	//SetEnemy(34.0f, 8.0f);
	//SetEnemy(34.0f, 9.0f);
	//SetEnemy(34.0f, 10.0f);
	//SetEnemy(34.0f, 11.0f);

	//SetEnemy(37.0f, 3.0f);
	//SetEnemy(37.0f, 4.0f);
	//SetEnemy(37.0f, 5.0f);
	//SetEnemy(37.0f, 6.0f);
	//SetEnemy(37.0f, 7.0f);
	//SetEnemy(37.0f, 8.0f);
	//SetEnemy(37.0f, 9.0f);
	//SetEnemy(37.0f, 10.0f);
	//SetEnemy(37.0f, 11.0f);

	//SetEnemy(40.0f, 3.0f);
	//SetEnemy(40.0f, 4.0f);
	//SetEnemy(40.0f, 5.0f);
	//SetEnemy(40.0f, 6.0f);
	//SetEnemy(40.0f, 7.0f);
	//SetEnemy(40.0f, 8.0f);
	//SetEnemy(40.0f, 9.0f);
	//SetEnemy(40.0f, 10.0f);
	//SetEnemy(40.0f, 11.0f);
}

//===================================================
//更新
//===================================================
void UpdateEnemy(void)
{
	//時間経過で敵をセット
	g_timeCntEnemy++;
	
	//switch (g_timeCntEnemy)
	//{
	//case 2:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 3:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 4:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 5:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 6:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 7:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 300:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//default:
	//	break;
	//}

	//敵の動作
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_enemy[i].isUse)
		{
			//前フレームの座標を格納
			g_enemy[i].oldXPos = g_enemy[i].xPos;
			g_enemy[i].oldYPos = g_enemy[i].yPos;

			g_enemy[i].xSpeed = cosf(g_enemy[i].moveTime * 0.5f) * 2.0f;
			//g_enemy[i].xSpeed = sinf(g_enemy[i].moveTime * 0.1f) * 0.1f;
			g_enemy[i].moveTime++;

			//移動
			g_enemy[i].xPos += g_enemy[i].xSpeed;
			g_enemy[i].yPos += g_enemy[i].ySpeed;
			//外面端で移動方向反転
			if (g_enemy[i].yPos > DRAWING_HEIGHT_MAX - 2)
			{
				g_enemy[i].ySpeed = -g_enemy[i].ySpeed;
			}

			if (g_enemy[i].yPos < 1 + 1)
			{
				g_enemy[i].ySpeed = -g_enemy[i].ySpeed;
			}

			//画面外に出たら消す
			if (g_enemy[i].xPos <= DRAWING_WIDTHW_MIN || g_enemy[i].xPos >= DRAWING_WIDTHW_MAX||
				g_enemy[i].yPos <= DRAWING_HEIGHT_MIN || g_enemy[i].yPos >= DRAWING_HEIGHT_MAX)
			{
				g_enemy[i].isUse = false;
				continue;//今回のループをスキップする
			}

			//弾の当たり判定処理
			BULLET* pBullet = GetBullet(); //弾の先頭アドレスを取得

			//弾のループカウンター → j
			for (int j = 0; j < MAX_BULLET; j++)
			{
				if ((pBullet + j)->isUse)
				{
					//弾と敵がint型として前の座標～今の座標に重なったら
					if (g_enemy[i].xPos <= (pBullet + j)->xPos && g_enemy[i].xPos >= (pBullet + j)->oldXPos &&
						(int)g_enemy[i].yPos == (int)(pBullet + j)->yPos ||
						g_enemy[i].xPos >= (pBullet + j)->xPos && g_enemy[i].xPos <= (pBullet + j)->oldXPos &&
						(int)g_enemy[i].yPos == (int)(pBullet + j)->yPos)
					{
						//どちらも消す
						//敵消す
						g_enemy[i].isUse = false;

						//弾消す
						(pBullet + j)->isUse = false;

						//爆発アニメーションのセット
						SetExplosion(g_enemy[i].xPos, g_enemy[i].yPos);

						//スコアを加算
						AddScore(50000);
					}
				}
			}
		}
		else
		{
			//使い終わったら初期化
			g_enemy[i].xPos = g_enemy[i].oldXPos = 0.0f;
			g_enemy[i].yPos = g_enemy[i].oldYPos = 0.0f;
			g_enemy[i].xSpeed = 0.0f;
			g_enemy[i].ySpeed = 0.0f;
		}
	}
}

//===================================================
//描画
//===================================================
void DrawEnemy(void)
{

}

//===================================================
//終了処理
//===================================================
void FinalizeEnemy(void)
{

}

//===================================================
//敵のセット(セッター)
//===================================================
void SetEnemy(float px, float py, float sx, float sy)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (!g_enemy[i].isUse)
		{
			g_enemy[i].xPos = g_enemy[i].oldXPos = px;
			g_enemy[i].yPos = g_enemy[i].oldYPos = py;
			g_enemy[i].xSpeed = sx;
			g_enemy[i].ySpeed = sy;
			g_enemy[i].isUse = true;

			break;
		}
	}
}

//===================================================
//エネミーアドレス取得
//===================================================
ENEMY* GetEnemy(void)
{
	return g_enemy;
}