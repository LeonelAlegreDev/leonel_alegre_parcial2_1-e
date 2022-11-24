#include "linkedlist.h"

#ifndef VENTAS_H_
#define VENTAS_H_

typedef struct{
	int idVenta;
	char fecha[32];
	char modelo[64];
	int cantidad;
	float precio;
	char numeroTarjeta[128];
}Venta;

Venta* venta_newParametros(int id, char* fehca, char* modelo, int cantidad, float precio, char* numeroTarjeta);
int venta_generarNewId(LinkedList* pListVentas, int* id);

int venta_setFecha(Venta* venta, char* fecha);
int venta_setModelo(Venta* venta, char* modelo);
int venta_setCantidad(Venta* venta, int cantidad);
int venta_setPrecio(Venta* venta, float precio);
int venta_setTarjeta(Venta* venta, char* tarjeta);

int venta_precioMayorA(Venta* venta);

#endif /* VENTAS_H_ */
