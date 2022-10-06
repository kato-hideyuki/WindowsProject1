//==============================================================================
// Filename: Direct3D.cpp
// Description: Direct3D SetUp 
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

    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);
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
        return false;
    }

    return true;
}

//--------------------------------------------- 
/// �o�b�N�o�b�t�@�̏�����
/// \param[in] hWnd	�E�B���h�E�Y�n���h��
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
