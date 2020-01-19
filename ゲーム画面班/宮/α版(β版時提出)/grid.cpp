
#include"common.h"
#include"grid.h"

#include"direct3d.h"
#include"texture.h"

cGrid* cGrid::numberOfGrid;	// オブジェクト格納

LPDIRECT3DVERTEXBUFFER9	cGrid::pVertexBuffer;	// 頂点バッファ
VERTEX_3D*				cGrid::pVertex;			// 頂点バッファの中身を埋める

D3DXVECTOR3 cGrid::position;	// 位置(中央座標)
D3DXVECTOR3 cGrid::rotation;	// 回転
D3DXVECTOR3 cGrid::scale;		// 大きさ
D3DXMATRIX cGrid::worldMatrix;	// ワールドマトリックス

// 頂点セット
void cGrid::SetVertex_Grid()
{

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * NUMBER_OF_VERTEX_OF_GRID,	// 頂点データように確保するバッファサイズ(バイト単位)//頂点数
		D3DUSAGE_WRITEONLY,	// 頂点バッファの使用法
		FVF_VERTEX_3D,		// 使用する頂点フォーマット
		D3DPOOL_MANAGED,	// リソースのバッファを保持するメモリクラスを指定
		&pVertexBuffer,		// 頂点バッファインターフェースへのポインタ
		NULL
	);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	// 頂点の要素数
	int countOfVertex = 0;
	// 縦
	for (int i = 0; i < NUMBER_OF_GRAIN; i++)
	{
		pVertex[countOfVertex].vtx = D3DXVECTOR3
		(
			-(NUMBER_OF_GRAIN - 1) * SPACEING_BETWEEN_GRID_LINES / 2 + i * SPACEING_BETWEEN_GRID_LINES,
			0,
			HALF_LENGTH_OF_GRID
		);
		countOfVertex++;

		pVertex[countOfVertex].vtx = D3DXVECTOR3
		(
			-(NUMBER_OF_GRAIN - 1) * SPACEING_BETWEEN_GRID_LINES / 2 + i * SPACEING_BETWEEN_GRID_LINES,
			0,
			-HALF_LENGTH_OF_GRID
		);
		countOfVertex++;
	}
	// 横
	for (int i = 0; i < NUMBER_OF_GRAIN; i++)
	{
		pVertex[countOfVertex].vtx = D3DXVECTOR3
		(
			-HALF_LENGTH_OF_GRID,
			0,
			(NUMBER_OF_GRAIN - 1) * SPACEING_BETWEEN_GRID_LINES / 2 - i * SPACEING_BETWEEN_GRID_LINES
		);
		countOfVertex++;

		pVertex[countOfVertex].vtx = D3DXVECTOR3
		(
			HALF_LENGTH_OF_GRID,
			0,
			(NUMBER_OF_GRAIN - 1) * SPACEING_BETWEEN_GRID_LINES / 2 - i * SPACEING_BETWEEN_GRID_LINES
		);
		countOfVertex++;
	}

	// 法線ベクトルの設定
	for (int i = 0; i < NUMBER_OF_VERTEX_OF_GRID; i++)
		pVertex[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 反射光
	for (int i = 0; i < NUMBER_OF_VERTEX_OF_GRID; i++)
		pVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// 中央線は赤色
	if (NUMBER_OF_GRAIN % 2 == 1)
	{
		pVertex[NUMBER_OF_GRAIN * 2 / 2 - 1].diffuse					   = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[NUMBER_OF_GRAIN * 2 / 2].diffuse						   = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[NUMBER_OF_GRAIN * 2 + NUMBER_OF_GRAIN * 2 / 2 - 1].diffuse = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[NUMBER_OF_GRAIN * 2 + NUMBER_OF_GRAIN * 2 / 2].diffuse	   = D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}

	// テクスチャ
	for (int i = 0; i < NUMBER_OF_VERTEX_OF_GRID; i++)
		pVertex[i].tex = D3DXVECTOR2(0.0f, 0.0f);

	// 頂点データをアンロックする
	pVertexBuffer->Unlock();

}

//初期化
void cGrid::Init()
{
	numberOfGrid = new cGrid;	// 特に意味はない

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	rotation = D3DXVECTOR3(0, 0, 0);			// 回転(rad)
	scale	 = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// 大きさ
	// 行列初期化

	// 頂点設定
	SetVertex_Grid();
}

//終了処理
void cGrid::Uninit()
{
	delete numberOfGrid;
}

//更新処理
void cGrid::Update()
{

}

//ポリゴンの描画
void cGrid::Draw()
{

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX scaleMatrix;			// スケーリング行列
	D3DXMATRIX RotationMatrix;		// 回転行列
	D3DXMATRIX translationMatrix;	// 平行移動行列

	// 行列初期化
	D3DXMatrixIdentity(&worldMatrix);

	D3DXMatrixScaling(&scaleMatrix, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scaleMatrix);

	D3DXMatrixRotationYawPitchRoll(&RotationMatrix, rotation.y, rotation.x, rotation.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &RotationMatrix);

	D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);

	// ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

	// 描画したいポリゴンの頂点バッファをデータストリーム(データの通り道)セット
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));

	// 描画したいポリゴンの頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, NUMBER_OF_LINE_OF_GRID);

}