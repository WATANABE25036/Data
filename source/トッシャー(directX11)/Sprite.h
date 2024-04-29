/*==============================================================================

   スプライト処理 [Sprite.h]
														 Author : 学校配布
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitSprite();
void UninitSprite();

void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);
void DrawSpriteColorRotate(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR Color, float Rot);


