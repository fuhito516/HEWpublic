
#include"common.h"
#include"peaple.h"
#include"sprite.h"
#include"texture.h"
#include"input.h"

static float	waku_x	= 50.0f;
static float	waku_y	= 225.0f;
static int		ninzu	= 1;

void UpdatePeaple(void)
{
	// �E�Ɉړ�
	if (ninzu >= 1 && ninzu < 4)
	{
		if (Keyboard_IsTrigger(DIK_RIGHT))
		{
			waku_x += 235;
			ninzu += 1;
		}
	}
	// ���Ɉړ�
	if(ninzu > 1 && ninzu <= 4){
		if (Keyboard_IsTrigger(DIK_LEFT))
		{
			waku_x -= 235;
			ninzu -= 1;
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

void DrawPeaple(void)
{
	// �X�v���C�g�`��
	Sprite_Draw
	(
		TEXTURE_INDEX_HAIKEI,
		0.0f, 0.0f,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	); // 1024 576

	Sprite_Draw
	(
		TEXTURE_INDEX_WAKU,
		waku_x, waku_y,
		0, 0,
		WAKU_WIDTH_P, WAKU_HEIGHT_P
	);
}