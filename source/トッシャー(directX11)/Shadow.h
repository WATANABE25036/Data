/*==============================================================================

   �e���� [Shadow.h]
														 Author : �n� �C
														 Date   : 2023/11/09
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Main.h"
#include "Renderer.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, float size);
void ReleaseShadow(int index);
void SetPositionShadow(int index, D3DXVECTOR3 pos);
void SetColorShadow(int index, D3DXCOLOR col);
