#pragma once

#include <Windows.h>
#include <d3d9.h>

// Direct3D�̏�����
bool MyDirect3D_Initialize(HWND hWnd);	// �߂�l:�������Ɏ��s������false
// Direct3D�̏I������
void MyDirect3D_Finalize(void);
// Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);