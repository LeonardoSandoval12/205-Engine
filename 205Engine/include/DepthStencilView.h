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
	
	//Método de inicialización que configura la DepthStencilView. Recibe un objeto Device para interactuar con el dispositivo gráfico,
	//un objeto Texture que representa la textura de profundidad y stencil, y DXGI_FORMAT que especifica el formato del buffer de profundidad.
	void
	init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

	void 
	update();

	// Método para renderizar o aplicar la vista de profundidad/stencil utilizando un DeviceContext.
	// En DirectX, esto podría significar configurar el pipeline gráfico para usar esta vista de profundidad durante el renderizado.
	void 
	render(DeviceContext& deviceContext);

	void 
	destroy();


public:
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
};
