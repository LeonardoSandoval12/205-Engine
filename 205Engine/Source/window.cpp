#include "Window.h"

/// <summary>
/// l código define la implementación de la clase Window, que incluye métodos para inicializar (init),
///  actualizar (update), renderizar (render) y destruir (destroy) una ventana en una aplicación Windows. 
/// El método init se encarga de registrar la clase de ventana, crear la ventana y ajustarla a las dimensiones especificadas, 
/// además de mostrarla en pantalla. Los métodos update, render y destroy están definidos pero aún no tienen implementación, 
/// dejando espacio para añadir la lógica de actualización, renderización y destrucción de recursos.


HRESULT Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc)
{
    m_hInst = hInstance;
    // Register class
    
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndproc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    RECT rc = { 0, 0, 1500, 840 };
    m_rect = rc;
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    m_hWnd = CreateWindow("TutorialWindowClass", m_windowName.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!m_hWnd)
        return E_FAIL;

    ShowWindow(m_hWnd, nCmdShow);

    GetClientRect(m_hWnd, &m_rect);
    m_width = m_rect.right - m_rect.left;
    m_height = m_rect.bottom - m_rect.top;
    return S_OK;
}

void Window::update()
{

}

void Window::render()
{

}

void Window::destroy()
{

}

