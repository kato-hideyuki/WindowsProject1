//==============================================================================
// Filename: Camera.h
// Description: �J�����N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once
#include "pch.h"
class Camera
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Camera();
	~Camera();

	static Camera* GetInstance()
	{
		static Camera instance;
		return &instance;
	}

	void Init(
		float nearClip, float farClip, float aspect, float fov,
		DirectX::XMFLOAT3 eye,
		DirectX::XMFLOAT3 lookat,
		DirectX::XMFLOAT3 up
	);

	//void SetConstantBuffer(ConstantBuffer* cb);

	const DirectX::XMFLOAT4X4& GetWorldMtx()
	{
		return m_world;
	}
	const DirectX::XMFLOAT4X4& GetView()
	{
		return m_view;
	}
	const DirectX::XMFLOAT4X4& GetProjection()
	{
		return m_projection;
	}
private:
	//---------------------------------------------------------------------------
	// private methods.
	//---------------------------------------------------------------------------
	void SetView(
		DirectX::XMFLOAT3 eye,
		DirectX::XMFLOAT3 lookat,
		DirectX::XMFLOAT3 up
	);
	void SetProjection(float nearClip, float farClip, float aspect, float fov);
	//---------------------------------------------------------------------------
	// private variables.
	//---------------------------------------------------------------------------
	
	DirectX::XMFLOAT4X4 m_world;		//	���[���h���W
	DirectX::XMFLOAT4X4 m_view;			//	�r���[���W
	DirectX::XMFLOAT4X4 m_projection;	//	�v���W�F�N�V�������W

	DirectX::XMFLOAT3 m_eye;	//	�J�������_
	DirectX::XMFLOAT3 m_lookat;	//	�����_
	DirectX::XMFLOAT3 m_up;		//	������x�N�g��

	float m_nearClip;	//	������`�惉�C����O
	float m_farClip;	//	������`�惉�C�����s��
	float m_aspect;	//	��ʔ�
	float m_fov;	//	����p
};

