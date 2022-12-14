//==============================================================================
// Filename: Direct3D_Triangle.h
// Description: 三角ポリゴン作成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#pragma once
#include "Direct3D_Vertex.h"
#include "Shader.h"

class Triangle
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Triangle();
	~Triangle();

	void Create(ID3D11Device* device);
	void Draw(ID3D11DeviceContext* context);

private:
	//---------------------------------------------------------------------------
	// private methods.
	//---------------------------------------------------------------------------
	bool CreateVertexBuffer(ID3D11Device* device);
	//---------------------------------------------------------------------------
	// private variables.
	//---------------------------------------------------------------------------
	static constexpr size_t VERTEX_NUM = 3;	//	頂点数
	Vertex m_vertices[VERTEX_NUM];			//	各頂点データ
	ID3D11Buffer* m_pVertexBuffer = nullptr;//	頂点バッファ
	Shader m_shader;			//	シェーダーコンパイラー
};