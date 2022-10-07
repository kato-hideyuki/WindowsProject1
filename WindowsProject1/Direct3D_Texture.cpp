//==============================================================================
// Filename: Texture.cpp
// Description: テクスチャ作成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Direct3D_Texture.h"

//--------------------------------------------- 
/// コンストラクタ
///
/// \return 
//--------------------------------------------- 
Texture::Texture()
{
}

//--------------------------------------------- 
/// デストラクタ
///
/// \return 
//--------------------------------------------- 
Texture::~Texture()
{

}

//--------------------------------------------- 
/// テクスチャ作成
///
/// \param[in,out] device   描画デバイスへのインターフェース
/// \param[in,out] context  描画命令インターフェース
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
/// テクスチャ描画
///
/// \param[in,out] context      描画命令インターフェース
/// \param[in,out] vertexBuffer 頂点バッファ
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
/// テクスチャ作成
///
/// \param[in,out] device   描画デバイスへのインターフェース
/// \param[in,out] context  描画命令インターフェース
///
/// \return true on success
//---------------------------------------------
bool Texture::CreateTexture(
    ID3D11Device* device, 
    ID3D11DeviceContext* context
)
{
    const int iPixSize = 32;//縦横ピクセル数

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

    //テクスチャ書き替え
    D3D11_MAPPED_SUBRESOURCE msr;
    context->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

    //乱数生成
    std::random_device seed;
    std::mt19937 random(seed());
    std::uniform_int_distribution<> number(0, 255);//0～255までのランダムな数

    byte srcData[iPixSize * iPixSize * 4] = { 0 };//ビットマップを黒で初期化
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
/// サンプラーステート設定
///
/// \param[in,out] device   描画デバイスへのインターフェース
/// 
/// \return true on success
//---------------------------------------------
bool Texture::CreateSamplerState(ID3D11Device* device)
{
    Microsoft::WRL::ComPtr<ID3D11SamplerState> D3DSamplerState;
    D3D11_SAMPLER_DESC sd = {};
    //補間方法　D3D11_FILTER_MIN_MAG_MIP_POINT（ポイントサンプリング）、D3D11_FILTER_MIN_MAG_MIP_LINEAR（線形補間）、D3D11_FILTER_ANISOTROPIC（異方性補間）等
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//★---変更---
    //0～1の範囲外テクスチャ　D3D11_TEXTURE_ADDRESS_WRAP（並べる）、D3D11_TEXTURE_ADDRESS_MIRROR（反転）等
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
/// ラスタライザ作成
///
/// \param[in,out] device   描画デバイスへのインターフェース
/// \param[in,out] context  描画命令インターフェース
///
/// \return true on success
//---------------------------------------------
bool Texture::CreateRasterizer(
    ID3D11Device* device,
    ID3D11DeviceContext* context
)
{
    //ラスタライザの作成
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> D3DRasterizerState;
    D3D11_RASTERIZER_DESC ras = {};
    //D3D11_FILL_WIREFRAME（ワイヤーフレーム） D3D11_FILL_SOLID（ソリッド）
    ras.FillMode = D3D11_FILL_SOLID;
    //D3D11_CULL_NONE（カリングなし：裏表描画） D3D11_CULL_FRONT（表面カリング：裏面描画） D3D11_CULL_BACK（裏面カリング：表面描画）
    ras.CullMode = D3D11_CULL_NONE;
    HRESULT hr = device->CreateRasterizerState(&ras, &D3DRasterizerState);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"CreateRasterrizer", L"Error", MB_OK);
        return false;
    }

    //ラスタライザの設定
    context->RSSetState(D3DRasterizerState.Get());

	return true;
}