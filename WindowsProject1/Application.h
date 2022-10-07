#pragma once
//==============================================================================
// Filename: Application.h
// Description: DirectX11初期化、描画処理、全体の処理
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#include "Direct3D.h"

class Application
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Application();
	~Application();

	static Application* GetInstance()
	{
		static Application instance;
		return &instance;
	}

	bool Init(HINSTANCE hInst);
	void Updata();
	void Draw();
	void Release();

	HWND GetHWnd()
	{
		return m_hWnd;
	}
	HINSTANCE GetHInstance()
	{
		return m_hInst;
	}
	WCHAR* GetSZTitle()
	{
		return m_szTitle;
	}
	WCHAR* GetSZWindowClass()
	{
		return m_szWindowClass;
	}
	UINT GetMAX_LOADSTRING()
	{
		return MAX_LOADSTRING;
	}

private:
	//--------------------------------------------------------------------------
	//	private variables
	//--------------------------------------------------------------------------
	static const UINT MAX_LOADSTRING = 100;
	HINSTANCE m_hInst;                                // 現在のインターフェイス
	WCHAR m_szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名
	HWND m_hWnd;		//	ウィンドウズハンドル
};

