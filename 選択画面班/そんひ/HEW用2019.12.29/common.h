#pragma once

// 3Dポリゴン頂点フォーマット(頂点座標[3D]/法線/反射光/テクスチャ座標)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// スクリーンサイズ(クライアント領域)
#define SCREEN_WIDTH	(1024)	// 幅
#define SCREEN_HEIGHT	(576)	// 高さ