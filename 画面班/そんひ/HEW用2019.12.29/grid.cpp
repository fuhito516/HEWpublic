
#include"grid.h"
// システム
#include"common.h"
#include"directx.h"
// 描画
#include"texture.h"
#include"sprite.h"
#include"vertex.h"

cGrid gcGrid;

void cGrid::Init_Grid()
{	
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * GRID_NUMBER_OF_VERTEX,	// 頂点データように確保するバッファサイズ(バイト単位)//頂点数
		D3DUSAGE_WRITEONLY,		// 頂点バッファの使用法
		FVF_VERTEX_3D,			// 使用する頂点フォーマット
		D3DPOOL_MANAGED,		// リソースのバッファを保持するメモリクラスを指定
		&pVertexBuffer,			// 頂点バッファインターフェースへのポインタ
		NULL
	);
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
	
	int count_of_vtx = 0;
	// 縦
	for (int i = 0; i < GRID_NUMBER; i++)
	{
		pVertex[count_of_vtx].vtx = 
			D3DXVECTOR3(-(GRID_NUMBER - 1) * GRID_INTERVALLENGTH / 2 + i * GRID_INTERVALLENGTH, 0, GRID_HALF_OF_LINELENGTH);
		count_of_vtx++;
		pVertex[count_of_vtx].vtx = 
			D3DXVECTOR3(-(GRID_NUMBER - 1) * GRID_INTERVALLENGTH / 2 + i * GRID_INTERVALLENGTH, 0, -GRID_HALF_OF_LINELENGTH);
		count_of_vtx++;
	}
	// 横
	for (int i = 0; i < GRID_NUMBER; i++)
	{
		pVertex[count_of_vtx].vtx =
			D3DXVECTOR3(-GRID_HALF_OF_LINELENGTH, 0, (GRID_NUMBER - 1) * GRID_INTERVALLENGTH / 2 - i * GRID_INTERVALLENGTH);
		count_of_vtx++;
		pVertex[count_of_vtx].vtx =
			D3DXVECTOR3(GRID_HALF_OF_LINELENGTH, 0, (GRID_NUMBER - 1) * GRID_INTERVALLENGTH / 2 - i * GRID_INTERVALLENGTH);
		count_of_vtx++;
	}

	// 法線ベクトルの設定
	for (int i = 0; i < GRID_NUMBER_OF_VERTEX; i++)
		pVertex[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 反射光
	for (int i = 0; i < GRID_NUMBER_OF_VERTEX; i++)
		pVertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (GRID_NUMBER % 2 == 1)
	{
		pVertex[GRID_NUMBER * 2 / 2 - 1].diffuse					= D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[GRID_NUMBER * 2 / 2].diffuse						= D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[GRID_NUMBER * 2 + GRID_NUMBER * 2 / 2 - 1].diffuse	= D3DXCOLOR(1.0f, 0, 0, 1.0f);
		pVertex[GRID_NUMBER * 2 + GRID_NUMBER * 2 / 2].diffuse		= D3DXCOLOR(1.0f, 0, 0, 1.0f);
	}

	// テクスチャ
	for (int i = 0; i < GRID_NUMBER_OF_VERTEX; i++)
		pVertex[i].tex = D3DXVECTOR2(0.0f, 0.0f);

	// 頂点データをアンロックする
	pVertexBuffer->Unlock();
}
void cGrid::Uninit_Grid()
{

}
void cGrid::Update_Grid()
{

}
void cGrid::Draw_Grid()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX mtxScl;	// スケーリング行列
	D3DXMATRIX mtxRot;	// 回転行列
	D3DXMATRIX mtxTrs;	// 平行移動行列

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	rot = D3DXVECTOR3(0, 0, 0);				// 向き(回転)(rad)
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// 大きさ(スケール)

	D3DXMatrixIdentity(&worldMtx);

	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxRot);

	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&worldMtx, &worldMtx, &mtxTrs);

	pDevice->SetTransform(D3DTS_WORLD, &worldMtx);

	// 描画したいポリゴンの頂点バッファをデータストリーム(データの通り道)セット
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
	// 描画したいポリゴンの頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	// ポリゴンの描画
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, GRID_NUMBER_OF_LINE);
}

cGrid* GetGrid()
{
	return &gcGrid;
}