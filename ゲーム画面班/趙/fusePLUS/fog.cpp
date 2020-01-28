#include "fog.h"

struct Vertex
{
	float x, y, z; // Position
	float u, v;	// Texture coordinates
};
using namespace std;

static LPDIRECT3DDEVICE9       Fog_pd3dDevice = NULL;// Our rendering device
static float baceKesu, kesu, k1, k2;
static 	LPDIRECT3DTEXTURE9	g_p;
static D3DXMATRIX matTexture;
static float size_change = 0.1f;

void Fog::Init(LPDIRECT3DDEVICE9 pD3D, float w, float h, float d)
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
	Fog_pd3dDevice = pD3D;
	Fog_pd3dDevice->CreateVertexBuffer(4 * sizeof(Vertex), D3DUSAGE_WRITEONLY,
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

	D3DXCreateTextureFromFile(Fog_pd3dDevice, "asset/texture/111.png", &g_p);
	for (int i = 1; i <= 7; i++)
	{
		Fog_pd3dDevice->SetTexture(i, g_p);
	}
	baceKesu = kesu = INITIAL_SIZE_KESU;
	D3DXMatrixIdentity(&matTexture);
	matTexture._11 = width / kesu;
	matTexture._22 = height / kesu;
	k1 = matTexture._11 / width;
	k2 = matTexture._22 / height;
}

void Fog::Move(float m_x, float m_y, float m_z) //ˆÚ“®
{
	x += m_x;
	y += m_y;
	z += m_z;
	D3DXMatrixTranslation(&mtxTrs, x, y, z);
}

void Fog::Rotation(float r_x, float r_y, float r_z) //‰ñ“]
{
	rx += r_x;
	ry += r_y;
	rz += r_z;
	D3DXMatrixRotationYawPitchRoll(&mtxRot, ry, rx, rz);
}

void Fog::Zoom(float s_x, float s_y, float s_z) //•ÏŒ`
{
	sx *= s_x;
	sy *= s_y;
	sz *= s_z;
	D3DXMatrixScaling(&mtxScl, sx, sy, sz);
}

void Fog::setType(int t)
{
	type = t;
}

void Fog::setGravity(float g)
{
	gravity = g;
}
void Fog::setT(LPDIRECT3DTEXTURE9 g_T)
{
	g_pTexture = g_T;
}
void Fog::setRB(int rr)
{
	RB = rr;
}

void Fog::Draw()
{
	Fog_pd3dDevice->BeginScene();
	Fog_pd3dDevice->SetTexture(0, g_pTexture);
	Fog_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	Fog_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

	for (int i = 0; i < Light_count; i++)
	{
		matTexture._31 = ((x - width / 2) - Light[i].x + kesu / 2)  * k1;
		matTexture._32 = -((y - height / 2) - Light[i].y + height - kesu / 2) * k2;
		Fog_pd3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)(i+17), &matTexture);
		Fog_pd3dDevice->SetTextureStageState(i + 1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		Fog_pd3dDevice->SetTextureStageState(i + 1, D3DTSS_TEXCOORDINDEX, 0);
		Fog_pd3dDevice->SetTextureStageState(i + 1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
		Fog_pd3dDevice->SetTextureStageState(i + 1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		Fog_pd3dDevice->SetTextureStageState(i + 1, D3DTSS_COLORARG2, D3DTA_CURRENT);
		Fog_pd3dDevice->SetTextureStageState(i + 1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	}

	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrs);
	Fog_pd3dDevice->SetStreamSource(0, g_pD3DVtxBuff, 0, sizeof(Vertex));
	Fog_pd3dDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	Fog_pd3dDevice->SetFVF(Vertex_FVF);

	// Draw quad
	Fog_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	Fog_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	Fog_pd3dDevice->EndScene();

}

int Fog::getLC()
{

	return Light_count;

}
void Fog::setLC(int k)
{

	Light_count = k;

}
void Fog::setL(int k, float l_x, float l_y)
{

	Light[k].x = l_x;
	Light[k].y = l_y;

}

float Fog::GetBACEKESU()
{
	float f = baceKesu;

	return f;
}
void Fog::ChangeSize(float _baceKesu)
{
	baceKesu = _baceKesu;
}

void Fog::Update()
{
	if ((kesu > baceKesu + 3) || (kesu < baceKesu - 3))
	{
		size_change *= -1;
	}
	/*if ((kesu > 30) || (kesu < 20))
	{
		size_change *= -1;
	}*/
	kesu += size_change;
	matTexture._11 = width / kesu;
	matTexture._22 = height / kesu;
	k1 = matTexture._11 / width;
	k2 = matTexture._22 / height;
}
