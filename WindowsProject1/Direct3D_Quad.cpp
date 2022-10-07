//==============================================================================
// Filename: Direct3D_Quad.cpp
// Description: 四角形ポリゴン作成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Direct3D_Quad.h"

//--------------------------------------------- 
/// コンストラクタ
///
/// \return 
//--------------------------------------------- 
Quad::Quad()
{
	m_vertices[0] = {-0.25f, 0.5f, 0.5f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f,0.0f};
	m_vertices[1] = { 0.25f,-0.5f, 0.5f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f,0.0f};
	m_vertices[2] = {-0.25f,-0.5f, 0.5f,	0.0f, 0.0f, 1.0f, 1.0f,		0.0f,1.0f};
	m_vertices[3] = { 0.25f, 0.5f, 0.5f,	1.0f, 1.0f, 0.0f, 1.0f,		1.0f,1.0f};
}

//--------------------------------------------- 
/// デストラクタ
///
/// \return 
//--------------------------------------------- 
Quad::~Quad()
{
	m_pVertexBuffer->Release();
	m_pIndexBuffer->Release();
}

//--------------------------------------------- 
/// 四角形ポリゴン作成
///
/// \return 
//--------------------------------------------- 
void Quad::Create(ID3D11Device* device)
{
	CreateVertexBuffer(device);
	CreateIndexBuffer(device);
}

//--------------------------------------------- 
/// バッファ描画
/// \param[in] context 描画命令インターフェース
/// 
/// \return
//--------------------------------------------- 
void Quad::Draw(ID3D11DeviceContext* context)
{
	context->IASetInputLayout(m_shader.GetInputLayout());
	context->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->VSSetShader(m_shader.GetVertexShader(), nullptr, 0);
	context->PSSetShader(m_shader.GetPixelShader(), nullptr, 0);

	uint32_t strides = sizeof(Vertex);
	uint32_t offsets = 0;
	context->IASetVertexBuffers(
		0,	//	バインド用最初の入力スロット
		1,	//	配列内頂点バッファ数
		&m_pVertexBuffer,	//	頂点バッファポインタ
		&strides,	//	ストライド値の配列へのポインタ
		&offsets		//	オフセット値の配列へのポインタ
	);

	context->DrawIndexed(ARRAYSIZE(m_indexList), 0, 0);

}

//--------------------------------------------- 
/// 頂点バッファ作成
/// \param[in] device 描画デバイスへのインターフェース
/// 
/// \return true On Success
//--------------------------------------------- 
bool Quad::CreateVertexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexDesc = {};
	//	バッファ読み取り、書き出し指定
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	//	バッファサイズ（バイト単位）
	vertexDesc.ByteWidth = sizeof(Vertex) * VERTEX_NUM;
	//	バッファをパイプライン特定方法
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	CPUアクセスが必要か　0：必要なし
	vertexDesc.CPUAccessFlags = 0;
	//	その他フラグ　0：未使用
	vertexDesc.MiscFlags = 0;
	//	構造体が構造化バッファを表すときのサイズ
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexSub;
	vertexSub.pSysMem = m_vertices;	//	初期化データへのポインタ
	vertexSub.SysMemPitch = 0;		//	テクスチャ線の先端から隣までの距離
	vertexSub.SysMemSlicePitch = 0;	//	深度レベル先端から隣の深度レベル距離

	HRESULT hr = device->CreateBuffer(
		&vertexDesc,	//	バッファを記述する構造体ポインタ
		&vertexSub,		//	初期化データを記述する構造体ポインタ
		&m_pVertexBuffer	//	作成したバッファオブジェクト
	);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreateVertexBuffer", L"Error", MB_OK);
		return false;
	}
	m_shader.CreateShaderAndLayout(
		L"shader/vsTexture.hlsl",
		L"shader/psTexture.hlsl",
		device
	);

	return true;
}

//--------------------------------------------- 
/// インデックスバッファ作成
/// \param[in] device 描画デバイスへのインターフェース
/// 
/// \return true On Success
//--------------------------------------------- 
bool Quad::CreateIndexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC indexDesc;
	//	バッファ読み取り、書き出し指定
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	//	バッファサイズ（バイト単位）
	indexDesc.ByteWidth = sizeof(WORD) * ARRAYSIZE(m_indexList);
	//	バッファをパイプライン特定方法
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//	CPUアクセスが必要か　0：必要なし
	indexDesc.CPUAccessFlags = 0;
	//	その他フラグ　0：未使用
	indexDesc.MiscFlags = 0;
	//	構造体が構造化バッファを表すときのサイズ
	indexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexSub;
	indexSub.pSysMem = m_indexList;	//	初期化データへのポインタ
	indexSub.SysMemPitch = 0;		//	テクスチャ線の先端から隣までの距離
	indexSub.SysMemSlicePitch = 0;	//	深度レベル先端から隣の深度レベル距離

	HRESULT hr = device->CreateBuffer(
		&indexDesc,			//	バッファを記述する構造体ポインタ
		&indexSub,			//	初期化データを記述する構造体ポインタ
		&m_pIndexBuffer		//	作成したバッファオブジェクト
	);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreateIndexBuffer", L"Error", MB_OK);
		return false;
	}

	return true;
}

