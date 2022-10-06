#pragma once

class Triangle
{
public:
	//---------------------------------------------------------------------------
	// public methods.
	//---------------------------------------------------------------------------
	Triangle();
	~Triangle();

	bool CreateVertexBuffer(ID3D11Device* device);
	void Draw(ID3D11Device* device);

private:
	//---------------------------------------------------------------------------
	// private variables.
	//---------------------------------------------------------------------------
	static constexpr size_t VERTEX_NUM = 3;	//	頂点数
	Vertex vertices[VERTEX_NUM];			//	各頂点データ
	ID3D11Buffer* vertexBuffer = nullptr;	//	頂点バッファ
};