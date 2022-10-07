//==============================================================================
// Filename: Application.cpp
// Description: DirectX11初期化、描画処理、全体の処理
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#include "Application.h"
#include "Resource.h"

//--------------------------------------------- 
/// コンストラクタ
///
/// \return 
//--------------------------------------------- 
Application::Application()
{

}

//--------------------------------------------- 
/// デストラクタ
///
/// \return 
//--------------------------------------------- 
Application::~Application()
{
	Release();
}

//--------------------------------------------- 
/// アプリケーション初期化処理
/// \param[in] ( hInst )
///
/// \return 
//--------------------------------------------- 
bool Application::Init(HINSTANCE hInst)
{
	LoadStringW(hInst, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadStringW(hInst, IDC_WINDOWSPROJECT1, m_szWindowClass, MAX_LOADSTRING);
	m_hInst = hInst;

	HWND hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!hWnd)
	{
		return false;
	}

	Direct3D::GetInstance().Init(hWnd);

	return true;
}

//--------------------------------------------- 
/// アプリケーション更新処理
/// 
/// \return 
//--------------------------------------------- 
void Application::Updata()
{
	HACCEL hAccelTable = LoadAccelerators(m_hInst, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

	MSG msg;
	// メイン メッセージ ループ:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		Draw();
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

//--------------------------------------------- 
/// アプリケーション描画処理
///
/// \return 
//--------------------------------------------- 
void Application::Draw()
{
	Direct3D::GetInstance().Draw();
	Direct3D::GetInstance().Swap();
}

//--------------------------------------------- 
/// アプリケーション解放処理
///
/// \return 
//--------------------------------------------- 
void Application::Release()
{
	Direct3D::GetInstance().Release();
}

