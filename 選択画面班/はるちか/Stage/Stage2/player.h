#pragma once

#include"direct3d.h"
#include"vertex.h"

// プレイヤーの移動スピード
#define PLAYER_MOVEMENT_SPEED (0.2f)
// プレイヤーのジャンプの力
#define PLAYER_JUMPPOWER (1.5f)
// プレイヤーの最高落下速度
#define PLAYER_MAXIMUM_FALLSPEED (0.3f)
// プレイヤーの初期位置(x, y)
#define PLAYER_INITIAL_POSITION_X (0.0f)
#define PLAYER_INITIAL_POSITION_Y (8.0f)

// プレイヤーの数
#define NUMBER_OF_PLAYER (1)
// プレイヤーの頂点数
#define NUMBER_OF_PLAYER_VERTEXES (4)
// プレイヤーの縦横のサイズ
#define PLAYER_VERTICAL_SIZE	(4.0f)
#define PLAYER_HORIZONTAL_SIZE	(4.0f)

class cPlayer
{
// 共通部
public:

	static cPlayer* numberOfObjects[NUMBER_OF_PLAYER]; // オブジェクト格納

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;	// 頂点バッファ
	static VERTEX_3D*				pVertex;		// 頂点バッファの中身を埋める

	// 関数
	static void SetVertex();
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

// 要素部
public:

	// 前フレームの位置
	D3DXVECTOR2 pastPosition;

	// 移動方向
	int directionVertical;
	int directionHorizontal;

	// ジャンプ可能判定
	bool jumpPossible;
	// ジャンプ中判定
	bool jumping;
	// ジャンプ最中の天井への当たり判定
	bool hitCeilingWhileJumping;

	// 重力カウンター
	float gravityTimer;

	// 当たり判定(何に当たっているのか)
	int collision;

	// 聖火保持
	bool retention;

	// 描画
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

};