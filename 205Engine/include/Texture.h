#pragma once
#include "PreRequisites.h"

//<El primer m�todo init permite crear texturas a partir de archivos de imagen.
//La sobrecarga del m�todo init permite especificar dimensiones y formatos para la creaci�n de texturas.
//El m�todo update est� definido pero actualmente no tiene implementaci�n.
//El m�todo render permite renderizar la textura utilizando un contexto de dispositivo.
//El m�todo destroy es crucial para liberar los recursos asociados a la textura. 

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