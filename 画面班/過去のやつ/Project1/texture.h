#pragma once

#define SCENE_WIDTH		(1920 / 2)
#define SCENE_HEIGHT	(1080 / 2)
#define SMALL			(256 / 2)

#include <d3d9.h>


/*------------------------------------------------------------------------------
   テクスチャ列挙型
------------------------------------------------------------------------------*/
// テクスチャ管理番号
enum TextureIndex
{
	// SCENE
	TEXTURE_SCENE_TITLE,
	TEXTURE_SCENE_PLAYER,
	TEXTURE_SCENE_CHARACTER,
	TEXTURE_SCENE_NAME,
	TEXTURE_SCENE_DIFFICULTY,
	TEXTURE_SCENE_STAGE,
	TEXTURE_SCENE_STAGECHARACTER,
	TEXTURE_SCENE_GAMEOVER,
	TEXTURE_SCENE_AREARANKING,
	TEXTURE_SCENE_STAGECLEAR,
	TEXTURE_SCENE_STAGERANKING,
	TEXTURE_SCENE_SCORETABLE,
	TEXTURE_SCENE_RETURN,

	// 河野
	TEXTURE_INDEX_BACK,
	TEXTURE_INDEX_KETTEI,
	TEXTURE_INDEX_4PCARSOLU,
	TEXTURE_INDEX_3PCARSOLU,
	TEXTURE_INDEX_2PCARSOLU,
	TEXTURE_INDEX_1PCARSOLU,
	TEXTURE_INDEX_LIGHT,
	TEXTURE_INDEX_SENTAKU,
	TEXTURE_INDEX_BG,

	// 李
	TEXTURE_INDEX_HAIKEI,
	TEXTURE_INDEX_WAKU,
	TEXTURE_INDEX_NANNIDOHAIKEI,
	TEXTURE_INDEX_NANNIDOWAKU,

	TEXTURE_INDEX_FOG,
	TEXTURE_INDEX_BLACK,
    TEXTURE_INDEX_MAX
};


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/
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