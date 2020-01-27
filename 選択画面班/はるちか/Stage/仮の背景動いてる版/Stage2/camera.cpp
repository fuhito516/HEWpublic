
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