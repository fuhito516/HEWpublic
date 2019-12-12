
#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <d3d9.h>
#define FIREPOS_X	(800)
#define FIREPOS_Y	(40)
#define KETTEIPOS_X (SCREEN_WIDTH/2)
#define KETTEIPOS_Y	(SCREEN_HEIGHT/2+200)

#define M_KIHONTEXTURE_W	(256)
#define M_KIHONTEXTURE_H	(256)
#define S_KIHONTEXTURE_H	(128)
#define	S_KIHONTEXTURE_W	(128)

/*------------------------------------------------------------------------------
   テクスチャ列挙型
------------------------------------------------------------------------------*/
// テクスチャ管理番号
typedef enum TextureIndex
{
	TEXTURE_INDEX_BG,
	TEXTURE_INDEX_UNKO,
	TEXTURE_INDEX_PURESENTER,
    TEXTURE_INDEX_TITLE,

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



#endif // TEXTURE_H_
