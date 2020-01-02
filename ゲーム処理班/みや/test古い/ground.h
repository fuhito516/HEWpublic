#pragma once

#include"direct3d.h"
#include"vertex.h"

// ボードの数(上限)
#define NUMBER_OF_GROUND (10)
// ボードの頂点数
#define NUMBER_OF_GROUND_VERTEXES (4)
// ボードの縦横のサイズ(初期値)
#define GROUND_VERTICAL_SIZE	(1.0f)
#define GROUND_HORIZONTAL_SIZE	(1.0f)

class cGround
{
// 共通部
public:

	static cGround* numberOfObjects[NUMBER_OF_GROUND]; // オブジェクト格納

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// 頂点バッファ
	static VERTEX_3D*				pVertex;		// 頂点バッファの中身を埋める

	// 関数
	static void SetVertex();
	static void SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 要素部
public:

	// 使用
	bool use;

	// サイズ
	D3DXVECTOR2 size;

	// 行列
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;
};