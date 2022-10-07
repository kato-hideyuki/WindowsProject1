//==============================================================================
// Filename: Direct3D_Quad.cpp
// Description: �l�p�`�|���S���쐬
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Direct3D_Quad.h"

//--------------------------------------------- 
/// �R���X�g���N�^
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
/// �f�X�g���N�^
///
/// \return 
//--------------------------------------------- 
Quad::~Quad()
{
	m_pVertexBuffer->Release();
	m_pIndexBuffer->Release();
}

//--------------------------------------------- 
/// �l�p�`�|���S���쐬
///
/// \return 
//--------------------------------------------- 
void Quad::Create(ID3D11Device* device)
{
	CreateVertexBuffer(device);
	CreateIndexBuffer(device);
}

//--------------------------------------------- 
/// �o�b�t�@�`��
/// \param[in] context �`�施�߃C���^�[�t�F�[�X
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
		0,	//	�o�C���h�p�ŏ��̓��̓X���b�g
		1,	//	�z������_�o�b�t�@��
		&m_pVertexBuffer,	//	���_�o�b�t�@�|�C���^
		&strides,	//	�X�g���C�h�l�̔z��ւ̃|�C���^
		&offsets		//	�I�t�Z�b�g�l�̔z��ւ̃|�C���^
	);

	context->DrawIndexed(ARRAYSIZE(m_indexList), 0, 0);

}

//--------------------------------------------- 
/// ���_�o�b�t�@�쐬
/// \param[in] device �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
/// 
/// \return true On Success
//--------------------------------------------- 
bool Quad::CreateVertexBuffer(ID3D11Device* device)
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
		L"shader/vsTexture.hlsl",
		L"shader/psTexture.hlsl",
		device
	);

	return true;
}

//--------------------------------------------- 
/// �C���f�b�N�X�o�b�t�@�쐬
/// \param[in] device �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
/// 
/// \return true On Success
//--------------------------------------------- 
bool Quad::CreateIndexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC indexDesc;
	//	�o�b�t�@�ǂݎ��A�����o���w��
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

