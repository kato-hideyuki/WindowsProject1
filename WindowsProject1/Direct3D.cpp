//==============================================================================
// Filename: Direct3D.cpp
// Description: DirectX11�������A�`�揈��
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Direct3D.h"

//--------------------------------------------- 
/// DirectX11�̏���������
/// \param[in] hWnd	�E�B���h�E�Y�n���h��
///
/// \return True On Success
//--------------------------------------------- 
bool Direct3D::Init(HWND hWnd)
{
    //  �E�B���h�E�ɍ��킹�ăX�N���[���T�C�Y������������
    RECT rect;
    GetClientRect(hWnd, &rect);
    m_screenWidth = (UINT)(rect.right - rect.left);
    m_screenHeight = (UINT)(rect.bottom - rect.top);

    InitDeviceAndSwapChein(hWnd);
    InitBuckBuffer();
    InitDepthStencilBuffer();

    Camera::GetInstance()->Init(
        0.1f,   //  nearClip
        100.0f, //  farClip
        m_screenWidth / m_screenHeight,     //  aspect
        DirectX::XMConvertToRadians(45.0f), //  fov
        DirectX::XMFLOAT3(2.0f, 2.0f, -2.0f),   //  eye
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),    //  lookat
        DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)     //  up
    );
    //m_triangle.Create(m_pDevice);
    //m_quad.Create(m_pDevice);
    m_cube.Create(m_pDevice);

    return true;
}

//--------------------------------------------- 
/// �o�b�t�@�̓���ւ�
///
/// \return 
//--------------------------------------------- 
void Direct3D::Swap()
{
    HRESULT hr;
    //  �o�b�N�o�b�t�@�\��
    hr = m_pSwapChain->Present(0, 0);
    if (FAILED(hr)) 
    {
        MessageBox(nullptr, L"swap backbuffer", L"Error", MB_OK);
        return;
    }
}

//--------------------------------------------- 
/// �`��O����
///
/// \return 
//--------------------------------------------- 
void Direct3D::Draw()
{
    if (!m_pDeviceContext || !m_pRenderTargetView)
    {
        //  ���g�i�V�i�����������܂������Ă��Ȃ��j
        return;
    }
    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);

    //m_triangle.Draw(m_pDeviceContext);
    //m_quad.Draw(m_pDeviceContext);
    m_cube.Draw(m_pDeviceContext, m_pDepthStencilView, m_pRenderTargetView);
}

//--------------------------------------------- 
/// �e�C���^�[�t�F�[�X�������
///
/// \return 
//--------------------------------------------- 
void Direct3D::Release()
{
    //  �f�o�C�X�X�e�[�g�̃N���A
    if (m_pDeviceContext)   m_pDeviceContext->ClearState();
    //  �X���b�v�`�F�C�����E�B���h�E���[�h�ɂ���
    if (m_pSwapChain)    m_pSwapChain->SetFullscreenState(FALSE, nullptr);

    //  �e�C���^�[�t�F�[�X���
    m_pRenderTargetView->Release();
    m_pSwapChain->Release();
    m_pDeviceContext->Release();
    m_pDevice->Release();
}

//--------------------------------------------- 
/// �f�o�C�X�ƃX���b�v�`�F�C���̏�����
/// \param[in] hWnd	�E�B���h�E�Y�n���h��
///	
/// \return True On Success
//--------------------------------------------- 
bool Direct3D::InitDeviceAndSwapChein(HWND hWnd)
{
    HRESULT hr;
    DXGI_SWAP_CHAIN_DESC dxgi;
    ZeroMemory(&dxgi, sizeof(dxgi));
    dxgi.BufferCount = m_backBufferNum;         //  �o�b�N�o�b�t�@�̐�
    dxgi.BufferDesc.Width = m_screenWidth;      //  �o�b�N�o�b�t�@����
    dxgi.BufferDesc.Height = m_screenHeight;    //  �o�b�N�o�b�t�@�c��
    dxgi.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;    //  �J���[�t�H�[�}�b�g
    dxgi.BufferDesc.RefreshRate.Numerator = 60;             //  ���t���b�V�����[�g����
    dxgi.BufferDesc.RefreshRate.Denominator = 1;            //  ���t���b�V�����[�g���q
    dxgi.BufferDesc.ScanlineOrdering = 
        DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;               //  �X�L�������C���̕��@
    dxgi.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;   //  �o�b�N�o�b�t�@����scale����
    dxgi.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     //  �o�b�N�o�b�t�@�g�p�@
    dxgi.OutputWindow = hWnd;       //  �o�̓E�B���h�E
    dxgi.SampleDesc.Count = 1;      //  �}���`�T���v���i�A���`�G�C���A�V���O�j�̃T���v����
    dxgi.SampleDesc.Quality = 0;    //  �}���`�T���v���i�A���`�G�C���A�V���O�j�̃N�I���e�B
    dxgi.Windowed = true;			//  �E�B���h�E���[�h�w��
    dxgi.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    //  ���[�h�̎����؂芷��

#if defined(DEBUG)||defined(_DEBUG)
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
    UINT createDeviceFlags = 0;
#endif

    const D3D_DRIVER_TYPE driverType[] =    //  �h���C�o�[���
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

	D3D_FEATURE_LEVEL featureLevels[]=  //  �@�\���x���z��
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT featureLevelNum = ARRAYSIZE(featureLevels);    //  �@�\���x���z��v�f��

    for (auto type : driverType)
    {
        m_driverType = type;
        hr = D3D11CreateDeviceAndSwapChain(
            nullptr,                        //  �r�f�I�A�_�v�^�̎w��
            type,                           //  �h���C�o�̃^�C�v
            nullptr,                        //  D3D_DRIVER_TYPR_SOFTWARE�̎w�莞�Ɏg�p
            createDeviceFlags,              //  �f�o�C�X�쐬�t���O�̎w��
            featureLevels,                  //  D3D_FEATURE_LEVEL�w��Œ�`�����z����w��\
            featureLevelNum,                //  ��L�̔z��v�f��
            D3D11_SDK_VERSION,              //  SDK�o�[�W����
            &dxgi,                          //  DXGI_SWAP_CHAIN_DESC
            &m_pSwapChain,                  //  ��������SwapChain
            &m_pDevice,                     //  ��������Device
            &m_featureLevel,                //  ��������FEATURE_LEVEL
            &m_pDeviceContext               //  ��������DeviceContext
        );
        if (SUCCEEDED(hr))
        {
            break;
        }
    }
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"CreateDeviceAndSwapChain", L"Error", MB_OK);
        return false;
    }

    return true;
}

//--------------------------------------------- 
/// �o�b�N�o�b�t�@�̏�����
///	
/// \return True On Success
//--------------------------------------------- 
bool Direct3D::InitBuckBuffer()
{
    HRESULT hr;

    ID3D11Texture2D* pBackBuffer;
    hr = m_pSwapChain->GetBuffer(
        0,                          //  �o�b�N�o�b�t�@�ԍ�
        __uuidof(ID3D11Texture2D),  //  �o�b�t�@�ɃA�N�Z�X����C���^�[�t�F�[�X
        (LPVOID*)&pBackBuffer       //  �󂯎�����o�b�t�@
    );
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"InitBackBuffer SwapChain", L"Error", MB_OK);
        return false;
    }

    D3D11_TEXTURE2D_DESC descBackBuffer;    //  �o�b�N�o�b�t�@�̏��
    pBackBuffer->GetDesc(&descBackBuffer);

    hr = m_pDevice->CreateRenderTargetView(
        pBackBuffer,            //  �r���[�ŃA�N�Z�X���郊�\�[�X
        nullptr,                //  �`��^�[�Q�b�g�A�r���[�̒�`
        &m_pRenderTargetView    //  �`��^�[�Q�b�g�E�r���[���󂯎��ϐ�
    );
    pBackBuffer->Release();     //  �ȍ~�g��Ȃ��̂ŉ��
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"CreaterenderTargetView", L"Error", MB_OK);
        return false;
    }

    m_viewport[0].TopLeftX = 0.0f;  //  �r���[�|�[�g����X���W
    m_viewport[0].TopLeftY = 0.0f;  //  �r���[�|�[�g����Y���W
    m_viewport[0].Width = (float)m_screenWidth;     //  �r���[�|�[�g�̈敝
    m_viewport[0].Height = (float)m_screenHeight;   //  �r���[�|�[�g�̈捂��
    m_viewport[0].MinDepth = 0.0f;  //  �r���[�|�[�g�ŏ��[�x�l
    m_viewport[0].MaxDepth = 1.0f;  //  �r���[�|�[�g�ő�[�x�l
    m_pDeviceContext->RSSetViewports(1, &m_viewport[0]);

    return true;
}

//--------------------------------------------- 
/// �[�x�X�e���V���o�b�t�@�̏�����
///	
/// \return True On Success
//--------------------------------------------- 
bool Direct3D::InitDepthStencilBuffer()
{
    D3D11_TEXTURE2D_DESC txDesc;
    ZeroMemory(&txDesc, sizeof(txDesc));
    txDesc.Width = m_screenWidth;
    txDesc.Height = m_screenHeight;
    txDesc.MipLevels = 1;
    txDesc.ArraySize = 1;
    txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    txDesc.SampleDesc.Count = 1;
    txDesc.SampleDesc.Quality = 0;
    txDesc.Usage = D3D11_USAGE_DEFAULT;
    txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    txDesc.CPUAccessFlags = 0;
    txDesc.MiscFlags = 0;
    HRESULT hr = m_pDevice->CreateTexture2D(&txDesc, NULL, &m_pDepthStencilTexture);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"CreateTexture2D", L"Error", MB_OK);
        return false;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.Format = txDesc.Format;
    dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsDesc.Texture2D.MipSlice = 0;
    hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsDesc, &m_pDepthStencilView);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"CreateDepthStencilView", L"Error", MB_OK);
        return false;
    }

    return true;
}
