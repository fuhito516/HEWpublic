
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

LPDIRECT3DTEXTURE9 cSelectDifficulty::pTextures[NUMBER_OF_SELECT_DIFFICULTY_TEXTURE];
bool cSelectDifficulty::use = false;

float dwaku_x = SCREEN_WIDTH / 4;                              //��Փx�gx
float dwaku_y = SCREEN_HEIGHT / 2;                             //��Փx�gy
int nannido;

// ������
void cSelectDifficulty::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// �g�p
	use = true;

	nannido = 1;

	// �e�N�X�`���[
	for (int i = 0; i < NUMBER_OF_SELECT_DIFFICULTY_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}

	// ��
	cCamera::Init();
	/* �f�o�b�O�@�\�̒ǉ� */
}
// �I��
void cSelectDifficulty::Uninit()
{
	// �g�p
	use = false;

	// ��
	cCamera::Uninit();

	// �e�N�X�`��
	for (int i = 0; i < NUMBER_OF_SELECT_DIFFICULTY_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// �X�V
void cSelectDifficulty::Update()
{
	PrintDebugProc("SELECT_DIFFICULTY\n");

	if (nannido >= 1 && nannido < 3) {
		if (GetKeyboardRelease(DIK_RIGHT) || GetKeyboardRelease(DIK_D)) {
			dwaku_x += (float)SCREEN_WIDTH / 4;   //�E�Ɉړ�
			nannido += 1;
		}
	}
	if (nannido > 1 && nannido <= 3) {
		if (GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_A))
		{
			dwaku_x -= (float)SCREEN_WIDTH / 4;  //���Ɉړ�
			nannido -= 1;
		}
	}

	// �J��------------------------------------------------------
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_SELECT_STAGE);
	}
}
// �`��
void cSelectDifficulty::Draw()
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
	//�V�[��------------------------------------------------------------------------
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_LIGHT,
		dwaku_x, dwaku_y,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_EASY,
		(float)SCREEN_WIDTH / 4, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_NORMAL,
		(float)SCREEN_WIDTH / 4 * 2, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DIFFICULTY_HARD,
		(float)SCREEN_WIDTH / 4 * 3, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
}