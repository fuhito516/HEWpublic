
#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <d3d9.h>
#define FIREPOS_X	(800)
#define FIREPOS_Y	(40)
#define KETTEIPOS_X (SCREEN_WIDTH/2)
#define KETTEIPOS_Y	(SCREEN_HEIGHT/2+200)

#define M_KIHONTEXTURE_W	(256)
#define M_KIHONTEXTURE_H	(256)
#define S_KIHONTEXTURE_H	(128)
#define	S_KIHONTEXTURE_W	(128)

/*------------------------------------------------------------------------------
   �e�N�X�`���񋓌^
------------------------------------------------------------------------------*/
// �e�N�X�`���Ǘ��ԍ�
typedef enum TextureIndex
{
	TEXTURE_INDEX_BG,
	TEXTURE_INDEX_UNKO,
	TEXTURE_INDEX_PURESENTER,
    TEXTURE_INDEX_TITLE,

    TEXTURE_INDEX_MAX
};


/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/
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
