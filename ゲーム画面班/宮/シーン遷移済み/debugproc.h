#pragma once

#include<Windows.h>

HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);

void PrintDebugProc(char *fmt,...);	// ”CˆÓ‚ÌêŠ‚Å•`‰æ“à—e‚ğ‹Lq