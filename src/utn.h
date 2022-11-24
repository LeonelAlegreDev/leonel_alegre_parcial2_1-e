#ifndef UTN_H_
#define UTN_H_

int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int intentos);
int utn_getNumeroDecimal(float* pResultado, char* mensaje, char* MensajeError, float minimo, float maximo, int intentos);
int utn_getCadenaAlfanumerica(char* pString, int lenght, char* mensaje, char* mensajeError, int intentos);
int utn_getCadenaNumerica(char* pString, int lenght, char* mensaje, char* mensajeError, int minDigits, int maxDigits , int intentos);
int utn_getFecha(char* pString, int length, char* mensaje, char* mensajeError, int intentos);
#endif /* UTN_H_ */

