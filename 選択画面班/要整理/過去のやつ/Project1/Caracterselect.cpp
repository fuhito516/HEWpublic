
#include"common.h"
#include"Caracterselect.h"

#include"texture.h"
#include"sprite.h"
#include"input.h"

//�O���[�o���ϐ�
int NumberOfPeople; //�l��
int NumberOfPeople2;//�l��
float Playercarsolu, Playercarsolu2, Playercarsolu3, Playercarsolu4;//P1�@P2���̃J�[�\�����W
float Lightxpos, Lightxpos2, Lightxpos3, Lightxpos4;//P1P2���̃��C�g�̈ړ�

void CaracterselectInitialize() 
{
	
	NumberOfPeople = 4;
	NumberOfPeople2 = 2;
	//==================================
	//���C�g�ƃJ�[�\���̍��W�̌���
	//==================================
	Lightxpos = SCREEN_WIDTH / 2 - 125 - 260;
	Playercarsolu = Lightxpos;


	Lightxpos2 = SCREEN_WIDTH / 2 - 125 - 260;
	Playercarsolu = Lightxpos2;


	Lightxpos3 = SCREEN_WIDTH / 2 - 125 - 260;
	Playercarsolu = Lightxpos3;

	Lightxpos4 = SCREEN_WIDTH / 2 - 125 - 260;
	Playercarsolu = Lightxpos4;
	////�����܂ł����W
}
void CaracterselectUpdate() {

	//==========================================
	//1P�̓���
	//=========================================

	if (Keyboard_IsTrigger(DIK_RIGHT)) {
		Lightxpos += 130;
		Playercarsolu += 130;
	}

	if (Lightxpos >= SCREEN_WIDTH / 2 - 125 + 262) {
		Lightxpos -= 130;
		Playercarsolu -= 130;

	}
	//���ړ�
	if (Keyboard_IsTrigger(DIK_LEFT)) {
		Lightxpos -= 130;
		Playercarsolu -= 130;

	}
	//���[����
	if (Lightxpos <= SCREEN_WIDTH / 2 - 125 - 262) {
		Lightxpos += 130;
		Playercarsolu += 130;
	}

	//======================================
	//�QP����
	//======================================


	if (Keyboard_IsTrigger(DIK_D)) {

		Lightxpos2 += 130;
		Playercarsolu2 += 130;
	}

	if (Lightxpos2 >= SCREEN_WIDTH / 2 - 125 + 262) {
		Lightxpos2 -= 130;
		Playercarsolu2 -= 130;

	}
	//���ړ�
	if (Keyboard_IsTrigger(DIK_A)) {
		Lightxpos2 -= 130;
		Playercarsolu2 -= 130;

	}
	//���[����
	if (Lightxpos2 <= SCREEN_WIDTH / 2 - 125 - 262) {
		Lightxpos2 += 130;
		Playercarsolu2 += 130;

	}

	//======================================
	//�RP����
	//======================================


	if (Keyboard_IsTrigger(DIK_H)) {

		Lightxpos3 += 130;
		Playercarsolu3 += 130;
	}

	if (Lightxpos3 >= SCREEN_WIDTH / 2 - 125 + 262) {
		Lightxpos3 -= 130;
		Playercarsolu3 -= 130;

	}
	//���ړ�
	if (Keyboard_IsTrigger(DIK_F)) {
		Lightxpos3 -= 130;
		Playercarsolu3 -= 130;

	}
	//���[����
	if (Lightxpos3 <= SCREEN_WIDTH / 2 - 125 - 262) {
		Lightxpos3 += 130;
		Playercarsolu3 += 130;

	}

	//=====================================
	//4P��������
	//=====================================

	if (Keyboard_IsTrigger(DIK_L)) {
		Lightxpos4 += 130;
		Playercarsolu4 += 130;
	}
	if (Lightxpos4 >= SCREEN_WIDTH / 2 - 125 + 262) {
		Lightxpos4 -= 130;
		Playercarsolu4 -= 130;
	}
	if (Keyboard_IsTrigger(DIK_J)) {
		Lightxpos4 -= 130;
		Playercarsolu4 -= 130;
	}
	if (Lightxpos4 <= SCREEN_WIDTH / 2 - 125 - 262) {
		Lightxpos4 += 130;
		Playercarsolu4 += 130;
	}

	if (Keyboard_IsTrigger(DIK_B))
	{
		//�����ɑJ�ځi�߂��i�l���I���j������j

	}

	if (Keyboard_IsTrigger(DIK_Z))
	{
		NumberOfPeople -= 1;
		if (NumberOfPeople <= 0) {
			//�J�ځi�i��i�X�e�[�W�I���j������j
		}
	}
}

void CaracterselectDraw()
{
	Sprite_Draw
	(
		TEXTURE_INDEX_BG,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);

	Sprite_Draw
	(
		TEXTURE_INDEX_KETTEI,
		SCREEN_WIDTH - 300, -35,
		0, 0,
		256, 256
	);

	Sprite_Draw
	(
		TEXTURE_INDEX_SENTAKU,
		SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT / 2 - 125,
		0, 0,
		256, 256
	);

	Sprite_Draw
	(
		TEXTURE_INDEX_SENTAKU,
		SCREEN_WIDTH / 2 - 125 + 130, SCREEN_HEIGHT / 2 - 125,
		0, 0,
		256, 256
	);

	Sprite_Draw
	(
		TEXTURE_INDEX_SENTAKU,
		SCREEN_WIDTH / 2 - 125 - 130, SCREEN_HEIGHT / 2 - 125, 0, 0, 256, 256);

	Sprite_Draw
	(
		TEXTURE_INDEX_SENTAKU,
		SCREEN_WIDTH / 2 - 125 + 260, SCREEN_HEIGHT / 2 - 125,
		0, 0,
		256, 256
	);

	Sprite_Draw
	(
		TEXTURE_INDEX_SENTAKU,
		SCREEN_WIDTH / 2 - 125 - 260, SCREEN_HEIGHT / 2 - 125,
		0, 0,
		256, 256
	);

	if (NumberOfPeople2 >= 1) 
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_LIGHT,
			Lightxpos, SCREEN_HEIGHT / 2 - 125,
			0, 0,
			256, 256
		);
		Sprite_Draw
		(
			TEXTURE_INDEX_1PCARSOLU,
			Lightxpos, SCREEN_HEIGHT / 2 + 20,
			0, 0,
			256, 256
		);
	}
	if (NumberOfPeople2 >= 2)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_LIGHT,
			Lightxpos2, SCREEN_HEIGHT / 2 - 125,
			0, 0,
			256, 256
		);
		Sprite_Draw
		(
			TEXTURE_INDEX_2PCARSOLU,
			Lightxpos2, SCREEN_HEIGHT / 2 + 55,
			0, 0,
			256, 256
		);
	}
	if (NumberOfPeople2 >= 3)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_LIGHT,
			Lightxpos3, SCREEN_HEIGHT / 2 - 125,
			0, 0,
			256, 256
		);
		Sprite_Draw
		(
			TEXTURE_INDEX_3PCARSOLU,
			Lightxpos3, SCREEN_HEIGHT / 2 + 90,
			0, 0,
			256, 256
		);

	}
	if (NumberOfPeople2 >= 4) 
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_LIGHT,
			Lightxpos4, SCREEN_HEIGHT / 2 - 125,
			0, 0,
			256, 256
		);
		Sprite_Draw
		(
			TEXTURE_INDEX_4PCARSOLU,
			Lightxpos4, SCREEN_HEIGHT / 2 + 125,
			0, 0,
			256, 256
		);
	}

	Sprite_Draw
	(
		TEXTURE_INDEX_BACK,
		0, -50,
		0, 0,
		256, 256
	);
}