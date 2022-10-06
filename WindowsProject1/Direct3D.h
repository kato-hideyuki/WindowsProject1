#pragma once
//==============================================================================
// Filename: Direct3D
// Description: DirectX11�������A�`�揈��
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================

class Direct3D
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Direct3D() {}
	~Direct3D() {}

	static Direct3D& GetInstance()
	{
		static Direct3D instance;
		return instance;
	}

	bool Init(HWND hWin);
	void Swap();
	void Draw();
	void Release();

	ID3D11Device* GetDevice()
	{
		return m_pDevice;
	}
	ID3D11DeviceContext* GetContext()
	{
		return m_pDeviceContext;
	}

private:
	//---------------------------------------------------------------------------
	//	private methods
	//---------------------------------------------------------------------------
	bool InitDeviceAndSwapChein(HWND hWnd);
	bool InitBuckBuffer();

	//---------------------------------------------------------------------------
	// private variables.
	//---------------------------------------------------------------------------
	D3D_DRIVER_TYPE	  m_driverType;		// �h���C�o�^�C�v
	D3D_FEATURE_LEVEL m_featureLevel;	// �@�\���x��

	ID3D11Device*           m_pDevice = nullptr;			//	�`��f�o�C�X�ւ̃C���^�[�t�F�[�X
	ID3D11DeviceContext*    m_pDeviceContext = nullptr;		//	�`�施�߃C���^�[�t�F�[�X
	IDXGISwapChain*         m_pSwapChain = nullptr;			//	��ʂւ̍X�V���f
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;	//	�`��^�[�Q�b�g�r���[

	D3D11_VIEWPORT m_viewport[1];	//	�r���[�|�[�g

	UINT m_screenWidth = 0;		//	�X�N���[������
	UINT m_screenHeight = 0;	//	�X�N���[���c��
	UINT m_backBufferNum = 3;	//	�o�b�N�o�b�t�@��

	float m_clearColor[4] = { 0,1,1,0 };	//	�N���A�J���[
};