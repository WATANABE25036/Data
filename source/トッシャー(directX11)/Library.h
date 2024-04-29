#pragma once
#include <d3dx9.h>
#include <string>
#include <random>

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int Sign(float value);
int Sign(int value);
int Nat(float value);
int Nat(int value);
float Round(float num, int digit);
double PointDirection(double x1, double y1, double x2, double y2);
double PointDirectionRadian(double x1, double y1, double x2, double y2);
D3DXVECTOR2 CalculateVector(double length, double angleRadians);
D3DXVECTOR3 GlobalToLocal(D3DXVECTOR3 starting, D3DXVECTOR3 subject);
D3DXVECTOR2 SetAnimation(int basePattern = 0, int animeCount = 0, int allWidthPattern = 1, int allHeightPattern = 1, int widthPattern = 1, bool reverse = false);
D3DXVECTOR2 GetUV(int index, int widthPattern, int heightPattern);
int Counter(int count, int max);
int GetRandomInt(int min, int max);
float GetRandomFloat(float min, float max);
int RandomPercent(float percent1, float percent2 = 0, float percent3 = 0, float percent4 = 0, float percent5 = 0, float percent6 = 0, float percent7 = 0, float percent8 = 0, float percent9 = 0, float percent10 = 0);

