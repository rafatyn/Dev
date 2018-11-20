#include <iostream>
#include "SerialClass.h"

void main()
{
	// Puerto serie.
	Serial* Puerto = new Serial(const_cast<char*>("COM3"));

	int opc; // Guarda un 1 o 2 tipo entero queintroduces desde la consola.

	while (Puerto->IsConnected())
	{		
		std::cout << "Introduzca la opcion deseada: " << std::endl;
		std::cout << "Pulse 1 para encender el Led, pulse 2 para apagar." << std::endl << std::endl; // Muestra texto en pantalla.

		std::cin >> opc; // Aquí introduces un número, el 1 o el 2.

		switch (opc) // Espera recibir un 1 o un 2.
		{
		case 1:
			// Encener luz.
			std::cout << "Encendiendo" << std::endl;
			Puerto->WriteData(const_cast<char*>("A"), 1); 
			break;

		case 2:
			// Apagar luz.
			std::cout << "Apagando" << std::endl;
			Puerto->WriteData(const_cast<char*>("B"), 1);
			break;
		}
	}
}