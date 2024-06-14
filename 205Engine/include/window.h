#pragma once
#include "PreRequisites.h"


///La clase Window gestiona la creaci�n, actualizaci�n, renderizaci�n y destrucci�n de una ventana en una aplicaci�n.
///  Tiene m�todos para inicializar (init), actualizar (update), renderizar (render) y destruir (destroy) la ventana.
///  Adem�s, contiene miembros para almacenar el handle de la ventana (m_hWnd), las dimensiones de la ventana (m_width y m_height), 
/// la instancia de la aplicaci�n (m_hInst), 
/// las dimensiones del rect�ngulo de la ventana (m_rect) y el nombre de la ventana (m_windowName).


class Window
{
public:
    Window() = default;
    ~Window() = default;

    HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

    void update();

    void render();

    void destroy();

public:
    HWND m_hWnd = nullptr;
    unsigned int m_width;
    unsigned int m_height;
private:
    HINSTANCE m_hInst = nullptr;
    RECT m_rect;
    std::string m_windowName = "205Engine";
};
