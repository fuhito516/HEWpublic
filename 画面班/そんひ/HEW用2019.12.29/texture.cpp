
#include"directx.h"
#include"texture.h"

#define TEXTURE_FILENAME_MAX (64) // テクスチャファイル名最大文字数（パス、NULL文字含む）

// テクスチャファイル管理構造体
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX]; // テクスチャファイル名
	int width;  // テクスチャ解像度横幅
	int height; // テクスチャ解像度縦幅

} TextureFile;

// 読み込みテクスチャ情報
static const TextureFile g_TextureFiles[] =
{

	// システム
	{ "asset/texture/fade.png",			SIZE_2, SIZE_2},
	{ "asset/texture/blacknumber.png",	SIZE_512, SIZE_256},


	// 共通
    { "asset/texture/black.png",	SIZE_1024, SIZE_576 },
	{ "asset/texture/back.png",		SIZE_256, SIZE_64},
	{ "asset/texture/decision.png",	SIZE_256, SIZE_64},


	//タイトル

	//人数
	{ "asset/texture/people heading.png",		SIZE_256, SIZE_64 },
	{ "asset/texture/people light.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/people ninzu1.png",		SIZE_256, SIZE_256 },
	{ "asset/texture/people ninzu2.png",		SIZE_256, SIZE_256 },
	{ "asset/texture/people ninzu3.png",		SIZE_256, SIZE_256 },
	{ "asset/texture/people ninzu4.png",		SIZE_256, SIZE_256 },

	//キャラクター
	{ "asset/texture/character heading.png",		SIZE_512, SIZE_64 },
	{ "asset/texture/character light.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character select.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character one.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character two.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character three.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character four.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/Chara_Beta.png",		        SIZE_256, SIZE_256 },

	//名前

	//難易度
	{ "asset/texture/difficulty heading.png",		SIZE_256, SIZE_64 },
	{ "asset/texture/difficulty light.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/difficulty easy.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/difficulty normal.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/difficulty hard.png",		    SIZE_256, SIZE_256 },

	// STAGE
	{ "asset/texture/stage heading.png",	SIZE_256, SIZE_64},
	{ "asset/texture/stage rope.png",		SIZE_64, SIZE_256},
	{ "asset/texture/stage character.png",	SIZE_128, SIZE_128},

};
// 読み込みテクスチャ数
static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);
// static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFiles); // required Windows.h

// 読み込みテクスチャ数とテクスチャ管理番号列挙数に差があった場合コンパイルエラーとする
static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {}; // テクスチャインターフェース管理配列

// テクスチャの読み込み
int Texture_Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{

		if (FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i]))) {
			// DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

// テクスチャの解放
void Texture_Release(void)
{
	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{
		if (g_pTextures[i])
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

// テクスチャインターフェースの取得
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
	if (index < 0 || index >= TEXTURE_INDEX_MAX)
	{
		return NULL;
	}

	return g_pTextures[index];
}

// テクスチャ解像度幅の取得
int Texture_GetWidth(TextureIndex index)
{
	if (index < 0 || index >= TEXTURE_INDEX_MAX)
	{
		return NULL;
	}

	return g_TextureFiles[index].width;
}
// テクスチャ解像度高さの取得
int Texture_GetHeight(TextureIndex index)
{
	if (index < 0 || index >= TEXTURE_INDEX_MAX)
	{
		return NULL;
	}

	return g_TextureFiles[index].height;
}