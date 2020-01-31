#pragma once

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"winmm.lib")

#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>

// Direct3D�̏�����
bool MyDirect3D_Initialize(HWND hWnd);
// Direct3D�̏I������
void MyDirect3D_Finalize(void);
// Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);