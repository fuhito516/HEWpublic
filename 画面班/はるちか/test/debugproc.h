#pragma once

#include<Windows.h>

HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);

void PrintDebugProc(char *fmt,...);	// 任意の場所で描画内容を記述