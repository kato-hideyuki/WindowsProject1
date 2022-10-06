#pragma once
class Shader
{
public:
	//---------------------------------------------------------------------------
	//	private methods
	//---------------------------------------------------------------------------
	Shader();
	~Shader();

	bool CompileShader(
		const WCHAR* vsPath,
		const WCHAR* psPath,
		ID3D11Device* device
	);

private:
	//---------------------------------------------------------------------------
	// private variables.
	//---------------------------------------------------------------------------
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pInputLayout = nullptr;
};

