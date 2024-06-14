#include "Device.h"
#include "../PreRequisites.h"


void Device::init()
{
}

void Device::update()
{
}

void Device::render()
{
}

void Device::destroy()
{
	SAFE_RELEASE(m_device);
}

//La función toma tres argumentos:
//pResource: Un puntero a un recurso DirectX 11 existente, generalmente una textura o un búfer de la cadena de intercambio en el que desea renderizar.
//pDesc : Un puntero a una estructura D3D11_RENDER_TARGET_VIEW_DESC.Esta estructura especifica detalles sobre la RTV que se está creando, como su formato y dimensiones.
//ppRTView : Un puntero doble a una interfaz ID3D11RenderTargetView.Si la creación es exitosa, la función almacena la dirección de la RTV recién creada a través de este puntero doble.

HRESULT Device::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
{
	HRESULT hr = S_OK;
	//Check if the resource and RTView exist
	if (pResource != nullptr || ppRTView != nullptr)
	{
		hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);
		MESSAGE("Device", "CreateRenderTarfetView", "OK")
	}
	else
	{
		ERROR("Device", "CreateRenderTargetView", "CHECK FOR CREATION METHOD")
			exit(1);
	}
	return hr;
}



//La función toma una descripción (pDesc) de la textura deseada y datos iniciales opcionales.
//llama a la función CreateTexture2D del dispositivo DirectX 11 subyacente (m_device variable miembro) 
// para crear la textura en base a la descripción proporcionada.
//--
// Si la creación es exitosa, la función almacena la dirección de la textura recién creada en la ubicación de memoria señalada por ppTexture2D. 
// Esto le permite acceder y manipular la textura más adelante en su código.
//Si la creación es exitosa, la función almacena la dirección de la textura recién creada en la ubicación de memoria señalada por ppTexture2D.Esto le permite acceder y manipular la textura más adelante en su código.
HRESULT Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
{
	{
		HRESULT hr = S_OK;
		//Check if the resource and RTView exist
		if (pDesc != nullptr || ppTexture2D != nullptr)
		{
			hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
			MESSAGE("Device", "CreateRenderTarfetView", "OK")
		}
		else
		{
			ERROR("Device", "CreateTexture2D", "CHECK FOR CREATION METHOD")
				exit(1);
		}
		return hr;
	}
}


//La función toma un recurso existente (pResource) y una descripción (pDesc) que especifica cómo se creará la DSV a partir de ese recurso.
//llama a la función CreateDepthStencilView del dispositivo DirectX 11 subyacente (m_device variable miembro) para crear la DSV.
//Si la creación es exitosa, la función almacena la dirección de la DSV recién creada en la ubicación de memoria señalada por ppDepthStencilView.
HRESULT Device::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
{

	HRESULT hr = S_OK;
	//Check if the resource and RTView exist
	if (pResource == nullptr)
	{
		ERROR("Device", "CreateDepthStencilView", "CHECK FOR CreateDepthStencilView METHOD")
			exit(1);
	}
	else if (ppDepthStencilView == nullptr)
	{
		ERROR("Device", "CreateDepthStencilView", "CHECK FOR ID2D11DepthStencilView** ppDepthStencilView")
			exit(1);
	}
	else
	{
		hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
		MESSAGE("Device", "CreateRenderTarfetView", "OK")
	}
	return hr;
}


//pShaderBytecode: Puntero a un bloque de memoria constante que contiene el código binario compilado del sombreado de vértices (bytecode).
//BytecodeLength: Valor entero sin signo(unsigned int) que indica la longitud en bytes del código binario(pShaderBytecode).
//pClassLinkage(opcional) : Puntero a una interfaz ID3D11ClassLinkage.Este parámetro se utiliza para vincular recursos compartidos entre diferentes sombreadores
// (menos común en sombreadores de vértices).Si no se usa, se puede establecer en NULL.
HRESULT Device::CreateVertexShader(const void* pShaderBytecode, unsigned int BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
{
	HRESULT hr = S_OK;
	//Check if the resource and RTView exist
	if (pShaderBytecode == nullptr)
	{
		ERROR("Device", "CreateVertexShader", "CHECK FOR const void* pShaderBytecode")
			exit(1);
	}
	else if (ppVertexShader == nullptr)
	{
		ERROR("Device", "CreateVertexShader", "CHECK FOR ID2D11VertexShader** ppVertexShader")
			exit(1);
	}
	else
	{
		hr = m_device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
		MESSAGE("Device", "CreateVertexShader", "OK")
	}
	return hr;
}


//Puntero a un arreglo constante de estructuras D3D11_INPUT_ELEMENT_DESC
//NumElements: Valor entero sin signo (UINT) que indica el número de elementos de entrada descritos en pInputElementDescs
//pShaderBytecodeWithInputSignature**: Puntero a un bloque de memoria constante que contiene el código binario compilado del sombreado de vértices (bytecode),
//  pero debe incluir la firma de entrada (información sobre los elementos que espera recibir el sombreado).
HRESULT Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
{
	HRESULT hr = S_OK;
	//Check if the resource and RTView exist
	if (pInputElementDescs == nullptr)
	{
		ERROR("Device", "CreateInputLayout", "CHECK FOR const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs")
			exit(1);
	}
	else if (pShaderBytecodeWithInputSignature == nullptr)
	{
		ERROR("Device", "CreateInputLayout", "CHECK FOR const void* pShaderBytecodeWithInputSignature")
			exit(1);
	}
	else if (ppInputLayout == nullptr)
	{
		ERROR("Device", "CreateInputLayout", "CHECK FOR  ID3D11InputLayout** ppInputLayout")
			exit(1);
	}
	else
	{
		hr = m_device->CreateInputLayout(pInputElementDescs,
			NumElements,
			pShaderBytecodeWithInputSignature,
			BytecodeLength,
			ppInputLayout);
		MESSAGE("Device", "CreateInputLayout", "OK")
	}
	return hr;
}


//Si los parámetros son válidos, se llama a la función original m_device->CreatePixelShader del dispositivo DirectX 11 para crear el sombreado de píxeles.
//m_device probablemente sea un miembro de la clase que contiene esta función y almacena una referencia al dispositivo DirectX 11.
HRESULT Device::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
{
	HRESULT hr = S_OK;
	//Check if the resource and RTView exist
	if (pShaderBytecode == nullptr)
	{
		ERROR("Device", "CreatePixelShader", "CHECK FOR const void* pShaderBytecode")
			exit(1);
	}
	else if (ppPixelShader == nullptr)
	{
		ERROR("Device", "CreatePixelShader", "CHECK FOR ID3D11PixelShader** ppPixelShader")
			exit(1);
	}
	else
	{
		hr = m_device->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
		MESSAGE("Device", "CreatePixelShader", "OK")
	}
	return hr;
}


//esta función se llamaría para crear el buffer en la memoria.
HRESULT Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
{
	HRESULT hr = S_OK;
	//Check if the resource and RTView exist
	if (pDesc == nullptr)
	{
		ERROR("Device", "CreateBuffer", "CHECK FOR const D3D11_BUFFER_DESC* pDesc")
			exit(1);
	}
	else if (ppBuffer == nullptr)
	{
		ERROR("Device", "CreateBuffer", "CHECK FOR ID3D11Buffer** ppBuffer")
			exit(1);
	}
	else
	{
		hr = m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);
		MESSAGE("Device", "CreateBuffer", "OK")
	}
	return hr;
}

HRESULT Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
{
	HRESULT hr = S_OK;
	//Check if the resource and RTView exist
	if (pSamplerDesc == nullptr)
	{
		ERROR("Device", "CreateSamplerState", "CHECK FOR const D3D11_BUFFER_DESC* pDesc")
			exit(1);
	}
	else if (ppSamplerState == nullptr)
	{
		ERROR("Device", "CreateSamplerState", "CHECK FOR ID3D11Buffer** ppBuffer")
			exit(1);
	}
	else
	{
		hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);
		MESSAGE("Device", "CreateSamplerState", "OK")
	}
	return hr;
}













