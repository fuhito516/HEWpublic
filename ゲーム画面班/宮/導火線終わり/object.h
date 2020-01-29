#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <d3dx9.h>

struct OBJ_XY
{
	float x, y;
};

struct Vertex
{
	float x, y, z; // Position
	float u, v;	// Texture coordinates
};

#define Vertex_FVF D3DFVF_XYZ | D3DFVF_TEX1

class Obj
{
private:
	float x, y, z, height, width, deep, rx, ry, rz, sx, sy, sz;
	int type;
	float gravity;
	int RB;
	LPDIRECT3DTEXTURE9	g_pTexture;
	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff;
	D3DXMATRIX mtxScl, mtxRot, mtxTrs, mtxWorld;
	// Ç›Ç‚í«â¡
	bool jump;
	float jumpPow;
public:
	void Init(LPDIRECT3DDEVICE9 pD3D, float h, float w, float d); //èâä˙âª
	void Move(float m_x, float m_y, float m_z); //à⁄ìÆ
	void Rotation(float r_x, float r_y, float r_z); //âÒì]
	void Zoom(float s_x, float s_y, float s_z); //ïœå`
	void setType(int t);
	void setGravity(float g);
	void setT(LPDIRECT3DTEXTURE9 g_T);
	void setRB(int rr);
	void Draw(); //ï`âÊ
	OBJ_XY getXY();
	int getType();
	void Update();
};