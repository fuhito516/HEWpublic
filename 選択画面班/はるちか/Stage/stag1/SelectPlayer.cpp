
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

LPDIRECT3DTEXTURE9 cSelectPlayer::pTextures[NUMBER_OF_SELECT_PLAYER_TEXTURE];
bool cSelectPlayer::use = false;

//�O���[�o���ϐ�
float pwaku_x = SCREEN_WIDTH / 5;                              //�l���gx
float pwaku_y = SCREEN_HEIGHT / 2;                             //�l���gy
extern int people;                                                       //�l��

// ������
void cSelectPlayer::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// �g�p
	use = true;

	people = 1;

	// �e�N�X�`���[
	for (int i = 0; i < NUMBER_OF_SELECT_PLAYER_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}

	// ��
	cCamera::Init();
	/* �f�o�b�O�@�\�̒ǉ� */
}
// �I��
void cSelectPlayer::Uninit()
{
	// �g�p
	use = false;

	// ��
	cCamera::Uninit();

	// �e�N�X�`��
	for (int i = 0; i < NUMBER_OF_SELECT_PLAYER_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// �X�V
void cSelectPlayer::Update()
{
	PrintDebugProc("SELECT_PLAYER\n");

	if (people >= 1 && people < 4) {
		if (GetKeyboardRelease(DIK_RIGHT) || GetKeyboardRelease(DIK_D)) 
		{
			pwaku_x += (float)SCREEN_WIDTH / 5;   //�E�ړ�
			people++;
		}
	}
	if (people > 1 && people <= 4) {
		if (GetKeyboardRelease(DIK_LEFT) || GetKeyboardRelease(DIK_A))
		{
			pwaku_x -= (float)SCREEN_WIDTH / 5;  //���ړ�
			people--;
		}
	}

	// �J��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_SELECT_CHARACTER);
	}
}
// �`��
void cSelectPlayer::Draw()
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

	//�V�[��----------------------------------------------------------------------
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_LIGHT,
		pwaku_x, pwaku_y,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_ONE,
		(float)SCREEN_WIDTH / 5, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_TWO,
		(float)SCREEN_WIDTH / 5 * 2, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_THREE,
		(float)SCREEN_WIDTH / 5 * 3, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_PEOPLE_FOUR,
		(float)SCREEN_WIDTH / 5 * 4, (float)SCREEN_HEIGHT / 2,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);

}