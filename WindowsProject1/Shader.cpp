//==============================================================================
// Filename: Shader.h
// Description: shaderのコンパイル、読み取り
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#include "pch.h"
#include "Shader.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

//--------------------------------------------- 
/// コンストラクタ
/// 
/// \return 
//--------------------------------------------- 
Shader::Shader()
{
}

//--------------------------------------------- 
/// デストラクタ
/// 
/// \return 
//--------------------------------------------- 
Shader::~Shader()
{
	m_pVertexShader->Release();
	m_pPixelShader->Release();
	m_pInputLayout->Release();
}

//--------------------------------------------- 
/// shaderとlayoutの作成
/// \param[in]		vsPath	頂点シェーダ　ファイルパス
/// \param[in]		psPath	ピクセルシェーダ　ファイルパス
/// \param[inout]	device	描画デバイスインターフェース
///
/// \return True On Success
//--------------------------------------------- 
void Shader::CreateShaderAndLayout(
	const WCHAR* vsPath, 
	const WCHAR* psPath, 
	ID3D11Device* pDevice
)
{
	//	シェーダーのコンパイル
	CompileShader(
		vsPath,
		psPath,
		pDevice
	);
	//	頂点シェーダー作成
	CreateVertexShader(pDevice);
	//	頂点レイアウト作成
	CreateInputLayout(pDevice);
	//	ピクセルシェーダー作成
	CreatePixelShader(pDevice);
}

//--------------------------------------------- 
/// shaderのコンパイル
/// \param[in]		vsPath	頂点シェーダ　ファイルパス
/// \param[in]		psPath	ピクセルシェーダ　ファイルパス
/// \param[inout]	device	描画デバイスインターフェース
///
/// \return True On Success
//--------------------------------------------- 
bool Shader::CompileShader(
	const WCHAR* vsPath,
	const WCHAR* psPath,
	ID3D11Device* device
)
{
	ID3DBlob* errBlob = nullptr;
	ID3D11Device* pDevice = device;

	HRESULT hr = D3DCompileFromFile(
		vsPath,		//	シェーダーコードファイル名
		nullptr,	//	シェーダーマクロ定義　未使用:nullptr
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//	インクルード取り扱い指定
		"main",		//	エントリーポイント関数
		"vs_4_0",	//	シェーダーモデル
		D3DCOMPILE_DEBUG |				//	コンパイルオプション
		D3DCOMPILE_SKIP_OPTIMIZATION,	//	コンパイルオプション
		0,			//	コンパイルオプション（シェーダーは0）
		&m_vsBlob,	//	コンパイル結果のバイナリコード
		&errBlob	//	コンパイルエラー内容
	);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"VS ComPile", L"Error", MB_OK);
		return false;
	}

	hr = D3DCompileFromFile(
		psPath,		//	シェーダーコードファイル名
		nullptr,	//	シェーダーマクロ定義　未使用:nullptr
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//	インクルード取り扱い指定
		"main",		//	エントリーポイント関数
		"ps_4_0",	//	シェーダーモデル
		D3DCOMPILE_DEBUG |				//	コンパイルオプション
		D3DCOMPILE_SKIP_OPTIMIZATION,	//	コンパイルオプション
		0,			//	コンパイルオプション（シェーダーは0）
		&m_psBlob,	//	コンパイル結果のバイナリコード
		&errBlob	//	コンパイルエラー内容
	);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"PS Compile", L"Error", MB_OK);
		return false;
	}

	return true;
}
//--------------------------------------------- 
/// 頂点シェーダー作成
/// \param[inout]	device	描画デバイスインターフェース
///
/// \return True On Success
//--------------------------------------------- 
bool Shader::CreateVertexShader(ID3D11Device* device)
{
	HRESULT hr;
	ID3D11VertexShader* pVertexShader = nullptr;	//	頂点シェーダーオブジェクト
	hr = device->CreateVertexShader(
		m_vsBlob->GetBufferPointer(),	//	コンパイル済みシェーダーのポインタ
		m_vsBlob->GetBufferSize(),	//	コンパイル済みシェーダーのサイズ
		nullptr,		//	クラスリンケージインターフェイスへのポインタ
		&pVertexShader	//	頂点シェーダインターフェースポインタ
	);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreateVertexShader", L"Error", MB_OK);
		return false;
	}

	m_pVertexShader = pVertexShader;
	return true;
}
//--------------------------------------------- 
/// ピクセルシェーダー作成
/// \param[inout]	device	描画デバイスインターフェース
///
/// \return True On Success
//--------------------------------------------- 
bool Shader::CreatePixelShader(ID3D11Device* device)
{
	HRESULT hr;
	ID3D11PixelShader* pPixelShader = nullptr;	//	ピクセルシェーダーオブジェクト
	hr = device->CreatePixelShader(
		m_psBlob->GetBufferPointer(),	//	コンパイル済みシェーダーのポインタ
		m_psBlob->GetBufferSize(),	//	コンパイル済みシェーダーのサイズ
		nullptr,		//	クラスリンケージインターフェイスへのポインタ
		&pPixelShader	//	頂点シェーダインターフェースポインタ
	);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreatePixelShader", L"Error", MB_OK);
		return false;
	}

	m_pPixelShader = pPixelShader;
	return true;
}
//--------------------------------------------- 
/// 頂点レイアウト作成
/// \param[inout]	device	描画デバイスインターフェース
///
/// \return True On Success
//--------------------------------------------- 
bool Shader::CreateInputLayout(ID3D11Device* device)
{
	HRESULT hr;
	ID3D11InputLayout* pInputLayout = nullptr;	//	入力レイアウトオブジェクト
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{
			"POSITION",	//	HLSLセマンティック名
			0,			//	要素のセマンティックインデックス
			DXGI_FORMAT_R32G32B32_FLOAT,	//	要素データ型
			0,			//	入力アセンブラ識別整数値
			0,			//	頂点先頭からのオフセット
			D3D11_INPUT_PER_VERTEX_DATA,	//	入力データクラス識別
			0			//	同じインスタンスごとの描画インスタンス数
		},
		{ 
			"COLOR",	//	HLSLセマンティック名
			0,			//	要素のセマンティックインデックス
			DXGI_FORMAT_R32G32B32A32_FLOAT, //	要素データ型
			0,			//	入力アセンブラ識別整数値
			D3D11_APPEND_ALIGNED_ELEMENT,	//	頂点先頭からのオフセット
			D3D11_INPUT_PER_VERTEX_DATA,	//	入力データクラス識別
			0			//	同じインスタンスごとの描画インスタンス数
		},
	};
	hr = device->CreateInputLayout(
		layout,		//	入力データ型配列
		_countof(layout),	//	配列内入力データ型の数
		m_vsBlob->GetBufferPointer(),	//	コンパイル済みシェーダーのポインタ
		m_vsBlob->GetBufferSize(),	//	コンパイル済みシェーダーのサイズ
		&pInputLayout		//	入力レイアウトオブジェクト
	);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreateInputLayout", L"Error", MB_OK);
		return false;
	}

	m_pInputLayout = pInputLayout;
	return true;
}
