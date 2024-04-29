//===================================================
//スコア(score.cpp)
//Auhor:渡邉 修	Date:2023.8.8
//===================================================
#include <fstream>
#include <iostream>
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "sound.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static int g_ScoreList[SCORE_MAX];
static int g_Score;
unsigned int g_ScoreTexture;
static float g_scale;
static float g_easingFactor;
static bool g_fanfare;
static int g_SE_up;
static bool g_upSeCheck;
static D3DXCOLOR g_color;

//クイックソートで使用
int cmpScore(const void* n1, const void* n2)
{
	int value1 = *((const int*)n1);
	int value2 = *((const int*)n2);

	if (value1 < value2)
	{
		return 1;
	}
	else if (value1 > value2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitScore()
{
	for (int i = 0; i < SCORE_MAX; i++)
	{
		g_ScoreList[i] = 0;
	}

	//ゲーム画面に移行する時だけ初期化
	switch (GetScene())
	{
	case SCENE_GAME:
		g_Score = SCORE_INIT_SCORE;
		break;

	case SCENE_RESULT:
		LoadScore();
		SaveScore();
		break;

	default:
		break;
	}

	//テクスチャ作成
	g_ScoreTexture = LoadTexture((char*)"data/TEXTURE/number.png");

	//効果音作成
	char se1[] =
	{
		"data\\SE\\up.wav"
	};
	g_SE_up = LoadSound(&se1[0]);

	g_scale = 0.0f;
	g_easingFactor = 1.0f;
	g_fanfare = false;
	g_upSeCheck = false;
	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateScore()
{
	//一定のスコアになるたびに実行
	if (g_Score % SCORE_FANFARE_SCORE == 0 && !g_fanfare && g_Score != 0)
	{
		g_upSeCheck = true;

		g_fanfare = true;
		g_scale = 1.0f; // スケールをリセット
	}

	//一定のスコアになるたびに一回だけ
	if (g_upSeCheck)
	{
		PlaySound(g_SE_up, 0);
		g_upSeCheck = false;
		g_color.g -= 0.06f;
		g_color.b -= 0.06f;
	}

	if (g_fanfare)
	{
		g_scale += SCORE_SCALE_UP_SPEED;

		if (g_scale > SCORE_SCALE_MAX)
		{
			g_scale = SCORE_SCALE_MAX;
			g_fanfare = false; // ファンファーレ終了

			// ここでファンファーレを再生する処理を追加
		}

		g_easingFactor = EaseInOut(g_scale); // イージング関数を適用
	}
	else
	{
		if (g_scale > 1.0f)
		{
			g_scale -= SCORE_SCALE_DOWN_SPEED;
			g_easingFactor = EaseInOut(g_scale); // イージング関数を適用
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawScore()
{
	switch (GetScene())
	{
	case SCENE_GAME:
		SetDrawScore(g_Score, SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 80, 88, g_easingFactor);
		break;

	case SCENE_RESULT:
		SetDrawScore(g_Score, SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 80, 88 * 1.5, 1.0f);
		for (int i = 0; i < 9; i++)
		{
			SetDrawRank(i + 1, SCREEN_WIDTH_HALF - 80 * 2.5f, SCREEN_HEIGHT * 0.2f + (((80 * 0.5f) + 20) * i), 77, 88 * 0.5f);
			SetDrawScore(g_ScoreList[i], SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.2f + (((80 * 0.5f) + 20) * i) , 80 * 0.5f, 88 * 0.5f, 1.0f);
		}
		break;

	default:
		break;
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitScore()
{

}

//---------------------------------------------------
//スコアを増やす
//---------------------------------------------------
void AddScore(int Score)
{
	g_Score += Score;
}

//---------------------------------------------------
//プレイヤー情報をファイルへ書き込む
//---------------------------------------------------
bool SaveScore()
{
	//ファイルオープン
	std::ofstream ofs("score.txt");

	//ファイルがオープンできなかったら
	if (ofs.fail())
	{
		return false;
	}
	
	//ソートして書き込む
	//リストの一番小さいスコアより大きければ書き込む
	SortScore();
	if (g_ScoreList[SCORE_MAX - 1] < g_Score)
	{
		g_ScoreList[SCORE_MAX - 1] = g_Score;
		SortScore();
	}

	//リストの書き込み
	for (int i = 0; i < SCORE_MAX; i++)
	{
		ofs << g_ScoreList[i] << std::endl;
	}

	//ファイルのクローズ
	ofs.close();

	return false;
}

//---------------------------------------------------
//プレイヤー情報をファイルから読み込む
//---------------------------------------------------
bool LoadScore()
{
	//ファイルオープン
	std::ifstream ifs("score.txt");

	//ファイルがオープンできなかったら
	if (ifs.fail())
	{
		return false;
	}

	//プレイヤーデータの書き込み
	for (int i = 0; i < SCORE_MAX; i++)
	{
		//プレイヤーデータを読み込み
		ifs >> g_ScoreList[i];
	}

	SortScore();

	//ファイルのクローズ
	ifs.close();

	return false;
}

//---------------------------------------------------
//クイックソート
//---------------------------------------------------
void SortScore()
{
	qsort(g_ScoreList, SCORE_MAX, sizeof(int), cmpScore);//クイックソート
}

//---------------------------------------------------
//スコア表示
//---------------------------------------------------
void SetDrawScore(int score, float posX, float posY, float sizeX, float sizeY, float scale)
{
	for (int i = 0; i < SCORE_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = score % 10;
		tx = (n % 10) * 0.1f;
		ty = (n / 10) * 1.0f;

		score /= 10;

		float sx, sy;
		sx = (posX - (sizeX * SCORE_FIGURE * 0.5f * scale)) + ((sizeX * 0.5f * scale) * (SCORE_FIGURE * 2 - (i + i + 1)));
		sy = posY;

		switch (GetScene())
		{
		case SCENE_GAME:
			DrawSpriteColorRotateScale(g_ScoreTexture, sx, sy, sizeX, sizeY,
				0.0f, 0.0f,
				tx, ty, 0.1f, 1.0f,
				g_color.r, g_color.g, g_color.b, g_color.a,
				0.0f,
				scale, scale);
			break;

		case SCENE_RESULT:
			DrawSpriteColorRotateScale(g_ScoreTexture, sx, sy, sizeX, sizeY,
				0.0f, 0.0f,
				tx, ty, 0.1f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				scale, scale);
			break;

		default:
			break;
		}

	}
}

//---------------------------------------------------
//順位表示
//---------------------------------------------------
void SetDrawRank(int score, float posX, float posY, float sizeX, float sizeY)
{
	for (int i = 0; i < RANK_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = score % 10;
		tx = (n % 10) * 0.1f;
		ty = (n / 10) * 1.0f;

		score /= 10;

		float sx, sy;
		sx = (posX - (sizeX * RANK_FIGURE * 0.5f)) + ((sizeX * 0.5f) * (RANK_FIGURE * 2 - (i + i + 1)));
		sy = posY;

		DrawSprite(g_ScoreTexture, sx, sy, sizeX, sizeY,
			tx, ty, 0.1f, 1.0f);
	}
}

//---------------------------------------------------
//スコアを取得
//---------------------------------------------------
int GetScore()
{
	return g_Score;
}

//---------------------------------------------------
//カーブを描く値を取得
//---------------------------------------------------
float EaseInOut(float t)
{
	// ベジェ曲線や他のイージング関数を使用して、時間 t の補間値を計算する
	return t * t + (1 - t) * (1 - t);
}

//---------------------------------------------------
//スコアを～にする
//---------------------------------------------------
void SetScore(int Score)
{
	g_Score = Score;
}