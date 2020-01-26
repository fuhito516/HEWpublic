
#include"direct3d.h"
#include"texture.h"

#include"common.h"

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
	// �e�X�g���C�g
	{ "asset/texture/test1.png",	SCREEN_WIDTH * 2, SCREEN_WIDTH},
	// �w�i
	{ "asset/texture/back/back1.png",	SCREEN_WIDTH, SCREEN_HEIGHT / 2},
	{ "asset/texture/back/back2.png",	256, 256},
	{ "asset/texture/back/back3.png",	SCREEN_WIDTH, SCREEN_HEIGHT / 2},
	{ "asset/texture/back/back4.png",	SCREEN_WIDTH, SCREEN_HEIGHT / 2},
	{ "asset/texture/back/back5.png",	256, 256},
	{ "asset/texture/back/back6.png",	SCREEN_WIDTH, SCREEN_HEIGHT / 2},
	{ "asset/texture/back/back7.png",	SCREEN_WIDTH, SCREEN_HEIGHT / 2},
	// �L�����N�^�[
	{ "asset/texture/baby.png",		128, 128},
	{ "asset/texture/seika.png",	64, 64},
	{ "asset/texture/ya.png",	512, 256},
	// �M�~�b�N
	{ "asset/texture/candle1.png",	128, 128},
	{ "asset/texture/candle2.png",	128, 128},
	{ "asset/texture/black.png",	128, 128},
	{ "asset/texture/goal1.png",	256, 128},
	{ "asset/texture/goal2.png",	256, 128},
	{ "asset/texture/obake.png",	128, 128},
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
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();
	if (!pD3DDevice)
	{
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for (int i = 0; i < TEXTURE_FILE_COUNT; i++)
	{

		if (FAILED(D3DXCreateTextureFromFile(pD3DDevice, g_TextureFiles[i].filename, &g_pTextures[i]))) {
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