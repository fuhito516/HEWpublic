#pragma once

#include"common.h"

#include"sprite.h"
#include"texture.h"

#define FADE_COUNT (60)	// �J�ڎ���(�t���[��)
#define NUMBER_OF_STAGE (3)

// �V�[���̎��
enum eScene
{
	TITLE,
	NUMBER_OF_PEOPLE,
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
#define FIRST_SCENE STAGE
// �t�F�[�h�̏��
enum eFadeState
{
	FADE_STATE_NONE,
	FADE_STATE_IN,
	FADE_STATE_OUT,
};

class cFade
{
public:

	int currentScene;	// ���݂̃V�[��
	int	nextScene;		// ���̃V�[��
	int	fadeState;	// �t�F�[�h���
	int	fadeAlpha;	// �A���t�@�l

	void Init_Fade();
	void Update_Fade();
	void Draw_Fade();

};

cFade* GetFade();
void Fade(int nextScene);	// ���̃V�[���ֈړ�