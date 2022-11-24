#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/*
 * \breif Crea una nueva LinkedList
 * \return Retorna un puntero a LinkedList o NULL
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = (LinkedList*)malloc(sizeof(LinkedList*));
    if(this != NULL)
    {
        this->pFirstNode = NULL;
        this->size = 0;
    }

    return this;
}

/*
 * \brief Devuelve la cantidad de Nodos de la LinkedList
 * \param *this Puntero a LinkedList
 * \return Retorna el size de la LinkedList o -1(ERROR)
 */
int ll_len(LinkedList* this)
{
    int retorno = -1;	//ERROR

    if(this != NULL){
        retorno = this->size;
    }
    return retorno;
}

/*
 * \brief Recibe un index y devuelve el nodo correspondiente en la LinkedList
 * \param this Puntero a LinkedList
 * \param nodeIndex Indice del Nodo a buscar
 * \return Retorna un puntero al Node encontrado o NULL
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* auxNode = NULL;

    if(this != NULL && nodeIndex>= 0 && nodeIndex<ll_len(this))
    {
        auxNode = this->pFirstNode;
        for(int i=0; i<nodeIndex; i++)
        {
            auxNode = auxNode->pNextNode;
        }
    }

    return auxNode;
}

/*
 * \brief Agrega un nuevo Nodo a la LinkedList
 * \param this Puntero a LinkedList
 * \param nodeIndex Indice del Nodo
 * \return Retorna  0(EXITO) o -1(ERROR)
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
	int retorno = -1;
	Node* auxNode = (Node*)malloc(sizeof(Node*));
	Node* auxPrevNode=NULL;

    if(auxNode != NULL && this != NULL && nodeIndex >= 0 && pElement != NULL && nodeIndex <= ll_len(this))
    {
        auxNode->pElement=pElement;

        if(nodeIndex == 0){
            auxNode->pNextNode = this->pFirstNode;
            this->pFirstNode = auxNode;
            this->size++;
            retorno=0;
        }
        else{
        	auxPrevNode = getNode(this,nodeIndex-1);

        	if(auxPrevNode != NULL){
        		auxNode->pNextNode = auxPrevNode->pNextNode;
        		auxPrevNode->pNextNode = auxNode;
        		this->size++;
        		retorno=0;
        	}
        }
    }

    return retorno;
}

/*
 * \brief Agrega un nuevo elemento
 * \param this Puntero a LinkedList
 * \pElement Puntero al Elemento
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int ll_add(LinkedList* this, void* pElement)
{
    int retorno=-1;

    if(this != NULL && pElement != NULL)
    {
    	if(addNode(this, ll_len(this), pElement)==0)
        {
            retorno=0;
        }
    }

    return retorno;
}

/*
 *  \brief Busca un elemento dentro de la LinkedList mediante un index
 *  \param this Puntero a la LinkedList
 *  \param index Indice a buscar
 *  \return Retorna un puntero al elemento o NULL
 */
void* ll_get(LinkedList* this, int index)
{
    Node* auxNode = NULL;
    void* pRetorno = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this)){
       auxNode = getNode(this, index);
       if(auxNode != NULL){
           pRetorno = auxNode->pElement;
       }
    }

    return pRetorno;
}

/*
 * \brief Setea un elemento en un indice
 * \param this Puntero a la LinkedList
 * \param index Indice de la LinkedList
 * \param pElement Puntero al elemento a setear
 * \return Retorna 0(EXITO) o  -1(ERROR)
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
    int retorno = -1;
    Node* auxNode = NULL;

    if(this != NULL && pElement != NULL && index >= 0 && index < ll_len(this)){
        auxNode = getNode(this, index);
        if(auxNode != NULL){
            auxNode->pElement = pElement;
            retorno = 0;
        }
    }
    return retorno;
}

/*
 * \brief Elimina un Nodo de la LinkedList
 * \param *this Puntero a la LinkedList
 * \param index Indice del nodo a eleminar
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int ll_remove(LinkedList* this,int index)
{
    int retorno = -1;	//ERROR
    Node* auxNode = NULL;
    Node* auxPrevNode = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        auxNode = getNode(this,index);

        if(auxNode != NULL){
            if(index==0){
                this->pFirstNode=auxNode->pNextNode;
                this->size--;
            }else{
                auxPrevNode = getNode(this,index-1);
                auxPrevNode->pNextNode = auxNode->pNextNode;
                this->size--;
            }
            retorno = 0;
        }
    }

    return retorno;
}

/*
 * \brief Borra los Nodos de la LinkedList
 * \param *this Puntero a memoria de la LinkedList
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int ll_clear(LinkedList* this){
	int retorno = -1;	//ERROR
	int length  = ll_len(this);

	if(this != NULL && length > 0){
		for(int i = 0; i < length; i++){
			ll_remove(this, 0);
		}

		retorno = 0;	//EXITO
	}

	return retorno;
}

/*
 * \brief Borra la LinkedList
 * \param *this Puntero a memoria de la LinkedList
 * \return Retorna 0(EXITO) y -1(ERROR)
 */
int ll_deleteLinkedList(LinkedList* this){
	int retorno = -1;	//ERROR

	if(this != NULL){
		if(ll_clear(this) == 0){
			free(this);

			retorno = 0;	//EXITO
		}
	}

	return retorno;
}

/*
 * \brief Busca un elemento dentro de la LinkedList y retorna el indice
 * \param *this Puntero a memoria de la LinkedList
 * \param *pElement Puntero al elemento a buscar
 * \return Retorna el indice del elemento encontrado o -1(ERROR)
 */
int ll_indexOf(LinkedList* this, void* pElement){
	int retorno = -1;
	int length = ll_len(this);
	Node* auxNode;

	if(this != NULL && pElement != NULL && length > 0){
		for(int i = 0; i < length; i++){
			auxNode = getNode(this, i);

			if(auxNode != NULL && auxNode->pElement == pElement){
				retorno = i;
				break;
			}
		}
	}

	return retorno;
}

/*
 * \brief Comprueba si la LinkedList esta vacia
 * \param *this Puntero a memoria de la LinkedList
 * \return Retorna 0 (NOT EMPTY), 1 (EMPTY) - 1(ERROR)
 */
int ll_isEmpty(LinkedList* this){
	int retorno = -1;	//ERROR

	if(this != NULL){
		if(ll_len(this) > 0){
			retorno = 0;	//NO VACIO
		}
		else retorno = 1;	//VACIO
	}
	return retorno;
}

/*
 * \brief
 * \param *this Puntero a memoria de la LinkedList
 * \param index Indice
 * \param pElement Puntero al elemento
 * \return Retorna  -1(ERROR)
 */
int ll_push(LinkedList* this, int index, void* pElement){
	int retorno = -1;	//ERROR

	if(this != NULL && index >= 0 && index <= ll_len(this) && pElement != NULL){
		addNode(this, index, pElement);
		retorno = 0;
	}
	return retorno;
}

//Elimina el Nodo y retorna
void* ll_pop(LinkedList* this,int index){
	void* retorno = NULL;
	void* auxPElement = NULL;
	if(this != NULL && index >= 0 && index < ll_len(this)){
		auxPElement = ll_get(this, index);

		if(auxPElement != NULL){
			retorno = auxPElement;
			ll_remove(this, index);
		}
	}

	return retorno;
}

/*
 *
 */
int ll_contains(LinkedList* this, void* pElement){
	int retorno = -1;	//null

	if(this != NULL && pElement != NULL){
		if(ll_indexOf(this, pElement) != -1){
			retorno = 1;	//contiene el elemento
		}
		else{
			retorno = 0;	//no contiene el elemento
		}

	}

	return retorno;
}

//los elementos de la lista 2 esten en la lista 1
/*
 * \brief Valida que los elementos de una LinkedList esten en otra LinkedList
 */
int ll_containsAll(LinkedList* this,LinkedList* this2){
	int retorno = -1;
	int len;
	if(this != NULL && this != NULL){
		len = ll_len(this2);
		if(len == 0){
			retorno = 0;	//no contiene
		}
		else{
			for(int i = 0; i < len; i++){
				if(ll_contains(this, ll_get(this2, i)) == 0){
					retorno = 0;	// no contiene
					break;
				}
				else{
					retorno = 1;	//contiene
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief Retorna una nueva lista que tenga los elementos en un rango determinado
 * \param *this
 * \param from
 * \param to
 * \return
 */
LinkedList* ll_subList(LinkedList* this,int from,int to){
	LinkedList* subList = NULL;
	void* auxPElement;

	if(this != NULL && to <= ll_len(this) && to < from && from >= 0 && from < ll_len(this)){
		subList = ll_newLinkedList();

		if(subList != NULL){
			for(int i = from; i < to; i++){
				auxPElement = ll_get(this, i);

				if(auxPElement != NULL){
					ll_add(subList, auxPElement);

				}
			}
		}
	}

	return subList;
}

/**
 * \brief Clona una LinkedList
 * \param *this
 * \return
 */
LinkedList* ll_clone(LinkedList* this){
	LinkedList* clonList = NULL;

	if(this != NULL){
		clonList = ll_subList(this, 0, ll_len(this));
	}

	return clonList;
}

/*
 * \brief Ordena los elementos de la LinkedList usando la funcion criterio
 * \param *this Puntero a la LinkedList
 * \param *pFunc Puntero a la funcion criterio
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order){
	int retorno = -1;	//ERROR

	int estaOrdenado;
	int len;
	void* auxElement1 = NULL;
	void* auxElement2 = NULL;
	int retornoPFunc;

	len = ll_len(this);
	do{
		estaOrdenado = 1;
		len--;
		for(int i = 0; i < len;  i++){
			auxElement1 = ll_get(this, i);
			auxElement2 = ll_get(this, i + 1);

			retornoPFunc = 	pFunc(auxElement1, auxElement2);

			if((retornoPFunc > 0 && order == 1) || (retornoPFunc < 0 && order == 0)){
				ll_set(this, i, auxElement2);
				ll_set(this, i+1, auxElement1);

				 estaOrdenado = 0;
			}
		}

	}while(estaOrdenado == 0);

	return retorno;
}

/**
 * \brief Recibe una funcion criterio y filtra la LinkedList basado en ese criterio.
 * 			Los elementos que cumplan con el criterio se añaden a una nueva sub LinkedList.
 * \param int (*fn)(void* element) Funcion que se encarga de compara si el elemento cumple cierto criterio.
 * \return Retorna un puntero a LinkedList o NULL
 */
LinkedList* ll_filter(LinkedList* this, int (*fn)(void* element)){
    void* auxElement;
    LinkedList* filterList = NULL;

    if(this != NULL && fn != NULL){
        filterList = ll_newLinkedList();

        if(filterList != NULL && ll_len(this) > 0){
            for(int i = 0; i < ll_len(this); i++){
                auxElement = ll_get(this, i);

                if(fn(auxElement) == 1){
                    ll_add(filterList, auxElement);
                }
            }
        }
    }

    return filterList;
}

/**
 * \brief Recibe una funcion criterio que analiza los elementos de la LinkedList. Dicha funcion
 * 			podra realizar calculos con el elemento recibido y modificar alguno de sus campos si es necesario.
 * \param int (*fn)(void* element) Funcion que se encarga de analizar los elementos.
 * \return Retorna un puntero a LinkedList o NULL
 */
LinkedList* ll_map(LinkedList* this, void (*fn)(void* element)){
    void* auxElement;

    if(this != NULL && fn != NULL){
    	for(int i = 0; i < ll_len(this); i++){
    		auxElement = ll_get(this, i);

    		if(auxElement != NULL){
    			fn(auxElement);
    		}
    	}

    }

    return this;
}

int ll_count(LinkedList* this, int (*fn)(void* element)){
	int retorno = 0;
	void* auxElement;

	if(this != NULL && fn != NULL){
		for(int i = 0; i < ll_len(this); i++){
			auxElement = ll_get(this, i);

			if(auxElement != NULL && fn(auxElement) == 1){
				retorno++;
			}
		}
	}

	return retorno;
}







