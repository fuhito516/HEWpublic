#pragma once

#include"direct3d.h"
#include"vertex.h"

// ろうそくの数
#define NUMBER_OF_GOAL (1)
// ろうそくの縦横のサイズ
#define GOAL_VERTICAL_SIZE		(8.0f)
#define GOAL_HORIZONTAL_SIZE	(16.0f)

class cGoal
{
	// 共通部
public:

	static cGoal* numberOfObjects[NUMBER_OF_GOAL];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// 関数
	static void SetVertex();
	static void SetGoal(D3DXVECTOR2 _position);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 要素部
public:

	// 使用
	bool use;
	// 灯る
	bool turnOn;

	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;
};