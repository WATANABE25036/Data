/*==============================================================================

   ビルボード [BillBoard.cpp]
														 Author : 渡邉 修
														 Date   : 2023/11/30
--------------------------------------------------------------------------------

==============================================================================*/
#include "BillBoard.h"
#include "Texture.h"
#include "Shadow.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
BillBoard::BillBoard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Camera* camera)
	:Object(pos, rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f), gameWorld), m_pCamera(camera)
{

}

BillBoard::~BillBoard()
{

}

//=============================================================================
// 初期化
//=============================================================================
void BillBoard::Init()
{

}

//=============================================================================
// 終了処理
//=============================================================================
void BillBoard::Uninit(void)
{
	if (m_VertexBuffer != nullptr)
	{// 頂点バッファの解放
		m_VertexBuffer->Release();
		m_VertexBuffer = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void BillBoard::Update(void)
{
		//座標の更新
		m_Pos += m_Dir * m_Spd;

		//影の座標を更新する
		SetPositionShadow(m_Shadow, D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z));
}

//=============================================================================
// 描画処理
//=============================================================================
void BillBoard::Draw(void)
{
	// αテストを有効に
	SetAlphaTestEnable(true);

	// ライティングを無効
	SetLightEnable(false);

	D3DXMATRIX m_MtxView, mtxScale, mtxTranslate;

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_MtxWorld);

			// ポリゴンを正面に向ける
#if 0
			// ビューマトリックスの逆行列を取得
			m_MtxWorld = m_pCamera->GetMtxInvView();
			m_MtxWorld._41 = 0.0f;
			m_MtxWorld._42 = 0.0f;
			m_MtxWorld._43 = 0.0f;
#else
			// ビューマトリックスを取得
			D3DXMATRIX m_CameraMtxView = m_pCamera->GetMtxView();

			m_MtxWorld._11 = m_CameraMtxView._11;
			m_MtxWorld._12 = m_CameraMtxView._21;
			m_MtxWorld._13 = m_CameraMtxView._31;
			m_MtxWorld._21 = m_CameraMtxView._12;
			m_MtxWorld._22 = m_CameraMtxView._22;
			m_MtxWorld._23 = m_CameraMtxView._32;
			m_MtxWorld._31 = m_CameraMtxView._13;
			m_MtxWorld._32 = m_CameraMtxView._23;
			m_MtxWorld._33 = m_CameraMtxView._33;
#endif


			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, m_Pos.x,
				m_Pos.y,
				m_Pos.z);
			D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&m_MtxWorld);

			// マテリアル設定
			SetMaterial(m_Material);

			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexNo));

			// ポリゴンの描画
			GetDeviceContext()->Draw(4, 0);

	// ライティングを有効に
	SetLightEnable(true);

	// αテストを無効に
	SetAlphaTestEnable(false);
}

void BillBoard::ModelLoad()
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);


	// 頂点バッファに値をセットする
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// 頂点座標の設定
		vertex[0].Position = D3DXVECTOR3(-m_Scl.x / 2.0f, 0.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(-m_Scl.x / 2.0f, m_Scl.y, 0.0f);
		vertex[2].Position = D3DXVECTOR3(m_Scl.x / 2.0f, 0.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(m_Scl.x / 2.0f, m_Scl.y, 0.0f);

		// 頂点カラーの設定
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	// マテリアル初期化
	ZeroMemory(&m_Material, sizeof(m_Material));
	m_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}