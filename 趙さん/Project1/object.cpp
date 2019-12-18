#include "object.h"
#include "input.h"

using namespace std;

static LPDIRECT3DDEVICE9       obj_pd3dDevice = NULL;	// Our rendering device

OBJ_XY posPlayer1;
bool throwingPlayer1 = false;
float throwingPow = 0;

void Obj::Init(LPDIRECT3DDEVICE9 pD3D, float w, float h, float d)
{
	Vertex Quad[] =
	{
		{ -w/2, -h/2, d/2, 0.0f,  1.0f },  // 0
		{ -w/2,  h/2, d/2, 0.0f,  0.0f },  // 1
		{ w/2, -h/2, d/2, 1.0f,  1.0f },  // 3
		{ w/2,  h/2, d/2, 1.0f,  0.0f },  // 2
	};
	height = h;
	width = w;
	deep = d;
	obj_pd3dDevice = pD3D;
	obj_pd3dDevice->CreateVertexBuffer(4 * sizeof(Vertex), D3DUSAGE_WRITEONLY,
		Vertex_FVF, D3DPOOL_MANAGED, &g_pD3DVtxBuff, NULL);
	Vertex* v;
	g_pD3DVtxBuff->Lock(0, 0, (void**)&v, 0);
	memcpy(v, Quad, 4 * sizeof(Vertex));
	g_pD3DVtxBuff->Unlock();
	x = 0;
	y = 0;
	z = 0;
	rx = 0;
	ry = 0;
	rz = 0;
	sx = 1;
	sy = 1;
	sz = 1;
	D3DXMatrixTranslation(&mtxTrs, x, y, z);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, ry, rx, rz);
	D3DXMatrixScaling(&mtxScl, sx, sy, sz);

	// ‚Ý‚â’Ç‰Á
	jump = false;
	jumpPow = 0;
}

void Obj::Move(float m_x, float m_y, float m_z) //ˆÚ“®
{
	x += m_x;
	y += m_y;
	z += m_z;
	D3DXMatrixTranslation(&mtxTrs, x, y, z);
}

void Obj::Rotation(float r_x, float r_y, float r_z) //‰ñ“]
{
	rx += r_x;
	ry += r_y;
	rz += r_z;
	D3DXMatrixRotationYawPitchRoll(&mtxRot, ry, rx, rz);
}

void Obj::Zoom(float s_x, float s_y, float s_z) //•ÏŒ`
{
	sx *= s_x;
	sy *= s_y;
	sz *= s_z;
	D3DXMatrixScaling(&mtxScl, sx, sy, sz);
}

void Obj::setType(int t)
{
	type = t;
}

void Obj::setGravity(float g)
{
	gravity = g;
}
void Obj::setT(LPDIRECT3DTEXTURE9 g_T)
{
	g_pTexture = g_T;
}
void Obj::setRB(int rr)
{
	RB = rr;
}

void Obj::Draw()
{
	obj_pd3dDevice->BeginScene();

	obj_pd3dDevice->SetTexture(0, g_pTexture);
	obj_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	obj_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrs);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrs);
	//obj_pd3dDevice->SetTextureStageState(0,
	//	D3DTSS_TEXTURETRANSFORMFLAGS,
	//	D3DTTFF_COUNT2);
	obj_pd3dDevice->SetStreamSource(0, g_pD3DVtxBuff, 0, sizeof(Vertex));
	obj_pd3dDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	obj_pd3dDevice->SetFVF(Vertex_FVF);

	// Draw quad
	obj_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	obj_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	obj_pd3dDevice->EndScene();
}

OBJ_XY Obj::getXY()
{
	OBJ_XY NewXY;
	NewXY.x = x;
	NewXY.y = y;
	return NewXY;
}


int Obj::getType()
{
	return type;
}

void Obj::Update()
{
	if (type == 1)
	{
		if (Keyboard_IsPress(DIK_LEFT) || Keyboard_IsPress(DIK_A))
		{
			Move(-0.6f, 0, 0);
		}
		if (Keyboard_IsPress(DIK_RIGHT) || Keyboard_IsPress(DIK_D))
		{
			Move(0.6f, 0, 0);
		}
		if (Keyboard_IsPress(DIK_UP) || Keyboard_IsPress(DIK_SPACE))
		{
			if (!jump)
			{
				jump = true;
				jumpPow = 3;
			}
		}
		if (Keyboard_IsPress(DIK_DOWN))
		{
			Move(0, -0.5, 0);
		}
		if (Keyboard_IsPress(DIK_K))
		{
			if (!throwingPlayer1)
			{
				throwingPlayer1 = true;
				throwingPow = 3;
			}
		}

		if (jump)
		{
			Move(0, jumpPow - gravity, 0);
			jumpPow -= 0.1f;
		}
		if (y - 3 < 0)
		{
			jump = false;
			jumpPow = 0;
			Move(0, 3 - y, 0);
		}

		if (throwingPlayer1)
		{
			
		}

		posPlayer1 = getXY();
	}
	else if (type == 3)
	{
		if (!throwingPlayer1)
		{
			x = posPlayer1.x + 1;
			y = posPlayer1.y + 1;
			D3DXMatrixTranslation(&mtxTrs, x, y, z);
		}
		else
		{
			Move(0, throwingPow - gravity, 0);
			throwingPow -= 0.05f;
		}

		if (y - 2 < 0)
		{
			throwingPlayer1 = false;
			throwingPow = 0;
			Move(0, 2 - y, 0);
		}
	}
	else
	{
		return;
	}
}