
// ���C��
#include"Gameclear.h"
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

// ������
void cGameclear::Init()
{
	fade = false;

	// ��
	cCamera::Init();
}
// �I��
void cGameclear::Uninit()
{
	// ��
	cCamera::Uninit();
}
// �X�V
void cGameclear::Update()
{
	// PrintDebugProc("GAMECLEAR\n");

	// �J��
	if (GetKeyboardTrigger(DIK_RETURN) && !fade)
	{
		cScene::Fade(SCENE_RETURN);
		fade = true;
	}
}
// �`��
void cGameclear::Draw()
{
	sprite_draw
	(
		TEXTURE_INDEX_GAMECLEAR,
		0, 0,
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	);
}