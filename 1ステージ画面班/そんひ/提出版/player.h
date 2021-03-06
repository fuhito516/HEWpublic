#pragma once

#include"direct3d.h"
#include"vertex.h"

// プレイヤーの移動スピード
#define PLAYER_MOVEMENT_SPEED (0.2f)
// プレイヤーのジャンプの力
#define PLAYER_JUMPPOWER (0.9f)
// プレイヤーの最高落下速度
#define PLAYER_MAXIMUM_FALLSPEED (1.0f)
// プレイヤーの初期位置(x, y)
#define PLAYER_INITIAL_POSITION_X (0.0f)
#define PLAYER_INITIAL_POSITION_Y (8.0f)

// プレイヤーの数
#define NUMBER_OF_PLAYER (1)
// 縦横のサイズ
#define PLAYER_HORIZONTAL_SIZE	(4.0f)
#define PLAYER_VERTICAL_SIZE	(4.0f)
// 矢の縦横のサイズ
#define YA_VERTICAL_SIZE	(2.0f)
#define YA_HORIZONTAL_SIZE	(4.0f)

// 衝突半径
#define RADIUS_PLAYER (PLAYER_HORIZONTAL_SIZE / 2)

class cPlayer
{
public:

	static cPlayer* objects[NUMBER_OF_PLAYER];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;
	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer_ya;
	static VERTEX_3D*				pVertex_ya;

	// 前フレームの位置
	D3DXVECTOR2 pastPosition;

	// 移動方向
	int directionVertical;
	int pastDirectionHorizontal;
	int directionHorizontal;

	// ジャンプ
	bool jumpPossible;
	bool jumping;
	bool hitCeilingWhileJumping;

	// 重力タイマー
	float gravityTimer;

	// 衝突
	int collision;

	// 聖火
	bool throwMode;
	bool retention;
	int  throwDegree;

	// 描画
	int frameAnimation;

	D3DXMATRIX	worldMatrix;
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;

	D3DXMATRIX	worldMatrix_ya;
	D3DXVECTOR3	position_ya;
	D3DXVECTOR3	rotation_ya;
	D3DXVECTOR3	scale_ya;

	// コンストラクタ
	cPlayer(D3DXVECTOR3 _position);

	static void SetVertex();

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void Set(D3DXVECTOR3 _position);
};