#pragma once

#include"common.h"
#include"direct3d.h"

// カメラのパラメータ
#define	VALUE_MOVE_CAMERA	(0.2f)				// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.008f)	// カメラの回転量

// プロジェクション用パラメータ
#define VIEW_ANGLE (D3DXToRadian(45.0f))							// ビュー平面の視野角
#define VIEW_ASPECT ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)		// ビュー平面のアスペクト比
#define VIEW_NEAR_Z (1.0f)											// ビュー平面のNearZ値
#define VIEW_FAR_Z (1000.0f)										// ビュー平面のFarZ値

class cCamera
{
public:

	static cCamera* object;

	static D3DXVECTOR3 position;	// カメラの視点(位置)
	static D3DXVECTOR3 lookAt;		// カメラの注視点
	static D3DXVECTOR3 up;			// カメラの上方向ベクトル

	static D3DXVECTOR3 rotation;		// カメラの回転
	static float	   lengthOfView;	// カメラの視点と注視点の距離

	static D3DXMATRIX viewMatrix;		// ビューマトリックス
	static D3DXMATRIX projectionMatrix;	// プロジェクションマトリックス

	// 関数
	static void Init();
	static void Uninit();
	static void Update();
	static void SetCamera();

};