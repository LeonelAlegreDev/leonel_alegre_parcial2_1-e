#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Controller.h"
#include "linkedlist.h"
#include "Ventas.h"
#include "utn.h"

int main(void) {
	setbuf(stdout, NULL);

	LinkedList* pVentas;

	int opcion;
	int opcionGuardarArchivo;

	pVentas = ll_newLinkedList();
	controller_cargarVentasDesdeTexto("./data/MOCK_DATA.csv", pVentas);

	do{
		printf("**************** Menu Principal ****************\n");
		printf("1) Cargar nueva venta.\n");
		printf("2) Borrar venta.\n");
		printf("3) Modificar venta.\n");
		printf("4) Guardar cambios.\n");
		printf("5) Generar informes.\n");

		if(utn_getNumero(&opcion, "Ingresar opcion: \n", "Error. Opcion invalida.\n", 1, 10, 1) == 1)
		{
			switch(opcion){
			case 1:
				printf("********** Alta **********\n");
				if(controller_agregarVenta(pVentas) == 0){
					printf("Venta cargada en el sistema.\n");
				}
				else{
					printf("Error. No se pudo cargar la venta.\n");
				}
				break;

			case 2:
				printf("********** Baja **********\n");
				if(controller_removerVenta(pVentas) == 0){
					printf("Venta removida del sistema.\n");
				}
				else{
					printf("Error. No se pudo remover la venta.\n");
				}
				break;

			case 3:
				printf("********** Modificar **********\n");
				if(controller_editarVenta(pVentas) == 0){
					printf("Se modifico la venta con exito.\n");
				}
				else{
					printf("Error No se pudo moficiar la venta.\n");
				}
				break;

			case 4:
				printf("********** Guardar archivo **********\n");
				printf("1) Guardar archivo en formato texto.\n");
				printf("2) Guardar archivo en formato binario.\n");

				if(utn_getNumero(&opcionGuardarArchivo,"Seleccionar opcion de guardado: \n","Error, opcion invalida\n", 1, 2, 2) == 1){
					switch(opcionGuardarArchivo){
					case 1:
						if(controller_guardarVentassModoTexto("./data/VentasGuardadasModoTexto.csv", pVentas) == 0){
							printf("El archivo se guardo correctamente.\n");
						}
						else printf("Error. No se pudo guardar el archivo.\n");
						break;
					case 2:
						if(controller_guardarVentassModoBinario("./data/VentasGuardadasModoBinario.txt", pVentas) == 0){
							printf("El archivo se guardo correctamente.\n");
						}
						else printf("Error. No se pudo guardar el archivo.\n");
						break;
					}
				}
				break;

			case 5:
				printf("Generar Informe Ventas\n");
				if(controller_generarInformeModoTexto("./data/InformeDeVentas.txt" , pVentas) == 0){
					printf("Informe generado correctamente.\n");
				}
				else printf("Error. No se pudo generar informe.\n");
				break;

			case 6:
				printf("Salir\n");
				break;
			}
		}

	}while(opcion != 6);

	return EXIT_SUCCESS;
}
