
#include"directx.h"
#include"texture.h"

#define TEXTURE_FILENAME_MAX (64) // �e�N�X�`���t�@�C�����ő啶�����i�p�X�ANULL�����܂ށj

// �e�N�X�`���t�@�C���Ǘ��\����
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX]; // �e�N�X�`���t�@�C����
	int width;  // �e�N�X�`���𑜓x����
	int height; // �e�N�X�`���𑜓x�c��

} TextureFile;

// �ǂݍ��݃e�N�X�`�����
static const TextureFile g_TextureFiles[] =
{

	// �V�X�e��
	{ "asset/texture/fade.png",			SIZE_2, SIZE_2},
	{ "asset/texture/blacknumber.png",	SIZE_512, SIZE_256},


	// ����
    { "asset/texture/black.png",	SIZE_1024, SIZE_576 },
	{ "asset/texture/back.png",		SIZE_256, SIZE_64},
	{ "asset/texture/decision.png",	SIZE_256, SIZE_64},


	//�^�C�g��

	//�l��
	{ "asset/texture/people heading.png",		SIZE_256, SIZE_64 },
	{ "asset/texture/people light.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/people ninzu1.png",		SIZE_256, SIZE_256 },
	{ "asset/texture/people ninzu2.png",		SIZE_256, SIZE_256 },
	{ "asset/texture/people ninzu3.png",		SIZE_256, SIZE_256 },
	{ "asset/texture/people ninzu4.png",		SIZE_256, SIZE_256 },

	//�L�����N�^�[
	{ "asset/texture/character heading.png",		SIZE_512, SIZE_64 },
	{ "asset/texture/character light.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character select.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character one.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character two.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character three.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/character four.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/Chara_Beta.png",		        SIZE_256, SIZE_256 },

	//���O

	//��Փx
	{ "asset/texture/difficulty heading.png",		SIZE_256, SIZE_64 },
	{ "asset/texture/difficulty light.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/difficulty easy.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/difficulty normal.png",		    SIZE_256, SIZE_256 },
	{ "asset/texture/difficulty hard.png",		    SIZE_256, SIZE_256 },

	// STAGE
	{ "asset/texture/stage heading.png",	SIZE_256, SIZE_64},
	{ "asset/texture/stage rope.png",		SIZE_64, SIZE_256},
	{ "asset/texture/stage character.png",	SIZE_128, SIZE_128},

};
// �ǂݍ��݃e�N�X�`����
static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);
// static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFiles); // required Windows.h

// �ǂݍ��݃e�N�X�`�����ƃe�N�X�`���Ǘ��ԍ��񋓐��ɍ����������ꍇ�R���p�C���G���[�Ƃ���
static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {}; // �e�N�X�`���C���^�[�t�F�[�X�Ǘ��z��

// �e�N�X�`���̓ǂݍ���
int Texture_Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{

		if (FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i]))) {
			// DebugPrintf("�e�N�X�`���̓ǂݍ��݂Ɏ��s ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

// �e�N�X�`���̉��
void Texture_Release(void)
{
	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{
		if (g_pTextures[i])
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

// �e�N�X�`���C���^�[�t�F�[�X�̎擾
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
	if (index < 0 || index >= TEXTURE_INDEX_MAX)
	{
		return NULL;
	}

	return g_pTextures[index];
}

// �e�N�X�`���𑜓x���̎擾
int Texture_GetWidth(TextureIndex index)
{
	if (index < 0 || index >= TEXTURE_INDEX_MAX)
	{
		return NULL;
	}

	return g_TextureFiles[index].width;
}
// �e�N�X�`���𑜓x�����̎擾
int Texture_GetHeight(TextureIndex index)
{
	if (index < 0 || index >= TEXTURE_INDEX_MAX)
	{
		return NULL;
	}

	return g_TextureFiles[index].height;
}