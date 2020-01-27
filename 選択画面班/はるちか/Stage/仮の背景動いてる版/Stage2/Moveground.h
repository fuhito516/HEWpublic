#pragma once

#include"direct3d.h"
#include"vertex.h"

// ボードの数(上限)
#define NUMBER_OF_GROUND_MOVE (10)
// ボードの頂点数
#define NUMBER_OF_GROUND_VERTEXES_MOVE (4)
// ボードの縦横のサイズ(初期値)
#define GROUND_VERTICAL_SIZE_MOVE	(1.0f)
#define GROUND_HORIZONTAL_SIZE_MOVE	(1.0f)

class cMoveGround
{
	// 共通部
public:

	static cMoveGround* MovenumberOfObjects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

	static LPDIRECT3DVERTEXBUFFER9	pMoveVertexBuffer;	// 頂点バッファ
	static VERTEX_3D*				pMoveVertex;		// 頂点バッファの中身を埋める

													// 関数
	static void MoveSetVertex();
	static void MoveSetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize);
	static void MoveInit();
	static void MoveUninit();
	static void MoveUpdate();
	static void MoveDraw();

	//static void GetMovegroundpos(float GetPos);
	
	// 要素部
public:

	// 使用
	bool use;

	// フレームカウンター
	int frameCounter;

	// サイズ
	D3DXVECTOR2 size;

	D3DXVECTOR3 fastMovePos;

	// 行列
	D3DXVECTOR3	Mposition;
	D3DXVECTOR3	Mrotation;
	D3DXVECTOR3	Mscale;
	D3DXMATRIX	MworldMatrix;
	D3DXVECTOR3	Nposition;

};