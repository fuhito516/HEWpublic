
#include"camera.h"
#include"player.h"

#include"direct3d.h"
#include"input.h"

cCamera* cCamera::object;

D3DXVECTOR3 cCamera::position;	// カメラの視点(位置)
D3DXVECTOR3	cCamera::lookAt;	// カメラの注視点
D3DXVECTOR3	cCamera::up;		// カメラの上方向ベクトル

D3DXVECTOR3 cCamera::rotation;		// カメラの回転
float		cCamera::lengthOfView;	// カメラの視点と注視点の距離

D3DXMATRIX cCamera::viewMatrix;			// ビューマトリックス
D3DXMATRIX cCamera::projectionMatrix;	// プロジェクションマトリックス

void cCamera::Init()
{
	object = new cCamera;

	position = D3DXVECTOR3(0, 1.0f, -30.0f);
	lookAt   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	up		 = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離を計算
	float vectorX, vectorZ;
	vectorX = position.x - lookAt.x;
	vectorZ = position.z - lookAt.z;
	lengthOfView = sqrtf(vectorX * vectorX + vectorZ * vectorZ);

}
void cCamera::Uninit()
{

}
void cCamera::Update()
{

	//// 左移動
	//if (GetKeyboardPress(DIK_A))
	//{
	//	position.x -= cosf(rotation.y) * VALUE_MOVE_CAMERA;
	//	position.z += sinf(rotation.y) * VALUE_MOVE_CAMERA;

	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// 右移動
	//if (GetKeyboardPress(DIK_D))
	//{
	//	position.x += cosf(rotation.y) * VALUE_MOVE_CAMERA;
	//	position.z -= sinf(rotation.y) * VALUE_MOVE_CAMERA;
	//	
	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// 前移動
	//if (GetKeyboardPress(DIK_W))
	//{
	//	position.x += sinf(rotation.y) * VALUE_MOVE_CAMERA;
	//	position.z += cosf(rotation.y) * VALUE_MOVE_CAMERA;

	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// 後移動
	//if (GetKeyboardPress(DIK_S))
	//{
	//	position.x -= sinf(rotation.y) * VALUE_MOVE_CAMERA;
	//	position.z -= cosf(rotation.y) * VALUE_MOVE_CAMERA;

	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// 上移動
	//if (GetKeyboardPress(DIK_SPACE))
	//{
	//	position.y += VALUE_MOVE_CAMERA;
	//	lookAt.y  += VALUE_MOVE_CAMERA;
	//}
	//// 下移動
	//if (GetKeyboardPress(DIK_LCONTROL))
	//{
	//	position.y -= VALUE_MOVE_CAMERA;
	//	lookAt.y  -= VALUE_MOVE_CAMERA;
	//}

	//// 注視点左旋回
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	rotation.y -= VALUE_ROTATE_CAMERA;
	//	if (rotation.y < -D3DX_PI)
	//	{
	//		rotation.y += D3DX_PI * 2.0f;
	//	}

	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// 注視点右旋回
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	rotation.y += VALUE_ROTATE_CAMERA;
	//	if (rotation.y > D3DX_PI)
	//	{
	//		rotation.y -= D3DX_PI * 2.0f;
	//	}

	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// 注視点上移動
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	lookAt.y += VALUE_MOVE_CAMERA * 2;
	//}
	//// 注視点下移動
	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	lookAt.y -= VALUE_MOVE_CAMERA * 2;
	//}

	// プレイヤーを追いかける(仮に１プレイヤーを追う)
	lookAt.x = cPlayer::numberOfObjects[0]->position.x;
	lookAt.y = cPlayer::numberOfObjects[0]->position.y;
	position.x = cPlayer::numberOfObjects[0]->position.x;
	position.y = cPlayer::numberOfObjects[0]->position.y;

	// 近づく
	if (GetKeyboardPress(DIK_U))
	{
		lengthOfView -= VALUE_MOVE_CAMERA;
	}
	// 離れる
	if (GetKeyboardPress(DIK_M))
	{
		lengthOfView += VALUE_MOVE_CAMERA;
	}

}
void cCamera::SetCamera()
{

	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&viewMatrix);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH
	(
		&viewMatrix,
		&position,		// カメラの位置
		&lookAt,		// カメラの注視点
		&up				// カメラの上方向ベクトル
	);

	// ビューマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&projectionMatrix);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH
	(
		&projectionMatrix,
		VIEW_ANGLE,			// ビュー平面の視野角
		VIEW_ASPECT,		// ビュー平面のアスペクト比
		VIEW_NEAR_Z,		// ビュー平面のNearZ値
		VIEW_FAR_Z			// // ビュー平面のFarZ値
	);

	// プロジェクションマトリックスの設定(透視変換の設定)
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

}