#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

static int getInt(int* pResultado);
static int esNumerica(char* cadena);
static int myGets(char* cadena, int longitud);
static int getFloat(float* pResultado);
static int esFlotante(char* cadena);
static int getCadenaAlfanumerica(char *pString);
static int esAlfanumerica(char* cadena);
static int getFecha(char *pString);
static int esFecha(char* cadena);
static int getCadenaNumerica(char *pString, int minDigits, int maxDigits);



/**
 * \brief Solicita un numero entero por consola
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el valor minimo tolerado
 * \param maximo Es el valor maximo tolerado
 * \param intentos La cantidad de intentos tolerados, minimo 1
 * \return Retorna 1 = EXITO y 0 = ERROR
 */
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int intentos){
	int returnValue;
	int numero;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && intentos >= 1){	//validacion de parametros
		while(intentos > 0){
			printf(mensaje);
			if(getInt(&numero) == 1){
				if(numero <= maximo && numero >= minimo) break;
			}
			fflush(stdin);
			intentos--;
			printf(mensajeError);
		}//end while
		if(intentos == 0){
			returnValue = 0;		//false
		}
		else{
			returnValue = 1;		//true
			*pResultado = numero;
		}
	}
	else returnValue = 0;			//false

	return returnValue;
}

/**
 * \brief Recibe un entero y verifica que la cadena sea valida
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 1 = EXITO y 0 = ERROR
*/
static int getInt(int* pResultado){
	int returnValue = 0;	//ERR0R
	char buffer[64];

	if(pResultado != NULL){
		if(myGets(buffer, sizeof(buffer)) && esNumerica(buffer)){
			*pResultado = atoi(buffer);
			returnValue = 1;	//EXITO
		}
	}
	return returnValue;
}

/**
* \brief Valida si la cadena ingresada es un numero entero
* \param cadena Cadena de caracteres a validar
* \return Retorna 1 = TRUE si la cadena es numerica y 0 = FALSE si no lo es
*/
static int esNumerica(char* cadena){
	int i = 0;
	int returnValue = 1;	//TRUE

	if(cadena != NULL && strlen(cadena) > 0){
		while(cadena[i] != '\0'){
			if(cadena[i] < '0' || cadena[i] > '9'){
				returnValue = 0;	//FALSE
				break;
			}
			i++;
		}
	}
	else{
		returnValue = 0;	//FALSE
	}
	return returnValue;
}

/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * un máximo de 'longitud - 1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 1  = EXITO y 0 = ERROR
*/
static int myGets(char* cadena, int longitud){
	int returnValue = 0;	//ERROR

	if(cadena != NULL && longitud > 0 && fgets(cadena, longitud, stdin) == cadena){
		fflush(stdin);
		if(cadena[strlen(cadena) - 1] == '\n'){
			cadena[strlen(cadena) - 1] = '\0';
		}
		returnValue = 1;	//EXITO
	}
	return returnValue;
}

/**
 * \brief Solicita un numero decimal por consola
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el numero minimo tolerado
 * \param maximo Es el numero maximo tolerado
 * \param intentos La cantidad de intentos tolerados, minimo 1
 * \return Retorna 1 = EXITO y 0 = ERROR
 */
int utn_getNumeroDecimal(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int intentos){
	int returnValue;
	float floatNumber;

	while(intentos > 0){
		printf(mensaje);
		if(getFloat(&floatNumber) == 1){
			if(floatNumber <= maximo && floatNumber >= minimo) break;
		}
		fflush(stdin);
		intentos--;
		printf(mensajeError);
	}//end while
	if(intentos == 0) returnValue = 0;	//ERROR
	else{
		returnValue = 1;				//EXITO
		*pResultado = floatNumber;
	}

	return returnValue;
}

/**
 * \brief Recibe un numero flotante y verifica que la cadena sea valida
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 1 = EXITO y 0 = ERROR
*/
static int getFloat(float* pResultado){
	int returnValue = 0;	//ERROR
	char buffer[64];

	if(myGets(buffer, sizeof(buffer)) && esFlotante(buffer)){
		*pResultado = atof(buffer);
		returnValue = 1;	//EXITO
	}

	return returnValue;
}

/**
* \brief Verifica si la cadena ingresada es un numero flotante
* \param cadena Cadena de caracteres a ser analizada
* \return Retorna 1 = TRUE si la cadena es numerica y 0 FALSE si no lo es
*/
static int esFlotante(char* cadena){
	int i = 0;
	int returnValue = 1;	//TRUE
	int deteccionDeComa = 0;

	if(cadena != NULL && strlen(cadena) > 0){
		while(cadena[i] != '\0'){
			if(cadena[i] < '0' || cadena[i] > '9'){
				if(cadena[i] == '.' && deteccionDeComa == 0){
					deteccionDeComa = 1;
				}else{
					returnValue = 0;	//FALSE
					break;
				}
			}
			i++;
		}//end while
	}
	else returnValue = 0;	//FALSE
	return returnValue;
}

/**
 * \brief Solicita una cadena alfanumerica por consola
 * \param pString Puntero al espacio de memoria donde se guarda la cadena ingresada
 * \param length Cantidad de caracteres permitidos
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param intentons La cantidad de intentos tolerados, minimo 1
 * \return Retorna 1 en caso de EXITO y 0 en caso de ERROR
 */
int utn_getCadenaAlfanumerica(char* pString, int lenght, char* mensaje, char* mensajeError, int intentos){
	int returnValue;
	char buffer[32];

	if(pString != NULL && mensaje != NULL && mensajeError != NULL && intentos > 0){
		while(intentos > 0){
			printf(mensaje);
			if(getCadenaAlfanumerica(buffer) == 1){
				break;
			}
			fflush(stdin);
			intentos--;
			printf(mensajeError);
		}//end while
		if(intentos == 0){
			returnValue = 0;	//ERROR
		}
		else{
			returnValue = 1;	//EXITO
			strcpy(pString, buffer);
		}
	}
	else returnValue = 0;	//ERROR

	return returnValue;
}

/**
 * \brief Recibe una cadena de caracteres por consola y verifica que sea alfanumerica
 * \param pString Puntero al espacio de memoria donde se guarda el resultado de la funcion
 * \return Retorna 1 = EXITO y 0 = ERROR
*/
static int getCadenaAlfanumerica(char *pString){
	int returnValue = 0;	//ERROR
	char buffer[32];
	if(myGets(buffer, sizeof(buffer)) && esAlfanumerica(buffer)){
		strcpy(pString, buffer);
		returnValue = 1;	//EXITO
	}
	return returnValue;
}

/**
* \brief Verifica si la cadena ingresada es alfanumerica
* \param cadena Cadena de caracteres a validar
* \return Retorna 1 = VERDADERO y 0 = FALSO
*/
static int esAlfanumerica(char* cadena){
	int i = 0;
	int returnValue = 1;	//VERDADERO

	//validacion de parametro
	if(cadena != NULL && strlen(cadena) > 0){
		//itera hasta encontrar el fin de la cadena
		while(cadena[i] != '\0'){
			//valida que los caracteres ingresados sean alfanumericos y espacio
			if((cadena[i] < '0' || cadena[i] > '9') && (cadena[i] != 32) &&
				(cadena[i] < 65 || cadena[i] > 90) && (cadena[i] < 97 || cadena[i] > 122))
			{
				returnValue = 0;	//FALSE
				break;
			}
			i++;
		}
	}
	else returnValue = 0;	//FALSE

	return returnValue;
}

/**
 * \brief Solicita una fecha por consola
 * \param pString Puntero al espacio de memoria donde se guarda la cadena ingresada
 * \param length Cantidad de caracteres permitidos
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param intentons La cantidad de intentos tolerados, minimo 1
 * \return Retorna 1 en caso de EXITO y 0 en caso de ERROR
 */
int utn_getFecha(char* pString, int lenght, char* mensaje, char* mensajeError, int intentos){
	int returnValue;
	char buffer[32];

	if(pString != NULL && mensaje != NULL && mensajeError != NULL && intentos > 0){
		while(intentos > 0){
			printf(mensaje);
			if(getFecha(buffer) == 1){
				break;
			}
			fflush(stdin);
			intentos--;
			printf(mensajeError);
		}//end while
		if(intentos == 0){
			returnValue = 0;	//ERROR
		}
		else{
			returnValue = 1;	//EXITO
			strcpy(pString, buffer);
		}
	}
	else returnValue = 0;	//ERROR

	return returnValue;
}

/**
 * \brief Recibe una cadena de caracteres por consola y verifica que sea una fecha
 * \param pString Puntero al espacio de memoria donde se guarda el resultado de la funcion
 * \return Retorna 1 = EXITO y 0 = ERROR
*/
static int getFecha(char *pString){
	int returnValue = 0;	//ERROR
	char buffer[32];
	if(myGets(buffer, sizeof(buffer)) && esFecha(buffer)){
		strcpy(pString, buffer);
		returnValue = 1;	//EXITO
	}
	return returnValue;
}

/**
* \brief Verifica si la cadena ingresada es alfanumerica
* \param cadena Cadena de caracteres a validar
* \return Retorna 1 = VERDADERO y 0 = FALSO
*/
static int esFecha(char* cadena){
	int i = 0;
	int returnValue = 1;	//VERDADERO

	//validacion de parametro
	if(cadena != NULL && strlen(cadena) == 10){
		//itera hasta encontrar el fin de la cadena
		while(cadena[i] != '\0'){
			//valida que los caracteres ingresados tengan el formato dd/mm/yyyy
			switch(i){
			/*
			 	dd / mm / yyyy
			 	01 2 34 5 6789
			*/
			case 0:
				if(cadena[i] < 48 || cadena[i] > 51){
					returnValue = 0;
				}
				break;
			case 1:
				if(cadena[i] < 48 || cadena[i] > 57){
					returnValue = 0;
				}
				break;
			case 2:
				if(cadena[i] != 47){
					returnValue = 0;
				}
				break;
			case 3:
				if(cadena[i] < 48 || cadena[i] > 49){
					returnValue = 0;
				}
				break;
			case 4:
				if(cadena[3] == 48){
					if(cadena[i] < 48 || cadena[i] > 57){
						returnValue = 0;
					}
				}
				else if(cadena[3] == 49){
					if(cadena[i] < 48 || cadena[i] > 50){
						returnValue = 0;
					}
				}
				break;
			case 5:
				if(cadena[i] != 47){
					returnValue = 0;
				}
				break;
			case 6:
				if(cadena[i] != 50){//2000 para adelante
					returnValue = 0;
				}
				break;
			case 7:
				if(cadena[i] < 48 || cadena[i] > 49){
					returnValue = 0;
				}
				break;
			case 8:
				if(cadena[i] < 48 || cadena[i] > 57){
					returnValue = 0;
				}
				break;
			case 9:
				if(cadena[i] < 48 || cadena[i] > 57){
					returnValue = 0;
				}
				break;
			}

			if(returnValue == 0) break;
			i++;
		}
	}
	else returnValue = 0;	//FALSE

	return returnValue;
}


/**
 * \brief Solicita una cadena alfanumerica por consola
 * \param pString Puntero al espacio de memoria donde se guarda la cadena ingresada
 * \param length Cantidad de caracteres permitidos
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param intentons La cantidad de intentos tolerados, minimo 1
 * \return Retorna 1 en caso de EXITO y 0 en caso de ERROR
 */
int utn_getCadenaNumerica(char* pString, int lenght, char* mensaje, char* mensajeError, int minDigits, int maxDigits , int intentos){
	int returnValue;
	char buffer[32];

	if(pString != NULL && mensaje != NULL && mensajeError != NULL && intentos > 0){
		while(intentos > 0){
			printf(mensaje);
			if(getCadenaNumerica(buffer, minDigits, maxDigits) == 1){
				break;
			}
			fflush(stdin);
			intentos--;
			printf(mensajeError);
		}//end while
		if(intentos == 0){
			returnValue = 0;	//ERROR
		}
		else{
			returnValue = 1;	//EXITO
			strcpy(pString, buffer);
		}
	}
	else returnValue = 0;	//ERROR

	return returnValue;
}

/**
 * \brief Recibe una cadena de caracteres por consola y verifica que sea alfanumerica
 * \param pString Puntero al espacio de memoria donde se guarda el resultado de la funcion
 * \return Retorna 1 = EXITO y 0 = ERROR
*/
static int getCadenaNumerica(char *pString, int minDigits, int maxDigits){
	int returnValue = 0;	//ERROR
	char buffer[32];
	if(myGets(buffer, sizeof(buffer)) && esNumerica(buffer) && (strlen(buffer) >= minDigits && strlen(buffer) <= maxDigits)){
		strcpy(pString, buffer);
		returnValue = 1;	//EXITO
	}
	return returnValue;
}
