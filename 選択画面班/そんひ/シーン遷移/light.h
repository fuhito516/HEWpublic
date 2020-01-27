#pragma once

#include"direct3d.h"
#include"vertex.h"
#include"common.h"
#include"seika.h"

// サイズ
#define LIGHT_HORIZONTAL_SIZE	(SCREEN_WIDTH / 5)
#define LIGHT_VERTICAL_SIZE		(LIGHT_HORIZONTAL_SIZE / 2)
// ライフ(GAMEOVERまでの制限時間)
#define SECONDS_FOR_DEAD (10.0f)

class cLight
{
public:

	static cLight* objects[NUMBER_OF_SEIKA];

	static LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	static VERTEX_3D*				pVertex;

	// パラメータ
	float life;
	static bool dead;

	// 描画
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;
	D3DXMATRIX	worldMatrix;

	// コンストラクタ
	cLight();

	// 頂点
	static void SetVertex();

	// 基本関数
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 配置
	static void Set();
};