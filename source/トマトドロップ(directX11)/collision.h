/*==============================================================================

   テクスチャの描画 [collision.h]
                                                         Author :
                                                         Date   :
--------------------------------------------------------------------------------

==============================================================================*/

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void UpdateCollision(void);
// 円同士の当たり判定
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2); //BC = バウンディングサークル
// 短形同士の当たり判定
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2); //BB = バウンディングボックス

bool CollisionRot(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2, float rot2);

bool CollisionRotRect(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2, float rot1, float rot2);
