#pragma once

#include<Windows.h>

HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);

void PrintDebugProc(char *fmt,...);	// �C�ӂ̏ꏊ�ŕ`����e���L�q