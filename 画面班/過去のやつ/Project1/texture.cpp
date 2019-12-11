
#include"common.h"
#include"texture.h"

#include"debug_Printf.h"
#include<d3dx9.h>
#include"mydirect3d.h"

// 構造体宣言
#define TEXTURE_FILENAME_MAX (64) // テクスチャファイル名最大文字数（パス、NULL文字含む）
// テクスチャファイル管理構造体
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX]; // テクスチャファイル名
	int width;  // テクスチャ解像度横幅
	int height; // テクスチャ解像度縦幅
} TextureFile;

// 要整理
// 読み込みテクスチャ情報
static const TextureFile g_TextureFiles[] =
{
	// SCENE
	{ "asset/texture/title.png",		SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/player.png",		SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/character.png",	SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/name.png",			SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/difficulty.png",	SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/stage.png",		SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/Chara_Beta.png",	SMALL,			SMALL},
	{ "asset/texture/gameover.png",		SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/arearanking.png",	SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/stageclear.png",	SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/stageranking.png",	SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/scoretable.png",	SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/return.png",		SCREEN_WIDTH,	SCREEN_HEIGHT},
	// 河野
	{ "asset/texture/Back.png",			256,			256},
	{ "asset/texture/Kettei.png",		256,			256},
	{ "asset/texture/4p.png",			256,			256},
	{ "asset/texture/3p.png",			256,			256},
	{ "asset/texture/2p.png",			256,			256},
	{ "asset/texture/1p.png",			256,			256},
	{ "asset/texture/Light2.png",		256,			256},
	{ "asset/texture/SENTAKU2.png",		256,			256},
	{ "asset/texture/BG.png",			225,			225},
	// 李
	{ "asset/texture/ninzuhaikei.png",  SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/waku.png",			224,			203},
	{ "asset/texture/nannidohaikei.png", SCREEN_WIDTH,	SCREEN_HEIGHT},
	{ "asset/texture/waku.png",			294,			273},

	{ "asset/texture/Fog_ex.png",		256,			256},
	{ "asset/texture/black.png",		SCREEN_WIDTH,	SCREEN_HEIGHT}
};
// 読み込みテクスチャ数
static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);
// static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFiles); // required Windows.h

// 読み込みテクスチャ数とテクスチャ管理番号列挙数に差があった場合コンパイルエラーとする
static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");

/*------------------------------------------------------------------------------
   グローバル変数宣言
------------------------------------------------------------------------------*/
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {}; // テクスチャインターフェース管理配列

/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

// テクスチャの読み込み
int Texture_Load(void)
{   
    LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if( !pDevice )
	{
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ )
	{
		
		if( FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i])) ) {
            // DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

// テクスチャの解放
void Texture_Release(void)
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ )
	{
		
		if( g_pTextures[i] )
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

// テクスチャインターフェースの取得
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX )
	{
        return NULL;
    }

	return g_pTextures[index];
}

// テクスチャ解像度幅の取得
int Texture_GetWidth(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX )
	{
        return NULL;
    }

	return g_TextureFiles[index].width;
}

// テクスチャ解像度高さの取得
int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX )
	{
        return NULL;
    }

	return g_TextureFiles[index].height;
}