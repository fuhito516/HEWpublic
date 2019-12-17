
#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"


/*------------------------------------------------------------------------------
構造体宣言
------------------------------------------------------------------------------*/
// ２Dポリゴン頂点構造体
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 position; // 頂点座標（座標変換済み頂点）
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // ２Dポリゴン頂点フォーマット


/*------------------------------------------------------------------------------
グローバル変数宣言
------------------------------------------------------------------------------*/
static D3DCOLOR g_Color = 0xffffffff;
// static D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);

static float sx = 0.01f;
static float sy = 0.01f;
static int alpha = 9;
static int alphaBG = 0;
static int alphaflg = 0;
static int alphaflg1 = 0;
/*------------------------------------------------------------------------------
関数定義
------------------------------------------------------------------------------*/

//// スプライトポリゴンの頂点カラー設定
void sprite_setcolor(D3DCOLOR g_Color)
{
	g_Color = D3DCOLOR_RGBA(0,0,0,0);
}


// スプライト描画
// ※テクスチャ切り取り幅、高さと同じ大きさのスプライトを指定座標に描画する
void Sprite_animetionDraw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float sx, float sy)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice) return;

	float w = (float)Texture_GetWidth(texture_index);

	float h = (float)Texture_GetHeight(texture_index);

	// UV座標計算
	float u[2], v[2];


	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

	float dw, dh;
	dw = tw * sx;
	dh = th * sy;

	Vertex2D vertexes[] = {

	{ D3DXVECTOR4(dx - dw / 2, dy - dh / 2, 0, 1), g_Color, D3DXVECTOR2(u[0], v[0]) },
	{ D3DXVECTOR4(dx + dw / 2, dy - dh / 2, 0, 1), g_Color, D3DXVECTOR2(u[1], v[0]) },
	{ D3DXVECTOR4(dx - dw / 2, dy + dh / 2, 0, 1), g_Color, D3DXVECTOR2(u[0], v[1]) },
	{ D3DXVECTOR4(dx + dw / 2, dy + dh / 2, 0, 1), g_Color, D3DXVECTOR2(u[1], v[1]) },
	};


	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}
void Sprite_animetion_Alpha_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float sx, float sy)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	float w = (float)Texture_GetWidth(texture_index);

	float h = (float)Texture_GetHeight(texture_index);

	//フェードイ
	if (alpha <52) {
		alphaflg = 0;
	}

	if (alpha > 255) {
		alphaflg =1;
	}

	if (alphaflg == 0) {
		alpha += 1;
	}

	if (alphaflg ==1) {
		alpha -= 1;
	}
	
	// UV座標計算
	float u[2], v[2];

	u[0] = (float)tx / w;

	v[0] = (float)ty / h;

	u[1] = (float)(tx + tw) / w;

	v[1] = (float)(ty + th) / h;


	float dw, dh;
	
	dw = tw * sx;
	
	dh = th * sy;


	Vertex2D vertexes[] = {
	{ D3DXVECTOR4(dx - dw / 2, dy - dh / 2, 0, 1), D3DCOLOR_RGBA(255, 255, 255, alpha), D3DXVECTOR2(u[0], v[0]) },
	{ D3DXVECTOR4(dx + dw / 2, dy - dh / 2, 0, 1),  D3DCOLOR_RGBA(255, 255, 255, alpha), D3DXVECTOR2(u[1], v[0]) },
	{ D3DXVECTOR4(dx - dw / 2, dy + dh / 2, 0, 1),  D3DCOLOR_RGBA(255, 255, 255, alpha), D3DXVECTOR2(u[0], v[1]) },
	{ D3DXVECTOR4(dx + dw / 2, dy + dh / 2, 0, 1),  D3DCOLOR_RGBA(255, 255, 255, alpha), D3DXVECTOR2(u[1], v[1]) },
	};

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}
//LIGHT系
void Sprite_Alpha_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float sx, float sy)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	float w = (float)Texture_GetWidth(texture_index);

	float h = (float)Texture_GetHeight(texture_index);

	//フェードイ
	if (alphaBG <1) {
		alphaflg1 = 0;
	}

	if (alphaBG > 100) {
		alphaflg1 = 1;
	}

	if (alphaflg1 == 0) {
		alphaBG += 1;
	}

	if (alphaflg1 == 1) {
		alphaBG -= 1;
	}

	// UV座標計算
	float u[2], v[2];

	u[0] = (float)tx / w;

	v[0] = (float)ty / h;

	u[1] = (float)(tx + tw) / w;

	v[1] = (float)(ty + th) / h;


	float dw, dh;

	dw = tw * sx;

	dh = th * sy;


	Vertex2D vertexes[] = {
		{ D3DXVECTOR4(dx - dw / 2, dy - dh / 2, 0, 1), D3DCOLOR_RGBA(255, 255, 255, alphaBG), D3DXVECTOR2(u[0], v[0]) },
	{ D3DXVECTOR4(dx + dw / 2, dy - dh / 2, 0, 1),  D3DCOLOR_RGBA(255, 255, 255, alphaBG), D3DXVECTOR2(u[1], v[0]) },
	{ D3DXVECTOR4(dx - dw / 2, dy + dh / 2, 0, 1),  D3DCOLOR_RGBA(255, 255, 255, alphaBG), D3DXVECTOR2(u[0], v[1]) },
	{ D3DXVECTOR4(dx + dw / 2, dy + dh / 2, 0, 1),  D3DCOLOR_RGBA(255, 255, 255, alphaBG), D3DXVECTOR2(u[1], v[1]) },
	};

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}