#pragma once

#include"direct3d.h"
#include"vertex.h"

// 橋の数
#define NUMBER_OF_BRIDGE (1)
// 橋の仕掛けの縦横のサイズ
#define BRIDGE_VERTICAL_SIZE	(1.0f)
#define BRIDGE_HORIZONTAL_SIZE	(1.0f)

class cBridge
{
public:

	static cBridge* objects[NUMBER_OF_BRIDGE];

	// 使用
	bool use;

	// 衝突
	bool collision;

	// 描画
	D3DXMATRIX	gimmickWorldMatrix;
	D3DXVECTOR3	gimmickPosition;
	D3DXVECTOR3	gimmickRotation;
	D3DXVECTOR3	gimmickScale;

	D3DXMATRIX	bridgeWorldMatrix;
	D3DXVECTOR3	bridgePosition;
	D3DXVECTOR3	bridgeRotation;
	D3DXVECTOR3	bridgeScale;

	// コンストラクタ
	cBridge(D3DXVECTOR2 _gimmickPosition, D3DXVECTOR2 _bridgePosition, D3DXVECTOR2 _bridgeSize);

	// 基本関数
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 配置
	static void SetBridge(D3DXVECTOR2 _gimmickPosition, D3DXVECTOR2 _bridgePosition, D3DXVECTOR2 _bridgeSize);
};