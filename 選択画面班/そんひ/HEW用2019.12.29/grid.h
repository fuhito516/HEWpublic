#pragma once

#include"vertex.h"

#define GRID_NUMBER				(13)
#define GRID_INTERVALLENGTH		(5.0f)
#define GRID_HALF_OF_LINELENGTH	(GRID_NUMBER * GRID_INTERVALLENGTH / 2 - GRID_INTERVALLENGTH / 2)
#define GRID_NUMBER_OF_VERTEX	(GRID_NUMBER * 2 * 2)
#define GRID_NUMBER_OF_LINE		(GRID_NUMBER * 2)

class cGrid
{
public:

	LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// 頂点バッファ
	VERTEX_3D				*pVertex;

	D3DXVECTOR3 pos;		// 地面の位置(四角形の中央座標)
	D3DXVECTOR3 rot;		// 地面の向き(回転)
	D3DXVECTOR3 scl;		// 地面の大きさ(スケール)
	D3DXMATRIX worldMtx;	// ワールドマトリックス

	void Init_Grid();		// 初期化
	void Uninit_Grid();		// 終了
	void Update_Grid();		// 更新
	void Draw_Grid();		// 描画

};

cGrid* GetGrid();