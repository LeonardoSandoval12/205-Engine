#pragma once
#include "PreRequisites.h"

//<>
class Device;
class DeviceContext;

class
	Texture {
public:
	Texture() = default;
	~Texture() = default;

	///<summary>
	///Brief: CREA UNA TEXTURA A PARIR de una imagen (.dds) desde el ordenador
	///</summary>
	/// <param name ="device">: Llamamos al device para poder generar los drecursos en memoria </param>
	/// <param name ="width">: Llamamos al device para poder generar los drecursos en memoria </param>  
  
	HRESULT
		init(Device device, std::string textureName);

	void
		init(Device device,
			unsigned int width,
			unsigned int height,
			DXGI_FORMAT Format,
			unsigned int BindFlags);

	void
		update();



	void
		render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);



	void
		destroy();

public:

	ID3D11Texture2D* m_texture = nullptr;

	ID3D11ShaderResourceView* m_textureFromImg;
	
};