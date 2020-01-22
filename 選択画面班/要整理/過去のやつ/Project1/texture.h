#pragma once

#define SCENE_WIDTH		(1920 / 2)
#define SCENE_HEIGHT	(1080 / 2)
#define SMALL			(256 / 2)

#include <d3d9.h>


/*------------------------------------------------------------------------------
   �e�N�X�`���񋓌^
------------------------------------------------------------------------------*/
// �e�N�X�`���Ǘ��ԍ�
enum TextureIndex
{
	// SCENE
	TEXTURE_SCENE_TITLE,
	TEXTURE_SCENE_PLAYER,
	TEXTURE_SCENE_CHARACTER,
	TEXTURE_SCENE_NAME,
	TEXTURE_SCENE_DIFFICULTY,
	TEXTURE_SCENE_STAGE,
	TEXTURE_SCENE_STAGECHARACTER,
	TEXTURE_SCENE_GAMEOVER,
	TEXTURE_SCENE_AREARANKING,
	TEXTURE_SCENE_STAGECLEAR,
	TEXTURE_SCENE_STAGERANKING,
	TEXTURE_SCENE_SCORETABLE,
	TEXTURE_SCENE_RETURN,

	// �͖�
	TEXTURE_INDEX_BACK,
	TEXTURE_INDEX_KETTEI,
	TEXTURE_INDEX_4PCARSOLU,
	TEXTURE_INDEX_3PCARSOLU,
	TEXTURE_INDEX_2PCARSOLU,
	TEXTURE_INDEX_1PCARSOLU,
	TEXTURE_INDEX_LIGHT,
	TEXTURE_INDEX_SENTAKU,
	TEXTURE_INDEX_BG,

	// ��
	TEXTURE_INDEX_HAIKEI,
	TEXTURE_INDEX_WAKU,
	TEXTURE_INDEX_NANNIDOHAIKEI,
	TEXTURE_INDEX_NANNIDOWAKU,

	TEXTURE_INDEX_FOG,
	TEXTURE_INDEX_BLACK,
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