//זג
#include "fuse.h"
#include "camera.h"
#include "debugproc.h"

//static LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
static LPDIRECT3DTEXTURE9	g_p;

void Fuse::Init(LPDIRECT3DDEVICE9 pD3D, float s_x, float s_y, int s_length, int s_type)
{
	type = s_type;
	float l_size = s_length * BLOCK_SIZE;
	int i;
	Fuse_pDevice = pD3D;
	for (i = 0; i < s_length; i++)
	{
		Block[i].Init(pD3D, BLOCK_SIZE, BLOCK_SIZE, 1);
		Block[i].Move(s_x, s_y, 0);
		D3DXCreateTextureFromFile(pD3D, "asset/texture/fuse_0.png", &g_p);
		Block[i].setT(g_p);
		Block[i].setType(5);
	}
	head = &Block[0];
	length = s_length;
	tail = &Block[length-1];
	state = 0;
	switch (s_type)
	{
	case 0:
	{
		for (i = 0; i < s_length; i++)
		{
			Block[i].Move(- l_size / 2 + i * BLOCK_SIZE, 0, 0);
		}
		break;
	}
	case 1:
	{
		for (i = 0; i < s_length; i++)
		{
			Block[i].Move(l_size / 2 - i * BLOCK_SIZE, 0, 0);
		}
		break;
	}
	case 2:
	{
		for (i = 0; i < s_length; i++)
		{
			Block[i].Move(0, - l_size / 2 + i * BLOCK_SIZE, 0);
		}
		break;
	}
	case 3:
	{
		for (i = 0; i < s_length; i++)
		{
			Block[i].Move(0, l_size / 2 - i * BLOCK_SIZE, 0);
		}
		break;
	}
	}
}

void Fuse::Uninit()
{
}

void Fuse::Update() 
{
	
	DWORD now;
	now = GetTickCount();
	long int kk = (now - fire_start_time) * length / fire_time;
	if (kk > length) kk = length;
	for (long int i = 0; i < kk; i++)
	{
		
		if ((Block[i].getType() == 6) && (now - fire_start_time - i * fire_time / length >= BLOCK_LIFE))
		{
			D3DXCreateTextureFromFile(Fuse_pDevice, "asset/texture/fuse_2.png", &g_p);
			Block[i].setT(g_p);
			Block[i].setType(7);
			if (i == length - 1) state = 2;
		}
		else if (Block[i].getType() == 5)
		{
			D3DXCreateTextureFromFile(Fuse_pDevice, "asset/texture/fuse_1.png", &g_p);
			Block[i].setT(g_p);
			Block[i].setType(6);
		}
	}
}

void Fuse::Draw()
{
	for (int i = 0; i < length; i++)
	{
		Block[i].Draw();
	}
}

int Fuse::getType()
{
	return type;
}

int Fuse::getState()
{
	return state;
}

void Fuse::setType(int sT_type) 
{
	type = sT_type;
}

void Fuse::setState(int sS_state)
{
	state = sS_state;
}

void Fuse::setTime(DWORD sT_time)
{
	fire_time = sT_time;
}

void Fuse::setStartTime(DWORD sST_time)
{
	fire_start_time = sST_time;
	state = 1;
}
