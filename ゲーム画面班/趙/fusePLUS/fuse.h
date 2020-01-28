#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <d3dx9.h>
#include "object.h"

#define BLOCK_SIZE (0.2) //���ΐ��̌���
#define BLOCK_LIFE (2000)  //��u���b�N��LIFE

class Fuse
{
public:
	float x, y;
	long int length, type, state;
	DWORD  fire_start_time; //�R���Ďn�߂鎞�_
	DWORD  fire_time; //�R���鎞��
	LPDIRECT3DDEVICE9 Fuse_pDevice;

	Obj Block[10000];

	Obj *head;
	Obj *tail;

	void Init(LPDIRECT3DDEVICE9 pD3D, float s_x, float s_y, int s_length, int s_type);
	void Uninit();
	void Update();
	void Draw();

	int getType();  // 0�@������E�Ɂ@ 1�@�E���獶�Ɂ@2  �������Ɂ@3  �ォ�牺��
	int getState(); //0 �R���ĂȂ��@1 �R����r���@2�@�R���ďI�����
	void setType(int sT_type);  
	void setState(int sS_state); 
	void setTime(DWORD sT_time);
	void setStartTime(DWORD sST_time);
};
