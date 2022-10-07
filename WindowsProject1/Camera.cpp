//==============================================================================
// Filename: Camera.cpp
// Description: �J�����N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "Camera.h"
using namespace DirectX;

//--------------------------------------------- 
///	�R���X�g���N�^
///
/// \return 
//---------------------------------------------
Camera::Camera()
{
}

//--------------------------------------------- 
///	�f�X�g���N�^
///
/// \return 
//---------------------------------------------
Camera::~Camera()
{
}

//--------------------------------------------- 
/// �J�����f�[�^�̏�����
///
/// \param[in] nearClip	//	������`�惉�C����O
/// \param[in] farClip	//	������`�惉�C�����s��
/// \param[in] aspect	//	��ʔ�
/// \param[in] fov		//	����p
/// \param[in] eye		//	�J�������_
/// \param[in] lookat	//	�����_
/// \param[in] up		//	������x�N�g��
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
/// �萔�o�b�t�@�̃Z�b�g
/// 
/// \return	cb	�萔�o�b�t�@
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
/// �r���[�s��쐬
///
/// \param[in] eye		//	�J�������_
/// \param[in] lookat	//	�����_
/// \param[in] up		//	������x�N�g��
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
/// �v���W�F�N�V�����s��쐬
///
/// \param[in] nearClip	//	������`�惉�C����O
/// \param[in] farClip	//	������`�惉�C�����s��
/// \param[in] aspect	//	��ʔ�
/// \param[in] fov		//	����p
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
