
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <d3d9.h>

#define SIZE_1024	(1024)
#define SIZE_512	(512)
#define SIZE_256	(256)
#define SIZE_128	(128)
#define SIZE_64		(64)
#define SIZE_2		(2)

// �e�N�X�`���Ǘ��ԍ�
enum TextureIndex
{
	// �V�X�e��
	TEXTURE_INDEX_KOUMEI,
	TEXTURE_INDEX_BABY,
	TEXTURE_INDEX_SEIKA,
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