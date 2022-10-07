//==============================================================================
// Filename: Shader.h
// Description: shaderのコンパイル、読み取り
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================

#pragma once
class Shader
{
public:
	//---------------------------------------------------------------------------
	//	private methods
	//---------------------------------------------------------------------------
	Shader();
	~Shader();

	void CreateShaderAndLayout(
		const WCHAR* vsPath,
		const WCHAR* psPath,
		ID3D11Device* pDevice
	);



	ID3D11VertexShader* GetVertexShader()
	{
		return m_pVertexShader;
	}
	ID3D11PixelShader* GetPixelShader()
	{
		return m_pPixelShader;
	}
	ID3D11InputLayout* GetInputLayout()
	{
		return m_pInputLayout;
	}

private:
	bool CompileShader(
		const WCHAR* vsPath,
		const WCHAR* psPath,
		ID3D11Device* pDevice
	);
	bool CreateVertexShader(
		ID3D11Device* pDevice
	);
	bool CreatePixelShader(
		ID3D11Device* pDevice
	);
	bool CreateInputLayout(
		ID3D11Device* pDevice
	);
	//---------------------------------------------------------------------------
	// private variables.
	//---------------------------------------------------------------------------
	ID3DBlob* m_vsBlob = nullptr;	//	コンパイル済み頂点シェーダー
	ID3DBlob* m_psBlob = nullptr;	//	コンパイル済みピクセルシェーダー
	ID3D11VertexShader* m_pVertexShader = nullptr;	//	頂点シェーダー
	ID3D11PixelShader* m_pPixelShader = nullptr;	//	ピクセルシェーダー
	ID3D11InputLayout* m_pInputLayout = nullptr;	//	頂点レイアウト
};

