
#include"scene.h"

#include"directx.h"
#include"texture.h"
#include"sprite.h"
#include"fade.h"

#include"input.h"

#include"camera.h"
#include"grid.h"

//--------------------------------------------------------------------------------------------------------------
// グローバル変数
//--------------------------------------------------------------------------------------------------------------
static Camera* gcCamera = GetCamera();
static cGrid* gcGrid = GetGrid();
static float pwaku_x = SCREEN_WIDTH / 5;                              //人数枠x
static float pwaku_y = SCREEN_HEIGHT / 2;                             //人数枠y
static float dwaku_x = SCREEN_WIDTH / 4;                              //難易度枠x
static float dwaku_y = SCREEN_HEIGHT / 2;                             //難易度枠y
int people = 1;                                                       //人数
float Playercarsolu = (float)SCREEN_WIDTH / 32 * 4;                                      //カーソル座標の決定
float Playercarsolu2 = (float)SCREEN_WIDTH / 32 * 4;                                    //カーソル座標の決定
float Playercarsolu3 = (float)SCREEN_WIDTH / 32 * 4;                                      //カーソル座標の決定
float Playercarsolu4 = (float)SCREEN_WIDTH / 32 * 4;                                   //カーソル座標の決定
int Character1P = 1;                                                  //１Pの選択キャラクター
int Character2P = 1;                                                  //２Pの選択キャラクター
int Character3P = 1;                                                  //３Pの選択キャラクタ-
int Character4P = 1;                                                  //４Pの選択キャラクター
static int gStage = 1;                                                //ステージ

//------------------------------------------------------------------------------------------------------------------
// GAME
//------------------------------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------------------------------------------------
void Update_TITLE()
{
	if (GetKeyboardRelease(DIK_RETURN))
	{
		Fade(NUMBER_OF_PEOPLE);
	}
}
void Update_NUMBER_OF_PEOPLE()
{
	if (people >= 1 && people < 4){
		if (GetKeyboardRelease(DIK_RIGHT)){
			pwaku_x += (float)SCREEN_WIDTH / 5;   //右移動
			people++;
		}
	}
	if (people > 1 && people <= 4) {
		if (GetKeyboardRelease(DIK_LEFT))
		{
			pwaku_x -= (float)SCREEN_WIDTH / 5;  //左移動
			people--;
		}
	}
	if (GetKeyboardRelease(DIK_RETURN)){
		Fade(CHARACTER);                 //キャラクター選択へ進む
	}
	if (GetKeyboardRelease(DIK_Z)) {
		Fade(TITLE);                      //タイトルへ戻る
	}
}
void Update_CHARACTER()
{
	//1Pの動き-------------------------------------------------------
	if (Character1P >= 1 && Character1P < 5 ) {
		if (GetKeyboardRelease(DIK_RIGHT)) {
			Playercarsolu += (float)SCREEN_WIDTH / 32 * 6;  //右移動
			Character1P++;
		}
	}
	if (Character1P > 1 && Character1P <= 5 ) {
		if (GetKeyboardRelease(DIK_LEFT)) {
			Playercarsolu -= (float)SCREEN_WIDTH / 32 * 6;   //左移動
			Character1P--;
		}
	}
	//２P動き----------------------------------------------------------
	if (Character2P >= 1 && Character2P < 5 ) {
		if (GetKeyboardRelease(DIK_D)) {
			Playercarsolu2 += (float)SCREEN_WIDTH / 32 * 6;   //右移動
			Character2P++;
		}
	}
	if (Character2P > 1 && Character2P <= 5) {
		if (GetKeyboardRelease(DIK_A)) {
			Playercarsolu2 -= (float)SCREEN_WIDTH / 32 * 6;   //左移動
			Character2P--;
		}
	}
	//３P動き------------------------------------------------------------
	if (Character3P >= 1 && Character3P < 5) {
		if (GetKeyboardRelease(DIK_H)) {
			Playercarsolu3 += (float)SCREEN_WIDTH / 32 * 6;    //右移動
			Character3P++;
		}
	}
	if (Character3P > 1 && Character3P <= 5) {
		if (GetKeyboardRelease(DIK_F)) {
			Playercarsolu3 -= (float)SCREEN_WIDTH / 32 * 6;    //左移動
			Character3P--;
		}
	}
	//4P動く処理---------------------------------------------------------------
	if (Character4P >= 1 && Character4P < 5 ) {
		if (GetKeyboardRelease(DIK_L)) {
			Playercarsolu4 += (float)SCREEN_WIDTH / 32 * 6;    //右移動
			Character4P++;
		}
	}
	if (Character4P > 1 && Character4P <= 5 ) {
		if (GetKeyboardRelease(DIK_J)) {
			Playercarsolu4 -= (float)SCREEN_WIDTH / 32 * 6;    //左移動
			Character4P--;
		}
	}
	if (GetKeyboardRelease(DIK_RETURN)) {
		Fade(DIFFICULTY);                   //難易度選択へ進む
	}
	if (GetKeyboardRelease(DIK_Z)){
		Fade(NUMBER_OF_PEOPLE);              //人数選択へ戻る
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
	static int nannido = 1;
	if (nannido >= 1 && nannido < 3) {
		if (GetKeyboardRelease(DIK_RIGHT)) {
			dwaku_x += (float)SCREEN_WIDTH / 4;   //右に移動
			nannido += 1;
		}
	}
	if (nannido > 1 && nannido <= 3) {
		if (GetKeyboardRelease(DIK_LEFT))
		{
			dwaku_x -= (float)SCREEN_WIDTH / 4;  //左に移動
			nannido -= 1;
		}
	}
	if (GetKeyboardRelease(DIK_RETURN)) {
		Fade(STAGE);                        //ステージ選択へ進む
	}
	if (GetKeyboardRelease(DIK_Z)) {
		Fade(CHARACTER);                      //キャラクター選択へ戻る
	}
}
void Update_STAGE()
{
	if (GetKeyboardRelease(DIK_LEFT)){
		gStage--;
	}
	if (GetKeyboardRelease(DIK_RIGHT)){
		gStage++;
	}
	// 制御
	if (gStage < 1)
		gStage = 1;
	if (gStage > NUMBER_OF_STAGE)
		gStage = NUMBER_OF_STAGE;
	if (GetKeyboardRelease(DIK_RETURN)){
		Fade(GAME);                           //ゲーム画面へ進む
	}
	if (GetKeyboardRelease(DIK_Z)) {
		Fade(DIFFICULTY);                      //難易度選択へ戻る
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

//------------------------------------------------------------------------------------------------------------------------------
// Draw
//------------------------------------------------------------------------------------------------------------------------------
void Draw_TITLE()
{
	
}
void Draw_NUMBER_OF_PEOPLE()
{

	// 共通-----------------------------------------------------------------------
	BACK();
	//シーン----------------------------------------------------------------------
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
void Draw_CHARACTER()
{

	// 共通------------------------------------------------------------------
	BACK();
	//シーン-----------------------------------------------------------------
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
			((float)SCREEN_WIDTH / 32 * (4 + 6 * charaselect)) , (float)SCREEN_HEIGHT / 2,
			1.0f, 1.0f, 0, 0, 1.0f, 1.0f
		);
	}

	if (people >= 1)
	{
		Sprite_Draw
		(
			TEXTURE_INDEX_CHARACTER_ONE,
			Playercarsolu, (float)SCREEN_HEIGHT / 2 ,
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
void Draw_NAME()
{

	// 共通----------------------------------------------------------------------
	BACK();
	//シーン----------------------------------------------------------------------
	
}
void Draw_DIFFICULTY()
{

	// 共通-----------------------------------------------------------------------
	BACK();
	//シーン------------------------------------------------------------------------
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
void Draw_STAGE()
{

	// 共通-----------------------------------------------------------------
	BACK();
	// シーン----------------------------------------------------------------
	Sprite_Draw
	(
		TEXTURE_INDEX_STAGE_HEADING,
		(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 10,
		1.0f, 1.0f,0, 0, 1.0f, 1.0f
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

//共通背景
void BACK()
{
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
}