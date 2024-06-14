#pragma once
#include "PreRequisites.h"



//La funci�n RSSetViewports() se encarga de configurar los viewports en el contexto del dispositivo, y verifica si el puntero pViewports es nulo antes de usarlo para evitar errores. 
// Los otros m�todos (init(), update(), render(), destroy() y PSSetShaderResources()) son funciones gen�ricas relacionadas con la manipulaci�n del contexto del dispositivo.
// Siendo destroy utilizado para limpiar la memoria
//Adem�s, la clase contiene un puntero p�blico m_deviceContext que apunta a un objeto del tipo ID3D11DeviceContext, que probablemente es proporcionado por la API de Direct3D.


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