#pragma once

#include <Windows.h>
#include <d3d9.h>

// Direct3Dの初期化
bool MyDirect3D_Initialize(HWND hWnd);	// 戻り値:初期化に失敗したらfalse
// Direct3Dの終了処理
void MyDirect3D_Finalize(void);
// Direct3Dデバイスポインタの取得
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);