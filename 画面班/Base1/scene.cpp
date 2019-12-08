
#include"scene.h"

#include"texture.h"
#include"sprite.h"
#include"fade.h"

#include"input.h"

#include"camera.h"
#include"grid.h"

static Camera* gcCamera = GetCamera();
static cGrid* gcGrid = GetGrid();
static int gStage = 1;

// GAME
void Init_GAME()
{
	gcCamera->InitCamera();
	gcGrid->Init_Grid();
}
void Uninit_GAME()
{

}
void Update_GAME()
{
	gcCamera->UpdateCamera();
}
void Draw_GAME()
{
	gcGrid->Draw_Grid();
	gcCamera->SetCamera();
}

// Update
void Update_TITLE()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(NUMBER_OF_PEOPLE);
	}
}
void Update_NUMBER_OF_PEOPLE()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(CHARACTER);
	}
}
void Update_CHARACTER()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(NAME);
	}
}
void Update_NAME()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(DIFFICULTY);
	}
}
void Update_DIFFICULTY()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(STAGE);
	}
}
void Update_STAGE()
{
	if (GetKeyboardRelease(DIK_LEFT))
	{
		gStage--;
	}
	if (GetKeyboardRelease(DIK_RIGHT))
	{
		gStage++;
	}
	// êßå‰
	if (gStage < 1)
		gStage = 1;
	if (gStage > NUMBER_OF_STAGE)
		gStage = NUMBER_OF_STAGE;

	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(GAME);
	}
}
void Update_GAMEOVER()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(AREARANKING);
	}
}
void Update_AREARANKING()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(STAGECLEAR);
	}
}
void Update_STAGECLEAR()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(STAGERANKING);
	}
}
void Update_STAGERANKING()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(SCORETABLE);
	}
}
void Update_SCORETABLE()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(RETURN);
	}
}
void Update_RETURN()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(TITLE);
	}
}

// Draw
void Draw_TITLE()
{
	
}
void Draw_NUMBER_OF_PEOPLE()
{

}
void Draw_CHARACTER()
{

}
void Draw_NAME()
{
	
}
void Draw_DIFFICULTY()
{

}
void Draw_STAGE()
{

	// ã§í 
	Sprite_Draw
	(
		TEXTURE_INDEX_BACK,
		(float)SCREEN_WIDTH / 10, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f,
		0, 0, 1.0f, 1.0f 
	);
	Sprite_Draw
	(
		TEXTURE_INDEX_DECISION,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT * (9.0f / 10.0f),
		1.0f, 1.0f,
		0, 0, 1.0f, 1.0f
	);
	// ÉVÅ[Éì
	Sprite_Draw
	(
		TEXTURE_INDEX_STAGE_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f,
		0, 0, 1.0f, 1.0f
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
void Draw_GAMEOVER()
{
	
}
void Draw_AREARANKING()
{
	
}
void Draw_STAGECLEAR()
{
	
}
void Draw_STAGERANKING()
{
	
}
void Draw_SCORETABLE()
{
	
}
void Draw_RETURN()
{
	
}