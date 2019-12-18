
#include"scene.h"

#include"texture.h"
#include"sprite.h"
#include"fade.h"
#include"input.h"

#include"camera.h"
#include"object.h"
#include"fog.h"

eScene	cScene::scene;
int		cScene::stage;
bool	cScene::checkPastPressed;

void cScene::Initialize_Scene()
{
	scene = TITLE;
	stage = STAGE1;
	checkPastPressed = false;
}

// Update
void cScene::Update_TITLE()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(PLAYER);
	}
}
void cScene::Update_PLAYER()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(CHARACTER);
	}
}
void cScene::Update_CHARACTER()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(NAME);
	}
}
void cScene::Update_NAME()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(DIFFICULTY);
	}
}
void cScene::Update_DIFFICULTY()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(STAGE);
	}
}
void cScene::Update_STAGE()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_LEFT))
	{
		checkPastPressed = true;
		stage--;
	}
	if (!checkPastPressed && Keyboard_IsPress(DIK_RIGHT))
	{
		checkPastPressed = true;
		stage++;
	}
	// êßå‰
	if (stage < STAGE1)
		stage = STAGE1;
	if (stage > STAGEMAX - 1)
		stage = STAGEMAX - 1;

	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(GAME);
	}
}
void cScene::Update_GAME()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(GAMEOVER);
	}
}
void cScene::Update_GAMEOVER()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(AREARANKING);
	}
}
void cScene::Update_AREARANKING()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(STAGECLEAR);
	}
}
void cScene::Update_STAGECLEAR()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(STAGERANKING);
	}
}
void cScene::Update_STAGERANKING()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(SCORETABLE);
	}
}
void cScene::Update_SCORETABLE()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(RETURN);
	}
}
void cScene::Update_RETURN()
{
	if (!checkPastPressed && Keyboard_IsPress(DIK_RETURN))
	{
		checkPastPressed = true;
		cFade::Fade(TITLE);
	}
}

// Draw
void cScene::Draw_TITLE()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_TITLE,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}
void cScene::Draw_PLAYER()
{

}
void cScene::Draw_CHARACTER()
{

}
void cScene::Draw_NAME()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_NAME,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}
void cScene::Draw_DIFFICULTY()
{

}
void cScene::Draw_STAGE()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_STAGE,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
	Sprite_Draw
	(
		TEXTURE_SCENE_STAGECHARACTER,
		(float)stage * 145 + 100, SCREEN_HEIGHT / 2 + SMALL / 2,
		0, 0,
		SMALL, SMALL
	);
}
void cScene::Draw_GAME()
{

}
void cScene::Draw_GAMEOVER()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_GAMEOVER,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}
void cScene::Draw_AREARANKING()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_AREARANKING,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}
void cScene::Draw_STAGECLEAR()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_STAGECLEAR,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}
void cScene::Draw_STAGERANKING()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_STAGERANKING,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}
void cScene::Draw_SCORETABLE()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_SCORETABLE,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}
void cScene::Draw_RETURN()
{
	Sprite_Draw
	(
		TEXTURE_SCENE_RETURN,
		0, 0,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT
	);
}