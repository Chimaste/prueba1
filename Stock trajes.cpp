#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_TRAJES 100

struct Traje {
	int tipo;
	int cantidad;
	struct Traje* siguiente;
} Traje;

struct Persona {
	char nombre[MAX_NOMBRE];
	struct Traje* stockTrajes;
	struct Persona* siguiente;
} Persona;

void guardarDatos(struct Persona* inicio) {
	FILE* archivo = fopen("datos.txt", "w");
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	struct Persona* personaActual = inicio;
	while (personaActual != NULL) {
		fprintf(archivo, "%s ", personaActual->nombre);
		struct Traje* trajeActual = personaActual->stockTrajes;
		while (trajeActual != NULL) {
			fprintf(archivo, "%d %d ", trajeActual->tipo, trajeActual->cantidad);
			trajeActual = trajeActual->siguiente;
		}
		fprintf(archivo, "\n");
		personaActual = personaActual->siguiente;
	}
	
	fclose(archivo);
	printf("Datos guardados en el archivo.\n");
}

void agregarPersona(struct Persona** inicio) {
	struct Persona* nuevaPersona = (struct Persona*)malloc(sizeof(struct Persona));
	if (nuevaPersona == NULL) {
		printf("Error al asignar memoria.\n");
		return;
	}
	
	printf("Ingrese el nombre de la persona: ");
	scanf("%s", nuevaPersona->nombre);
	
	nuevaPersona->stockTrajes = NULL;
	nuevaPersona->siguiente = *inicio;
	*inicio = nuevaPersona;
	
	printf("Persona agregada correctamente.\n");
}



void agregarTraje(struct Persona *persona) {
	struct Traje *nuevoTraje = (struct Traje *)malloc(sizeof(struct Traje));
	if (nuevoTraje == NULL) {
		printf("Error al asignar memoria.\n");
		return;
	}
	
	printf("Ingrese el tipo de traje: ");
	scanf("%d", &nuevoTraje->tipo);
	
	printf("Ingrese la cantidad de trajes: ");
	scanf("%d", &nuevoTraje->cantidad);
	
	nuevoTraje->siguiente = persona->stockTrajes;
	persona->stockTrajes = nuevoTraje;
	
	printf("Traje agregado correctamente.\n");
}



void actualizarStock(struct Persona *inicio) {
	if (inicio == NULL) {
		printf("No hay personas registradas.\n");
		return;
}
	
	printf("Lista de personas:\n");
	int index = 1;
	struct Persona *personaActual = inicio;
	while (personaActual != NULL) {
		printf("%d. %s\n", index, personaActual->nombre);
		personaActual = personaActual->siguiente;
		index++;
}
	
	printf("Seleccione el número de la persona: ");
	int seleccion;
	scanf("%d", &seleccion);
	
	personaActual = inicio;
	for (int i = 1; i < seleccion && personaActual != NULL; i++) {
		personaActual = personaActual->siguiente;
}
	
	if (personaActual == NULL) {
		printf("Selección inválida.\n");
		return;
}
	
	agregarTraje(personaActual);
}

void verPersonas(struct Persona *inicio) {
	if (inicio == NULL) {
		printf("No hay personas registradas.\n");
		return;
	}
	
	printf("Lista de personas y sus stocks de trajes:\n");
	struct Persona *personaActual = inicio;
	while (personaActual != NULL) {
		printf("Nombre: %s\n", personaActual->nombre);
		struct Traje *trajeActual = personaActual->stockTrajes;
		while (trajeActual != NULL) {
			printf("Tipo de traje: %d, Cantidad: %d\n", trajeActual->tipo, trajeActual->cantidad);
			trajeActual = trajeActual->siguiente;
		}
		printf("\n");
		personaActual = personaActual->siguiente;
	}
}

void eliminarPersona(struct Persona **inicio) {
	if (*inicio == NULL) {
		printf("No hay personas registradas.\n");
		return;
	}
	
	printf("Lista de personas:\n");
	int index = 1;
	struct Persona *personaActual = *inicio;
	while (personaActual != NULL) {
		printf("%d. %s\n", index, personaActual->nombre);
		personaActual = personaActual->siguiente;
		index++;
	}
	
	printf("Seleccione el número de la persona a eliminar: ");
	int seleccion;
	scanf("%d", &seleccion);
	
	if (seleccion < 1) {
		printf("Selección inválida.\n");
		return;
	}
	
	if (seleccion == 1) {
		struct Persona *temp = *inicio;
		*inicio = (*inicio)->siguiente;
		free(temp);
	} else {
		struct Persona *anterior = *inicio;
		for (int i = 1; i < seleccion - 1 && anterior != NULL; i++) {
			anterior = anterior->siguiente;
		}
		if (anterior == NULL || anterior->siguiente == NULL) {
			printf("Selección inválida.\n");
			return;
		}
		struct Persona *eliminar = anterior->siguiente;
		anterior->siguiente = eliminar->siguiente;
		free(eliminar);
	}
	
	printf("Persona eliminada correctamente.\n");
}
void mostrarMenu() {
	printf("1. Agregar persona\n");
	printf("2. Actualizar stock de trajes\n");
	printf("3. Ver personas y stocks\n");
	printf("4. Eliminar persona\n");
	printf("5. Guardar datos\n");
	printf("6. Salir\n");
	printf("Selecciona una opción: ");
}

int obtenerOpcion() {
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

	
	int main() {
		struct Persona* inicio = NULL;
		
		while (1) {
			mostrarMenu();
			int opcion = obtenerOpcion();
			
			switch (opcion) {
			case 1:
				system("cls");
				agregarPersona(&inicio);
				break;
				
			case 2:
				system("cls");
				actualizarStock(inicio);
				break;
				
			case 3:
				system("cls");
				verPersonas(inicio);
				break;
				
			case 4:
				system("cls");
				eliminarPersona(&inicio);
				break;
				
			case 5:
				system("cls");
				guardarDatos(inicio);
				break;
				
			case 6:
				system("cls");
				printf("Saliendo del programa.\n");
				// Liberar memoria antes de salir
				while (inicio != NULL) {
					struct Persona* temp = inicio;
					inicio = inicio->siguiente;
					struct Traje* trajeActual = temp->stockTrajes;
					while (trajeActual != NULL) {
						struct Traje* tempTraje = trajeActual;
						trajeActual = trajeActual->siguiente;
						free(tempTraje);
					}
					free(temp);
				}
				return 0;
				
			default:
				system("cls");
				printf("Opción inválida.\n");
				break;
			}
		}
		
		return 0;
	}
	
 
