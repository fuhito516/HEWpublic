
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

LPDIRECT3DTEXTURE9 cSelectCharacter::pTextures[NUMBER_OF_SELECT_CHARACTER_TEXTURE];
bool cSelectCharacter::use = false;

//�O���[�o���ϐ�
float Playercarsolu = (float)SCREEN_WIDTH / 32 * 4;                                      //�J�[�\�����W�̌���
float Playercarsolu2 = (float)SCREEN_WIDTH / 32 * 4;                                    //�J�[�\�����W�̌���
float Playercarsolu3 = (float)SCREEN_WIDTH / 32 * 4;                                      //�J�[�\�����W�̌���
float Playercarsolu4 = (float)SCREEN_WIDTH / 32 * 4;                                   //�J�[�\�����W�̌���
int Character1P = 1;                                                  //�PP�̑I���L�����N�^�[
int Character2P = 1;                                                  //�QP�̑I���L�����N�^�[
int Character3P = 1;                                                  //�RP�̑I���L�����N�^-
int Character4P = 1;                                                  //�SP�̑I���L�����N�^�[
int people;                                                       //�l��

// ������
void cSelectCharacter::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = MyDirect3D_GetDevice();

	// �g�p
	use = true;

	// �e�N�X�`���[
	for (int i = 0; i < NUMBER_OF_SELECT_CHARACTER_TEXTURE; i++)
	{
		pTextures[i] = NULL;
	}
	
	// ��
	cCamera::Init();
	/* �f�o�b�O�@�\�̒ǉ� */
}
// �I��
void cSelectCharacter::Uninit()
{
	// �g�p
	use = false;

	// ��
	cCamera::Uninit();

	// �e�N�X�`��
	for (int i = 0; i < NUMBER_OF_SELECT_CHARACTER_TEXTURE; i++)
	{
		if (pTextures[i] != NULL)
		{
			pTextures[i]->Release();
			pTextures[i] = NULL;
		}
	}
}
// �X�V
void cSelectCharacter::Update()
{
	//PrintDebugProc("SELECT_PLAYER\n");

	//1P�̓���-------------------------------------------------------
	if (Character1P >= 1 && Character1P < 5) {
		if (GetKeyboardRelease(DIK_D)) {
			Playercarsolu += (float)SCREEN_WIDTH / 32 * 6;  //�E�ړ�
			Character1P++;
		}
	}
	if (Character1P > 1 && Character1P <= 5) {
		if (GetKeyboardRelease(DIK_A)) {
			Playercarsolu -= (float)SCREEN_WIDTH / 32 * 6;   //���ړ�
			Character1P--;
		}
	}
	//�QP����----------------------------------------------------------
	if (Character2P >= 1 && Character2P < 5) {
		if (GetKeyboardRelease(DIK_RIGHT)) {
			Playercarsolu2 += (float)SCREEN_WIDTH / 32 * 6;   //�E�ړ�
			Character2P++;
		}
	}
	if (Character2P > 1 && Character2P <= 5) {
		if (GetKeyboardRelease(DIK_LEFT)) {
			Playercarsolu2 -= (float)SCREEN_WIDTH / 32 * 6;   //���ړ�
			Character2P--;
		}
	}
	//�RP����------------------------------------------------------------
	if (Character3P >= 1 && Character3P < 5) {
		if (GetKeyboardRelease(DIK_H)) {
			Playercarsolu3 += (float)SCREEN_WIDTH / 32 * 6;    //�E�ړ�
			Character3P++;
		}
	}
	if (Character3P > 1 && Character3P <= 5) {
		if (GetKeyboardRelease(DIK_F)) {
			Playercarsolu3 -= (float)SCREEN_WIDTH / 32 * 6;    //���ړ�
			Character3P--;
		}
	}
	//4P��������---------------------------------------------------------------
	if (Character4P >= 1 && Character4P < 5) {
		if (GetKeyboardRelease(DIK_L)) {
			Playercarsolu4 += (float)SCREEN_WIDTH / 32 * 6;    //�E�ړ�
			Character4P++;
		}
	}
	if (Character4P > 1 && Character4P <= 5) {
		if (GetKeyboardRelease(DIK_J)) {
			Playercarsolu4 -= (float)SCREEN_WIDTH / 32 * 6;    //���ړ�
			Character4P--;
		}
	}

	// �J��---------------------------------------------------------------------
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		cScene::Fade(SCENE_SELECT_DIFFICULTY);
	}
}
// �`��
void cSelectCharacter::Draw()
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
	//�V�[��-----------------------------------------------------------------
	Sprite_Draw
	(
		TEXTURE_INDEX_CHARACTER_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f, 0, 0, 1.0f, 1.0f
	);

	for (int charaselect = 0; charaselect <= 4; charaselect++) {
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_SELECT,
			((float)SCREEN_WIDTH / 32 * (4 + 6 * charaselect)), (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}

	if (people >= 1)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_ONE,
			Playercarsolu, (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}
	if (people >= 2)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_TWO,
			Playercarsolu2, (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}
	if (people >= 3)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_THREE,
			Playercarsolu3, (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);

	}
	if (people >= 4)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_FOUR,
			Playercarsolu4, (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}

}