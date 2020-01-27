#ifndef SPRITE_H_
#define SPRITE_H_


#include <d3d9.h>    // D3DCOLOR
#include "texture.h" // TextureIndex


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/

// スプライトポリゴンの頂点カラー設定
// ※4頂点すべてに同じカラーを設定する
//
// 引数 ... color 設定する色
void Sprite_SetColor(D3DCOLOR color);

// スプライト描画
//
// 引数:texture_index	... テクスチャ管理番号
//      dx				... 描画座標x
//      dy				... 描画座標y
//		width_ratio		... 横幅比率
//		height_ratio	... 高さ比率
//      u_start			... テクスチャ切り取り始まりu
//      v_start			... テクスチャ切り取り始まりv
//      u_finish		... テクスチャ切り取り終わりu
//      v_finish		... テクスチャ切り取り終わりv
void Sprite_Draw
(
	TextureIndex texture_index,
	float dx, float dy,
	float width_ratio, float height_ratio,
	float u_start, float v_start, float u_finish, float v_finish
);
void Sprite_KoumeiDraw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);

#endif // SPRITE_H_
