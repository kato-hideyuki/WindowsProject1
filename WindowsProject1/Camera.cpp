//==============================================================================
// Filename: Camera.cpp
// Description: カメラクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Camera.h"
using namespace DirectX;

//--------------------------------------------- 
///	コンストラクタ
///
/// \return 
//---------------------------------------------
Camera::Camera()
{
}

//--------------------------------------------- 
///	デストラクタ
///
/// \return 
//---------------------------------------------
Camera::~Camera()
{
}

//--------------------------------------------- 
/// カメラデータの初期化
///
/// \param[in] nearClip	//	視錐台描画ライン手前
/// \param[in] farClip	//	視錐台描画ライン奥行き
/// \param[in] aspect	//	画面比
/// \param[in] fov		//	視野角
/// \param[in] eye		//	カメラ視点
/// \param[in] lookat	//	注視点
/// \param[in] up		//	上向きベクトル
///
/// \return 
//---------------------------------------------
void Camera::Init(
	float nearClip, float farClip, float aspect, float fov,
	XMFLOAT3 eye, 
	XMFLOAT3 lookat, 
	XMFLOAT3 up
)
{
	SetView(eye, lookat, up);
	SetProjection(nearClip, farClip, aspect, fov);
}

//--------------------------------------------- 
/// 定数バッファのセット
/// 
/// \return	cb	定数バッファ
//--------------------------------------------- 
//void Camera::SetConstantBuffer(ConstantBuffer* cb)
//{
//	XMStoreFloat4x4(
//		&cb->world,
//		XMMatrixTranspose(XMLoadFloat4x4(&m_world))
//	);
//	XMStoreFloat4x4(
//		&cb->view,
//		XMMatrixTranspose(XMLoadFloat4x4(&m_view))
//	);
//	XMStoreFloat4x4(
//		&cb->projection,
//		XMMatrixTranspose(XMLoadFloat4x4(&m_projection))
//	);
//}

//--------------------------------------------- 
/// ビュー行列作成
///
/// \param[in] eye		//	カメラ視点
/// \param[in] lookat	//	注視点
/// \param[in] up		//	上向きベクトル
///
/// \return 
//---------------------------------------------
void Camera::SetView(
	XMFLOAT3 eye,
	XMFLOAT3 lookat,
	XMFLOAT3 up
)
{
	m_eye = eye;
	m_lookat = lookat;
	m_up = up;

	DirectX::XMVECTOR Eye =
		DirectX::XMVectorSet(eye.x, eye.y, eye.z, 0.0f);
	DirectX::XMVECTOR Up =
		DirectX::XMVectorSet(up.x, up.y, up.z, 0.0f);
	DirectX::XMVECTOR At =
		DirectX::XMVectorSet(lookat.x, lookat.y, lookat.z, 0.0f);

	DirectX::XMMATRIX view;
	view = DirectX::XMMatrixLookAtLH(Eye, At, Up);

	DirectX::XMStoreFloat4x4(&m_view, view);
}

//--------------------------------------------- 
/// プロジェクション行列作成
///
/// \param[in] nearClip	//	視錐台描画ライン手前
/// \param[in] farClip	//	視錐台描画ライン奥行き
/// \param[in] aspect	//	画面比
/// \param[in] fov		//	視野角
///
/// \return 
//---------------------------------------------
void Camera::SetProjection(
	float nearClip, float farClip, float aspect, float fov
)
{
	m_nearClip = nearClip;
	m_farClip = farClip;
	m_aspect = aspect;
	m_fov = fov;

	DirectX::XMMATRIX projection;
	projection = 
		DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearClip, farClip);
	DirectX::XMStoreFloat4x4(&m_projection, projection);

}
