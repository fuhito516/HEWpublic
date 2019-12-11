
#include"common.h"
#include"diffical.h"
#include"sprite.h"
#include"texture.h"
#include"input.h"

static float	nannidowaku_x	= 45.0f;
static float	nannidowaku_y	= 180.0f;
static int		nannido			= 1;

void UpdateDiffical(void)
{

	// �E�Ɉړ�
	if (nannido >= 1 && nannido < 3)
	{
		if (Keyboard_IsTrigger(DIK_RIGHT))
		{
			nannidowaku_x += 325.0f;
			nannido += 1;
		}
	}
	// ���Ɉړ�
	if (nannido > 1 && nannido <= 3) {
		if (Keyboard_IsTrigger(DIK_LEFT))
		{
			nannidowaku_x -= 325.0f;
			nannido -= 1;
		}
	}
	// ����
	if (Keyboard_IsTrigger(DIK_A))
	{
		// �L�����N�^�[�I����
	}
	// �߂�
	if (Keyboard_IsTrigger(DIK_Z))
	{
		// ���[�h�I����
	}
}

void DrawDiffical(void)
{
	Sprite_Draw
	(
		TEXTURE_INDEX_NANNIDOHAIKEI,
		0.0f, 0.0f,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	); // 1024 576

	Sprite_Draw
	(
		TEXTURE_INDEX_NANNIDOWAKU,
		nannidowaku_x, nannidowaku_y,
		0, 0,
		WAKU_WIDTH, WAKU_HEIGHT
	);
}