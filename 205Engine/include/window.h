#pragma once
#include "PreRequisites.h"


///La clase Window gestiona la creación, actualización, renderización y destrucción de una ventana en una aplicación.
///  Tiene métodos para inicializar (init), actualizar (update), renderizar (render) y destruir (destroy) la ventana.
///  Además, contiene miembros para almacenar el handle de la ventana (m_hWnd), las dimensiones de la ventana (m_width y m_height), 
/// la instancia de la aplicación (m_hInst), 
/// las dimensiones del rectángulo de la ventana (m_rect) y el nombre de la ventana (m_windowName).


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
