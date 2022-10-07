//==============================================================================
// Filename: Shader.h
// Description: shader�̃R���p�C���A�ǂݎ��
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#include "pch.h"
#include "Shader.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

//--------------------------------------------- 
/// �R���X�g���N�^
/// 
/// \return 
//--------------------------------------------- 
Shader::Shader()
{
}

//--------------------------------------------- 
/// �f�X�g���N�^
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
/// shader��layout�̍쐬
/// \param[in]		vsPath	���_�V�F�[�_�@�t�@�C���p�X
/// \param[in]		psPath	�s�N�Z���V�F�[�_�@�t�@�C���p�X
/// \param[inout]	device	�`��f�o�C�X�C���^�[�t�F�[�X
///
/// \return True On Success
//--------------------------------------------- 
void Shader::CreateShaderAndLayout(
	const WCHAR* vsPath, 
	const WCHAR* psPath, 
	ID3D11Device* pDevice
)
{
	//	�V�F�[�_�[�̃R���p�C��
	CompileShader(
		vsPath,
		psPath,
		pDevice
	);
	//	���_�V�F�[�_�[�쐬
	CreateVertexShader(pDevice);
	//	���_���C�A�E�g�쐬
	CreateInputLayout(pDevice);
	//	�s�N�Z���V�F�[�_�[�쐬
	CreatePixelShader(pDevice);
}

//--------------------------------------------- 
/// shader�̃R���p�C��
/// \param[in]		vsPath	���_�V�F�[�_�@�t�@�C���p�X
/// \param[in]		psPath	�s�N�Z���V�F�[�_�@�t�@�C���p�X
/// \param[inout]	device	�`��f�o�C�X�C���^�[�t�F�[�X
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
		vsPath,		//	�V�F�[�_�[�R�[�h�t�@�C����
		nullptr,	//	�V�F�[�_�[�}�N����`�@���g�p:nullptr
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//	�C���N���[�h��舵���w��
		"main",		//	�G���g���[�|�C���g�֐�
		"vs_4_0",	//	�V�F�[�_�[���f��
		D3DCOMPILE_DEBUG |				//	�R���p�C���I�v�V����
		D3DCOMPILE_SKIP_OPTIMIZATION,	//	�R���p�C���I�v�V����
		0,			//	�R���p�C���I�v�V�����i�V�F�[�_�[��0�j
		&m_vsBlob,	//	�R���p�C�����ʂ̃o�C�i���R�[�h
		&errBlob	//	�R���p�C���G���[���e
	);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"VS ComPile", L"Error", MB_OK);
		return false;
	}

	hr = D3DCompileFromFile(
		psPath,		//	�V�F�[�_�[�R�[�h�t�@�C����
		nullptr,	//	�V�F�[�_�[�}�N����`�@���g�p:nullptr
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//	�C���N���[�h��舵���w��
		"main",		//	�G���g���[�|�C���g�֐�
		"ps_4_0",	//	�V�F�[�_�[���f��
		D3DCOMPILE_DEBUG |				//	�R���p�C���I�v�V����
		D3DCOMPILE_SKIP_OPTIMIZATION,	//	�R���p�C���I�v�V����
		0,			//	�R���p�C���I�v�V�����i�V�F�[�_�[��0�j
		&m_psBlob,	//	�R���p�C�����ʂ̃o�C�i���R�[�h
		&errBlob	//	�R���p�C���G���[���e
	);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"PS Compile", L"Error", MB_OK);
		return false;
	}

	return true;
}
//--------------------------------------------- 
/// ���_�V�F�[�_�[�쐬
/// \param[inout]	device	�`��f�o�C�X�C���^�[�t�F�[�X
///
/// \return True On Success
//--------------------------------------------- 
bool Shader::CreateVertexShader(ID3D11Device* device)
{
	HRESULT hr;
	ID3D11VertexShader* pVertexShader = nullptr;	//	���_�V�F�[�_�[�I�u�W�F�N�g
	hr = device->CreateVertexShader(
		m_vsBlob->GetBufferPointer(),	//	�R���p�C���ς݃V�F�[�_�[�̃|�C���^
		m_vsBlob->GetBufferSize(),	//	�R���p�C���ς݃V�F�[�_�[�̃T�C�Y
		nullptr,		//	�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^
		&pVertexShader	//	���_�V�F�[�_�C���^�[�t�F�[�X�|�C���^
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
/// �s�N�Z���V�F�[�_�[�쐬
/// \param[inout]	device	�`��f�o�C�X�C���^�[�t�F�[�X
///
/// \return True On Success
//--------------------------------------------- 
bool Shader::CreatePixelShader(ID3D11Device* device)
{
	HRESULT hr;
	ID3D11PixelShader* pPixelShader = nullptr;	//	�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	hr = device->CreatePixelShader(
		m_psBlob->GetBufferPointer(),	//	�R���p�C���ς݃V�F�[�_�[�̃|�C���^
		m_psBlob->GetBufferSize(),	//	�R���p�C���ς݃V�F�[�_�[�̃T�C�Y
		nullptr,		//	�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^
		&pPixelShader	//	���_�V�F�[�_�C���^�[�t�F�[�X�|�C���^
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
/// ���_���C�A�E�g�쐬
/// \param[inout]	device	�`��f�o�C�X�C���^�[�t�F�[�X
///
/// \return True On Success
//--------------------------------------------- 
bool Shader::CreateInputLayout(ID3D11Device* device)
{
	HRESULT hr;
	ID3D11InputLayout* pInputLayout = nullptr;	//	���̓��C�A�E�g�I�u�W�F�N�g
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{
			"POSITION",	//	HLSL�Z�}���e�B�b�N��
			0,			//	�v�f�̃Z�}���e�B�b�N�C���f�b�N�X
			DXGI_FORMAT_R32G32B32_FLOAT,	//	�v�f�f�[�^�^
			0,			//	���̓A�Z���u�����ʐ����l
			0,			//	���_�擪����̃I�t�Z�b�g
			D3D11_INPUT_PER_VERTEX_DATA,	//	���̓f�[�^�N���X����
			0			//	�����C���X�^���X���Ƃ̕`��C���X�^���X��
		},
		{ 
			"COLOR",	//	HLSL�Z�}���e�B�b�N��
			0,			//	�v�f�̃Z�}���e�B�b�N�C���f�b�N�X
			DXGI_FORMAT_R32G32B32A32_FLOAT, //	�v�f�f�[�^�^
			0,			//	���̓A�Z���u�����ʐ����l
			D3D11_APPEND_ALIGNED_ELEMENT,	//	���_�擪����̃I�t�Z�b�g
			D3D11_INPUT_PER_VERTEX_DATA,	//	���̓f�[�^�N���X����
			0			//	�����C���X�^���X���Ƃ̕`��C���X�^���X��
		},
	};
	hr = device->CreateInputLayout(
		layout,		//	���̓f�[�^�^�z��
		_countof(layout),	//	�z������̓f�[�^�^�̐�
		m_vsBlob->GetBufferPointer(),	//	�R���p�C���ς݃V�F�[�_�[�̃|�C���^
		m_vsBlob->GetBufferSize(),	//	�R���p�C���ς݃V�F�[�_�[�̃T�C�Y
		&pInputLayout		//	���̓��C�A�E�g�I�u�W�F�N�g
	);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"CreateInputLayout", L"Error", MB_OK);
		return false;
	}

	m_pInputLayout = pInputLayout;
	return true;
}
