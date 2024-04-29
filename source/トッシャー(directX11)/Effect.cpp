/*==============================================================================

   エフェクト(ビルボード) [Effect.cpp]
														 Author : 渡邉 修
														 Date   : 2024/02/15
--------------------------------------------------------------------------------

==============================================================================*/
#include "Effect.h"
#include "Texture.h"

// 静的メンバ変数の定義
int Effect::m_sCou = 0;

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
Effect::Effect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, EFFECT_PATTERN pattern, GameWorld* gameWorld, ORDER_TAG tag, int ownerCou)
	:Board(pos, rot, gameWorld)
{
	m_sCou++;
	m_OwnerNum = m_sCou;
	m_OwnerTag = tag;
	m_OwnerCou = ownerCou;
	m_Tag = "Effect";
	m_HitSize.x = 30.0f;//球体で判定するので半径

	//-------------------------------------------------------------//エフェクトを追加したらここに追加
	//テクスチャと大きさの設定
	switch (pattern)
	{
	case RIPPLES:
		//表示大きさ設定
		m_Scl = D3DXVECTOR3(20.0f, 20.0f, 20.0f);
		//テクスチャの設定
		m_TexNo = LoadTexture((char*)"data/TEXTURE/Ripples.png");
		break;

	default:
		break;
	}
	//-------------------------------------------------------------//

	//モデルの読み込み
	Board::ModelLoad();
}

Effect::~Effect()
{

}

//=============================================================================
// 初期化
//=============================================================================
void Effect::Init()
{

}

void Effect::Update()
{
	Object::Update();
}
