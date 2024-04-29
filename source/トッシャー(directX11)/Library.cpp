/*==============================================================================

   関数集 [Library.cpp]
														 Author : 渡邉 修
														 Date   : 2024/01/18
--------------------------------------------------------------------------------

==============================================================================*/
#include "Library.h"

//-----------------------------------------------------------------------------
// 0なら0、正の符号なら1、不の符号なら-1を返す
//-----------------------------------------------------------------------------
int Sign(int value)
{
	if (value == 0)return 0;
	else if (value > 0)return 1;
	else return -1;
}

int Sign(float value)
{
	if (value == 0)return 0;
	else if (value > 0)return 1;
	else return -1;
}

//-----------------------------------------------------------------------------
// 自然数を返す
//-----------------------------------------------------------------------------
int Nat(int value)
{
	if (value < 0)return 0;

	return (int)value;
}

int Nat(float value)
{
	if (value < 0)return 0;

	return (int)value;
}

//-----------------------------------------------------------------------------
// 小数の切り捨て (digit = 10, 100, 1000...)
//-----------------------------------------------------------------------------
float Round(float num, int digit)
{
	int value = int(num * digit);
	num = float(value) / digit;
	return num;
}

//-----------------------------------------------------------------------------
// 座標から角度を計算する関数 度
//-----------------------------------------------------------------------------
double PointDirection(double x1, double y1, double x2, double y2)
{
	// ラジアン単位の角度を計算
	double angle = std::atan2(y2 - y1, x2 - x1);

	// ラジアンを度に変換
	double degrees = angle * 180.0f / 3.14159f;

	// 0から360度の範囲に調整
	if (degrees < 0)
	{
		degrees += 360.0;
	}

	return degrees;
}

//-----------------------------------------------------------------------------
// 座標から角度を計算する関数 ラジアン
//-----------------------------------------------------------------------------
double PointDirectionRadian(double x1, double y1, double x2, double y2)
{
	// ラジアン単位の角度を計算
	double angle = std::atan2(y2 - y1, x2 - x1);

	return angle;
}

//-----------------------------------------------------------------------------
// 対象までのxとyの距離を返す
//-----------------------------------------------------------------------------
D3DXVECTOR2 PointDistance(float x1, float y1, float x2, float y2)
{
	D3DXVECTOR2 distance;
	distance.x = x2 - x1;
	distance.y = y2 - y1;

	return distance;
}

//-----------------------------------------------------------------------------
// xとyのスカラー(向きを持たない力の大きさ)
//-----------------------------------------------------------------------------
float PointScalar(float x1, float y1, float x2, float y2)
{
	D3DXVECTOR2 distance;
	distance.x = x2 - x1;
	distance.y = y2 - y1;

	// ピタゴラスの定理を使って2点間の距離を計算
	float scalar = sqrt(distance.x * distance.x + distance.y * distance.y);

	return scalar;
}

//-----------------------------------------------------------------------------
// 角度と長さからベクトル (x, y) を計算
//-----------------------------------------------------------------------------
D3DXVECTOR2 CalculateVector(double length, double angleRadians)
{
	D3DXVECTOR2 result;

	result.x = float(cos(angleRadians));
	result.y = float(sin(angleRadians));

	D3DXVec2Normalize(&result, &result);
	result *= length;//目的のスピードにするためにスピードを乗算する

	return result;
}

//-----------------------------------------------------------------------------
// グローバル座標をローカル座標にする
//-----------------------------------------------------------------------------
D3DXVECTOR3 GlobalToLocal(D3DXVECTOR3 starting, D3DXVECTOR3 subject)
{
	D3DXVECTOR3 pos = subject - starting;
	return pos;
}

////-----------------------------------------------------------------------------
//// グローバルで見た角度を求める
////-----------------------------------------------------------------------------
//float LocalAngle(D3DXVECTOR3 startingPos, D3DXVECTOR3 startingDir, D3DXVECTOR3 subject)
//{
//	// プレイヤーの位置から相手の位置へのベクトルを求める
//	D3DXVECTOR3 enemyVector = subject - startingPos;
//
//	// プレイヤーの方向ベクトルと相手の位置ベクトルの間の角度を計算する
//	float angle = atan2f(enemyVector.z, enemyVector.x) - atan2f(startingDir.z, startingDir.x);
//	if (angle < 0.0f)
//	{
//		angle += 2.0f * D3DX_PI;
//	}
//
//	// 角度を度数法に変換する
//	angle = D3DXToDegree(angle);
//	return angle;
//}

//-----------------------------------------------------------------------------
// アニメーションを設定する
// [引数] basePattern: 左上を0とした開始フレーム, 
//		  widthPattern: 横のアニメパターン数, 
//-----------------------------------------------------------------------------
D3DXVECTOR2 SetAnimation(int basePattern, int animeCount, int allWidthPattern, int allHeightPattern, int widthPattern, bool reverse)
{
	D3DXVECTOR2 uv;
	//U      W											N番目の % 横のパターン数
	uv.x = (1.0f / allWidthPattern) * ((animeCount + basePattern) % widthPattern);	//横の座標計算
	//V     H											N番目の / 横の全パターン
	uv.y = (1.0f / allHeightPattern) * ((animeCount + basePattern) / allWidthPattern); //縦の座標計算

	//テクスチャ反転
	if (reverse)
	{
		uv.x = 1 + (1 - uv.x) - Round(1.0f / allWidthPattern, 100);//左端なので-0.25
	}

	return uv;
}

//-----------------------------------------------------------------------------
// UV座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//-----------------------------------------------------------------------------
D3DXVECTOR2 GetUV(int index, int widthPattern, int heightPattern)
{
	float U = (index % widthPattern) * (1.0f / widthPattern);
	float V = (index / widthPattern) * (1.0f / heightPattern);
	D3DXVECTOR2 UV = D3DXVECTOR2(U, V);
	return UV;
}

//-----------------------------------------------------------------------------
// 第一引数が第二引数になったら0にする
//-----------------------------------------------------------------------------
int Counter(int count, int max)
{
	count++;

	if (count >= max)
	{
		count = 0;
	}
	return count;
}

//-----------------------------------------------------------------------------
// ランダム
//-----------------------------------------------------------------------------
int GetRandomInt(int min, int max)
{
	std::random_device rd;
	std::uniform_int_distribution<> dist(min, max);
	return dist(rd);
}

float GetRandomFloat(float min, float max)
{
	std::random_device rd;
	std::uniform_real_distribution<> dist(min, max);
	return float(dist(rd));
}

//-----------------------------------------------------------------------------
// ％で抽選します
// 引数に何%かを入れ第一引数が選ばれれば1を第二引数なら2を返します
// どれも選ばれなければ0を返します
//-----------------------------------------------------------------------------
int RandomPercent(float percent1, float percent2, float percent3, float percent4, float percent5, float percent6, float percent7, float percent8, float percent9, float percent10)
{
	float percent[10] = { percent1 ,percent2 ,percent3 ,percent4 ,percent5 ,percent6 ,percent7 ,percent8 ,percent9 ,percent10 };
	float ran = GetRandomFloat(1.0f, 100.0f);

	for (int i = 0; i < 10; i++)
	{
		if (ran < percent[i])return i + 1;

		ran -= int(percent[i]);
	}

	return 0;
}