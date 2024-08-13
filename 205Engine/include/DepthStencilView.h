#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;
class Texture;

//

class DepthStencilView
{
public:
	DepthStencilView() = default;
	~DepthStencilView() = default;
	
	//M�todo de inicializaci�n que configura la DepthStencilView. Recibe un objeto Device para interactuar con el dispositivo gr�fico,
	//un objeto Texture que representa la textura de profundidad y stencil, y DXGI_FORMAT que especifica el formato del buffer de profundidad.
	void
	init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

	void 
	update();

	// M�todo para renderizar o aplicar la vista de profundidad/stencil utilizando un DeviceContext.
	// En DirectX, esto podr�a significar configurar el pipeline gr�fico para usar esta vista de profundidad durante el renderizado.
	void 
	render(DeviceContext& deviceContext);

	void 
	destroy();


public:
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
};
