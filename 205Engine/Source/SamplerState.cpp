#include "SamplerState.h"
#include "Device.h"
#include "DeviceContext.h"

void 
SamplerState::init(Device device){

    // Verifica si el dispositivo es v�lido
    if (device.m_device == nullptr)
    {
        ERROR("SamplerState", "init", "CHECK FOR Unsupported BindFlag");
        WARNING("ERROR: SamplerState::init : Error in data from params [CHECK FOR Device device]");
        exit(1);
    }

    // Crear el estado de muestreo
    HRESULT hr = S_OK;
    D3D11_SAMPLER_DESC sampDesc;
    memset(&sampDesc, 0, sizeof(sampDesc)); // Inicializa la descripci�n a cero
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // Filtro lineal
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; // Envuelve en el eje U
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP; // Envuelve en el eje V
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; // Envuelve en el eje W
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER; // Sin comparaci�n
    sampDesc.MinLOD = 0; // L�mite m�nimo de LOD
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX; // L�mite m�ximo de LOD

    // Crear el sampler state
    hr = device.CreateSamplerState(&sampDesc, &m_sampler);

    if (FAILED(hr))
    {
        ERROR("SamplerState", "init", "CHECK FOR CreateSamplerState");
        WARNING("ERROR: SamplerState::init : Error in data from params [CHECK FOR Device device]");
        exit(1);
    }
}

void 
SamplerState::update(){

    // M�todo vac�o para actualizaciones, puede ser implementado m�s adelante
}

void
SamplerState::render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumSamplers){

    // Configura el sampler en el dispositivo de contexto
    deviceContext.PSSetSamplers(StartSlot, NumSamplers, &m_sampler);
}

void
SamplerState::destroy(){
    // Liberar el sampler state
    SAFE_RELEASE(m_sampler);
}