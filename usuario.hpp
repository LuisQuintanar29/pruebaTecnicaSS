#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include "boleto.hpp"
#include <algorithm>

#define LINEAS_ 40

class Usuario
{
public:
    // Constructores
    Usuario() = default;
    Usuario(const std::string& nombre, const std::string& contra);
    ~Usuario();

    // Getters
    std::string getNombre() const;
    std::string getContra() const;
    std::vector<Boleto*> getHistorial() const;

    // Setters
    void setNombre(const std::string& nombre);
    void setContra(const std::string& contra);

    // Otros métodos
    void muestraHistorial() const;
    bool historial3Dias() const;
    void borrarBoleto(int idBoleto);
    void comprarBoleto(Boleto* boleto);
    void modificarBoleto(int idBoleto, int numAsiento);

private:
    // Atributos
    std::vector<Boleto*> historial;
    std::string nombre = "";
    std::string contra = "";
    int dias_tolerancia = 2;
};

// Constructor
Usuario::Usuario(const std::string& nombre, const std::string& contra)
    : nombre(nombre), contra(contra) {}

// Destructor para liberar memoria
Usuario::~Usuario() {
    for (Boleto* boleto : historial) {
        delete boleto;
    }
}

// Getters
std::string Usuario::getNombre() const { return nombre; }
std::string Usuario::getContra() const { return contra; }
std::vector<Boleto*> Usuario::getHistorial() const { return historial; }

// Setters
void Usuario::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Usuario::setContra(const std::string& contra) { this->contra = contra; }

// Otros métodos
void Usuario::muestraHistorial() const
{
    if (historial.empty())
    {
        std::cout << "No tienes historial con nosotros. No esperes más a vivir la experiencia con nosotros" << std::endl;
        return;
    }
    for (size_t i = 0; i < LINEAS_; i++) { std::cout << "_"; }
    std::cout << std::endl << "¡" << nombre << ", gracias por confiar en nosotros!" << std::endl;
    std::cout << "Aquí está tu historial de compras: " << std::endl;
    for (size_t i = 0; i < LINEAS_; i++) { std::cout << "_"; }
    std::cout << std::endl;
    for (const Boleto* boleto : historial)
    {
        boleto->imprimeBoleto();
        for (size_t i = 0; i < LINEAS_; i++) { std::cout << "_"; }
        std::cout << std::endl;
    }
}

bool Usuario::historial3Dias() const
{
    if (historial.empty())
    {
        std::cout << "No tienes historial dentro de los días de tolerancia" << std::endl;
        return false;
    }
    Fecha fechaActual;
    int cantidad = 0;
    for (const Boleto* boleto : historial)
    {
        if (fechaActual.compararFechas(boleto->getFechaCompra()) <= dias_tolerancia)
        {
            for (size_t i = 0; i < LINEAS_; i++) { std::cout << "_"; }
            std::cout << std::endl;
            boleto->imprimeBoleto();
            for (size_t i = 0; i < LINEAS_; i++) { std::cout << "_"; }
            std::cout << std::endl;
            cantidad ++;
        }
    }
    if (cantidad)
        return true;
    else
    {
        std::cout << "No tienes historial dentro de los días de tolerancia" << std::endl;
        return false;
    }
}

void Usuario::borrarBoleto(int idBoleto) {
    auto it = std::find_if(historial.begin(), historial.end(),
                           [idBoleto](const Boleto* boleto) { return boleto->getID() == idBoleto; });
    if (it != historial.end())
    {
        delete *it;
        historial.erase(it);
    }
}

void Usuario::comprarBoleto(Boleto* boleto)
{
    if (boleto != nullptr)
    {
        historial.push_back(boleto);
    }
}

void Usuario::modificarBoleto(int idBoleto, int numAsiento)
{
    for (Boleto* boleto : historial)
    {
        if (boleto->getID() == idBoleto)
        {
            boleto->setID(1111 + numAsiento);
            boleto->setAsiento(numAsiento);
            boleto->imprimeBoleto();
        }
    }
}

#endif // __USUARIO_HPP__
