

#include <d3dx9.h>
#include <math.h>
#include "direct3d.h"
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

/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

// �X�v���C�g�|���S���̒��_�J���[�ݒ�
void Sprite_SetColor(D3DCOLOR color)
{
	g_Color = color;
}


// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
void Sprite_Draw
	(
		TextureIndex texture_index,
		float dx, float dy,
		float width_ratio, float height_ratio,
		float u_start, float v_start, float u_finish, float v_finish
	)
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();
	if (!pD3DDevice) return;

	float w = Texture_GetWidth(texture_index) * width_ratio;
	float h = Texture_GetHeight(texture_index) * height_ratio;

	// �Y��������ꍇ(-0.5f)���e�����ɕt����
	Vertex2D vertexes[] =
	{
		{ D3DXVECTOR4(dx - (w * (u_finish - u_start)) / 2, dy - (h * (v_finish - v_start)) / 2, 0.0f, 1.0f),
		g_Color, D3DXVECTOR2(u_start, v_start) },
		{ D3DXVECTOR4(dx + (w * (u_finish - u_start)) / 2, dy - (h * (v_finish - v_start)) / 2, 0.0f, 1.0f),
		g_Color, D3DXVECTOR2(u_finish, v_start) },
		{ D3DXVECTOR4(dx - (w * (u_finish - u_start)) / 2, dy + (h * (v_finish - v_start)) / 2, 0.0f, 1.0f),
		g_Color, D3DXVECTOR2(u_start, v_finish) },
		{ D3DXVECTOR4(dx + (w * (u_finish - u_start)) / 2, dy + (h * (v_finish - v_start)) / 2, 0.0f, 1.0f),
		g_Color, D3DXVECTOR2(u_finish, v_finish) }
	};

	pD3DDevice->SetFVF(FVF_VERTEX2D);
	pD3DDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}
