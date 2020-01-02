
#include"camera.h"
#include"player.h"

#include"direct3d.h"
#include"input.h"

cCamera* cCamera::object;

D3DXVECTOR3 cCamera::position;	// �J�����̎��_(�ʒu)
D3DXVECTOR3	cCamera::lookAt;	// �J�����̒����_
D3DXVECTOR3	cCamera::up;		// �J�����̏�����x�N�g��

D3DXVECTOR3 cCamera::rotation;		// �J�����̉�]
float		cCamera::lengthOfView;	// �J�����̎��_�ƒ����_�̋���

D3DXMATRIX cCamera::viewMatrix;			// �r���[�}�g���b�N�X
D3DXMATRIX cCamera::projectionMatrix;	// �v���W�F�N�V�����}�g���b�N�X

void cCamera::Init()
{
	object = new cCamera;

	position = D3DXVECTOR3(0, 1.0f, -30.0f);
	lookAt   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	up		 = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
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

	//// ���ړ�
	//if (GetKeyboardPress(DIK_A))
	//{
	//	position.x -= cosf(rotation.y) * VALUE_MOVE_CAMERA;
	//	position.z += sinf(rotation.y) * VALUE_MOVE_CAMERA;

	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// �E�ړ�
	//if (GetKeyboardPress(DIK_D))
	//{
	//	position.x += cosf(rotation.y) * VALUE_MOVE_CAMERA;
	//	position.z -= sinf(rotation.y) * VALUE_MOVE_CAMERA;
	//	
	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// �O�ړ�
	//if (GetKeyboardPress(DIK_W))
	//{
	//	position.x += sinf(rotation.y) * VALUE_MOVE_CAMERA;
	//	position.z += cosf(rotation.y) * VALUE_MOVE_CAMERA;

	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// ��ړ�
	//if (GetKeyboardPress(DIK_S))
	//{
	//	position.x -= sinf(rotation.y) * VALUE_MOVE_CAMERA;
	//	position.z -= cosf(rotation.y) * VALUE_MOVE_CAMERA;

	//	lookAt.x = position.x + sinf(rotation.y) * lengthOfView;
	//	lookAt.z = position.z + cosf(rotation.y) * lengthOfView;
	//}
	//// ��ړ�
	//if (GetKeyboardPress(DIK_SPACE))
	//{
	//	position.y += VALUE_MOVE_CAMERA;
	//	lookAt.y  += VALUE_MOVE_CAMERA;
	//}
	//// ���ړ�
	//if (GetKeyboardPress(DIK_LCONTROL))
	//{
	//	position.y -= VALUE_MOVE_CAMERA;
	//	lookAt.y  -= VALUE_MOVE_CAMERA;
	//}

	//// �����_������
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
	//// �����_�E����
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
	//// �����_��ړ�
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	lookAt.y += VALUE_MOVE_CAMERA * 2;
	//}
	//// �����_���ړ�
	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	lookAt.y -= VALUE_MOVE_CAMERA * 2;
	//}

	// �v���C���[��ǂ�������(���ɂP�v���C���[��ǂ�)
	lookAt.x = cPlayer::numberOfObjects[0]->position.x;
	lookAt.y = cPlayer::numberOfObjects[0]->position.y;
	position.x = cPlayer::numberOfObjects[0]->position.x;
	position.y = cPlayer::numberOfObjects[0]->position.y;

	// �߂Â�
	if (GetKeyboardPress(DIK_U))
	{
		lengthOfView -= VALUE_MOVE_CAMERA;
	}
	// �����
	if (GetKeyboardPress(DIK_M))
	{
		lengthOfView += VALUE_MOVE_CAMERA;
	}

}
void cCamera::SetCamera()
{

	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&viewMatrix);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH
	(
		&viewMatrix,
		&position,		// �J�����̈ʒu
		&lookAt,		// �J�����̒����_
		&up				// �J�����̏�����x�N�g��
	);

	// �r���[�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&projectionMatrix);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH
	(
		&projectionMatrix,
		VIEW_ANGLE,			// �r���[���ʂ̎���p
		VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z			// // �r���[���ʂ�FarZ�l
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�(�����ϊ��̐ݒ�)
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

}