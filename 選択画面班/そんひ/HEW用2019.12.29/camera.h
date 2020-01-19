#pragma once

#include"directx.h"
#include"common.h"

// �J�����̏����ʒu�ƃp�����[�^
#define	POS_X_CAM		(0.0f)
#define	POS_Y_CAM		(0.0f)
#define	POS_Z_CAM		(-20.0f)
#define	VALUE_MOVE_CAMERA	(0.2f)				// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.008f)	// �J�����̉�]��

// �v���W�F�N�V�����p�p�����[�^
#define VIEW_ANGLE (D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define VIEW_ASPECT ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)		// �r���[���ʂ̃A�X�y�N�g��
#define VIEW_NEAR_Z (1.0f)											// �r���[���ʂ�NearZ�l
#define VIEW_FAR_Z (1000.0f)										// �r���[���ʂ�FarZ�l

#define CAMERA_SPEED (0.2f)

class Camera
{
public:

	D3DXVECTOR3			pos;			// �J�����̎��_(�ʒu)
	D3DXVECTOR3			at;				// �J�����̒����_
	D3DXVECTOR3			up;				// �J�����̏�����x�N�g��
	D3DXVECTOR3			rot;			// �J�����̉�]
	float				len;			// �J�����̎��_�ƒ����_�̋���

	D3DXMATRIX			mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX			mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X

	void InitCamera(void);
	void UninitCamera(void);
	void UpdateCamera(void);
	void SetCamera();

};

Camera* GetCamera();