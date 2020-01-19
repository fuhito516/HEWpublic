#pragma once

#include"common.h"
#include"direct3d.h"

// �J�����̃p�����[�^
#define	VALUE_MOVE_CAMERA	(0.2f)				// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.008f)	// �J�����̉�]��

// �v���W�F�N�V�����p�p�����[�^
#define VIEW_ANGLE (D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define VIEW_ASPECT ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)		// �r���[���ʂ̃A�X�y�N�g��
#define VIEW_NEAR_Z (1.0f)											// �r���[���ʂ�NearZ�l
#define VIEW_FAR_Z (1000.0f)										// �r���[���ʂ�FarZ�l

class cCamera
{
public:

	static cCamera* object;

	static D3DXVECTOR3 position;	// �J�����̎��_(�ʒu)
	static D3DXVECTOR3 lookAt;		// �J�����̒����_
	static D3DXVECTOR3 up;			// �J�����̏�����x�N�g��

	static D3DXVECTOR3 rotation;		// �J�����̉�]
	static float	   lengthOfView;	// �J�����̎��_�ƒ����_�̋���

	static D3DXMATRIX viewMatrix;		// �r���[�}�g���b�N�X
	static D3DXMATRIX projectionMatrix;	// �v���W�F�N�V�����}�g���b�N�X

	// �֐�
	static void Init();
	static void Uninit();
	static void Update();
	static void SetCamera();

};