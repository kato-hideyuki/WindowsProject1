//==============================================================================
// Filename: pch.h
// Description: �g�p�p�x�̍����w�b�_�[�⃉�C�u����
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#pragma once

#include <d3d11.h>
#include <directxmath.h>
#pragma comment(lib, "d3d11.lib")

#include "Direct3D.h"
#include "Direct3D_Vertex.h"

struct ConstantBuffer
{
	DirectX::XMFLOAT4X4	world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};
