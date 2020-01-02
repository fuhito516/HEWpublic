#pragma once

#include"direct3d.h"
#include"vertex.h"

// ボードのスピード
#define GROUND_MOVE_SPEED (0.05f)

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

	static cMoveGround* numberOfObjects[NUMBER_OF_GROUND_MOVE]; // オブジェクト格納

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// 頂点バッファ
	static VERTEX_3D*				pVertex;		// 頂点バッファの中身を埋める

	// 関数
	static void SetVertex();
	static void SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size, float _moveWidth);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

// 要素部
public:

	// 追加パラメータ
	float speed;
	float moveWidth;

	// 使用
	bool use;

	// サイズ
	D3DXVECTOR2 size;

	// 行列
	D3DXVECTOR3	position;
	D3DXVECTOR3 pastPosition;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;
};