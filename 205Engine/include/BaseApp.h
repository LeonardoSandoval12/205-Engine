#pragma once
#include "PreRequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "Texture.h"
#include "depthstencilView.h"
#include "RenderTargetView.h"
#include "ViewPort.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "ModelLoader.h"

#include "UserInterface.h"
#include "Actor.h"



class
    BaseApp {
public:
    BaseApp() = default;
    ~BaseApp() = default;

    HRESULT
        init();

    void
        update();

    void
        render();

    void
        destroy();

    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC wndproc);

    void CreateGrid(int width, int depth, float spacing);

    Window                                  m_window;
    Device									m_device;
    DeviceContext							m_deviceContext;
    SwapChain								m_swapchain;
    Texture									m_BackBuffer;
    Texture									m_DepthStencil;
    DepthStencilView						m_depthStencilView;
    RenderTargetView						m_RenderTargetView;
    Viewport								m_viewport;
    ShaderProgram							m_shaderProgram;
    std::vector<Buffer>						m_vertexBuffers;
    std::vector<Buffer>						m_indexBuffers;
    Buffer									m_CBBufferNeverChanges;
    Buffer									m_CBBufferChangeOnResize;
    Buffer									m_CBBufferChangesEveryFrame;

    //Mesh									m_mesh;
    std::vector<Texture>					modelTextures;
    SamplerState							m_sampler;
    ModelLoader								m_model;
    Texture									m_default;
    std::vector<Texture>					gridTexs;
    UserInterface                            m_UserInterface;

    //XMMATRIX                            m_World;
    XMMATRIX                            m_View;
    XMMATRIX                            m_Projection;
    XMFLOAT4                            m_vMeshColor;
    CBNeverChanges                      cbNeverChanges;
    CBChangeOnResize                    cbChangesOnResize;
    CBChangesEveryFrame                 cb;
    //Grid Data
    MeshComponent                       MC;
    EngineUtilities::TSharedPointer<Actor> AGrid;

    //Vela Actor
    EngineUtilities::TSharedPointer<Actor> AVela;
    //std::vector<Texture> gridTexs;
   
};
