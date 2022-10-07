//==============================================================================
// Filename: Application.cpp
// Description: DirectX11�������A�`�揈���A�S�̂̏���
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#include "Application.h"
#include "Resource.h"

//--------------------------------------------- 
/// �R���X�g���N�^
///
/// \return 
//--------------------------------------------- 
Application::Application()
{

}

//--------------------------------------------- 
/// �f�X�g���N�^
///
/// \return 
//--------------------------------------------- 
Application::~Application()
{
	Release();
}

//--------------------------------------------- 
/// �A�v���P�[�V��������������
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
/// �A�v���P�[�V�����X�V����
/// 
/// \return 
//--------------------------------------------- 
void Application::Updata()
{
	HACCEL hAccelTable = LoadAccelerators(m_hInst, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

	MSG msg;
	// ���C�� ���b�Z�[�W ���[�v:
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
/// �A�v���P�[�V�����`�揈��
///
/// \return 
//--------------------------------------------- 
void Application::Draw()
{
	Direct3D::GetInstance().Draw();
	Direct3D::GetInstance().Swap();
}

//--------------------------------------------- 
/// �A�v���P�[�V�����������
///
/// \return 
//--------------------------------------------- 
void Application::Release()
{
	Direct3D::GetInstance().Release();
}

