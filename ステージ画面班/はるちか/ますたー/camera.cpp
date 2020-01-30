
#include"camera.h"
#include"player.h"

#include"direct3d.h"
#include"input.h"

cCamera* cCamera::object;

D3DXVECTOR3 cCamera::position;
D3DXVECTOR3	cCamera::lookAt;
D3DXVECTOR3	cCamera::up;

D3DXVECTOR3 cCamera::rotation;
float		cCamera::lengthOfView;

D3DXMATRIX cCamera::viewMatrix;
D3DXMATRIX cCamera::projectionMatrix;

void cCamera::Init()
{
	object = NULL;
	object = new cCamera;

	position = D3DXVECTOR3(0, 1.0f, -30.0f);	// -30
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
	delete object;
	object = NULL;
}
void cCamera::Update()
{
	// プレイヤーを追いかける
	lookAt.x = cPlayer::objects[0]->position.x;
	lookAt.y = cPlayer::objects[0]->position.y;
	position.x = cPlayer::objects[0]->position.x;
	position.y = cPlayer::objects[0]->position.y;

	// 近づく
	if (GetKeyboardPress(DIK_U))
	{
		lengthOfView -= VALUE_DIRECTION_CAMERA;
	}
	// 離れる
	if (GetKeyboardPress(DIK_M))
	{
		lengthOfView += VALUE_DIRECTION_CAMERA;
	}

}
void cCamera::SetCamera()
{

	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	D3DXMatrixIdentity(&viewMatrix);

	D3DXMatrixLookAtLH
	(
		&viewMatrix,
		&position,
		&lookAt,
		&up
	);

	pD3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

	D3DXMatrixIdentity(&projectionMatrix);

	D3DXMatrixPerspectiveFovLH
	(
		&projectionMatrix,
		VIEW_ANGLE,
		VIEW_ASPECT,
		VIEW_NEAR_Z,
		VIEW_FAR_Z
	);

	pD3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}