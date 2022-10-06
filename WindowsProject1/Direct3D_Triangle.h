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
	static constexpr size_t VERTEX_NUM = 3;	//	���_��
	Vertex vertices[VERTEX_NUM];			//	�e���_�f�[�^
	ID3D11Buffer* vertexBuffer = nullptr;	//	���_�o�b�t�@
};