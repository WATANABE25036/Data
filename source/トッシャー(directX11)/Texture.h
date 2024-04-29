/*==============================================================================

   テクスチャの読み込み [Texture.h]
														 Author : 学校配布
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "Renderer.h"

int LoadTexture(char* fileName);
void UninitTexture(void);

ID3D11ShaderResourceView** GetTexture(int index);
