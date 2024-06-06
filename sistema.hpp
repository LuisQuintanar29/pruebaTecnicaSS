#ifndef __SISTEMA_HPP__
#define __SISTEMA_HPP__

#include "usuario.hpp"
#include "boleto.hpp"
#include "evento.hpp"
#include "fecha.hpp"

class Sistema
{
public:
    Sistema() : acceso(false), usuarioActivoIndex(-1) {}
    ~Sistema() = default;

    void accederUsuario();
    void menuUsuario();
    void comprarBoleto();
    void editarCompra();
    void eliminarCompra();

    void accederAdmin();
    void menuAdmin();
    void crearEvento();
    void crearEvento(int idEvento, string nombreEvento, Fecha fechaEvento, string lugar, int numAsientos);
    void crearUsuario();
    void crearUsuario(string nombre, string contra);
    void borrarUsuario();
    void mostrarUsuarios();

    void mostrarEventos();
    void editarUsuario();
    void menuPrincipal();
    void cerrarSesion();

private:
    bool acceso;
    int usuarioActivoIndex;
    Evento* eventoElegido;
    vector<Evento> listaEventos;
    vector<Usuario> listaUsuarios;

    Usuario* verificaUsuario(const string& nombre, const string& contra);
};

void Sistema::menuPrincipal()
{
    while (true)
    {
        int eleccion;
        do {
            cout << "Ingresar como " << endl;
            cout << "1. Usuario" << endl;
            cout << "2. Administrador" << endl;
            cout << "3. Salir" << endl;
            cout << "Seleccione una opcion: " << endl;
            cin >> eleccion;
        } while (eleccion < 1 || eleccion > 3);
        switch (eleccion)
        {
        case 1:
            accederUsuario();
            break;
        case 2:
            accederAdmin();
            break;
        case 3:
            exit(0);
            break;
        }
    }
}

void Sistema::accederUsuario()
{
    string nombre;
    string contra;
    acceso = false;
    int intentos = 3;
    if (!listaUsuarios.empty())
    {
        do
        {
            if (intentos > 0)
            {
                cout << "Ingrese usuario: ";
                cin >> nombre;
                cout << "Ingrese contraseña: ";
                cin >> contra;
                Usuario* usuario = verificaUsuario(nombre, contra);
                if (usuario)
                {
                    usuarioActivoIndex = usuario - &listaUsuarios[0];
                    acceso = true;
                    cout << "Contraseña correcta." << endl;
                    menuUsuario();
                }
                else
                {
                    intentos--;
                    cout << "Usuario o contraseña incorrectos. Intentos restantes: " << intentos << endl;
                }
            }
            else
            {
                cout << "Demasiados intentos. Saliendo del sistema." << endl;
                exit(1);
            }
        } while (!acceso);
    }
    else
    {
        cout << "No hay usuarios registrados." << endl;
    }
}

Usuario* Sistema::verificaUsuario(const string& nombre, const string& contra)
{
    for (Usuario& usuario : listaUsuarios)
    {
        if (nombre == usuario.getNombre() && contra == usuario.getContra())
        {
            return &usuario;
        }
    }
    return nullptr;
}

void Sistema::menuUsuario()
{
    while (true)
    {
        int eleccion;
        do {
            cout << "¡Nos da gusto verte nuevamente, " << listaUsuarios[usuarioActivoIndex].getNombre() << "!" << endl;
            cout << "Presione: " << endl;
            cout << "1. Ver historial" << endl;
            cout << "2. Ver eventos" << endl;
            cout << "3. Comprar boleto" << endl;
            cout << "4. Editar compra" << endl;
            cout << "5. Eliminar compra" << endl;
            cout << "6. Editar perfil" << endl;
            cout << "7. Cerrar sesion " << endl;
            cout << "Seleccione una opcion: " << endl;
            cin >> eleccion;
        } while (eleccion < 1 || eleccion > 7);

        switch (eleccion)
        {
        case 1:
            listaUsuarios[usuarioActivoIndex].muestraHistorial();
            break;
        case 2:
            mostrarEventos();
            break;
        case 3:
            comprarBoleto();
            break;
        case 4:
            editarCompra();
            break;
        case 5:
            eliminarCompra();
            break;
        case 6:
            editarUsuario();
            break;
        case 7:
            cerrarSesion();
            return;
        }
    }
}

void Sistema::comprarBoleto()
{
    if (listaEventos.empty())
    {
        cout << "¡Hola, " << listaUsuarios[usuarioActivoIndex].getNombre() << "!" << endl;
        cout << "Actualmente no hay eventos disponibles, te invitamos a volver";
        cout << " pronto para descubrir nuevas experiencias" << endl;
    }
    else
    {
        int idEvento;
        cout << "¡" << listaUsuarios[usuarioActivoIndex].getNombre();
        cout << ", tenemos los siguientes eventos disponibles!" << endl;
        mostrarEventos();
        cout << "Recuerda que una vez adquiridos tus boletos tendrás únicamente dos días para modificar o cancelar tu compra" << endl;
        cout << "Ingresa el ID del evento de tu interés: ";
        cin >> idEvento;

        // Buscar el evento correspondiente al ID ingresado
        Evento* eventoSeleccionado = nullptr;
        for (Evento& evento : listaEventos) {
            if (evento.getID() == idEvento) {
                eventoSeleccionado = &evento;
                break;
            }
        }

        // Verificar si se encontró el evento
        if (eventoSeleccionado != nullptr) {
            // Se encontró el evento, proceder con la selección
            cout << "Has seleccionado: " << endl;
            eventoSeleccionado->imprimeEvento();
            int numAsiento;
            bool elegido = false;
            do {
                cout << "Ingrese el numero de asiento que desee comprar: ";
                cin >> numAsiento;
                // Verificar si el asiento está disponible
                auto asientosDisponibles = eventoSeleccionado->getAsientosLibres();
                auto it = asientosDisponibles.find(numAsiento);
                if (it != asientosDisponibles.end()) {
                    // El asiento está disponible, proceder con la compra
                    int fechaActual_ = 1;
                    cout << "La fecha de compra es de hoy?" << endl;
                    cout << "1. SI \n2. NO" << endl;
                    cout << "Seleccione una opcion: ";
                    cin >> fechaActual_;
                    Fecha f;
                    if (fechaActual_ == 2)
                    {
                        int dia, mes, anio;
                        cout << "Ingrese el dia de compra: ";
                        cin >> dia;
                        cout << "Ingrese el mes numericamente: ";
                        cin >> mes;
                        cout << "Ingrese el año: ";
                        cin >> anio;
                        f = Fecha(dia, mes, anio);
                    }
                    Boleto* boleto = new Boleto(1111 + numAsiento, eventoSeleccionado, numAsiento, f);
                    listaUsuarios[usuarioActivoIndex].comprarBoleto(boleto);
                    eventoSeleccionado->comprarBoleto(numAsiento, boleto->getID());
                    elegido = true;
                    cout << "¡Compra realizada con éxito! Tu asiento es el número " << numAsiento << endl;
                }
                else {
                    // El asiento no está disponible
                    cout << "Lo siento, el asiento seleccionado no está disponible. Por favor, elige otro." << endl;
                }
            } while (!elegido);
        }
        else {
            // No se encontró el evento
            cout << "No se encontró ningún evento con el ID ingresado." << endl;
        }
    }
}


void Sistema::editarCompra()
{
    
    int idBoleto, nuevoAsiento;
    Fecha fechaActual;

    cout << "Recuerda que únicamente puedes cancelar o modificar compras en un lapso de 2 días" << endl;
    cout << "Te mostramos los eventos que puedes modificar" << endl;
    if(!listaUsuarios[usuarioActivoIndex].historial3Dias())
        return;
    cout << "Ingrese el ID del boleto que desee modificar: ";
    cin >> idBoleto;

    bool compraEncontrada = false;
    for (Boleto* boleto : listaUsuarios[usuarioActivoIndex].getHistorial())
    {
        if (boleto->getID() == idBoleto)
        {   
            if( fechaActual.compararFechas(boleto->getFechaCompra()) > 2)
            {
                cout << "El boleto que seleccionaste tiene mas de dos dias de compra" << endl;
                return;
            }
            eventoElegido = boleto->getEvento();
            compraEncontrada = true;
            int nuevaOpcion;
            cout << "Seleccione la acción a realizar: " << endl;
            cout << "1. Cambiar asiento" << endl;
            cout << "2. Cancelar" << endl;
            cout << "Ingrese una opción: ";
            cin >> nuevaOpcion;

            switch (nuevaOpcion)
            {
            case 1:
            {
                boleto->getEvento()->mostrarAsientosDisponibles();
                int nuevoAsiento;
                cout << "Ingrese el nuevo número de asiento: ";
                cin >> nuevoAsiento;

                if (boleto->getEvento()->getAsientosLibres().count(nuevoAsiento))
                {
                    boleto->getEvento()->liberarAsiento(boleto->getAsiento()); // Liberar el asiento anterior
                    // Actualizar asiento en el boleto
                    eventoElegido->comprarBoleto(nuevoAsiento, boleto->getID());                    
                    boleto->setAsiento(nuevoAsiento);
                    boleto->setID(1111+nuevoAsiento);
                    cout << "Asiento cambiado exitosamente." << endl;
                }
                else
                {
                    cout << "Asiento no disponible. Intente de nuevo." << endl;
                }
                break;
            }
            case 2:
                return;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
            }
        }
    }

    if (!compraEncontrada)
    {
        cout << "Compra no encontrada. Intente de nuevo." << endl;
    }
    
}

void Sistema::eliminarCompra()
{
    int idBoleto;
    Fecha fechaActual;
    cout << "Recuerda que únicamente puedes cancelar o modificar compras en un lapso de 2 días" << endl;
    cout << "Te mostramos los eventos que puedes cancelar" << endl;
    if(!listaUsuarios[usuarioActivoIndex].historial3Dias())
        return;
    cout << "Ingrese el ID del boleto que desee cancelar: ";
    cin >> idBoleto;

    bool compraEncontrada = false;
    for (Boleto* boleto : listaUsuarios[usuarioActivoIndex].getHistorial())
    {
        if (boleto->getID() == idBoleto)
        {
            if( fechaActual.compararFechas(boleto->getFechaCompra()) > 2)
            {
                cout << "El boleto que seleccionaste tiene mas de dos dias de compra" << endl;
                return;
            }
            eventoElegido = boleto->getEvento();
            compraEncontrada = true;
            boleto->getEvento()->liberarAsiento(boleto->getAsiento());
            listaUsuarios[usuarioActivoIndex].borrarBoleto(idBoleto);            
            cout << "Compra eliminada exitosamente." << endl;
            break;
        }
    }

    if (!compraEncontrada)
    {
        cout << "Compra no encontrada. Intente de nuevo." << endl;
    }
}

void Sistema::editarUsuario()
{
    Usuario& usuario = listaUsuarios[usuarioActivoIndex];
    string nuevoNombre, nuevaContra;
    cout << "Editar perfil de " << usuario.getNombre() << endl;
    cout << "Ingrese el nuevo nombre (dejar vacío para no cambiar): ";
    cin.ignore(); // Limpiar el buffer de entrada
    getline(cin, nuevoNombre);
    cout << "Ingrese la nueva contraseña (dejar vacío para no cambiar): ";
    getline(cin, nuevaContra);

    if (!nuevoNombre.empty())
    {
        usuario.setNombre(nuevoNombre);
    }
    if (!nuevaContra.empty())
    {
        usuario.setContra(nuevaContra);
    }

    cout << "Perfil actualizado exitosamente." << endl;
}

void Sistema::cerrarSesion()
{
    acceso = false;
    usuarioActivoIndex = -1;
    cout << "Sesión cerrada. Regresando al menú principal..." << endl;
    menuPrincipal();
}

void Sistema::accederAdmin()
{
    string contra;
    acceso = false;
    int intentos = 3;
    do
    {
        if (intentos > 0)
        {
            cout << "Ingrese contraseña: ";
            cin >> contra;
            if (contra == "admin")
            {
                acceso = true;
                cout << "Contraseña correcta." << endl;
                menuAdmin();
            }
            else
            {
                intentos--;
                cout << "Contraseña incorrecta. Intentos restantes: " << intentos << endl;
            }
        }
        else
        {
            cout << "Demasiados intentos. Saliendo del sistema." << endl;
            exit(1);
        }
    } while (!acceso);
}

void Sistema::menuAdmin()
{
    while (true)
    {
        int eleccion;
        do {
            cout << "¡Bienvenido, Administrador!" << endl;
            cout << "Presione: " << endl;
            cout << "1. Crear evento" << endl;
            cout << "2. Crear usuario" << endl;
            cout << "3. Mostrar eventos" << endl;
            cout << "4. Mostrar usuarios" << endl;
            cout << "5. Cerrar sesion" << endl;
            cout << "Seleccione una opcion: " << endl;
            cin >> eleccion;
        } while (eleccion < 1 || eleccion > 5);

        switch (eleccion)
        {
        case 1:
            crearEvento();
            break;
        case 2:
            crearUsuario();
            break;
        case 3:
            mostrarEventos();
            break;
        case 4:
            mostrarUsuarios();
            break;
        case 5:
            cerrarSesion();
            return;
        }
    }
}

void Sistema::crearEvento()
{
    int idEvento, numAsientos;
    string nombreEvento, lugar;
    Fecha fechaEvento;

    cout << "Ingrese ID del evento: ";
    cin >> idEvento;
    cout << "Ingrese nombre del evento: ";
    cin.ignore();
    getline(cin, nombreEvento);
    cout << "Ingrese fecha del evento (dd mm aaaa): ";
    int dia, mes, anio;
    cin >> dia >> mes >> anio;
    fechaEvento = Fecha(dia, mes, anio);
    cout << "Ingrese lugar del evento: ";
    cin.ignore();
    getline(cin, lugar);
    cout << "Ingrese numero de asientos: ";
    cin >> numAsientos;

    crearEvento(idEvento, nombreEvento, fechaEvento, lugar, numAsientos);
}

void Sistema::crearEvento(int idEvento, string nombreEvento, Fecha fechaEvento, string lugar, int numAsientos)
{
    Evento nuevoEvento(idEvento, nombreEvento, fechaEvento, lugar, numAsientos);
    listaEventos.push_back(nuevoEvento);
    cout << "Evento creado exitosamente." << endl;
}

void Sistema::crearUsuario()
{
    string nombre, contra;
    cout << "Ingrese nombre de usuario: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese contraseña: ";
    getline(cin, contra);

    crearUsuario(nombre, contra);
}

void Sistema::crearUsuario(string nombre, string contra)
{
    Usuario nuevoUsuario(nombre, contra);
    listaUsuarios.push_back(nuevoUsuario);
    cout << "Usuario creado exitosamente." << endl;
}

void Sistema::mostrarUsuarios()
{
    cout << "Lista de usuarios:" << endl;
    for (const Usuario& usuario : listaUsuarios)
    {
        cout << "Nombre: " << usuario.getNombre() << endl;
    }
}

void Sistema::mostrarEventos()
{
    cout << "Lista de eventos:" << endl;
    for (const Evento& evento : listaEventos)
    {
        evento.imprimeEvento();
    }
}

#endif
