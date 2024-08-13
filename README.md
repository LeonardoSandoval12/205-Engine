# 205-Engine
engine
Descripción
Project Name es una aplicación de renderizado 3D que utiliza Direct3D 11 y el SDK de Autodesk FBX para cargar y renderizar modelos 3D en una ventana de aplicación de Windows. El proyecto está diseñado para ser modular y extensible, permitiendo agregar componentes, texturas y modelos a la escena de manera flexible.

Características
Renderizado 3D: Utiliza Direct3D 11 para el renderizado de modelos 3D.
Carga de Modelos: Integración con el SDK de FBX para cargar y procesar modelos 3D.
Interfaz de Usuario: Interfaz gráfica utilizando ImGui para la manipulación de modelos y configuración de la escena.
Componentes de Actor: Soporte para componentes como mallas, transformaciones y texturas.
Estructura del Proyecto
Device.h: Manejo del dispositivo Direct3D.
DeviceContext.h: Manejo del contexto del dispositivo Direct3D.
Texture.h: Manejo de texturas.
RenderTargetView.h: Configuración de la vista de destino de renderizado.
Viewport.h: Configuración del área de visualización del renderizado.
Window.h: Gestión de la ventana de la aplicación.
Buffer.h: Manejo de buffers de datos.
MeshComponent.h: Componentes relacionados con mallas.
SamplerState.h: Configuración del estado del muestreador.
fbxsdk.h: SDK de Autodesk FBX para carga de modelos.
SwapChain.h: Manejo del swap chain para el renderizado.
BaseApp.h: Configuración de la aplicación base.
Actor.h: Definición de actores en la escena.
InputLayout.h: Configuración del diseño de entrada.
ModelLoader.h: Carga y procesamiento de modelos.
PreRequisites.h: Definiciones previas y dependencias.
ShaderProgram.h: Gestión de programas de sombreado.
UserInterface.h: Implementación de la interfaz de usuario con ImGui.
Component.h: Definición de componentes básicos.
Entity.h: Definición de entidades en la escena.
Transform.h: Manejo de transformaciones de objetos.
Instalación
Clonar el Repositorio:

bash
Copiar código
git clone https://github.com/yourusername/your-repository.git
Configurar el Entorno:
Asegúrate de tener instaladas las siguientes herramientas y bibliotecas:

Direct3D 11 SDK
Autodesk FBX SDK
ImGui para la interfaz de usuario
Construir el Proyecto:
Usa una herramienta de construcción como CMake para configurar y construir el proyecto.

Uso
Iniciar la Aplicación:
Ejecuta el binario generado para iniciar la aplicación.

Interacción:

Carga de Modelos: Utiliza el sistema de carga de modelos para importar archivos FBX.
Configuración de Escena: Usa la interfaz de usuario para ajustar parámetros y visualizar los modelos cargados.
Modificación:

Agregar Componentes: Modifica actores y componentes para extender la funcionalidad.
Actualizar Texturas y Modelos: Cambia y actualiza texturas y modelos según sea necesario.
