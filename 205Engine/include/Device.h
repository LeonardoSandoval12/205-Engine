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

    //Este método crea una vista de objetivo de renderizado.
    HRESULT
            CreateRenderTargetView(ID3D11Resource* pResource, 
                                   const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, 
                                   ID3D11RenderTargetView** ppRTView);

    //Este método crea una textura de profundidad 2D.
    HRESULT 
            CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
                             const D3D11_SUBRESOURCE_DATA* pInitialData,
                             ID3D11Texture2D** ppTexture2D);
   
    //Este método crea una vista de stencil de profundidad.
    HRESULT
            CreateDepthStencilView(ID3D11Resource* pResource,
                                   const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
                                   ID3D11DepthStencilView** ppDepthStencilView);

    //Este método crea un shader de vértice.
    HRESULT 
            CreateVertexShader(const void* pShaderBytecode, 
                               unsigned int BytecodeLength, 
                               ID3D11ClassLinkage* pClassLinkage, 
                               ID3D11VertexShader** ppVertexShader);

    //Este método crea un diseño de entrada, que describe cómo los datos de vértice son interpretados por el pipeline gráfico.
    HRESULT 
            CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
                              UINT NumElements, const void* pShaderBytecodeWithInputSignature, 
                              SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout);

    //Este método crea un shader de píxel.
    HRESULT 
            CreatePixelShader(const void* pShaderBytecode, 
                              SIZE_T BytecodeLength, 
                              ID3D11ClassLinkage* pClassLinkage, 
                              ID3D11PixelShader** ppPixelShader);

    //Este método crea un buffer.
    HRESULT 
            CreateBuffer(const D3D11_BUFFER_DESC* pDesc, 
                         const D3D11_SUBRESOURCE_DATA* pInitialData, 
                          ID3D11Buffer** ppBuffer);

    //Este método crea un estado de sampler, que define cómo se samplean las texturas.
    HRESULT 
            CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, 
                               ID3D11SamplerState** ppSamplerState);

    
private:


public:
    ID3D11Device* m_device = nullptr;
};
