
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <d3d9.h>

// テクスチャ管理番号
enum TextureIndex
{
	// テストライト
	TEXTURE_INDEX_TEST1,
	// ゲーム
	// 背景
	TEXTURE_INDEX_BACK1,
	TEXTURE_INDEX_BACK2,
	TEXTURE_INDEX_BACK3,
	TEXTURE_INDEX_BACK4,
	TEXTURE_INDEX_BACK5,
	TEXTURE_INDEX_BACK6,
	TEXTURE_INDEX_BACK7,
	// キャラクター
	TEXTURE_INDEX_BABY,
	TEXTURE_INDEX_SEIKA,
	TEXTURE_INDEX_YA,
	// ギミック
	TEXTURE_INDEX_CANDLE1,
	TEXTURE_INDEX_CANDLE2,
	TEXTURE_INDEX_GROUND,
	TEXTURE_INDEX_GOAL1,
	TEXTURE_INDEX_GOAL2,
	TEXTURE_INDEX_GHOST,

	TEXTURE_INDEX_MAX
};

// テクスチャの読み込み
//
// 戻り値:読み込めなかった数
//
int Texture_Load(void);

// テクスチャの解放
void Texture_Release(void);

// テクスチャインターフェースの取得
//
// 戻り値:テクスチャインターフェース
//        ただし存在しないindexを指定した場合、NULL
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);

// テクスチャ解像度幅の取得
//
// 引数 ... index テクスチャ管理番号
//
int Texture_GetWidth(TextureIndex index);

// テクスチャ解像度高さの取得
//
// 引数 ... index テクスチャ管理番号
//
int Texture_GetHeight(TextureIndex index);


#endif // TEXTURE_H_