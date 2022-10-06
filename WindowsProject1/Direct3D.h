#pragma once
//==============================================================================
// Filename: Direct3D
// Description: DirectX11初期化、描画処理
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
	D3D_DRIVER_TYPE	  m_driverType;		// ドライバタイプ
	D3D_FEATURE_LEVEL m_featureLevel;	// 機能レベル

	ID3D11Device*           m_pDevice = nullptr;			//	描画デバイスへのインターフェース
	ID3D11DeviceContext*    m_pDeviceContext = nullptr;		//	描画命令インターフェース
	IDXGISwapChain*         m_pSwapChain = nullptr;			//	画面への更新反映
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;	//	描画ターゲットビュー

	D3D11_VIEWPORT m_viewport[1];	//	ビューポート

	UINT m_screenWidth = 0;		//	スクリーン横幅
	UINT m_screenHeight = 0;	//	スクリーン縦幅
	UINT m_backBufferNum = 3;	//	バックバッファ数

	float m_clearColor[4] = { 0,1,1,0 };	//	クリアカラー
};