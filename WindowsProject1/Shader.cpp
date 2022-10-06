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
	ID3DBlob* vsBlob = nullptr;
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
		&vsBlob,	//	�R���p�C�����ʂ̃o�C�i���R�[�h
		&errBlob	//	�R���p�C���G���[���e
	);

	if (FAILED(hr))
	{
		return false;
	}

	ID3D11VertexShader* pVertexShader = nullptr;
	hr = pDevice->CreateVertexShader(
		vsBlob->GetBufferPointer(),	//	�o�b�t�@�̃|�C���^
		vsBlob->GetBufferSize(),	//	�o�b�t�@�̃T�C�Y
		nullptr,		//	�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^
		&pVertexShader	//	���_�V�F�[�_�C���^�[�t�F�[�X�|�C���^
	);

	return true;
}
