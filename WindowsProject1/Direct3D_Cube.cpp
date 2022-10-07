//==============================================================================
// Filename: Direct3D_Cube.h
// Description: �����̍쐬
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Direct3D_Cube.h"
#include "Camera.h"

//--------------------------------------------- 
///	�R���X�g���N�^
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
///	�f�X�g���N�^
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
///	�L���[�u�쐬
///
/// \param[in,out] device �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
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
///	�L���[�u�`��
///
/// \param[in,out] context	�`�施�߃C���^�[�t�F�[�X
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
///	���_�o�b�t�@�쐬
///
/// \param[in,out] device �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
///
/// \return true on success
//---------------------------------------------
bool Cube::CreateVertexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexDesc = {};
	//	�o�b�t�@�ǂݎ��A�����o���w��
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	//	�o�b�t�@�T�C�Y�i�o�C�g�P�ʁj
	vertexDesc.ByteWidth = sizeof(Vertex) * VERTEX_NUM;
	//	�o�b�t�@���p�C�v���C��������@
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	CPU�A�N�Z�X���K�v���@0�F�K�v�Ȃ�
	vertexDesc.CPUAccessFlags = 0;
	//	���̑��t���O�@0�F���g�p
	vertexDesc.MiscFlags = 0;
	//	�\���̂��\�����o�b�t�@��\���Ƃ��̃T�C�Y
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexSub;
	vertexSub.pSysMem = m_vertices;	//	�������f�[�^�ւ̃|�C���^
	vertexSub.SysMemPitch = 0;		//	�e�N�X�`�����̐�[����ׂ܂ł̋���
	vertexSub.SysMemSlicePitch = 0;	//	�[�x���x����[����ׂ̐[�x���x������

	HRESULT hr = device->CreateBuffer(
		&vertexDesc,	//	�o�b�t�@���L�q����\���̃|�C���^
		&vertexSub,		//	�������f�[�^���L�q����\���̃|�C���^
		&m_pVertexBuffer	//	�쐬�����o�b�t�@�I�u�W�F�N�g
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
///	�C���f�b�N�X�o�b�t�@�쐬
///
/// \param[in,out] device �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
///
/// \return true on success
//---------------------------------------------
bool Cube::CreateIndexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC indexDesc;
	//	�o�b�t�@�ǂݏ����w��
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	//	�o�b�t�@�T�C�Y�i�o�C�g�P�ʁj
	indexDesc.ByteWidth = sizeof(WORD) * ARRAYSIZE(m_indexList);
	//	�o�b�t�@���p�C�v���C��������@
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//	CPU�A�N�Z�X���K�v���@0�F�K�v�Ȃ�
	indexDesc.CPUAccessFlags = 0;
	//	���̑��t���O�@0�F���g�p
	indexDesc.MiscFlags = 0;
	//	�\���̂��\�����o�b�t�@��\���Ƃ��̃T�C�Y
	indexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexSub;
	indexSub.pSysMem = m_indexList;	//	�������f�[�^�ւ̃|�C���^
	indexSub.SysMemPitch = 0;		//	�e�N�X�`�����̐�[����ׂ܂ł̋���
	indexSub.SysMemSlicePitch = 0;	//	�[�x���x����[����ׂ̐[�x���x������

	HRESULT hr = device->CreateBuffer(
		&indexDesc,			//	�o�b�t�@���L�q����\���̃|�C���^
		&indexSub,			//	�������f�[�^���L�q����\���̃|�C���^
		&m_pIndexBuffer		//	�쐬�����o�b�t�@�I�u�W�F�N�g
	);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreateIndexBuffer", L"Error", MB_OK);
		return false;
	}

	return true;
}

//--------------------------------------------- 
///	�萔�o�b�t�@�쐬
///
/// \param[in,out] device �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
///
/// \return true on success
//---------------------------------------------
bool Cube::CreateConstantBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC constDesc;
	//	�o�b�t�@�T�C�Y�i�o�C�g�P�ʁj
	constDesc.ByteWidth = sizeof(ConstantBuffer);
	//	�o�b�t�@�ǂݏ����w��
	constDesc.Usage = D3D11_USAGE_DEFAULT;	
	//	�o�b�t�@���p�C�v���C��������@
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//	CPU�A�N�Z�X���K�v���@0�F�K�v�Ȃ�
	constDesc.CPUAccessFlags = 0;
	//	���̑��t���O�@0�F���g�p
	constDesc.MiscFlags = 0;
	//	�\���̂��\�����o�b�t�@��\���Ƃ��̃T�C�Y
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
