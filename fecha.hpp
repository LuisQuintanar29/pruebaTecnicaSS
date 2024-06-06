#ifndef __FECHA_HPP__
#define __FECHA_HPP__

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Fecha {
public:
    // constructores
    Fecha();
    Fecha(int dia, int mes, int anio);
    ~Fecha() = default;

    // setters
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    // getters 
    int getDia() const;
    int getAnio() const;
    string getMes() const;

    // otros metodos
    void imprimeFecha(const string& mensaje) const;
    int compararFechas(const Fecha& fech) const;

private:
    // atributos
    static const string meses[];
    int dia = 1;
    string mes = "Enero";
    int anio = 1900;
};

// Definición de los nombres de los meses
const string Fecha::meses[] = 
{
    "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", 
    "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
};

// Constructor
Fecha::Fecha(int dia, int mes, int anio)
    : dia(dia), mes((mes >= 1 && mes <= 12) ? meses[mes - 1] : meses[0]), anio(anio) {}

// Constructor con la fecha actual
Fecha::Fecha() 
{
    // Obtener la fecha actual del sistema
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    tm* current_tm = localtime(&current_time);

    // Establecer el día actual, asegurándose de que esté dentro del rango válido (1-31)
    dia = (current_tm->tm_mday >= 1 && current_tm->tm_mday <= 31) ? current_tm->tm_mday : 1;

    mes = meses[current_tm->tm_mon];
    // Se suma 1900 ya que tm_year es el número de años desde 1900
    anio = current_tm->tm_year + 1900; 
}

// Métodos setter
void Fecha::setDia(int dia) { this->dia = dia; }
void Fecha::setMes(int mes) { this->mes = (mes >= 1 && mes <= 12) ? meses[mes - 1] : meses[0]; }
void Fecha::setAnio(int anio) { this->anio = anio; }

// Métodos getter
int Fecha::getDia() const { return dia; }
int Fecha::getAnio() const { return anio; }
string Fecha::getMes() const { return mes; }

// Método para imprimir la fecha
void Fecha::imprimeFecha(const string& mensaje) const 
{
    cout << mensaje << dia << "/" << mes << "/" << anio << endl;
}
int Fecha::compararFechas(const Fecha& fecha2) const
{
    // Convertir ambas fechas a segundos
    tm tm1 = {};
    tm1.tm_year = anio - 1900;
    tm1.tm_mon = std::distance(Fecha::meses, std::find(std::begin(Fecha::meses), std::end(Fecha::meses), mes));
    tm1.tm_mday = dia;
    time_t time1 = std::mktime(&tm1);

    tm tm2 = {};
    tm2.tm_year = fecha2.getAnio() - 1900;
    tm2.tm_mon = std::distance(Fecha::meses, std::find(std::begin(Fecha::meses), std::end(Fecha::meses), fecha2.getMes()));
    tm2.tm_mday = fecha2.getDia();
    time_t time2 = std::mktime(&tm2);

    // Calcular la diferencia en segundos entre las dos fechas
    double differenceSeconds = difftime(time1, time2);

    // Convertir la diferencia de segundos a días
    return static_cast<int>(differenceSeconds / (60 * 60 * 24));
}

#endif // __FECHA_HPP__
