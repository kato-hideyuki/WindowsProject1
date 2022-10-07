//==============================================================================
// Filename: Direct3D_Cube.h
// Description: �����̍쐬
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

class Vertex
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Vertex(){}
	Vertex(
		float x, float y, float z,
		float r, float g, float b, float a,
		float u, float v
	)
	{
		position = { x,y,z };
		color = { r,g,b,a };
		texcoord = { u,v };
	}
	//---------------------------------------------------------------------------
	// public variables.
	//---------------------------------------------------------------------------
	DirectX::XMFLOAT3 position;	//	���W�l
	DirectX::XMFLOAT4 color;	//	rgba�J���[�l
	DirectX::XMFLOAT2 texcoord;	//	UV���W
};
