#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ventas.h"
#include "linkedlist.h"


/**
 * \brief Crea una nueva estructura de tipo Venta con los parametros seteados
 * \param id Id de la venta
 * \param fecha Fecha de la venta
 * \param modelo Modelo de la venta
 * \param cantidad Cantidad de objetos vendidos
 * \param precio Precio unitario
 * \param numeroTarjeta Numero de tarjeta
 * \return Retorna un puntero de tipo Venta o NULL
 */
Venta* venta_newParametros(int id, char* fecha, char* modelo, int cantidad, float precio, char* numeroTarjeta)
{
	Venta* auxVenta = NULL;

	if(id >= 0 && fecha != NULL && modelo!= NULL && cantidad > 0 && precio > 0 && numeroTarjeta != NULL)
	{
		auxVenta = malloc(sizeof(Venta));

		if(auxVenta != NULL){
			auxVenta->idVenta = id;
			strcpy(auxVenta->fecha, fecha);
			strcpy(auxVenta->modelo, modelo);
			auxVenta->cantidad = cantidad;
			auxVenta->precio = precio;
			strcpy(auxVenta->numeroTarjeta, numeroTarjeta);
		}
		else free(auxVenta);
	}

	return auxVenta;
}
/*
 * \biref Genera el valor del campo ID
 * \param pListVentas LinkedList que contiene las ventas
 * \param id Puntero donde se guardara el ID generado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int venta_generarNewId(LinkedList* pListVentas, int* id){
	int retorno = -1;	//ERROR
	int idGenerado;
	Venta* auxLastVenta;

	if(pListVentas != NULL){
		auxLastVenta = ll_get(pListVentas, ll_len(pListVentas) -1);

		if(auxLastVenta != NULL){
			idGenerado = auxLastVenta->idVenta;
			idGenerado++;
			*id = idGenerado;
			retorno = 0;
		}
	}

	return retorno;
}

/*
 * \brief Establece el valor del campo 'fecha' en una estructura de tipo Venta
 * \param venta Puntero a estructura de tipo Venta
 * \param fecha Cadena de carecteres con la fecha a cargar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int venta_setFecha(Venta* venta, char* fecha){
	int retorno = -1;	//ERROR

	if(venta != NULL && fecha != NULL){
		strcpy(venta->fecha, fecha);
		retorno = 0;	//EXITO
	}

	return retorno;
}

/*
 * \brief Establece el valor del campo 'modelo' en una estructura de tipo Venta
 * \param venta Puntero a estructura de tipo Venta
 * \param modelo Cadena de carecteres con el modelo a cargar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int venta_setModelo(Venta* venta, char* modelo){
	int retorno = -1;	//ERROR

	if(venta != NULL && modelo != NULL){
		strcpy(venta->modelo, modelo);
		retorno = 0;	//EXITO
	}

	return retorno;
}

/*
 * \brief Establece el valor del campo 'cantidad' en una estructura de tipo Venta
 * \param venta Puntero a estructura de tipo Venta
 * \param cantidad Entero con el valor a cargar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int venta_setCantidad(Venta* venta, int cantidad){
	int retorno = -1;	//ERROR

	if(venta != NULL && cantidad > 0){
		venta->cantidad = cantidad;
		retorno = 0;	//EXITO
	}

	return retorno;
}

/*
 * \brief Establece el valor del campo 'precio' en una estructura de tipo Venta
 * \param venta Puntero a estructura de tipo Venta
 * \param precio Numero decimal con el valor a cargar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int venta_setPrecio(Venta* venta, float precio){
	int retorno = -1;	//ERROR

	if(venta != NULL && precio > 0){
		venta->precio = precio;
		retorno = 0;	//EXITO
	}

	return retorno;
}

/*
 * \brief Establece el valor del campo 'numeroTarjeta' en una estructura de tipo Venta
 * \param venta Puntero a estructura de tipo Venta
 * \param tarjeta Cadena de caracteres con el numero de tarjeta a cargar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int venta_setTarjeta(Venta* venta, char* tarjeta){
	int retorno = -1;	//ERROR

	if(venta != NULL && tarjeta != NULL){
		strcpy(venta->numeroTarjeta, tarjeta);
		retorno = 0;	//EXITO
	}

	return retorno;
}

int venta_precioMayorA(Venta* venta){
	int retorno = 0;	//FALSO

	if(venta != NULL){
		if(venta->precio > 10000){
			retorno = 1;	//VERDADERO
		}
	}

	return retorno;
}
