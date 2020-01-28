#ifndef SPRITE_H_
#define SPRITE_H_


#include <d3d9.h>    // D3DCOLOR
#include "texture.h" // TextureIndex


/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/

// �X�v���C�g�|���S���̒��_�J���[�ݒ�
// ��4���_���ׂĂɓ����J���[��ݒ肷��
//
// ���� ... color �ݒ肷��F
void Sprite_SetColor(D3DCOLOR color);

// �X�v���C�g�`��
//
// ����:texture_index	... �e�N�X�`���Ǘ��ԍ�
//      dx				... �`����Wx
//      dy				... �`����Wy
//		width_ratio		... �����䗦
//		height_ratio	... �����䗦
//      u_start			... �e�N�X�`���؂���n�܂�u
//      v_start			... �e�N�X�`���؂���n�܂�v
//      u_finish		... �e�N�X�`���؂���I���u
//      v_finish		... �e�N�X�`���؂���I���v
void Sprite_Draw
(
	TextureIndex texture_index,
	float dx, float dy,
	float width_ratio, float height_ratio,
	float u_start, float v_start, float u_finish, float v_finish
);

void sprite_draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);


void Sprite_animetionDraw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float sx = 1.0f, float sy = 1.0f);

void Sprite_animetion_Alpha_Draw
(TextureIndex texture_index,
	float dx, float dy,
	int tx, int ty,
	int tw, int th,
	float sx, float sy);
void  Sprite_Alpha_Draw(TextureIndex texture_index,
	float dx, float dy,
	int tx, int ty,
	int tw, int th,
	float sx, float sy);

#endif // SPRITE_H_
