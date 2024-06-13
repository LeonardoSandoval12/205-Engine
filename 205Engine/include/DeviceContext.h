#pragma once
#include "PreRequisites.h"

class 
DeviceContext {
public:

	DeviceContext() = default;
	~DeviceContext() = default;

	void init();

	void update();

	void render();

	void DeviceContext::RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports)
	{
		if (pViewports == nullptr)
		{
			ERROR("DeviceContext", "RSSetViewports", "CHECK for const D3D11_VIEWPORT* pViewports")
				exit(1);
		}
		else
		{
			m_deviceContext->RSSetViewports(NumViewports, pViewports);
		}
	}

	void destroy();

	void PSSetShaderResources(unsigned int StartSlot, unsigned int NumViews,
		ID3D11ShaderResourceView* const* ppShaderResourceViews);

public: 
	ID3D11DeviceContext* m_deviceContext = nullptr;
private:

	

};