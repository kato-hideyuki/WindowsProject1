//==============================================================================
// Filename: Direct3D_Cube.h
// Description: 立方体作成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Direct3D_Cube.h"
#include "Camera.h"

//--------------------------------------------- 
///	コンストラクタ
///
/// \return 
//---------------------------------------------
Cube::Cube()
{
   m_vertices[0] = { -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,	0.0f,0.0f };
   m_vertices[1] = { 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,	1.0f,0.0f };
   m_vertices[2] = { -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,	0.0f,1.0f };
   m_vertices[3] = { 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,	1.0f,1.0f };
                                                                   
   m_vertices[4]  = { -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,	0.0f,0.0f   };
   m_vertices[5]  = { -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,	1.0f,0.0f   };
   m_vertices[6]  = {  0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,	0.0f,1.0f   };
   m_vertices[7]  = {  0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,	1.0f,1.0f   };
                                                                    
   m_vertices[8]  = { -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f,	0.0f,0.0f };
   m_vertices[9] = { -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,	1.0f,0.0f };
   m_vertices[10] = { -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f,	0.0f,1.0f };
   m_vertices[11] = { -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,	1.0f,1.0f };
                                                                     
   m_vertices[12] = {  0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f,0.0f };
   m_vertices[13] = { 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f,0.0f };
   m_vertices[14] = { 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f,1.0f };
   m_vertices[15] = { 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f,1.0f };
                                                                     
   m_vertices[16] = { -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f,0.0f };
   m_vertices[17] = { 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f,0.0f };
   m_vertices[18] = { -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f,1.0f };
   m_vertices[19] = { 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f,1.0f };
                                                                     
   m_vertices[20] = { -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,0.0f };
   m_vertices[21] = { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,0.0f };
   m_vertices[22] = { 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,1.0f };
   m_vertices[23] = { 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,1.0f };
}

//--------------------------------------------- 
///	デストラクタ
///
/// \return 
//---------------------------------------------
Cube::~Cube()
{
    m_pVertexBuffer->Release();
    m_pIndexBuffer->Release();
	m_pConstantBuffer->Release();
}

//--------------------------------------------- 
///	キューブ作成
///
/// \param[in,out] device 描画デバイスへのインターフェース
///
/// \return 
//---------------------------------------------
void Cube::Create(ID3D11Device* device)
{
    CreateVertexBuffer(device);
    CreateIndexBuffer(device);
	CreateConstantBuffer(device);
}

//--------------------------------------------- 
///	キューブ描画
///
/// \param[in,out] context	描画命令インターフェース
///
/// \return 
//---------------------------------------------
void Cube::Draw(
	ID3D11DeviceContext* context,
	ID3D11DepthStencilView* depthStencilView,
	ID3D11RenderTargetView* renderTargetView
)
{
	ConstantBuffer cb;
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
		//DirectX::XMLoadFloat4x4(&Camera::GetInstance()->GetWorldMtx());
	DirectX::XMMATRIX view =
		DirectX::XMLoadFloat4x4(&Camera::GetInstance()->GetView());
	DirectX::XMMATRIX projection =
		DirectX::XMLoadFloat4x4(&Camera::GetInstance()->GetProjection());

	DirectX::XMStoreFloat4x4(
		&cb.world,
		DirectX::XMMatrixTranspose(world)
	);
	DirectX::XMStoreFloat4x4(
		&cb.view,
		DirectX::XMMatrixTranspose(view)
	);
	DirectX::XMStoreFloat4x4(
		&cb.projection,
		DirectX::XMMatrixTranspose(projection)
	);
	context->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

	context->IASetInputLayout(m_shader.GetInputLayout());
	context->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	context->VSSetShader(m_shader.GetVertexShader(), NULL, 0);
	context->PSSetShader(m_shader.GetPixelShader(), NULL, 0);
	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);


	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
		1.0f, 
		0
	);
	context->DrawIndexed(36, 0, 0);
}

//--------------------------------------------- 
///	頂点バッファ作成
///
/// \param[in,out] device 描画デバイスへのインターフェース
///
/// \return true on success
//---------------------------------------------
bool Cube::CreateVertexBuffer(ID3D11Device* device)
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
		L"shader/vsCube.hlsl",
		L"shader/psCube.hlsl",
		device
	);

	return true;
}

//--------------------------------------------- 
///	インデックスバッファ作成
///
/// \param[in,out] device 描画デバイスへのインターフェース
///
/// \return true on success
//---------------------------------------------
bool Cube::CreateIndexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC indexDesc;
	//	バッファ読み書き指定
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

//--------------------------------------------- 
///	定数バッファ作成
///
/// \param[in,out] device 描画デバイスへのインターフェース
///
/// \return true on success
//---------------------------------------------
bool Cube::CreateConstantBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC constDesc;
	//	バッファサイズ（バイト単位）
	constDesc.ByteWidth = sizeof(ConstantBuffer);
	//	バッファ読み書き指定
	constDesc.Usage = D3D11_USAGE_DEFAULT;	
	//	バッファをパイプライン特定方法
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//	CPUアクセスが必要か　0：必要なし
	constDesc.CPUAccessFlags = 0;
	//	その他フラグ　0：未使用
	constDesc.MiscFlags = 0;
	//	構造体が構造化バッファを表すときのサイズ
	constDesc.StructureByteStride = 0;

	HRESULT hr = device->CreateBuffer(
		&constDesc,
		NULL,
		&m_pConstantBuffer
	);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreateConstantBuffer", L"Error", MB_OK);
		return false;
	}

	return true;;
}
