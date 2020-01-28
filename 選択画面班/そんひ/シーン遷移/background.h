#pragma once

#include"direct3d.h"
#include"vertex.h"
#include"texture.h"

// 背景レイヤーの数
#define NUMBER_OF_BACKLAYER (7)

class cBackground
{
public:

	static cBackground* objects[NUMBER_OF_BACKLAYER];

	// 使用
	bool use;

	TextureIndex textureIndex;

	// 描画
	D3DXMATRIX	worldMatrix;
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	scale;

	// コンストラクタ
	cBackground(TextureIndex _textureIndex, D3DXVECTOR3 _position, D3DXVECTOR3 _scale);

	// 基本関数
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// 配置
	static void SetBackground(TextureIndex _textureIndex, D3DXVECTOR3 _position, D3DXVECTOR3 _scale);
};