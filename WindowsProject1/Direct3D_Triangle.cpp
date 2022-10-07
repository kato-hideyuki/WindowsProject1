//==============================================================================
// Filename: Direct3D_Triangle.cpp
// Description: 三角ポリゴン作成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#include "pch.h"
#include "Direct3D_Triangle.h"

//--------------------------------------------- 
/// コンストラクタ
///
/// \return 
//--------------------------------------------- 
Triangle::Triangle()
{
	m_vertices[0] = { 0.0f, 0.5f, 0.0f,		1.0f, 1.0f, 1.0f, 1.0f,		0.5f,0.0f };
	m_vertices[1] = { 0.5f,-0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 1.0f,		0.0f,1.0f };
	m_vertices[2] = { -0.5f,-0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f,1.0f };
}

//--------------------------------------------- 
/// デストラクタ
///
/// \return 
//--------------------------------------------- 
Triangle::~Triangle()
{
	m_pVertexBuffer->Release();
}

//--------------------------------------------- 
/// バッファ描画
/// 
/// \return
//--------------------------------------------- 
void Triangle::Create(ID3D11Device* device)
{
	CreateVertexBuffer(device);
}

//--------------------------------------------- 
/// バッファ描画
/// \param[in] context 描画命令インターフェース
/// 
/// \return
//--------------------------------------------- 
void Triangle::Draw(ID3D11DeviceContext* context)
{
	context->IASetInputLayout(m_shader.GetInputLayout());
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
	context->Draw(VERTEX_NUM, 0);
}

//--------------------------------------------- 
/// 頂点バッファ作成
/// \param[in] device 描画デバイスへのインターフェース
/// 
/// \return true On Success
//--------------------------------------------- 
bool Triangle::CreateVertexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	//	バッファ読み取り、書き出し指定
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//	バッファサイズ（バイト単位）
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * VERTEX_NUM;
	//	バッファをパイプライン特定方法
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	CPUアクセスが必要か　0：必要なし
	vertexBufferDesc.CPUAccessFlags = 0;
	//	その他フラグ　0：未使用
	vertexBufferDesc.MiscFlags = 0;
	//	構造体が構造化バッファを表すときのサイズ
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexSubData;
	vertexSubData.pSysMem = m_vertices;	//	初期化データへのポインタ
	vertexSubData.SysMemPitch = 0;		//	テクスチャ線の先端から隣までの距離
	vertexSubData.SysMemSlicePitch = 0;	//	深度レベル先端から隣の深度レベル距離

	HRESULT hr = device->CreateBuffer(
		&vertexBufferDesc,	//	バッファを記述する構造体ポインタ
		&vertexSubData,		//	初期化データを記述する構造体ポインタ
		&m_pVertexBuffer		//	作成したバッファオブジェクト
	);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreateBuffer", L"Error", MB_OK);
		return false;
	}
	m_shader.CreateShaderAndLayout(
		L"shader/vs.hlsl",
		L"shader/ps.hlsl",
		device
	);

	return true;
}