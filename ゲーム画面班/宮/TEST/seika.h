#pragma once

#include"direct3d.h"
#include"vertex.h"

// 聖火の移動スピード
#define SEIKA_MOVEMENT_SPEED (1.0f)
// 聖火の最高落下速度
#define SEIKA_MAXSPEED (1.0f)

// 聖火の数
#define NUMBER_OF_SEIKA (1)
// 聖火の縦横のサイズ
#define SEIKA_VERTICAL_SIZE		(2.0f)
#define SEIKA_HORIZONTAL_SIZE	(2.0f)

class cSeika
{
// 共通部
public:

	static cSeika* numberOfObjects[NUMBER_OF_SEIKA];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;
	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer_light;
	static VERTEX_3D*				pVertex_light;

	// 以前の持主
	int owner;

	// 移動方向
	int directionVertical;
	int directionHorizontal;

	// ジャンプ中判定
	bool jumping;
	// ジャンプ最中の天井への当たり判定
	bool hitCeilingWhileJumping;
	// ジャンプ済判定
	bool jumped;

	// 重力カウンター
	float gravityTimer;

	// 当たり判定(何に当たっているのか)
	int collision;

	// 前フレームの位置
	D3DXVECTOR2 pastPosition;

	// 描画
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	D3DXVECTOR3	position_light;
	D3DXVECTOR3	rotation_light;
	D3DXVECTOR3	scale_light;
	D3DXMATRIX	worldMatrix_light;

	static void SetVertex();
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
};