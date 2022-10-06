//==============================================================================
// Filename: Direct3D.cpp
// Description: Direct3D SetUp 
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "Direct3D.h"

//--------------------------------------------- 
/// DirectX11の初期化処理
/// \param[in] hWnd	ウィンドウズハンドル
///
/// \return True On Success
//--------------------------------------------- 
bool Direct3D::Init(HWND hWnd)
{
    //  ウィンドウに合わせてスクリーンサイズを初期化する
    RECT rect;
    GetClientRect(hWnd, &rect);
    m_screenWidth = (UINT)(rect.right - rect.left);
    m_screenHeight = (UINT)(rect.bottom - rect.top);

    InitDeviceAndSwapChein(hWnd);

    InitBuckBuffer();
    return true;
}

//--------------------------------------------- 
/// バッファの入れ替え
///
/// \return 
//--------------------------------------------- 
void Direct3D::Swap()
{
    HRESULT hr;
    //  バックバッファ表示
    hr = m_pSwapChain->Present(0, 0);
    if (FAILED(hr)) 
    {
        return;
    }
}

//--------------------------------------------- 
/// 描画前処理
///
/// \return 
//--------------------------------------------- 
void Direct3D::Draw()
{
    if (!m_pDeviceContext || !m_pRenderTargetView)
    {
        //  中身ナシ（初期化がうまくいっていない）
        return;
    }

    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);
}

//--------------------------------------------- 
/// 各インターフェース解放処理
///
/// \return 
//--------------------------------------------- 
void Direct3D::Release()
{
    //  デバイスステートのクリア
    if (m_pDeviceContext)   m_pDeviceContext->ClearState();
    //  スワップチェインをウィンドウモードにする
    if (m_pSwapChain)    m_pSwapChain->SetFullscreenState(FALSE, nullptr);

    //  各インターフェース解放
    m_pRenderTargetView->Release();
    m_pSwapChain->Release();
    m_pDeviceContext->Release();
    m_pDevice->Release();
}

//--------------------------------------------- 
/// デバイスとスワップチェインの初期化
/// \param[in] hWnd	ウィンドウズハンドル
///	
/// \return True On Success
//--------------------------------------------- 
bool Direct3D::InitDeviceAndSwapChein(HWND hWnd)
{
    HRESULT hr;
    DXGI_SWAP_CHAIN_DESC dxgi;
    ZeroMemory(&dxgi, sizeof(dxgi));
    dxgi.BufferCount = m_backBufferNum;         //  バックバッファの数
    dxgi.BufferDesc.Width = m_screenWidth;      //  バックバッファ横幅
    dxgi.BufferDesc.Height = m_screenHeight;    //  バックバッファ縦幅
    dxgi.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;    //  カラーフォーマット
    dxgi.BufferDesc.RefreshRate.Numerator = 60;             //  リフレッシュレート分母
    dxgi.BufferDesc.RefreshRate.Denominator = 1;            //  リフレッシュレート分子
    dxgi.BufferDesc.ScanlineOrdering = 
        DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;               //  スキャンラインの方法
    dxgi.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;   //  バックバッファ時のscale遵守
    dxgi.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     //  バックバッファ使用法
    dxgi.OutputWindow = hWnd;       //  出力ウィンドウ
    dxgi.SampleDesc.Count = 1;      //  マルチサンプル（アンチエイリアシング）のサンプル数
    dxgi.SampleDesc.Quality = 0;    //  マルチサンプル（アンチエイリアシング）のクオリティ
    dxgi.Windowed = true;			//  ウィンドウモード指定
    dxgi.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    //  モードの自動切り換え

#if defined(DEBUG)||defined(_DEBUG)
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
    UINT createDeviceFlags = 0;
#endif

    const D3D_DRIVER_TYPE driverType[] =    //  ドライバー種類
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

	D3D_FEATURE_LEVEL featureLevels[]=  //  機能レベル配列
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT featureLevelNum = ARRAYSIZE(featureLevels);    //  機能レベル配列要素数

    for (auto type : driverType)
    {
        m_driverType = type;
        hr = D3D11CreateDeviceAndSwapChain(
            nullptr,                        //  ビデオアダプタの指定
            type,                           //  ドライバのタイプ
            nullptr,                        //  D3D_DRIVER_TYPR_SOFTWAREの指定時に使用
            createDeviceFlags,              //  デバイス作成フラグの指定
            featureLevels,                  //  D3D_FEATURE_LEVEL指定で定義した配列を指定可能
            featureLevelNum,                //  上記の配列要素数
            D3D11_SDK_VERSION,              //  SDKバージョン
            &dxgi,                          //  DXGI_SWAP_CHAIN_DESC
            &m_pSwapChain,                  //  成功時のSwapChain
            &m_pDevice,                     //  成功時のDevice
            &m_featureLevel,                //  成功時のFEATURE_LEVEL
            &m_pDeviceContext               //  成功時のDeviceContext
        );
        if (SUCCEEDED(hr))
        {
            break;
        }
    }
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

//--------------------------------------------- 
/// バックバッファの初期化
/// \param[in] hWnd	ウィンドウズハンドル
///	
/// \return True On Success
//--------------------------------------------- 
bool Direct3D::InitBuckBuffer()
{
    HRESULT hr;

    ID3D11Texture2D* pBackBuffer;
    hr = m_pSwapChain->GetBuffer(
        0,                          //  バックバッファ番号
        __uuidof(ID3D11Texture2D),  //  バッファにアクセスするインターフェース
        (LPVOID*)&pBackBuffer       //  受け取ったバッファ
    );
    if (FAILED(hr))
    {
        return false;
    }

    D3D11_TEXTURE2D_DESC descBackBuffer;    //  バックバッファの情報
    pBackBuffer->GetDesc(&descBackBuffer);

    hr = m_pDevice->CreateRenderTargetView(
        pBackBuffer,            //  ビューでアクセスするリソース
        nullptr,                //  描画ターゲット、ビューの定義
        &m_pRenderTargetView    //  描画ターゲット・ビューを受け取る変数
    );
    pBackBuffer->Release();     //  以降使わないので解放
    if (FAILED(hr))
    {
        return false;
    }

    m_viewport[0].TopLeftX = 0.0f;  //  ビューポート左上X座標
    m_viewport[0].TopLeftY = 0.0f;  //  ビューポート左上Y座標
    m_viewport[0].Width = (float)m_screenWidth;     //  ビューポート領域幅
    m_viewport[0].Height = (float)m_screenHeight;   //  ビューポート領域高さ
    m_viewport[0].MinDepth = 0.0f;  //  ビューポート最小深度値
    m_viewport[0].MaxDepth = 1.0f;  //  ビューポート最大深度値
    m_pDeviceContext->RSSetViewports(1, &m_viewport[0]);

    return true;
}
