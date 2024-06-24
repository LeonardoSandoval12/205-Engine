#include "DeviceContext.h"


/// <summary>
///  incluye dos métodos de la clase DeviceContext: destroy, que libera el contexto del dispositivo, y PSSetShaderResources, }
/// que establece las vistas de recursos de shader en el contexto del dispositivo y maneja la verificación de errores si los recursos de shader son nulos.
/// </summary>

void
DeviceContext::destroy() {
	SAFE_RELEASE(m_deviceContext)
}

void DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{
	if (pInputLayout == nullptr)
	{
		ERROR("DeviceContext", "IASetLayout", "CHECK FOR ID3D11InputLayout* pInputLayout")
			exit(1);
	}
	else
	{
		m_deviceContext->IASetInputLayout(pInputLayout);
	}
}

void DeviceContext::PSSetShaderResources(unsigned int StartSlot, unsigned int NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	if (ppShaderResourceViews == nullptr)
	{
		ERROR("DeviceContext", "PSSetShaderResources", " CHECK FOR  ID3D11ShaderResourceView* const* ppShaderResourceViews")
			exit(1);
	}
	else
	{
		m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}