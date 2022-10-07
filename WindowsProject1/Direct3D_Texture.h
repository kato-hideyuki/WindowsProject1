//==============================================================================
// Filename: Texture.h
// Description: テクスチャ作成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include "pch.h"
class Texture
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Texture();
	~Texture();

	void Create(
		ID3D11Device* device,
		ID3D11DeviceContext* context
	);
	void Draw(
		ID3D11DeviceContext* context, 
		ID3D11Buffer* vertexBuffer
	);
private:
	//---------------------------------------------------------------------------
	// private methods.
	//---------------------------------------------------------------------------
	bool CreateTexture(
		ID3D11Device* device,
		ID3D11DeviceContext* context
	);
	bool CreateSamplerState(ID3D11Device* device);
	bool CreateRasterizer(
		ID3D11Device* device,
		ID3D11DeviceContext* context
	);
};
