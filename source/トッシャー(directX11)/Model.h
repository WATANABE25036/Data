/*==============================================================================

   モデルの処理 [Model.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Main.h"
#include "Renderer.h"

//*********************************************************
// 構造体
//*********************************************************

// マテリアル構造体
struct DX11_MODEL_MATERIAL
{
	MATERIAL					Material;
	ID3D11ShaderResourceView	*Texture = nullptr;
};

// 描画サブセット構造体
struct DX11_SUBSET
{
	unsigned short	StartIndex = 0;
	unsigned short	IndexNum = 0;
	DX11_MODEL_MATERIAL	Material;
};

// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
};

// 描画サブセット構造体
struct SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	MODEL_MATERIAL	Material;
};

// モデル構造体
struct MODEL
{
	VERTEX_3D* VertexArray;
	unsigned short	VertexNum;
	unsigned short* IndexArray;
	unsigned short	IndexNum;
	SUBSET* SubsetArray;		//部分モデルの情報を格納する配列
	unsigned short	SubsetNum;	//SubsetArrayの要素数
};



struct DX11_MODEL
{
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;

	DX11_SUBSET* SubsetArray = nullptr;	//部分モデルの情報を格納する配列
	unsigned short	SubsetNum = 0;		//SubsetArrayの要素数

	MODEL Model;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void LoadModel( char *FileName, DX11_MODEL *model, std::string tag);
void UnloadModel( DX11_MODEL *model );
void DrawModel( DX11_MODEL &model );

bool DoubleCheck(const std::string tag, DX11_MODEL& Model);
