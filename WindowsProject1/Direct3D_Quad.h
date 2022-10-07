//==============================================================================
// Filename: Direct3D_Quad.h
// Description: 四角形ポリゴン作成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include "pch.h"
#include "Shader.h"

class Quad
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Quad();
	~Quad();

	void Create(ID3D11Device* device);
	void Draw(ID3D11DeviceContext* context);

private:
	//---------------------------------------------------------------------------
	// private methods.
	//---------------------------------------------------------------------------
	bool CreateVertexBuffer(ID3D11Device* device);
	bool CreateIndexBuffer(ID3D11Device* device);
	//---------------------------------------------------------------------------
	// private variables.
	//---------------------------------------------------------------------------
	static constexpr size_t VERTEX_NUM = 4;	//	頂点数
	Vertex m_vertices[VERTEX_NUM];			//	各頂点データ
	ID3D11Buffer* m_pVertexBuffer = nullptr;	//	頂点バッファ
	ID3D11Buffer* m_pIndexBuffer = nullptr;	//	インデックスバッファ
	Shader m_shader;	//	シェーダーコンパイラ

	static constexpr WORD m_indexList[6] = {	//	インデックスデータ
		0,1,2,
		0,3,1
	};
};