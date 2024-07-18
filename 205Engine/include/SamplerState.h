#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;

class SamplerState
{
public:
    // Constructor por defecto
    SamplerState() = default;
    // Destructor por defecto
    ~SamplerState() = default;

    // M�todo para inicializar el estado del sampler
    void init(Device device);

    // M�todo para actualizar el estado del sampler
    void update();

    // M�todo para renderizar usando el contexto del dispositivo
    // Recibe un contexto de dispositivo, la ranura de inicio y el n�mero de samplers
    void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumSamplers);

    // M�todo para destruir o liberar recursos del estado del sampler
    void destroy();

private:
    // Puntero al estado del sampler de Direct3D 11
    ID3D11SamplerState* m_sampler = nullptr;
};
