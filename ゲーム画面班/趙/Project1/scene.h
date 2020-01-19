#pragma once
// �I�u�W�F�N�g����̎g�p�A�s�Ή�

// ��b
#include"common.h"
#include"directx.h"
// �V�X�e��
#include"texture.h"
#include"sprite.h"
#include"input.h"

// �͖�
#include"Caracterselect.h"
// ��
#include"peaple.h"
#include"diffical.h"

// �V�[����
enum eScene
{
	NONE,
	TITLE,
	PLAYER,
	CHARACTER,
	NAME,
	DIFFICULTY,
	STAGE,
	GAME,
	GAMEOVER,
	AREARANKING,
	STAGECLEAR,
	STAGERANKING,
	SCORETABLE,
	RETURN
};
// �X�e�[�W��
enum eStage
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	
	STAGEMAX
};

class cScene
{
private:
protected:
public:
	static eScene	scene;
	static int		stage;
	static bool		checkPastPressed;

	static void Initialize_Scene();

	// �v����(GAME)
	static void Update_TITLE();
	static void Update_PLAYER();
	static void Update_CHARACTER();
	static void Update_NAME();
	static void Update_DIFFICULTY();
	static void Update_STAGE();
	static void Update_GAME();
	static void Update_GAMEOVER();
	static void Update_AREARANKING();
	static void Update_STAGECLEAR();
	static void Update_STAGERANKING();
	static void Update_SCORETABLE();
	static void Update_RETURN();

	static void Draw_TITLE();
	static void Draw_PLAYER();
	static void Draw_CHARACTER();
	static void Draw_NAME();
	static void Draw_DIFFICULTY();
	static void Draw_STAGE();
	static void Draw_GAME();
	static void Draw_GAMEOVER();
	static void Draw_AREARANKING();
	static void Draw_STAGECLEAR();
	static void Draw_STAGERANKING();
	static void Draw_SCORETABLE();
	static void Draw_RETURN();

	/* ���S�̂��߂ɍו��� */
};