#include "Window.h"

/// <summary>
/// l c�digo define la implementaci�n de la clase Window, que incluye m�todos para inicializar (init),
///  actualizar (update), renderizar (render) y destruir (destroy) una ventana en una aplicaci�n Windows. 
/// El m�todo init se encarga de registrar la clase de ventana, crear la ventana y ajustarla a las dimensiones especificadas, 
/// adem�s de mostrarla en pantalla. Los m�todos update, render y destroy est�n definidos pero a�n no tienen implementaci�n, 
/// dejando espacio para a�adir la l�gica de actualizaci�n, renderizaci�n y destrucci�n de recursos.


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

