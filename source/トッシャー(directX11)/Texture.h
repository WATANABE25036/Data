/*==============================================================================

   �e�N�X�`���̓ǂݍ��� [Texture.h]
														 Author : �w�Z�z�z
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "Renderer.h"

int LoadTexture(char* fileName);
void UninitTexture(void);

ID3D11ShaderResourceView** GetTexture(int index);
