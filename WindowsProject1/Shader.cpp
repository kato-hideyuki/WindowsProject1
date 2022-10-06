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
	ID3DBlob* vsBlob = nullptr;
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
		&vsBlob,	//	コンパイル結果のバイナリコード
		&errBlob	//	コンパイルエラー内容
	);

	if (FAILED(hr))
	{
		return false;
	}

	ID3D11VertexShader* pVertexShader = nullptr;
	hr = pDevice->CreateVertexShader(
		vsBlob->GetBufferPointer(),	//	バッファのポインタ
		vsBlob->GetBufferSize(),	//	バッファのサイズ
		nullptr,		//	クラスリンケージインターフェイスへのポインタ
		&pVertexShader	//	頂点シェーダインターフェースポインタ
	);

	return true;
}
