#pragma once

#include"direct3d.h"
#include"vertex.h"

// ���̐�
#define NUMBER_OF_BRIDGE (1)
// ���̎d�|���̏c���̃T�C�Y
#define BRIDGE_VERTICAL_SIZE	(1.0f)
#define BRIDGE_HORIZONTAL_SIZE	(1.0f)

class cBridge
{
// ���ʕ�
public:

	static cBridge* objects[NUMBER_OF_BRIDGE];

	// �֐�
	static void SetBridge(D3DXVECTOR2 _gimmickPosition, D3DXVECTOR2 _bridgePosition, D3DXVECTOR2 _bridgeSize);
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

// �v�f��
public:

	// �g�p
	bool use;
	// ����
	bool collision;

	D3DXMATRIX	gimmickWorldMatrix;
	D3DXVECTOR3	gimmickPosition;
	D3DXVECTOR3	gimmickRotation;
	D3DXVECTOR3	gimmickScale;

	D3DXMATRIX	bridgeWorldMatrix;
	D3DXVECTOR3	bridgePosition;
	D3DXVECTOR3	bridgeRotation;
	D3DXVECTOR3	bridgeScale;
};