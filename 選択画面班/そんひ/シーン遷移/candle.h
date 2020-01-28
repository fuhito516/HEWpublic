#pragma once

#include"direct3d.h"
#include"vertex.h"

// ろうそくの数
#define NUMBER_OF_CANDLE (10)
// ろうそくの縦横のサイズ
#define CANDLE_VERTICAL_SIZE	(4.0f)
#define CANDLE_HORIZONTAL_SIZE	(4.0f)

class cCandle
{
public:

	static cCandle* objects[NUMBER_OF_CANDLE];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// 使用
	bool use;

	// 衝突
	bool collision;

	// 描画
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	// コンストラクタ
	cCandle(D3DXVECTOR2 _position);

	// 頂点
	static void SetVertex();

	// 基本関数
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 配置
	static void SetCandle(D3DXVECTOR2 _position);
};