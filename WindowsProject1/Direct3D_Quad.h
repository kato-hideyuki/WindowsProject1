//==============================================================================
// Filename: Direct3D_Quad.h
// Description: �l�p�`�|���S���쐬
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
	static constexpr size_t VERTEX_NUM = 4;	//	���_��
	Vertex m_vertices[VERTEX_NUM];			//	�e���_�f�[�^
	ID3D11Buffer* m_pVertexBuffer = nullptr;	//	���_�o�b�t�@
	ID3D11Buffer* m_pIndexBuffer = nullptr;	//	�C���f�b�N�X�o�b�t�@
	Shader m_shader;	//	�V�F�[�_�[�R���p�C��

	static constexpr WORD m_indexList[6] = {	//	�C���f�b�N�X�f�[�^
		0,1,2,
		0,3,1
	};
};