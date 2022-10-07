//==============================================================================
// Filename: Direct3D_Cube.h
// Description: 立方体作成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include "pch.h"
class Cube
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Cube();
	~Cube();

	void Create(ID3D11Device* device);
	void Draw(
		ID3D11DeviceContext* context,
		ID3D11DepthStencilView* depthStencilView,
		ID3D11RenderTargetView* renderTargetView
	);

private:
	//---------------------------------------------------------------------------
	// private methods.
	//---------------------------------------------------------------------------
	bool CreateVertexBuffer(ID3D11Device* device);
	bool CreateIndexBuffer(ID3D11Device* device);
	bool CreateConstantBuffer(ID3D11Device* device);
	//---------------------------------------------------------------------------
	// private variables.
	//---------------------------------------------------------------------------
	static constexpr size_t VERTEX_NUM = 4*6;	//	頂点数
	Vertex m_vertices[VERTEX_NUM];				//	各頂点データ
	ID3D11Buffer* m_pVertexBuffer = nullptr;	//	頂点バッファ
	ID3D11Buffer* m_pIndexBuffer = nullptr;		//	インデックスバッファ
	ID3D11Buffer* m_pConstantBuffer = nullptr;	//	定数バッファ
	Shader m_shader;	//	シェーダーコンパイラ

	static constexpr WORD m_indexList[] = {    //  インデックスデータ
		0,  1,  2,     3,  2,  1,
		4,  5,  6,     7,  6,  5,
		8,  9, 10,    11, 10,  9,
	   12, 13, 14,    15, 14, 13,
	   16, 17, 18,    19, 18, 17,
	   20, 21, 22,    23, 22, 21,
	};
};
