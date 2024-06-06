#ifndef __BOLETO_HPP__
#define __BOLETO_HPP__

#include "fecha.hpp"
#include "evento.hpp"

class Boleto
{
public:
    // Constructores
    Boleto() = default;
    Boleto(int idBoleto, Evento* evento, int asiento, const Fecha& fechaCompra);
    ~Boleto() = default;

    // Getters
    int getID() const;
    int getAsiento() const;
    Evento* getEvento() const;
    const Fecha& getFechaCompra() const;

    // Setters
    void setID(int idBoleto);
    void setEvento(Evento* evento);
    void setFechaCompra(int dia, int mes, int anio);
    void setAsiento(int asiento);

    // Otros métodos
    void imprimeBoleto() const;

private:
    // Atributos
    int idBoleto;
    int asiento;
    Evento* evento;
    Fecha fechaCompra;
};

// Constructor
Boleto::Boleto(int idBoleto, Evento* evento, int asiento, const Fecha& fechaCompra)
    : idBoleto(idBoleto), evento(evento), asiento(asiento), fechaCompra(fechaCompra) {}

// Getters
int Boleto::getID() const { return idBoleto; }
int Boleto::getAsiento() const { return asiento; }
Evento* Boleto::getEvento() const { return evento; }
const Fecha& Boleto::getFechaCompra() const { return fechaCompra; }

// Setters
void Boleto::setID(int idBoleto) { 
    if (idBoleto > 0) {
        this->idBoleto = idBoleto; 
    }
}
void Boleto::setEvento(Evento* evento) { 
    if (evento != nullptr) {
        this->evento = evento; 
    }
}
void Boleto::setAsiento(int asiento) { 
    if (asiento > 0) {
        this->asiento = asiento; 
    }
}
void Boleto::setFechaCompra(int dia, int mes, int anio)
{
    fechaCompra.setDia(dia);
    fechaCompra.setMes(mes);
    fechaCompra.setAnio(anio);
}

// Método para imprimir el boleto
void Boleto::imprimeBoleto() const
{
    cout << "Boleto: " << idBoleto << endl;
    cout << "Evento: " << evento->getNombre() << endl;
    evento->getFecha().imprimeFecha("Fecha del evento: ");
    cout << "Lugar: " << evento->getLugar() << endl;
    cout << "Asiento: " << asiento << endl;
    fechaCompra.imprimeFecha("Fecha de compra: ");
}

#endif // __BOLETO_HPP__
