#pragma once

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"winmm.lib")

#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>

// Direct3Dの初期化
bool MyDirect3D_Initialize(HWND hWnd);
// Direct3Dの終了処理
void MyDirect3D_Finalize(void);
// Direct3Dデバイスポインタの取得
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);