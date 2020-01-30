#pragma once

#include"direct3d.h"
#include"vertex.h"

// ボードの数(上限)
#define NUMBER_OF_GROUND (120)
// ボードの縦横のサイズ(初期値)
#define GROUND_VERTICAL_SIZE	(1.0f)
#define GROUND_HORIZONTAL_SIZE	(1.0f)

class cGround
{
public:

	static cGround*				objects[NUMBER_OF_GROUND];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// 使用
	bool use;

	// 描画
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	// コンストラクタ
	cGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size);

	// 頂点
	static void SetVertex();

	// 基本関数
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 配置
	static void SetGround(D3DXVECTOR2 _position, D3DXVECTOR2 _size);
};