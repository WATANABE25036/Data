/*==============================================================================

   ���f���̏��� [Model.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Main.h"
#include "Renderer.h"

//*********************************************************
// �\����
//*********************************************************

// �}�e���A���\����
struct DX11_MODEL_MATERIAL
{
	MATERIAL					Material;
	ID3D11ShaderResourceView	*Texture = nullptr;
};

// �`��T�u�Z�b�g�\����
struct DX11_SUBSET
{
	unsigned short	StartIndex = 0;
	unsigned short	IndexNum = 0;
	DX11_MODEL_MATERIAL	Material;
};

// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
};

// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	MODEL_MATERIAL	Material;
};

// ���f���\����
struct MODEL
{
	VERTEX_3D* VertexArray;
	unsigned short	VertexNum;
	unsigned short* IndexArray;
	unsigned short	IndexNum;
	SUBSET* SubsetArray;		//�������f���̏����i�[����z��
	unsigned short	SubsetNum;	//SubsetArray�̗v�f��
};



struct DX11_MODEL
{
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;

	DX11_SUBSET* SubsetArray = nullptr;	//�������f���̏����i�[����z��
	unsigned short	SubsetNum = 0;		//SubsetArray�̗v�f��

	MODEL Model;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void LoadModel( char *FileName, DX11_MODEL *model, std::string tag);
void UnloadModel( DX11_MODEL *model );
void DrawModel( DX11_MODEL &model );

bool DoubleCheck(const std::string tag, DX11_MODEL& Model);
