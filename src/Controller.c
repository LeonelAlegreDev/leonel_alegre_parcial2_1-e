#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Controller.h"
#include "linkedlist.h"
#include "Ventas.h"
#include "utn.h"

/** \brief Carga los datos de las ventas desde un archivo .csv(modo texto).
 * \param path Ruta del texto a leer.
 * \param pListVentas Puntero a LinkedList de ventas
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int controller_cargarVentasDesdeTexto(char* path , LinkedList* pListVentas)
{
	int retorno = -1;	//ERROR

	FILE* pArchivo;
	Venta* auxVentas;

	char auxId[32];
	char auxFecha[64];
	char auxModelo[64];
	char auxCantidad[43];
	char auxPrecio[128];
	char auxTarjeta[64];

	int auxId2;
	int auxCantidad2;
	float auxPrecio2;

	int contador = 0;

	pArchivo = fopen(path, "r");

	if(pArchivo != NULL && path != NULL && pListVentas != NULL){
		do{
			if(fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					auxId, auxFecha, auxModelo, auxCantidad, auxPrecio, auxTarjeta))
			{
				if(contador == 0){
					contador++;
				}
				else{
					auxId2 = atoi(auxId);
					auxCantidad2 = atoi(auxCantidad);
					auxPrecio2 = atof(auxPrecio);

					auxVentas = venta_newParametros(auxId2, auxFecha, auxModelo, auxCantidad2, auxPrecio2, auxTarjeta);

					if(auxVentas != NULL){
						if(ll_add(pListVentas, auxVentas) == 0){
							retorno = 0;	//EXITO
						}
					}
				}
			}
			else break;

		}while(feof(pArchivo) == 0);

		fclose(pArchivo);
	}

    return retorno;
}

/** \brief Carga una Venta en la LinkedList.
 * \param pListVentas Puntero a LinkedList de ventas.
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int controller_agregarVenta(LinkedList* pListVentas){
	int retorno = -1;	//ERROR
	Venta* auxVenta;

	int id;
	char fecha[64];
	char modelo[64];
	int cantidad;
	float precio;
	char numeroTarjeta[64];

	if(pListVentas != NULL)
	{
		if(utn_getFecha(fecha, 64, "Ingresar fecha: \n", "Error fecha no valida\n", 2) == 1 &&
		   utn_getCadenaAlfanumerica(modelo, 64, "Ingresar nombre del modelo:\n","Error. Usar solo caracteres alfanumericos.\n", 2) == 1 &&
		   utn_getCadenaNumerica(numeroTarjeta, 64, "Ingresar numero de tarjeta:\n", "Error. Tarjeta invalida.\n", 13, 18, 2) == 1 &&
		   utn_getNumeroDecimal(&precio, "Ingresar Precio Unitario de la venta:\n", "Error. Ingresar un precio entre 1 y 10000000(10M).\n", 1, 10000000, 2) == 1 &&
		   utn_getNumero(&cantidad, "Ingresar la cantidad vendidad:\n", "Error. Ingresar un numero entre el 1 y el 50\n", 1, 50, 2) == 1 &&
		   venta_generarNewId(pListVentas, &id) == 0)
		{
			auxVenta = venta_newParametros(id, fecha, modelo, cantidad, precio, numeroTarjeta);

			if(ll_add(pListVentas, auxVenta) == 0){
				retorno = 0;
			}
		}
	}
	return retorno;
}

/** \brief Remueve una Venta de la LinkedList.
 * \param pListVentas Puntero a LinkedList de ventas.
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int controller_removerVenta(LinkedList* pListVentas){
	int retorno = -1;	//ERROR
	int auxId;
	Venta* auxVenta;

	if(pListVentas != NULL){
		if(utn_getNumero(&auxId, "Ingresar el ID de la venta a remover:\n", "Error, ID invalido.\n", 1, 30000, 2) == 1)
		{
			auxVenta = malloc(sizeof(Venta));

			for(int i = 0; i < ll_len(pListVentas); i++){
				auxVenta = ll_get(pListVentas, i);

				if(auxVenta != NULL && auxVenta->idVenta == auxId){
					if(ll_remove(pListVentas, i) == 0){
						retorno = 0;
					}
				}

			}
		}
	}
	free(auxVenta);

	return retorno;
}


/** \brief Edita una Venta ya cargada en la LinkedList.
 * \param pListVentas Puntero a LinkedList de ventas.
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int controller_editarVenta(LinkedList* pListVentas){
	int retorno = -1;	//ERROR
	int opcion;
	int id;
	int boolIndiceEncontrado = 0;
	Venta* auxVenta;
	char auxString[64];
	int auxInt;
	float auxFloat;

	if(pListVentas != NULL){
		auxVenta = malloc(sizeof(Venta));

		if(utn_getNumero(&id, "Ingresar el ID de la venta a modificar:\n","Error, ID no valido.\n", 1, 30000, 2) == 1)
		{
			for(int i = 0; i < ll_len(pListVentas); i++){
				auxVenta = ll_get(pListVentas, i);

				if(auxVenta != NULL && auxVenta->idVenta == id){
					boolIndiceEncontrado = 1;
					break;
				}
			}
			if(boolIndiceEncontrado == 1){
				printf("Seleccionar campo a modificar:\n");
				printf("1)Modificar Fecha\n");
				printf("2)Modificar Modelo\n");
				printf("3)Modificar Cantidad\n");
				printf("4)Modificar Precio\n");
				printf("5)Modificar Tarjeta\n");
				if(utn_getNumero(&opcion, "Ingresar opcion:\n","Error, opcion incorrecta.\n", 1, 5, 2) == 1)
				{
					switch(opcion){
					case 1:
						if(utn_getFecha(auxString, 64,"Ingresar nueva fecha: \n", "Error, fecha no valida.\n", 2) == 1)
						{
							if(venta_setFecha(auxVenta, auxString) == 0){
								retorno = 0;	//EXITO
							}
						}
						break;
					case 2:
						if(utn_getCadenaAlfanumerica(auxString, 64,"Ingresa nombre del modelo:\n", "Error al ingresar el nombre.\n", 2) == 1)
						{
							if(venta_setModelo(auxVenta, auxString) == 0){
								retorno = 0;	//EXITO
							}
						}
						break;
					case 3:
						if(utn_getNumero(&auxInt,"Ingresa nueva cantidad:\n", "Error, Ingresar un numero entre el 1 y 50.\n", 1, 50, 2) == 1)
						{
							if(venta_setCantidad(auxVenta, auxInt) == 0){
								retorno = 0;	//EXITO
							}
						}
						break;
					case 4:
						if(utn_getNumeroDecimal(&auxFloat,"Ingresa nuevo precio:\n", "Error. Ingresar un precio entre 1 y 10000000(10M)\n", 1, 10000000, 2) == 1)
						{
							if(venta_setPrecio(auxVenta, auxFloat) == 0){
								retorno = 0;	//EXITO
							}
						}
						break;
					case 5:
						if(utn_getCadenaNumerica(auxString, 64,"Ingresa nuevo numero de tarjeta:\n", "Error. Tarjeta invalida.\n", 13, 18, 2) == 1)
						{
							if(venta_setTarjeta(auxVenta, auxString) == 0){
								retorno = 0;	//EXITO
							}
						}
						break;
					}
				}
			}
		}
	}

	return retorno;
}

/** \brief Guarda los datos de las ventas en modo texto.
 * \param path Ruta del archivo a guardar.
 * \param pListVentas Puntero a LinkedList de ventas
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int controller_guardarVentassModoTexto(char* path , LinkedList* pListVentas){
	int retorno = -1;	//ERROR
	Venta* auxVenta;
	FILE* file;

	if(path != NULL && pListVentas != NULL)
	{
		file = fopen(path, "w");

		for(int i = 0; i < ll_len(pListVentas); i++){
			auxVenta = ll_get(pListVentas, i);

			if(auxVenta != NULL){
				fprintf(file, "%d,%s,%s,%d,%f,%s\n", auxVenta->idVenta, auxVenta->fecha, auxVenta->modelo,
						auxVenta->cantidad, auxVenta->precio, auxVenta->numeroTarjeta);
			}
		}
		retorno = 0;	//EXITO
	}

	fclose(file);
	return retorno;
}

/** \brief Guarda los datos de las ventas en modo binario.
 * \param path Ruta del archivo a guardar.
 * \param pListVentas Puntero a LinkedList de ventas
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int controller_guardarVentassModoBinario(char* path , LinkedList* pListVentas){
	int retorno = -1;	//ERROR
	Venta* auxVenta;
	FILE* file;

	if(path != NULL && pListVentas != NULL){
		file = fopen(path, "w");

		for(int i = 0; i < ll_len(pListVentas); i++){
			auxVenta = ll_get(pListVentas, i);

			if(auxVenta != NULL){
				if(fwrite(auxVenta, sizeof(Venta), 1, file) == 1){
				}
			}
		}
		retorno = 0;	//EXITO
		fclose(file);
	}

	return retorno;
}

/** \brief Genera un informe de las ventas y lo guarda en modo texto.
 * \param path Ruta del archivo a guardar.
 * \param pListVentas Puntero a LinkedList de ventas
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int controller_generarInformeModoTexto(char* path , LinkedList* pListVentas){
	int retorno = -1;	//ERROR
	Venta* auxVenta;
	FILE* file;
	int totalUnidadesVendidas = 0;
	int cantVentasMayorDe10000 = 0;
	int cantVentasMayorDe20000 = 0;
	int cantCamaroVendidos = 0;

	if(path != NULL && pListVentas != NULL){
		file = fopen(path, "w");

		for(int i = 0; i < ll_len(pListVentas); i++){
			auxVenta = ll_get(pListVentas, i);

			if(auxVenta != NULL){
				totalUnidadesVendidas = totalUnidadesVendidas + auxVenta->cantidad;
				if(auxVenta->precio > 10000){
					cantVentasMayorDe10000++;

					if(auxVenta->precio > 20000){
						cantVentasMayorDe20000++;
					}
				}
				//ll_count(pListVentas, venta_precioMayorA(auxVenta));

				if(strcmp(auxVenta->modelo, "Camaro") == 0){
					cantCamaroVendidos++;
				}
			}
		}

		fprintf(file, "********************\n");
		fprintf(file, "Informe de ventas\n");
		fprintf(file, "********************\n");
		fprintf(file, "- Cantidad de unidades vendidas totales: %d\n", totalUnidadesVendidas);
		fprintf(file, "- Cantidad de ventas por un monto mayor a $10000: %d\n", cantVentasMayorDe10000);
		fprintf(file, "- Cantidad de ventas por un monto mayor a $20000: %d\n", cantVentasMayorDe20000);
		fprintf(file, "- Cantidad de Camaro vendidos: %d\n", cantCamaroVendidos);
		fprintf(file, "********************\n");

		retorno = 0;	//EXITO
		fclose(file);
	}

	return retorno;
}





