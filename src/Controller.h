#include "linkedlist.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_cargarVentasDesdeTexto(char* path , LinkedList* pListVentas);
int controller_agregarVenta(LinkedList* pListVentas);
int controller_removerVenta(LinkedList* pListVentas);
int controller_editarVenta(LinkedList* pListVentas);
int controller_guardarVentassModoTexto(char* path , LinkedList* pListVentas);
int controller_guardarVentassModoBinario(char* path , LinkedList* pListVentas);
int controller_generarInformeModoTexto(char* path , LinkedList* pListVentas);

#endif /* CONTROLLER_H_ */
