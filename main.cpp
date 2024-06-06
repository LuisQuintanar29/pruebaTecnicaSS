# include "sistema.hpp"

int main()
{
	Fecha f;
	Sistema s;	
	s.crearEvento(12, "Juan Gabriel", f, "Bellas Artes", 300);
	s.crearEvento(15, "Luis Miguel", f, "Viña del mar", 350);
	s.crearEvento(18, "Feria Gastronómica Internacional", f, "Centro de Convenciones", 100);
	s.crearEvento(17, "Noche de Talentos", f, "Jardín Botánico", 75);
	s.crearUsuario("Luis", "1234");
	s.crearUsuario("Xavier", "1234");
	s.crearUsuario("Ana","1234");
	
	s.menuPrincipal();

	return 0;
}