#include "pch.h"
#include "Direct3D_Triangle.h"

//--------------------------------------------- 
/// �R���X�g���N�^
///
/// \return 
//--------------------------------------------- 
Triangle::Triangle()
{
	vertices[0] = { 0.0f, 0.5f, 0.0f };
	vertices[0] = { 0.5f,-0.5f, 0.0f };
	vertices[0] = {-0.5f,-0.5f, 0.0f };
}

//--------------------------------------------- 
/// �f�X�g���N�^
///
/// \return 
//--------------------------------------------- 
Triangle::~Triangle()
{
	vertexBuffer->Release();
}

//--------------------------------------------- 
/// ���_�o�b�t�@�쐬
/// \param[in] renderer	�o�b�t�@�n���p
/// 
/// \return 
//--------------------------------------------- 
bool Triangle::CreateVertexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	//	�o�b�t�@�ǂݎ��A�����o���̎w��
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;	
	//	�o�b�t�@�T�C�Y�i�o�C�g�P�ʁj
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	//	�o�b�t�@���p�C�v���C���ɓ��肷����@
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexSubData;
	vertexSubData.pSysMem = vertices;	//	�������f�[�^�ւ̃|�C���^

	HRESULT hr = device->CreateBuffer(
		&vertexBufferDesc,	//	�o�b�t�@���L�q����\���̃|�C���^
		&vertexSubData,		//	�������f�[�^���L�q����\���̃|�C���^
		&vertexBuffer		//	�쐬�����o�b�t�@�I�u�W�F�N�g
	);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

//--------------------------------------------- 
/// �o�b�t�@�`��
/// \param[in] renderer 
/// 
/// \return 
//--------------------------------------------- 
void Triangle::Draw(ID3D11Device* device)
{

}
