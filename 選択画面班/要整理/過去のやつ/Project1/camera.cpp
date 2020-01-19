#include "camera.h"
#include "input.h"


static Camera mainCamera;
static D3DXMATRIX g_mtxView;

static float k = 0.5;

D3DXMATRIX mtx_Cam_Trs, mtx_Cam_Rot;
D3DXVECTOR3 g_Cam_pos;


D3DXVECTOR3 Vy = D3DXVECTOR3(0, 1, 0);
D3DXVECTOR3 Vk;
static float g_Cam_rot= 0.03f;
static float rot_k = 1;



void InitializeCamera()
{

	mainCamera.Eye = D3DXVECTOR3(0, 0, -90.0f);
	mainCamera.At = D3DXVECTOR3(0, 0, 0);
	mainCamera.Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&g_mtxView,
		&mainCamera.Eye,
		&mainCamera.At,
		&mainCamera.Up);
}

void UpdateCamera()
{

	D3DXMatrixTranslation(&mtx_Cam_Trs, 0, 0, 0);
	D3DXMatrixRotationYawPitchRoll(&mtx_Cam_Rot, 0, 0, 0);
	if (Keyboard_IsPress(DIK_NUMPAD9))
	{
		D3DXMatrixLookAtLH(&g_mtxView,
			&mainCamera.Eye,
			&mainCamera.At,
			&mainCamera.Up);
	}

	D3DXVECTOR3 Target = mainCamera.At - mainCamera.Eye;
	D3DXVECTOR3 Target_k = Target;

	if (Keyboard_IsPress(DIK_NUMPAD3))
	{
		D3DXVec3Cross(&Vk, &Target, &Vy);
		D3DXVec3Normalize(&Vk, &Vk);
		//mainCamera.Eye -= Vk/2;
		mainCamera.At -= Vk/2;
	}
	if (Keyboard_IsPress(DIK_NUMPAD1))
	{
		D3DXVec3Cross(&Vk, &Target, &Vy);
		D3DXVec3Normalize(&Vk, &Vk);
		//mainCamera.Eye += Vk / 2;
		mainCamera.At += Vk / 2;
	}
	if (Keyboard_IsPress(DIK_NUMPAD0))
	{
		Vk = D3DXVECTOR3(Target.x, 0, Target.z);
		D3DXVec3Normalize(&Vk, &Vk);
		//mainCamera.Eye -= Vk / 2;
		mainCamera.At -= Vk / 2;
	}
	if (Keyboard_IsPress(DIK_NUMPAD2))
	{
		Vk = D3DXVECTOR3(Target.x, 0, Target.z);
		D3DXVec3Normalize(&Vk, &Vk);
		//mainCamera.Eye += Vk / 2;
		mainCamera.At += Vk / 2;
	}
	if (Keyboard_IsPress(DIK_NUMPAD4))
	{
		D3DXMatrixRotationYawPitchRoll(&mtx_Cam_Rot, -g_Cam_rot, 0, 0);
	}
	if (Keyboard_IsPress(DIK_NUMPAD6))
	{
		D3DXMatrixRotationYawPitchRoll(&mtx_Cam_Rot, g_Cam_rot, 0, 0);
	}
	if (Keyboard_IsPress(DIK_NUMPAD8))
	{
		if ((Target.x == 0) && (Target.z == 0)) {
			D3DXMatrixRotationYawPitchRoll(&mtx_Cam_Rot, 0, 0, 0);
		}
		else {
			D3DXVec3Cross(&Vk, &Target, &Vy);
			D3DXMatrixRotationAxis(&mtx_Cam_Rot, &Vk, g_Cam_rot*rot_k);
		}
	}
	if (Keyboard_IsPress(DIK_NUMPAD5))
	{
		if ((Target.x == 0) && (Target.z == 0)) {
			D3DXMatrixRotationYawPitchRoll(&mtx_Cam_Rot, 0, 0, 0);
		}
		else {
			D3DXVec3Cross(&Vk, &Target, &Vy);
			D3DXMatrixRotationAxis(&mtx_Cam_Rot, &Vk, -g_Cam_rot * rot_k);
		}
	}
	D3DXVec3TransformCoord(&Target, &Target, &mtx_Cam_Rot);
	mainCamera.Eye = mainCamera.At - Target;
	D3DXMatrixLookAtLH(&g_mtxView,
		&mainCamera.Eye,
		&mainCamera.At,
		&mainCamera.Up);

	if (Keyboard_IsPress(DIK_NUMPAD9))
	{
		InitializeCamera();
	}
	//D3DXMatrixMultiply(&g_mtxView, &g_mtxView, &mtx_Cam_Trs);
}

D3DXMATRIX GetCamera_mtx()
{
	return g_mtxView;
}
