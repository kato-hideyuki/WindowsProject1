//==============================================================================
// Filename: Texture.cpp
// Description: �e�N�X�`���쐬
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Direct3D_Texture.h"

//--------------------------------------------- 
/// �R���X�g���N�^
///
/// \return 
//--------------------------------------------- 
Texture::Texture()
{
}

//--------------------------------------------- 
/// �f�X�g���N�^
///
/// \return 
//--------------------------------------------- 
Texture::~Texture()
{

}

//--------------------------------------------- 
/// �e�N�X�`���쐬
///
/// \param[in,out] device   �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
/// \param[in,out] context  �`�施�߃C���^�[�t�F�[�X
///
/// \return true on success
//---------------------------------------------
void Texture::Create(
    ID3D11Device* device,
    ID3D11DeviceContext* context
)
{
    CreateRasterizer(device, context);
    CreateTexture(device, context);
    CreateSamplerState(device);
}

//--------------------------------------------- 
/// �e�N�X�`���`��
///
/// \param[in,out] context      �`�施�߃C���^�[�t�F�[�X
/// \param[in,out] vertexBuffer ���_�o�b�t�@
///
/// \return true on success
//---------------------------------------------
void Texture::Draw(
    ID3D11DeviceContext* context, 
    ID3D11Buffer* vertexBuffer
)
{

}

//--------------------------------------------- 
/// �e�N�X�`���쐬
///
/// \param[in,out] device   �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
/// \param[in,out] context  �`�施�߃C���^�[�t�F�[�X
///
/// \return true on success
//---------------------------------------------
bool Texture::CreateTexture(
    ID3D11Device* device, 
    ID3D11DeviceContext* context
)
{
    const int iPixSize = 32;//�c���s�N�Z����

    Microsoft::WRL::ComPtr<ID3D11Texture2D> D3DTexture;
    D3D11_TEXTURE2D_DESC td;
    td.Width = iPixSize;
    td.Height = iPixSize;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;
    td.Usage = D3D11_USAGE_DYNAMIC;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    td.MiscFlags = 0;
    HRESULT hr = device->CreateTexture2D(&td, nullptr, &D3DTexture);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"CreateTexture", L"Error", MB_OK);
        return false;
    }

    //�e�N�X�`�������ւ�
    D3D11_MAPPED_SUBRESOURCE msr;
    context->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

    //��������
    std::random_device seed;
    std::mt19937 random(seed());
    std::uniform_int_distribution<> number(0, 255);//0�`255�܂ł̃����_���Ȑ�

    byte srcData[iPixSize * iPixSize * 4] = { 0 };//�r�b�g�}�b�v�����ŏ�����
    for (int i = 0; i < iPixSize * iPixSize * 4; i += 4)
    {
        srcData[i] = number(random);//Red
        srcData[i + 1] = number(random);//Green
        srcData[i + 2] = number(random);//Blue
    }
    memcpy(msr.pData, srcData, sizeof(srcData));

    context->Unmap(D3DTexture.Get(), 0);
}

//--------------------------------------------- 
/// �T���v���[�X�e�[�g�ݒ�
///
/// \param[in,out] device   �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
/// 
/// \return true on success
//---------------------------------------------
bool Texture::CreateSamplerState(ID3D11Device* device)
{
    Microsoft::WRL::ComPtr<ID3D11SamplerState> D3DSamplerState;
    D3D11_SAMPLER_DESC sd = {};
    //��ԕ��@�@D3D11_FILTER_MIN_MAG_MIP_POINT�i�|�C���g�T���v�����O�j�AD3D11_FILTER_MIN_MAG_MIP_LINEAR�i���`��ԁj�AD3D11_FILTER_ANISOTROPIC�i�ٕ�����ԁj��
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//��---�ύX---
    //0�`1�͈̔͊O�e�N�X�`���@D3D11_TEXTURE_ADDRESS_WRAP�i���ׂ�j�AD3D11_TEXTURE_ADDRESS_MIRROR�i���]�j��
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    HRESULT hr = device->CreateSamplerState(&sd, &D3DSamplerState);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"CreatSamplerState", L"Error", MB_OK);
        return false;
    }

    return true;
}

//---------------------------------------------
/// ���X�^���C�U�쐬
///
/// \param[in,out] device   �`��f�o�C�X�ւ̃C���^�[�t�F�[�X
/// \param[in,out] context  �`�施�߃C���^�[�t�F�[�X
///
/// \return true on success
//---------------------------------------------
bool Texture::CreateRasterizer(
    ID3D11Device* device,
    ID3D11DeviceContext* context
)
{
    //���X�^���C�U�̍쐬
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> D3DRasterizerState;
    D3D11_RASTERIZER_DESC ras = {};
    //D3D11_FILL_WIREFRAME�i���C���[�t���[���j D3D11_FILL_SOLID�i�\���b�h�j
    ras.FillMode = D3D11_FILL_SOLID;
    //D3D11_CULL_NONE�i�J�����O�Ȃ��F���\�`��j D3D11_CULL_FRONT�i�\�ʃJ�����O�F���ʕ`��j D3D11_CULL_BACK�i���ʃJ�����O�F�\�ʕ`��j
    ras.CullMode = D3D11_CULL_NONE;
    HRESULT hr = device->CreateRasterizerState(&ras, &D3DRasterizerState);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"CreateRasterrizer", L"Error", MB_OK);
        return false;
    }

    //���X�^���C�U�̐ݒ�
    context->RSSetState(D3DRasterizerState.Get());

	return true;
}