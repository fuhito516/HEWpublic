#pragma once

#include"direct3d.h"
#include"vertex.h"

// オブジェクト数
#define NUMBER_OF_GHOST (1)
// サイズ
#define HORIZONTAL_SIZE_GHOST	(4.0f)
#define VERTICAL_SIZE_GHOST		(4.0f)
// スピード
#define SPEED_GHOST (0.1f)
// 衝突半径
#define RADIUS_GHOST (HORIZONTAL_SIZE_GHOST / 2)

class cGhost
{
public:

	// オブジェクト
	static cGhost* objects[NUMBER_OF_GHOST];

	// 頂点
	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;
	static void SetVertex();

	// 使用
	bool use;
	static void Set(D3DXVECTOR3 _position, float _width_move);
	cGhost(D3DXVECTOR3 _position, float _width_move);

	// パラメータ
	float width_move;
	D3DXVECTOR3 settingPosition;
	int moveDirection;
	static bool collision;

	// 描画
	D3DXMATRIX	worldMatrix;
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;

	// 基本関数
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	void Move();
	void CollisionInspection();
};