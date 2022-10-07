#pragma once
//==============================================================================
// Filename: Application.h
// Description: DirectX11�������A�`�揈���A�S�̂̏���
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
	HINSTANCE m_hInst;                                // ���݂̃C���^�[�t�F�C�X
	WCHAR m_szTitle[MAX_LOADSTRING];                  // �^�C�g�� �o�[�̃e�L�X�g
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // ���C�� �E�B���h�E �N���X��
	HWND m_hWnd;		//	�E�B���h�E�Y�n���h��
};

