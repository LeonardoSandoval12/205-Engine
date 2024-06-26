﻿//--------------------------------------------------------------------------------------
// File: 205Engine.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PreRequisites.h"
#include "window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "SwapChain.h"
#include "DepthStencilView.h"
#include "RenderTargetView.h"
#include "Viewport.h"
#include "Buffer.h"
#include "ShaderProgram.h"



//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
//HINSTANCE                           g_hInst = NULL;  
//HWND                                g_hWnd = NULL;

Device                              g_device;
Window                              g_window;
DeviceContext                       g_deviceContext;
SwapChain						    g_swapchain;
Texture								g_backBuffer;
Texture								g_DepthStencil;
DepthStencilView					g_DepthStencilView;
RenderTargetView                    g_renderTargetView;
Viewport                            g_viewport;
//InputLayout                         g_inputLayout;
ShaderProgram                       g_shaderProgram;
Buffer									g_vertexBuffer;
Buffer									g_indexBuffer;
Buffer									g_CBBufferNeverChanges;
Buffer									g_CBBufferChangeOnResize;
Buffer									g_CBBufferChangesEveryFrame;

Mesh									g_mesh;

//ID3D11RenderTargetView*             g_pRenderTargetView = NULL;
//ID3D11Texture2D*                    g_pDepthStencil = NULL;
//ID3D11DepthStencilView*             g_pDepthStencilView = NULL;
//ID3D11VertexShader*                 g_pVertexShader = NULL;
//                                    g_pPixelShader = NULL;
//ID3D11InputLayout*                  g_pVertexLayout = NULL;
ID3D11Buffer*                       g_pVertexBuffer = NULL;
ID3D11Buffer*                       g_pIndexBuffer = NULL;
ID3D11Buffer*                       g_pCBNeverChanges = NULL;
ID3D11Buffer*                       g_pCBChangeOnResize = NULL;
ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
ID3D11SamplerState*                 g_pSamplerLinear = NULL;
XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
//HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( g_window.init( hInstance, nCmdShow , WndProc ) ) )
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            Render();
        }
    }

    CleanupDevice();

    return ( int )msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
//HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
//{
//    // Register class
//    WNDCLASSEX wcex;
//    wcex.cbSize = sizeof( WNDCLASSEX );
//    wcex.style = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc = WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
//    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
//    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
//    wcex.lpszMenuName = NULL;
//    wcex.lpszClassName = "TutorialWindowClass";
//    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
//    if( !RegisterClassEx( &wcex ) )
//        return E_FAIL;
//
//    // Create window
//    g_hInst = hInstance;
//    RECT rc = { 0, 0, 640, 480 };
//    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
//    g_hWnd = CreateWindow( "TutorialWindowClass", "Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
//                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
//                           NULL );
//    if( !g_hWnd )
//        return E_FAIL;
//
//    ShowWindow( g_hWnd, nCmdShow );
//
//    return S_OK;
//}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

   
   
//    UINT createDeviceFlags = 0;
//#ifdef _DEBUG
//    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif
//
//    D3D_DRIVER_TYPE driverTypes[] =
//    {
//        D3D_DRIVER_TYPE_HARDWARE,
//        D3D_DRIVER_TYPE_WARP,
//        D3D_DRIVER_TYPE_REFERENCE,
//    };
//    UINT numDriverTypes = ARRAYSIZE( driverTypes );
//
//    D3D_FEATURE_LEVEL featureLevels[] =
//    {
//        D3D_FEATURE_LEVEL_11_0,
//        D3D_FEATURE_LEVEL_10_1,
//        D3D_FEATURE_LEVEL_10_0,
//    };
//    UINT numFeatureLevels = ARRAYSIZE( featureLevels );
//
//    DXGI_SWAP_CHAIN_DESC sd;
//    ZeroMemory( &sd, sizeof( sd ) );
//    sd.BufferCount = 1;
//    sd.BufferDesc.Width = g_window.m_width;
//    sd.BufferDesc.Height = g_window.m_height;
//    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    sd.BufferDesc.RefreshRate.Numerator = 60;
//    sd.BufferDesc.RefreshRate.Denominator = 1;
//    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    sd.OutputWindow = g_window.m_hWnd;
//    sd.SampleDesc.Count = 1;
//    sd.SampleDesc.Quality = 0;
//    sd.Windowed = TRUE;
//
//    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
//    {
//        g_driverType = driverTypes[driverTypeIndex];
//        hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
//                                            D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_device.m_device, &g_featureLevel, &g_deviceContext.m_deviceContext );
//        if( SUCCEEDED( hr ) )
//            break;
//    }
//    if( FAILED( hr ) )
//        return hr;
     g_swapchain.init(g_device, g_deviceContext, g_backBuffer, g_window);
//    // Create a render target view
// 
// //create Swapchain
    
// 
//    ID3D11Texture2D* pBackBuffer = NULL;
//    hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
//    if( FAILED( hr ) )
//        return hr;
//
     g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);

     
//   // if( FAILED( hr ) )
//        //return hr;
       g_DepthStencil.init(g_device, g_window.m_width
           , g_window.m_height,
           DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);
//    // Create depth stencil texture
;


    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory( &descDSV, sizeof(descDSV) );
    descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;

    g_device.CreateDepthStencilView(g_DepthStencil.m_texture, &descDSV, &g_DepthStencilView.m_DepthStencilView);
    //hr = g_device.m_device->CreateDepthStencilView( g_pDepthStencil, &descDSV, &g_pDepthStencilView );
    //if( FAILED( hr ) )
        //return hr;

    

    // Setup the viewport

    g_viewport.init(g_window);

    /*D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)g_window.m_width;
    vp.Height = (FLOAT)g_window.m_height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_deviceContext.m_deviceContext->RSSetViewports( 1, &vp );*/

    // Compile the vertex shader
   // ID3DBlob* pVSBlob = NULL;
   // hr = CompileShaderFromFile( "205Engine.fx", "VS", "vs_4_0", &pVSBlob );
   // if( FAILED( hr ) )
   // {
   //     MessageBox( NULL,
   //                 "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );
   //     return hr;
   // }

   // // Create the vertex shader
   // 
   // //hr = g_device.m_device->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );
   // hr = g_device.CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
   // if( FAILED( hr ) )
   // {    
   //    pVSBlob->Release();
   //    return hr;
   //}

    // Define the input layout
    std::vector<D3D11_INPUT_ELEMENT_DESC>Layout;
    D3D11_INPUT_ELEMENT_DESC position;
    position.SemanticName = "POSITION";
    position.SemanticIndex = 0;
    position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    position.InputSlot = 0;
    position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
    position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    position.InstanceDataStepRate = 0;
    Layout.push_back(position);

    D3D11_INPUT_ELEMENT_DESC texcoord;;
    texcoord.SemanticName = "TEXCOORD";
    texcoord.SemanticIndex = 0;
    texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
    texcoord.InputSlot = 0;
    texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
    texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    texcoord.InstanceDataStepRate = 0;
    Layout.push_back(texcoord);

    g_shaderProgram.init(g_device, "205Engine.fx", Layout);

    /*D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE( layout );*/

    // Create the input layout
    //hr = g_device.m_device->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
                                        //  pVSBlob->GetBufferSize(), &g_pVertexLayout );
    //hr = g_device.CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
       // pVSBlob->GetBufferSize(), &g_pVertexLayout);

    //g_inputLayout.init(g_device, Layout, pVSBlob);
    //pVSBlob->Release();
    ////if( FAILED( hr ) )
    //  //  return hr;

    //// Set the input layout
    ////g_deviceContext.m_deviceContext->IASetInputLayout( g_pVertexLayout );

    //// Compile the pixel shader
    //ID3DBlob* pPSBlob = NULL;
    //hr = CompileShaderFromFile( "205Engine.fx", "PS", "ps_4_0", &pPSBlob );
    //if( FAILED( hr ) )
    //{
    //    MessageBox( NULL,
    //                "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );
    //    return hr;
    //}

    //// Create the pixel shader
    ////hr = g_device.m_device->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );
    ////pPSBlob->Release();
    //hr = g_device.CreatePixelShader(pPSBlob->GetBufferPointer(),
    //                                pPSBlob->GetBufferSize(), 
    //                                NULL, &g_pPixelShader);

    //pPSBlob->Release();
    //if( FAILED( hr ) )
    //    return hr;

    // Create vertex buffer
    SimpleVertex vertices[] =
    {
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
    };

    g_mesh.name = "Cube";

    // Set vertex buffer
    for (const SimpleVertex& vertex : vertices)
    {
        g_mesh.vertex.push_back(vertex);
    }

    //// NOTA: El static_cast<unsigned int
    //se está utilizando aquí para convertir el resultado del método size() 
    //    de un std::vector a un tipo unsigned int.
    //    El método size() devuelve un valor del tipo std::size_t, 
    //    que es un tipo específico de tamaño no negativo.En algunas 
    //    plataformas, std : size_t puede ser de un tamaño diferente a unsigned int. /

    g_mesh.numVertex = static_cast<unsigned int>(g_mesh.vertex.size());


    // Create vertex buffer
    g_vertexBuffer.init(g_device, g_mesh, D3D11_BIND_VERTEX_BUFFER);

    
    // Create index buffer
    unsigned int indices[] =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };

    for (unsigned int index : indices) {
        g_mesh.index.push_back(index);
    }
    g_mesh.numIndex = static_cast<unsigned int>(g_mesh.index.size());

    // Set index buffer
    g_indexBuffer.init(g_device, g_mesh, D3D11_BIND_INDEX_BUFFER);

    // Inicialización de Constant Buffers
    g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

    g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

    g_CBBufferChangesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));

    // Load the Texture
    hr = D3DX11CreateShaderResourceViewFromFile( g_device.m_device, "seafloor.dds", NULL, NULL, &g_pTextureRV, NULL );
    if( FAILED( hr ) )
        return hr;

    // Create the sample state
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    //hr = g_device.m_device->CreateSamplerState( &sampDesc, &g_pSamplerLinear );
    hr = g_device.CreateSamplerState(&sampDesc, &g_pSamplerLinear);
    if( FAILED( hr ) )
        return hr;

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = XMMatrixLookAtLH( Eye, At, Up );

    cbNeverChanges.mView = XMMatrixTranspose(g_View);


    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f);

    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
    g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    if( g_deviceContext.m_deviceContext ) g_deviceContext.m_deviceContext->ClearState();

    if( g_pSamplerLinear ) g_pSamplerLinear->Release();
    if( g_pTextureRV ) g_pTextureRV->Release();
    if( g_pCBNeverChanges ) g_pCBNeverChanges->Release();
    if( g_pCBChangeOnResize ) g_pCBChangeOnResize->Release();
    if( g_pCBChangesEveryFrame ) g_pCBChangesEveryFrame->Release();
    if( g_pVertexBuffer ) g_pVertexBuffer->Release();
    if( g_pIndexBuffer ) g_pIndexBuffer->Release();

    g_shaderProgram.destroy();
    g_DepthStencilView.destroy();
    g_renderTargetView.destroy();
    g_deviceContext.destroy();
    g_swapchain.destroy();
    g_device.destroy();
    g_CBBufferNeverChanges.destroy();
    g_CBBufferChangeOnResize.destroy();
    g_CBBufferChangesEveryFrame.destroy();
    g_vertexBuffer.destroy();
    g_indexBuffer.destroy();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Clear the back buffer

    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    g_renderTargetView.render(g_deviceContext, g_DepthStencilView, 1, ClearColor);

    g_viewport.render(g_deviceContext);
    //
    // Clear the depth buffer to 1.0 (max depth)
    //
    //g_deviceContext.m_deviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    g_DepthStencilView.render(g_deviceContext);
    // Render the cube
    //
    g_shaderProgram.render(g_deviceContext);
    g_vertexBuffer.render(g_deviceContext, 0, 1);
    g_indexBuffer.render(g_deviceContext, DXGI_FORMAT_R32_UINT);
    g_CBBufferNeverChanges.render(g_deviceContext, 0, 1); // Slot 0
    g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1); // Slot 1
    g_CBBufferChangesEveryFrame.renderModel(g_deviceContext, 2, 1); // Slot 2
    g_modelTexture.render(g_deviceContext, 0, 1);
    //g_deviceContext.m_deviceContext->PSSetShaderResources( 0, 1, &g_pTextureRV );
    g_sampler.render(g_deviceContext, 0, 1);
    //Set primitve topology
    g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    g_deviceContext.m_deviceContext->DrawIndexed(g_mesh.numIndex, 0, 0);

    //
    // Present our back buffer to our front buffer
    //
    //g_pSwapChain->Present(0, 0);
    g_swapchain.present();
}
