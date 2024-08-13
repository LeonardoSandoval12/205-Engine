#pragma once
#include "PreRequisites.h"
#include "Utilities/Vectors/Vector3.h"
#include "Component.h"
#include "UserInterface.h"


class Transform : public Component
{
public:
    //Constructor que inicializa posicion, rotattion y escala
    Transform() : position(), rotation(), scale(), matrix(), Component(ComponentType::TRANSFORM) {}

    // Devuelve una referencia constante al vector position, que representa la posici�n del objeto en el espacio 3D.
    const EngineUtilities::Vector3& getPosition() const { return position; }

    // Establece un nuevo valor para position.
    void
    setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

    //Devuelve una referencia constante al vector rotation, que representa la rotaci�n del objeto.
    const EngineUtilities::Vector3& getRotation() const { return rotation; }

    //Establece un nuevo valor para rotation.
    void
        setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

    //Devuelve una referencia constante al vector scale, que representa la escala del objeto.
    const EngineUtilities::Vector3& getScale() const { return scale; }

    // Establece un nuevo valor para scale.
    void
    setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

    //M�todo que aplica una traslaci�n a la posici�n actual usando un vector de traslaci�n. 
    void
    translate(const EngineUtilities::Vector3& translation);


    ~Transform() = default;

    void
    init();

    // m�todo que actualiza el estado del objeto. El par�metro deltaTime representa el tiempo transcurrido desde la �ltima actualizaci�n
    void
    update(float deltaTime);

    //m�todo que renderiza (dibuja) el objeto utilizando un contexto de dispositivo (DeviceContext). 
    // Este contexto probablemente contiene informaci�n y recursos necesarios para realizar operaciones de dibujo en pantalla.
    void
    render(DeviceContext deviceContext);

    void
    destroy();

    //m�todo que gestiona la interfaz de usuario (UI) del objeto, 
    //abriendo una ventana de interfaz de usuario con un nombre dado (wName).
    //Aqui hay mas cosas relacionadas a la UI

    
    void
    ui(std::string wName);


    void
    ui_noWindow(std::string wName);

private:
    EngineUtilities::Vector3 position;
    EngineUtilities::Vector3 rotation;
    EngineUtilities::Vector3 scale;
    UserInterface UI;

public:
    XMMATRIX matrix;
};
