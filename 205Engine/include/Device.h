#pragma once
#include "PreRequisites.h"

class Device
{
public:
    Device() = default;
    ~Device() = default;

    void
    init();

    void
    update();

    void
    render();

    void 
    destroy();

    //Este m�todo crea una vista de objetivo de renderizado.
    HRESULT
            CreateRenderTargetView(ID3D11Resource* pResource, 
                                   const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, 
                                   ID3D11RenderTargetView** ppRTView);

    //Este m�todo crea una textura de profundidad 2D.
    HRESULT 
            CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
                             const D3D11_SUBRESOURCE_DATA* pInitialData,
                             ID3D11Texture2D** ppTexture2D);
   
    //Este m�todo crea una vista de stencil de profundidad.
    HRESULT
            CreateDepthStencilView(ID3D11Resource* pResource,
                                   const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
                                   ID3D11DepthStencilView** ppDepthStencilView);

    //Este m�todo crea un shader de v�rtice.
    HRESULT 
            CreateVertexShader(const void* pShaderBytecode, 
                               unsigned int BytecodeLength, 
                               ID3D11ClassLinkage* pClassLinkage, 
                               ID3D11VertexShader** ppVertexShader);

    //Este m�todo crea un dise�o de entrada, que describe c�mo los datos de v�rtice son interpretados por el pipeline gr�fico.
    HRESULT 
            CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
                              UINT NumElements, const void* pShaderBytecodeWithInputSignature, 
                              SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout);

    //Este m�todo crea un shader de p�xel.
    HRESULT 
            CreatePixelShader(const void* pShaderBytecode, 
                              SIZE_T BytecodeLength, 
                              ID3D11ClassLinkage* pClassLinkage, 
                              ID3D11PixelShader** ppPixelShader);

    //Este m�todo crea un buffer.
    HRESULT 
            CreateBuffer(const D3D11_BUFFER_DESC* pDesc, 
                         const D3D11_SUBRESOURCE_DATA* pInitialData, 
                          ID3D11Buffer** ppBuffer);

    //Este m�todo crea un estado de sampler, que define c�mo se samplean las texturas.
    HRESULT 
            CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, 
                               ID3D11SamplerState** ppSamplerState);

    
private:


public:
    ID3D11Device* m_device = nullptr;
};
