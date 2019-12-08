
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

	// ���_�ƒ����_�̋������v�Z
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
		// ���ړ�
		g_Camera.pos.x -= cosf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		g_Camera.pos.z += sinf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}
	if (GetKeyboardPress(DIK_D))
	{
		// �E�ړ�
		g_Camera.pos.x += cosf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		g_Camera.pos.z -= sinf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		
		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}
	if (GetKeyboardPress(DIK_W))
	{
		// �O�ړ�
		g_Camera.pos.x += sinf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;
		g_Camera.pos.z += cosf(g_Camera.rot.y) * VALUE_MOVE_CAMERA;

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}
	if (GetKeyboardPress(DIK_S))
	{
		// ��ړ�
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
		// �����_����u���v
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
		// �����_����u�E�v
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
		// �����_�ړ��u��v
		g_Camera.at.y += VALUE_MOVE_CAMERA * 2;
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		// �����_�ړ��u���v
		g_Camera.at.y -= VALUE_MOVE_CAMERA * 2;
	}

	if (GetKeyboardPress(DIK_U))
	{
		// �߂Â�
		g_Camera.len -= VALUE_MOVE_CAMERA;
	}
	if (GetKeyboardPress(DIK_M))
	{
		// �����
		g_Camera.len += VALUE_MOVE_CAMERA;
	}

}
void Camera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
		&g_Camera.pos,		// �J�����̎��_(�ʒu)
		&g_Camera.at,		// �J�����̒����_
		&g_Camera.up);		// �J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		VIEW_ANGLE,			// �r���[���ʂ̎���p
		VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�(�����ϊ��̐ݒ�)
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);
}

Camera* GetCamera(void)
{
	return &g_Camera;
}