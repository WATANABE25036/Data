/*==============================================================================

   テクスチャの描画 [collision.cpp]
                                                         Author :
                                                         Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "collision.h"

//*****************************************************************************
// 当たり判定処理
//*****************************************************************************
void UpdateCollision()
{

}

//---------------------------------------------------------------------
// 円同士の当たり判定
// in pos1, pos2: 円の中心座標
//    size1, size2: 円の半径
// out true:当たり flase:外れ
//---------------------------------------------------------------------
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
    //中心同士の長さ(ルートを使うバージョン)
    D3DXVECTOR2 distance = pos1 - pos2;
    float length = D3DXVec2Length(&distance);

    //円1と円2の半径の総和
    float size = size1 + size2;

    //中心同士の長さと半径の総和の比較
    if (length < size)
    {
        return true; //円同士が当たっている
    }

    return false; //円同士が当たっていない
}

//---------------------------------------------------------------------
// 短形同士の当たり判定
// in pos1, pos2: 矩形の中心座標
//    size1, size2: 矩形のサイズ
// out true:当たり flase:外れ
//---------------------------------------------------------------------
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
    D3DXVECTOR2 min1, max1; //キャラクタ1の左上座標、右下座標
    D3DXVECTOR2 min2, max2; //キャラクタ2の左上座標、右下座標

    min1.x = pos1.x - size1.x * 0.5f;//キャラクタ1の左上座標X
    min1.y = pos1.y - size1.y * 0.5f;//キャラクタ1の左上座標Y
    max1.x = pos1.x + size1.x * 0.5f;//キャラクタ1の右下座標X
    max1.y = pos1.y + size1.y * 0.5f;//キャラクタ1の右下座標Y

    min2.x = pos2.x - size2.x * 0.5f;//キャラクタ2の左上座標X
    min2.y = pos2.y - size2.y * 0.5f;//キャラクタ2の左上座標Y
    max2.x = pos2.x + size2.x * 0.5f;//キャラクタ2の右下座標X
    max2.y = pos2.y + size2.y * 0.5f;//キャラクタ2の右下座標Y

    //X軸の判定
    if ((min1.x < max2.x) && (max1.x > min2.x))
    {
        //Y軸の判定
        if ((min1.y < max2.y) && (max1.y > min2.y))
        {
            return true; //1つの矩形は当たっている
        }
    }

    return false; //2つの短径は当たっていない

}

//---------------------------------------------------------------------
// 短形同士き矩形の当たり判定(角度付)
// in pos1, pos2: 矩形の中心座標
// size1, size2: 矩形のサイズ
// rot2: 矩形の角度(ラジアン)
// out true:当たり flase:外れ
//---------------------------------------------------------------------
bool CollisionRot(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2, float rot2)
{
    //参考 https://yttm-work.jp/collision/collision_0007.html
    // 矩形の中心を原点とした相対座標を作成する
    D3DXVECTOR2 relative_position = D3DXVECTOR2(pos1.x - pos2.x, pos1.y - pos2.y);

    // 相対座標に対して矩形の回転を打ち消す逆行列を掛ける
    D3DXVECTOR2 transform_pos = D3DXVECTOR2(
        cosf(rot2) * relative_position.x + sinf(rot2) * relative_position.y,
        -sinf(rot2) * relative_position.x + cosf(rot2) * relative_position.y
    );

    // 矩形と点の当たり判定を行う
    if (-size2.x / 2.0f <= transform_pos.x + size1.x && size2.x / 2.0f >= transform_pos.x - size1.x &&
        -size2.y / 2.0f <= transform_pos.y + size1.y && size2.y / 2.0f >= transform_pos.y - size1.x)
    {
        return true;
    }

    return false;
}