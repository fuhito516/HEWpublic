
#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"


/*------------------------------------------------------------------------------
�\���̐錾
------------------------------------------------------------------------------*/
// �QD�|���S�����_�\����
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 position; // ���_���W�i���W�ϊ��ςݒ��_�j
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // �QD�|���S�����_�t�H�[�}�b�g


/*------------------------------------------------------------------------------
�O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static D3DCOLOR g_Color = 0xffffffff;
// static D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);

static float sx = 0.01f;
static float sy = 0.01f;

/*------------------------------------------------------------------------------
�֐���`
------------------------------------------------------------------------------*/

//// �X�v���C�g�|���S���̒��_�J���[�ݒ�
//void Sprite_SetColor(D3DCOLOR color)
//{
//	g_Color = D3DCOLOR_RGBA(255, 0, 0, 255);
//}


// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
void Sprite_animetionDraw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float sx, float sy)
{
	

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	// UV���W�v�Z
	float u[2], v[2];


	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

	float dw, dh;
	dw = tw * sx;
	dh = th * sy;

	Vertex2D vertexes[] = {

	{ D3DXVECTOR4(dx - dw / 2, dy - dh / 2, 0, 1), g_Color, D3DXVECTOR2(u[0], v[0]) },
	{ D3DXVECTOR4(dx + dw / 2, dy - dh / 2, 0, 1), g_Color, D3DXVECTOR2(u[1], v[0]) },
	{ D3DXVECTOR4(dx - dw / 2, dy + dh / 2, 0, 1), g_Color, D3DXVECTOR2(u[0], v[1]) },
	{ D3DXVECTOR4(dx + dw / 2, dy + dh / 2, 0, 1), g_Color, D3DXVECTOR2(u[1], v[1]) },
	};


	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}
