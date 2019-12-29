#pragma once

#include"direct3d.h"
#include"vertex.h"

// 木目の数(縦横同数)
#define NUMBER_OF_GRAIN (5)
// グリッド線の数
#define NUMBER_OF_LINE_OF_GRID (NUMBER_OF_GRAIN * 2)
// グリッドの頂点数
#define NUMBER_OF_VERTEX_OF_GRID (NUMBER_OF_LINE_OF_GRID * 2)
// グリッド線同士の間隔
#define SPACEING_BETWEEN_GRID_LINES (10.0f)
// グリッドの半分の長さ
#define HALF_LENGTH_OF_GRID	((NUMBER_OF_GRAIN * SPACEING_BETWEEN_GRID_LINES - SPACEING_BETWEEN_GRID_LINES) / 2)

class cGrid
{
// 共通部
public:

	static cGrid* numberOfGrid;	// オブジェクト格納

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// 頂点バッファ
	static VERTEX_3D				*pVertex;		// 頂点バッファの中身を埋める

	static D3DXVECTOR3 position;	// 位置(中央座標)
	static D3DXVECTOR3 rotation;	// 回転
	static D3DXVECTOR3 scale;		// 大きさ
	static D3DXMATRIX worldMatrix;	// ワールドマトリックス

	static void SetVertex_Grid();	// 頂点セット関数
	static void Init();				// 初期化
	static void Uninit();			// 終了処理
	static void Update();			// 更新
	static void Draw();				// 描画

};