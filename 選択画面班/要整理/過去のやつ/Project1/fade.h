#pragma once

#include"common.h"

#include"sprite.h"
#include"texture.h"

#include"scene.h"

#define FADE_COUNT (60)	// �J�ڎ���(�t���[��)

enum FadeState	// �t�F�[�h�̏��
{
	FADESTATE_NONE,
	FADESTATE_IN,
	FADESTATE_OUT,
};

class cFade
{
private:
protected:
public:
	static int		fadeState;	// �t�F�[�h���
	static int		fadeAlpha;	// �A���t�@�l
	static eScene	nextScene;	// ���̃V�[��

	static void Fade(eScene _nextScene);
	// usingFade = true��
	static void UpdateFade();
	static void DrawFade();
};