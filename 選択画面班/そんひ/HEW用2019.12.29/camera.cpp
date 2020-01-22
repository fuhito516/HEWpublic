
#include"camera.h"
#include"directx.h"
#include"input.h"

Camera g_Camera;

void Camera::InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	g_Camera.at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);

}
void Camera::UninitCamera(void)
{

}
void Camera::UpdateCamera(void)
{

	if (GetKeyboardPress(DIK_A))
	{
		// 左移動
		g_Camera.pos.x -= cosf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		g_Camera.pos.z += sinf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}
	if (GetKeyboardPress(DIK_D))
	{
		// 右移動
		g_Camera.pos.x += cosf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		g_Camera.pos.z -= sinf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		
		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}
	if (GetKeyboardPress(DIK_W))
	{
		// 前移動
		g_Camera.pos.x += sinf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		g_Camera.pos.z += cosf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}
	if (GetKeyboardPress(DIK_S))
	{
		// 後移動
		g_Camera.pos.x -= sinf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		g_Camera.pos.z -= cosf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_SPACE))
	{
		g_Camera.pos.y += VALUE_MOVE_CAMERA;
		g_Camera.at.y  += VALUE_MOVE_CAMERA;
	}
	if (GetKeyboardPress(DIK_LCONTROL))
	{
		g_Camera.pos.y -= VALUE_MOVE_CAMERA;
		g_Camera.at.y  -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_LEFT))
	{
		// 注視点旋回「左」
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		// 注視点旋回「右」
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}
	if (GetKeyboardPress(DIK_UP))
	{
		// 注視点移動「上」
		g_Camera.at.y += VALUE_MOVE_CAMERA * 2;
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		// 注視点移動「下」
		g_Camera.at.y -= VALUE_MOVE_CAMERA * 2;
	}

	if (GetKeyboardPress(DIK_U))
	{
		// 近づく
		g_Camera.len -= VALUE_MOVE_CAMERA;
	}
	if (GetKeyboardPress(DIK_M))
	{
		// 離れる
		g_Camera.len += VALUE_MOVE_CAMERA;
	}

}
void Camera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
		&g_Camera.pos,		// カメラの視点(位置)
		&g_Camera.at,		// カメラの注視点
		&g_Camera.up);		// カメラの上方向ベクトル

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		VIEW_ANGLE,			// ビュー平面の視野角
		VIEW_ASPECT,		// ビュー平面のアスペクト比
		VIEW_NEAR_Z,		// ビュー平面のNearZ値
		VIEW_FAR_Z);		// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定(透視変換の設定)
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);
}

Camera* GetCamera(void)
{
	return &g_Camera;
}