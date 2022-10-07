//==============================================================================
// Filename: pch.h
// Description: 使用頻度の高いヘッダーやライブラリ
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//=============================================================================
#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <wincodec.h>
#include <wrl/client.h>
#include <random>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"windowscodecs.lib")

#include "Direct3D.h"
#include "Direct3D_Vertex.h"

struct ConstantBuffer
{
	DirectX::XMFLOAT4X4	world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};
