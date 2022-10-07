//==============================================================================
// Filename: Direct3D_Triangle.cpp
// Description: �O�p�|���S���쐬
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#include "pch.h"
#include "Direct3D_Triangle.h"

//--------------------------------------------- 
/// �R���X�g���N�^
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
/// �f�X�g���N�^
///
/// \return 
//--------------------------------------------- 
Triangle::~Triangle()
{
	m_pVertexBuffer->Release();
}

//--------------------------------------------- 
/// �o�b�t�@�`��
/// 
/// \return
//--------------------------------------------- 
void Triangle::Create(ID3D11Device* device)
{
	CreateVertexBuffer(device);
}

//--------------------------------------------- 
/// �o�b�t�@�`��
/// \param[in] context �`�施�߃C���^�[�t�F�[�X
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
		0,	//	�o�C���h�p�ŏ��̓��̓X���b�g
		1,	//	�z������_�o�b�t�@��
		&m_pVertexBuffer,	//	���_�o�b�t�@�|�C���^
		&strides,	//	�X�g���C�h�l�̔z��ւ̃|�C���^
		&offsets		//	�I�t�Z�b�g�l�̔z��ւ̃|�C���^
	);
	context->Draw(VERTEX_NUM, 0);
}

//--------------------------------------------- 
/// ���_�o�b�t�@�쐬
/// \param[in] device �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
/// 
/// \return true On Success
//--------------------------------------------- 
bool Triangle::CreateVertexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	//	�o�b�t�@�ǂݎ��A�����o���w��
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//	�o�b�t�@�T�C�Y�i�o�C�g�P�ʁj
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * VERTEX_NUM;
	//	�o�b�t�@���p�C�v���C��������@
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	CPU�A�N�Z�X���K�v���@0�F�K�v�Ȃ�
	vertexBufferDesc.CPUAccessFlags = 0;
	//	���̑��t���O�@0�F���g�p
	vertexBufferDesc.MiscFlags = 0;
	//	�\���̂��\�����o�b�t�@��\���Ƃ��̃T�C�Y
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexSubData;
	vertexSubData.pSysMem = m_vertices;	//	�������f�[�^�ւ̃|�C���^
	vertexSubData.SysMemPitch = 0;		//	�e�N�X�`�����̐�[����ׂ܂ł̋���
	vertexSubData.SysMemSlicePitch = 0;	//	�[�x���x����[����ׂ̐[�x���x������

	HRESULT hr = device->CreateBuffer(
		&vertexBufferDesc,	//	�o�b�t�@���L�q����\���̃|�C���^
		&vertexSubData,		//	�������f�[�^���L�q����\���̃|�C���^
		&m_pVertexBuffer		//	�쐬�����o�b�t�@�I�u�W�F�N�g
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