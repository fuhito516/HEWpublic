
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <d3d9.h>

// �e�N�X�`���Ǘ��ԍ�
enum TextureIndex
{
	// �e�X�g���C�g
	TEXTURE_INDEX_TEST1,
	// �Q�[��
	// �w�i
	TEXTURE_INDEX_BACK1,
	TEXTURE_INDEX_BACK2,
	TEXTURE_INDEX_BACK3,
	TEXTURE_INDEX_BACK4,
	TEXTURE_INDEX_BACK5,
	TEXTURE_INDEX_BACK6,
	TEXTURE_INDEX_BACK7,
	// �L�����N�^�[
	TEXTURE_INDEX_BABY,
	TEXTURE_INDEX_SEIKA,
	TEXTURE_INDEX_YA,
	// �M�~�b�N
	TEXTURE_INDEX_CANDLE1,
	TEXTURE_INDEX_CANDLE2,
	TEXTURE_INDEX_GROUND,
	TEXTURE_INDEX_GOAL1,
	TEXTURE_INDEX_GOAL2,
	TEXTURE_INDEX_GHOST,

	TEXTURE_INDEX_MAX
};

// �e�N�X�`���̓ǂݍ���
//
// �߂�l:�ǂݍ��߂Ȃ�������
//
int Texture_Load(void);

// �e�N�X�`���̉��
void Texture_Release(void);

// �e�N�X�`���C���^�[�t�F�[�X�̎擾
//
// �߂�l:�e�N�X�`���C���^�[�t�F�[�X
//        ���������݂��Ȃ�index���w�肵���ꍇ�ANULL
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);

// �e�N�X�`���𑜓x���̎擾
//
// ���� ... index �e�N�X�`���Ǘ��ԍ�
//
int Texture_GetWidth(TextureIndex index);

// �e�N�X�`���𑜓x�����̎擾
//
// ���� ... index �e�N�X�`���Ǘ��ԍ�
//
int Texture_GetHeight(TextureIndex index);


#endif // TEXTURE_H_