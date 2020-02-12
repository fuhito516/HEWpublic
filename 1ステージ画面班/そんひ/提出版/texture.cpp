
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
	// ����
	{ "asset/texture/Common/black.png",		128, 128},
	{ "asset/texture/Common/back.png",		SIZE_256, SIZE_64},
	{ "asset/texture/Common/decision.png",	SIZE_256, SIZE_64},

	//�^�C�g��
	{ "asset/texture/BG.png",             SCREEN_WIDTH, SCREEN_HEIGHT},
	{ "asset/texture/LIGHT2.png",         SCREEN_WIDTH, SCREEN_HEIGHT},
	{ "asset/texture/fire.png",           2304, SIZE_256},
	{ "asset/texture/BGblack2.png",       SIZE_1024,SIZE_576},
	{ "asset/texture/Press Enter.png",    SIZE_256,SIZE_256},
	{ "asset/texture/Title1024.png",      SCREEN_WIDTH, SCREEN_HEIGHT},

	// �X�e�[�W�I�����
	{ "asset/texture/Stage/stage heading.png",	SIZE_256, SIZE_64 },
	{ "asset/texture/Stage/stage rope.png",		SIZE_64, SIZE_256 },
	{ "asset/texture/Stage/blacknumber.png",	384, 151},

	// �Q�[�����
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
	{ "asset/texture/ya.png",		512, 256},
	//�v���C���[�E
	{ "asset/texture/playerR/player_walk_00.png",   128,128},
	{ "asset/texture/playerR/player_walk_01.png",   128,128},
	{ "asset/texture/playerR/player_walk_02.png",   128,128},
	{ "asset/texture/playerR/player_walk_03.png",   128,128},
	{ "asset/texture/playerR/player_walk_04.png",   128,128},
	{ "asset/texture/playerR/player_walk_05.png",   128,128},
	{ "asset/texture/playerR/player_walk_06.png",   128,128},
	{ "asset/texture/playerR/player_walk_07.png",   128,128},
	{ "asset/texture/playerR/player_walk_08.png",   128,128},
	{ "asset/texture/playerR/player_walk_09.png",   128,128},
	{ "asset/texture/playerR/player_walk_10.png",   128,128},
	{ "asset/texture/playerR/player_walk_11.png",   128,128},
	{ "asset/texture/playerR/player_walk_12.png",   128,128},
	{ "asset/texture/playerR/player_walk_13.png",   128,128},
	{ "asset/texture/playerR/player_walk_14.png",   128,128},
	{ "asset/texture/playerR/player_walk_15.png",   128,128},
	{ "asset/texture/playerR/player_walk_16.png",   128,128},
	{ "asset/texture/playerR/player_walk_17.png",   128,128},
	{ "asset/texture/playerR/player_walk_18.png",   128,128},
	//�v���C���[��
	{ "asset/texture/playerL/player_walk_00_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_01_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_02_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_03_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_04_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_05_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_06_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_07_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_08_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_09_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_10_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_11_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_12_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_13_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_14_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_15_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_16_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_17_left.png",   128,128},
	{ "asset/texture/playerL/player_walk_18_left.png",   128,128},
	// �M�~�b�N
	{ "asset/texture/candle1.png",	128, 128},
	{ "asset/texture/candle2.png",	128, 128},
	{ "asset/texture/Common/black.png",	128, 128},
	{ "asset/texture/goal1.png",	256, 128},
	{ "asset/texture/goal2.png",	256, 128},
	{ "asset/texture/obake.png",	128, 128},
	// ������@
	{ "asset/texture/control.png",	540, 288},

	// �Q�[���I�[�o�[���
	{ "asset/texture/Gameover/end1.png",	SCREEN_WIDTH, SCREEN_HEIGHT},
	{ "asset/texture/Gameover/end2.png",	SCREEN_WIDTH, SCREEN_HEIGHT},
	{ "asset/texture/Gameover/end3.png",	SCREEN_WIDTH, SCREEN_HEIGHT},
	{ "asset/texture/Gameover/end4.png",	SCREEN_WIDTH, SCREEN_HEIGHT},
	// �Q�[���N���A���
	{ "asset/texture/Gameclear/gameclear.png",	SCREEN_WIDTH, SCREEN_HEIGHT},

	// �߂���
	{ "asset/texture/Return/return.png",	256, 64},
	{ "asset/texture/Return/toTitle.png",	256, 64 },
	{ "asset/texture/Return/toStage.png",	512, 64 },
	{ "asset/texture/Return/return select.png",	64, 64 },
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