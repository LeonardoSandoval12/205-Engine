#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;

class Texture
{
public:
	Texture() = default;
	~Texture() = default;
	
	HRESULT init(Device device, std::string textureName, ExtensionType extensionType);

	void 
    init(Device device, unsigned int width, unsigned int height,
		 DXGI_FORMAT Format,
		 unsigned int BindFlags);


	void 
	update();
	

	void 
	render(DeviceContext& deviceContext,
		   unsigned int StartSlot, 
		   unsigned int NumViews);
	/// <summary>
	/// Brief: Este metodo se encarga de dibujar los recursos en la pantalla
	/// </summary>

		/// <summary>
		/// Este metodo se encarga de realizar los recursos almacenados en la memoria de la clase
		/// </summary>
	void destroy();


public:
	ID3D11Texture2D* m_texture = nullptr;//Esta variable maneja un recurso de textura como datos
	ID3D11ShaderResourceView* m_textureFromImg;//Esta variable maneja un recurso de textura como datos de imagen

};