#pragma once

class Vertex
{
public:
	DirectX::XMFLOAT3 position;

	Vertex(){}
	Vertex(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}
};
