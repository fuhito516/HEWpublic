
// ���C��
#include"Return.h"
#include"common.h"
#include"direct3d.h"
#include"vertex.h"
// ��
#include"debugproc.h"
#include"camera.h"
#include"input.h"
#include"sprite.h"
// �V�[��
#include"scene.h"

// �V�[���J��
static bool fade = false;

// �A�j���[�V����
static int frame = 0;
static float second = 0;

// �I��
static int returnScene = 0;

// ������
void cReturn::Init()
{
	// �V�[���J��
	fade = false;

	// �A�j���[�V����
	frame = 0;
	second = 0;

	// ��
	cCamera::Init();
}
// �I��
void cReturn::Uninit()
{
	// ��
	cCamera::Uninit();
}
// �X�V
void cReturn::Update()
{
	//PrintDebugProc("SCENE_RETURN\n");

	// �I���ړ�
	if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S))
	{
		returnScene++;
	}
	else if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W))
	{
		returnScene--;
	}
	if (returnScene < 0)
	{
		returnScene = 0;
	}
	else if (returnScene > 1)
	{
		returnScene = 1;
	}

	PrintDebugProc("�V�[���J�ځ@%d\n", returnScene);
	// �J��
	if (GetKeyboardTrigger(DIK_RETURN) && !fade)
	{
		switch (returnScene)
		{
		case 0:
			cScene::Fade(SCENE_TITLE);
			break;
		case 1:
			cScene::Fade(SCENE_SELECT_STAGE);
			break;

		default:
			break;
		}
		fade = true;
	}
}
// �`��
void cReturn::Draw()
{
	// ���o��
	Sprite_Draw
	(
		TEXTURE_INDEX_RETURN,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10,
		0.8f, 0.8f,
		0, 0, 1, 1
	);

	// ����
	Sprite_Draw
	(
		TEXTURE_INDEX_TOTITLE,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50,
		0.8f, 0.8f,
		0, 0, 1, 1
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_TOSTAGE,
		SCREEN_WIDTH / 2 + 128 * 0.8f, SCREEN_HEIGHT / 2 + 50,
		0.8f, 0.8f,
		0, 0, 1, 1
	);

	// ���
	if (returnScene == 0)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_RETURNSELECT,
			SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 - 50,
			1, 1,
			0, 0, 1, 1
		);
	}
	else if (returnScene == 1)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_RETURNSELECT,
			SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 + 50,
			1, 1,
			0, 0, 1, 1
		);
	}
}