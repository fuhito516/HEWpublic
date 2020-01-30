#pragma once

#include"direct3d.h"
#include"vertex.h"

// ろうそくの数
#define NUMBER_OF_GOAL (1)
// ろうそくの縦横のサイズ
#define GOAL_HORIZONTAL_SIZE	(16.0f)
#define GOAL_VERTICAL_SIZE		(8.0f)
// 衝突半径
#define RADIUS_GOAL (GOAL_HORIZONTAL_SIZE / 2)

class cGoal
{
public:

	static cGoal* objects[NUMBER_OF_GOAL];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// 使用
	bool use;

	// 衝突
	static bool collision;

	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	// コンストラクタ
	cGoal(D3DXVECTOR3 _position);

	// 頂点
	static void SetVertex();

	// 基本関数
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 配置
	static void Set(D3DXVECTOR3 _position);
};