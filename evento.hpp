#ifndef __EVENTO_HPP__
#define __EVENTO_HPP__

#include "boleto.hpp"
#include "fecha.hpp"

class Evento
{
public:
    // Constructor
    Evento() = default;
    Evento(int idEvento, const string& nombreEvento, const Fecha& fechaEvento, const string& lugar, int numAsientos);
    ~Evento() = default;

    // Setters
    void setID(int idEvento);
    void setLugar(const string& lugar);
    void setNumAsientos(int numAsientos);
    void setNombre(const string& nombreEvento);
    void setFecha(int dia, int mes, int anio);

    // Getters
    int getID() const;
    const map<int,int>& getAsientosLibres() const;
    const map<int,int>& getAsientosTotales() const;
    const map<int,int>& getAsientosOcupados() const;
    const string& getNombre() const;
    const string& getLugar() const;
    const Fecha& getFecha() const;

    // Otros métodos
    void comprarBoleto(int numAsiento, int idBoleto);
    void liberarAsiento(int numAsiento);
    void editarAsiento(int numAsientoAnterior, int asientoNuevo, int idBoleto);    
    bool asientoDisponible(int asiento) const;
    void mostrarAsientosDisponibles() const;
    void imprimeEvento() const;

private:
    // Atributos
    int idEvento = 0;
    string nombreEvento;
    Fecha fechaEvento;
    string lugar;
    map<int,int> asientosLibres;
    map<int,int> asientosTotales;
    map<int,int> asientosOcupados;

    // Métodos privados
    void setAsientosTotales(int numAsientos);
};

// Constructor
Evento::Evento(int idEvento, const string& nombreEvento, const Fecha& fechaEvento, const string& lugar, int numAsientos)
    : idEvento(idEvento), nombreEvento(nombreEvento), fechaEvento(fechaEvento), lugar(lugar)
{
    this->setAsientosTotales(numAsientos);
}

// Setters
void Evento::setID(int idEvento) { this->idEvento = idEvento; }
void Evento::setNombre(const string& nombreEvento) { this->nombreEvento = nombreEvento; }
void Evento::setLugar(const string& lugar) { this->lugar = lugar; }
void Evento::setFecha(int dia, int mes, int anio)
{
    fechaEvento.setDia(dia);
    fechaEvento.setMes(mes);
    fechaEvento.setAnio(anio);
}

// Crear los asientos del evento según numAsientos, le asignamos -1 para indicar que están vacíos
void Evento::setAsientosTotales(int numAsientos)
{
    if (numAsientos > 0)
    {
        for (int i = 0; i < numAsientos; i++)
        {
            asientosTotales[i + 1] = -1;
            asientosLibres[i + 1] = -1;
        }
    }
}

// Getters
int Evento::getID() const { return idEvento; }
const map<int,int>& Evento::getAsientosLibres() const { return asientosLibres; }
const map<int,int>& Evento::getAsientosTotales() const { return asientosTotales; }
const map<int,int>& Evento::getAsientosOcupados() const { return asientosOcupados; }
const string& Evento::getNombre() const { return nombreEvento; }
const string& Evento::getLugar() const { return lugar; }
const Fecha& Evento::getFecha() const { return fechaEvento; }

// Comprar boleto, asignamos el ID del boleto al asiento y actualizamos los asientos ocupados y libres
void Evento::comprarBoleto(int numAsiento, int idBoleto)
{
    auto asientoElegido = asientosLibres.find(numAsiento);
    if (asientoElegido != asientosLibres.end())
    {
        // Elimina el asiento de los asientos libres
        asientosLibres.erase(asientoElegido);
        // Asigna el ID del boleto al asiento
        asientosOcupados[numAsiento] = idBoleto;
        asientosTotales[numAsiento] = idBoleto;
    }
}

// Liberar asiento, actualizar asientos libres y ocupados, y reiniciar a -1
void Evento::liberarAsiento(int numAsiento)
{
    auto asientoALiberar = asientosOcupados.find(numAsiento);
    if (asientoALiberar != asientosOcupados.end())
    {
        // Elimina el asiento de los asientos ocupados
        asientosOcupados.erase(asientoALiberar);
        // Restablece el asiento como libre
        asientosLibres[numAsiento] = -1;
        asientosTotales[numAsiento] = -1;
    }
}

// Editar asiento, liberar el asiento anterior y asignar el nuevo
void Evento::editarAsiento(int numAsientoAnterior, int asientoNuevo, int idBoleto)
{
    liberarAsiento(numAsientoAnterior);
    comprarBoleto(asientoNuevo, idBoleto);
}

void Evento::imprimeEvento() const
{
    cout << "ID del Evento: " << idEvento << endl;
    cout << "Nombre del Evento: " << nombreEvento << endl;
    fechaEvento.imprimeFecha("Fecha del Evento: ");
    cout << "Lugar del Evento: " << lugar << endl;
    cout << "Asientos Totales: " << asientosTotales.size() << endl;
    cout << "Asientos Ocupados: " << asientosOcupados.size() << endl;
    mostrarAsientosDisponibles();
}

// Verificar si el asiento está disponible
bool Evento::asientoDisponible(int asiento) const
{
    auto it = asientosTotales.find(asiento);
    return (it != asientosTotales.end() && it->second == -1);
}

void Evento::mostrarAsientosDisponibles() const
{
    int inicioRango = -1;
    int finRango = -1;
    bool enRango = false;

    for (const auto& par : asientosTotales) {
        int asiento = par.first;
        int idBoleto = par.second;

        if (idBoleto == -1) { // Asiento disponible
            if (!enRango) {
                inicioRango = asiento;
            }
            finRango = asiento; // Actualiza el final del rango en cada iteración
            enRango = true;
        }
        else { // Asiento ocupado
            if (enRango) {
                // Verifica si el rango es mayor o igual a tres
                if (finRango - inicioRango >= 2) {
                    cout << "Asientos del " << inicioRango << " al " << finRango << " están disponibles." << endl;
                }
                else {
                    // Imprime individualmente si el rango es menor a tres
                    for (int i = inicioRango; i <= finRango; ++i) {
                        cout << "Asiento " << i << " está disponible." << endl;
                    }
                }
                enRango = false;
            }
        }
    }

    if (enRango) { // Si quedó algún rango sin imprimir al final
        if (finRango - inicioRango >= 2) {
            cout << "Asientos del " << inicioRango << " al " << finRango << " están disponibles." << endl;
        }
        else {
            for (int i = inicioRango; i <= finRango; ++i) {
                cout << "Asiento " << i << " está disponible." << endl;
            }
        }
    }
}

#endif // __EVENTO_HPP__
