#pragma once

#include"directx.h"
#include"common.h"

// カメラの初期位置とパラメータ
#define	POS_X_CAM		(0.0f)
#define	POS_Y_CAM		(0.0f)
#define	POS_Z_CAM		(-20.0f)
#define	VALUE_MOVE_CAMERA	(0.2f)				// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.008f)	// カメラの回転量

// プロジェクション用パラメータ
#define VIEW_ANGLE (D3DXToRadian(45.0f))							// ビュー平面の視野角
#define VIEW_ASPECT ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)		// ビュー平面のアスペクト比
#define VIEW_NEAR_Z (1.0f)											// ビュー平面のNearZ値
#define VIEW_FAR_Z (1000.0f)										// ビュー平面のFarZ値

#define CAMERA_SPEED (0.2f)

class Camera
{
public:

	D3DXVECTOR3			pos;			// カメラの視点(位置)
	D3DXVECTOR3			at;				// カメラの注視点
	D3DXVECTOR3			up;				// カメラの上方向ベクトル
	D3DXVECTOR3			rot;			// カメラの回転
	float				len;			// カメラの視点と注視点の距離

	D3DXMATRIX			mtxView;		// ビューマトリックス
	D3DXMATRIX			mtxProjection;	// プロジェクションマトリックス

	void InitCamera(void);
	void UninitCamera(void);
	void UpdateCamera(void);
	void SetCamera();

};

Camera* GetCamera();