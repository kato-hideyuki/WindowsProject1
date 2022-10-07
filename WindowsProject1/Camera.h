//==============================================================================
// Filename: Camera.h
// Description: カメラクラス
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
	
	DirectX::XMFLOAT4X4 m_world;		//	ワールド座標
	DirectX::XMFLOAT4X4 m_view;			//	ビュー座標
	DirectX::XMFLOAT4X4 m_projection;	//	プロジェクション座標

	DirectX::XMFLOAT3 m_eye;	//	カメラ視点
	DirectX::XMFLOAT3 m_lookat;	//	注視点
	DirectX::XMFLOAT3 m_up;		//	上向きベクトル

	float m_nearClip;	//	視錐台描画ライン手前
	float m_farClip;	//	視錐台描画ライン奥行き
	float m_aspect;	//	画面比
	float m_fov;	//	視野角
};

