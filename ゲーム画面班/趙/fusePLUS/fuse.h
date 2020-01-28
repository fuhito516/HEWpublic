#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <d3dx9.h>
#include "object.h"

#define BLOCK_SIZE (0.2) //導火線の厚さ
#define BLOCK_LIFE (2000)  //一つブロックのLIFE

class Fuse
{
public:
	float x, y;
	long int length, type, state;
	DWORD  fire_start_time; //燃えて始める時点
	DWORD  fire_time; //燃える時間
	LPDIRECT3DDEVICE9 Fuse_pDevice;

	Obj Block[10000];

	Obj *head;
	Obj *tail;

	void Init(LPDIRECT3DDEVICE9 pD3D, float s_x, float s_y, int s_length, int s_type);
	void Uninit();
	void Update();
	void Draw();

	int getType();  // 0　左から右に　 1　右から左に　2  下から上に　3  上から下に
	int getState(); //0 燃えてない　1 燃える途中　2　燃えて終わった
	void setType(int sT_type);  
	void setState(int sS_state); 
	void setTime(DWORD sT_time);
	void setStartTime(DWORD sST_time);
};
