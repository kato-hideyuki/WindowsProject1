#include "pch.h"
#include "Direct3D_Triangle.h"

//--------------------------------------------- 
/// コンストラクタ
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
/// デストラクタ
///
/// \return 
//--------------------------------------------- 
Triangle::~Triangle()
{
	vertexBuffer->Release();
}

//--------------------------------------------- 
/// 頂点バッファ作成
/// \param[in] renderer	バッファ渡し用
/// 
/// \return 
//--------------------------------------------- 
bool Triangle::CreateVertexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	//	バッファ読み取り、書き出しの指定
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;	
	//	バッファサイズ（バイト単位）
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	//	バッファをパイプラインに特定する方法
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexSubData;
	vertexSubData.pSysMem = vertices;	//	初期化データへのポインタ

	HRESULT hr = device->CreateBuffer(
		&vertexBufferDesc,	//	バッファを記述する構造体ポインタ
		&vertexSubData,		//	初期化データを記述する構造体ポインタ
		&vertexBuffer		//	作成したバッファオブジェクト
	);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

//--------------------------------------------- 
/// バッファ描画
/// \param[in] renderer 
/// 
/// \return 
//--------------------------------------------- 
void Triangle::Draw(ID3D11Device* device)
{

}
