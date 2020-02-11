
// ���C��
#include"Gameover.h"
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

// �A�j���[�V����
static int frame = 0;
static float second = 0;

// ������
void cGameover::Init()
{
	// �A�j���[�V����
	frame = 0;
	second = 0;

	// ��
	cCamera::Init();
}
// �I��
void cGameover::Uninit()
{
	// ��
	cCamera::Uninit();
}
// �X�V
void cGameover::Update()
{
	// PrintDebugProc("GAMECLEAR\n");

	// �J��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		//cScene::Fade(SCENE_);
	}
}
// �`��
void cGameover::Draw()
{
	// �A�j���[�V����
	frame++;
	second = (float)frame / FRAME_PER_SECOND;

	if (second < 1.8f)
	{
		sprite_draw
		(
			TEXTURE_INDEX_GAMEOVER1,
			0, 0,
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
		);
	}
	else if (second < 2.6f)
	{
		sprite_draw
		(
			TEXTURE_INDEX_GAMEOVER2,
			0, 0,
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
		);
	}
	else if (second < 4.0f)
	{
		sprite_draw
		(
			TEXTURE_INDEX_GAMEOVER3,
			0, 0,
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
		);
	}
	else
	{
		sprite_draw
		(
			TEXTURE_INDEX_GAMEOVER4,
			0, 0,
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
		);
	}
}