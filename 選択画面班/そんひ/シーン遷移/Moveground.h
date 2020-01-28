#pragma once

#include"direct3d.h"
#include"vertex.h"

// ボードの数(上限)
#define NUMBER_OF_GROUND_MOVE (50)
// ボードの頂点数
#define NUMBER_OF_GROUND_VERTEXES_MOVE (4)
// ボードの縦横のサイズ(初期値)
#define GROUND_VERTICAL_SIZE_MOVE	(1.0f)
#define GROUND_HORIZONTAL_SIZE_MOVE	(1.0f)

class cMoveGround
{
	// 共通部
public:
	static cMoveGround* objects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

	static LPDIRECT3DVERTEXBUFFER9	pMoveVertexBuffer;	// 頂点バッファ
	static VERTEX_3D*				pMoveVertex;		// 頂点バッファの中身を埋める

													// 関数
	static void SetVertex();
	virtual void SetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize, D3DXVECTOR2 _distance);
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// 要素部
public:

	// 使用
	bool use;

	// フレームカウンター
	int frameCounter;

	//移動速度
	float spead = 0.05f;

	// 前フレームの位置
	//D3DXVECTOR3 pastMposition;

	// サイズ
	D3DXVECTOR2 size;
	//移動距離
	D3DXVECTOR2 distance;

	//最初の位置
	D3DXVECTOR3 fastMovePos;

	// 行列
	D3DXVECTOR3	Mposition;
	D3DXVECTOR3	Mrotation;
	D3DXVECTOR3	Mscale;
	D3DXMATRIX	MworldMatrix;
	
};

//縦移動床
class cVerticalMoveGround : public cMoveGround
{

public:
	static cVerticalMoveGround* objects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

	static void SetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize, D3DXVECTOR2 _distance);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};

//横移動床
class cHorizontalMoveGround : public cMoveGround
{

public:
	static cHorizontalMoveGround* objects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

	static void SetGround(D3DXVECTOR2 _mposition, D3DXVECTOR2 _msize, D3DXVECTOR2 _distance);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};