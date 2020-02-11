
// ���C��
#include"common.h"
#include"direct3d.h"
#include"vertex.h"
#include"debugproc.h"
// ��
#include"camera.h"
#include"input.h"
#include"sprite.h"
// �V�[��
#include"scene.h"
#include"Game.h"
#include"SelectPlayer.h"
#include"SelectCharacter.h"
#include"SelectDifficulty.h"
#include"SelectStage.h"

LPDIRECT3DTEXTURE9 cSelectStage::pTextures[NUMBER_OF_SELECT_STAGE_TEXTURE];
bool cSelectStage::use = false;

static int gStage = 1;                                                //�X�e�[�W

// ������
void cSelectStage::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// �g�p
	use = true;

	// �e�N�X�`���[
	for (int i = 0; i < NUMBER_OF_SELECT_STAGE_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}
	// ��
	cCamera::Init();
	/* �f�o�b�O�@�\�̒ǉ� */
}
// �I��
void cSelectStage::Uninit()
{
	// �g�p
	use = false;

	// ��
	cCamera::Uninit();

	// �e�N�X�`��
	for (int i = 0; i < NUMBER_OF_SELECT_STAGE_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// �X�V
void cSelectStage::Update()
{
	//PrintDebugProc("SELECT_STAGE\n");

	if (GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_A)) {
		gStage--;
	}
	if (GetKeyboardRelease(DIK_RIGHT) || GetKeyboardRelease(DIK_D)) {
		gStage++;
	}
	// ����
	if (gStage < 1)
		gStage = 1;
	if (gStage > NUMBER_OF_STAGE)
		gStage = NUMBER_OF_STAGE;

	// �J��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_GAME);
	}
}
// �`��
void cSelectStage::Draw()
{

	//����
	Sprite_Draw
	(
		TEXTURE_INDEX_BLACK,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_BACK,
		(float)SCREEN_WIDTH / 10, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DECISION,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT * (9.0f / 10.0f),
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);

	Sprite_Draw
	(
		TEXTURE_INDEX_STAGE_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	for (int i = 1; i <= NUMBER_OF_STAGE; i++)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_STAGE_ROPE,
			(float)SCREEN_WIDTH * ((float)i / (NUMBER_OF_STAGE + 1)), (float)SCREEN_HEIGHT / 2,
			1.2f, 1.2f,
			0, 0, 1.0f, 1.0f
		);
		Sprite_Draw
		(
			TEXTURE_INDEX_BLACKNUMBER,
			(float)SCREEN_WIDTH * ((float)i / (NUMBER_OF_STAGE + 1)), (float)SCREEN_HEIGHT / 2 - 118,
			0.8f, 0.8f,
			1.0f / 8 * (i - 1), 0, 1.0f / 8 * i, 0.5f
		);
	}
	Sprite_Draw
	(
		TEXTURE_INDEX_STAGE_CHARACTER,
		(float)SCREEN_WIDTH * ((float)gStage / (NUMBER_OF_STAGE + 1)) - 36, (float)SCREEN_HEIGHT * (2.0f / 3.0f),
		1.0f, 1.0f,
		0, 0, 1.0f, 1.0f
	);

}