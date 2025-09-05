#include <stdio.h>
#include <string.h>

struct datos{
	char titulo[100], autor[50];
	int ano;  
};

void inicializar(struct datos *pun);
void menu(void);
void nuevo(struct datos *pun);
void lista(struct datos *pun);
void mostrar(struct datos *pun);
void buscar_titulo_teclado(struct datos *pun);
void buscar_autor_teclado(struct datos *pun);
void buscar_ano_teclado(struct datos *pun);
void buscar_titulo_archivo(struct datos *pun);
void buscar_autor_archivo(struct datos *pun);
void buscar_ano_archivo(struct datos *pun);

int main (){
	
	int s;//selección de switch
	int n=0;//posición de tabla de libros
	struct datos libro[50];
	
	FILE *archivo;
	
	inicializar(&libro[0]); //deja todos los datos de la tabla en 0
	
	printf("\n\t\tBase de datos Libros\n\n");
	
	do{
		do{
			menu();
			scanf("%d",&s); //selección de opción
			
			while(getchar() != '\n' && s != EOF);// Limpia buffer para evitar falla en gets proximo
			
			switch(s){
				case 1 : //Ingresar un nuevomotor a la lista
					nuevo(&libro[n]);
					n++;
					break;
				case 2: //Muestra todos los motores guardados en la lista
					lista(&libro[0]);
					break;
				case 3 : 
					buscar_titulo_teclado(&libro[0]);
					break;
				case 4 : 
					buscar_autor_teclado(&libro[0]);
					break;
				case 5 : 
					buscar_ano_teclado(&libro[0]);
					break;
				case 6 : 
					buscar_titulo_archivo(&libro[0]);
					break;
				case 7 : 
					buscar_autor_archivo(&libro[0]);
					break;
				case 8 : 
					buscar_ano_archivo(&libro[0]);
					break;
				case 9 : //Guardar lista en archivo
					archivo = fopen("datos.txt","w");
					if(archivo!=NULL){
						for (int i=0;i<50;i++){
							if(libro[i].ano!=0){
								fputs(libro[i].titulo, archivo);
								fputc(',', archivo);
								fputs(libro[i].autor, archivo);
								fprintf(archivo, ",%d\n",libro[i].ano);
							}
						}
						printf("\n\tDatos guardados\n");
					}
					else{
						printf("\n\tProblemas al abrir\n");
					}
					fclose(archivo);
					break;
				case 0 : //Sale del programa
					printf("\n\tSaliendo\n");
					break;
				default:
					printf("\n\tOpción incorrecta, reingrese opción\n");	
					break;
			}
		} while(s<0&&s>9);
	} while(s!=0);
}

void inicializar(struct datos *pun){  //deja todos los datos de la tabla en 0
	for(int i=0;i<50;i++){ 
		strcpy((*pun).titulo,"0");
		strcpy((*pun).autor,"0");
		(*pun).ano=0;
		pun++;
	}
}
	
void menu(void){ //Menú
	printf("\n\t\tIngrese una opción:   \n");
	printf("\n\t1 - Ingresar libro nuevo");
	printf("\n\t2 - Mostrar lista de libros");
	printf("\n\t3 - Buscar libro por título - Por teclado");
	printf("\n\t4 - Buscar libro por autor - Por teclado");
	printf("\n\t5 - Buscar libro por año - Por teclado");
	printf("\n\t6 - Buscar libro por título - Por archivo");
	printf("\n\t7 - Buscar libro por autor - Por archivo");
	printf("\n\t8 - Buscar libro por año - Por archivo");
	printf("\n\t9 - Guardar lista");
	printf("\n\t0 - Salir");
	printf("\n\n\t");
}
	
void nuevo(struct datos *pun){ //Pide datos para crear un motor nuevo
	printf("\n\tTitulo:            ");	
	gets((*pun).titulo);
	printf("\tAutor:            ");	
	gets((*pun).autor);
	printf("\tAño de Publicación:    ");
	scanf("%d",&(*pun).ano);
	
}
	
void lista(struct datos *pun){ //Muestra todos los libros cargados
	printf("\n\t\tLibros cargados:\n\n");
	for(int i=0;i<50;i++){
		if(((*pun).ano)!=0){
			mostrar(pun);
		}
		pun++;
	}
}

void mostrar(struct datos *pun){	//muestra solo un motor segun puntero
	printf("\n\tTítulo: ");
	puts((*pun).titulo);
	printf("\tAutoro: ");
	puts((*pun).autor);
	printf("\tAño:    %d \n",(*pun).ano);
}	
	
void buscar_titulo_teclado(struct datos *pun){
	int aux=1,a=0;
	char titulo[100];
	printf("\n\t\tBusqueda de libro \n\tTítulo:  ");
	gets(titulo);
	for(int i=0;i<50;i++){ 
		aux=strcmp(titulo,(*pun).titulo);
		if (aux==0){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			a=1;
		}
		pun++;
	}
	if (a==0){
		printf("\n\tLibro inexisistente\n");
	}
}

void buscar_autor_teclado(struct datos *pun){
	int aux=1,a=0;
	char autor[50];
	printf("\n\t\tBusqueda de libro \n\tAutor:  ");
	gets(autor);
	for(int i=0;i<50;i++){ 
		aux=strcmp(autor,(*pun).autor);
		if (aux==0){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			a=1;
		}
		pun++;
	}
	if (a==0){
		printf("\n\tLibro inexisistente\n");
	}
}

void buscar_ano_teclado(struct datos *pun){
	int a=0;
	int ano;
	printf("\n\t\tBusqueda de libro \n\tAño:  ");
	scanf("%d",&ano);
	for(int i=0;i<50;i++){ 
		if (ano==(*pun).ano){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			a=1;
		}
		pun++;
	}
	if (a==0){
		printf("\n\tLibro inexisistente\n");
	}
}

void buscar_titulo_archivo(struct datos *pun){
	int aux=1,a=0;
	char titulo[100];
	FILE *archivo;
	archivo = fopen("titulo.txt","r");
	if(archivo!=NULL){
		fgets(titulo,100,archivo);
	}
	else{
		printf("\n\tProblemas al abrir\n");
	}
	fclose(archivo);
	
	printf("\n\t\tBusqueda de libro \n\tTítulo:  ");
	puts(titulo);
	for(int i=0;i<50;i++){ 
		aux=strcmp(titulo,(*pun).titulo);
		if (aux==0){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			a=1;
		}
		pun++;
	}
	if (a==0){
		printf("\n\tLibro inexisistente\n");
	}
}

void buscar_autor_archivo(struct datos *pun){
	int aux=1,a=0;
	char autor[50];
	FILE *archivo;
	archivo = fopen("autor.txt","r");
	if(archivo!=NULL){
		fgets(autor,50,archivo);
	}
	else{
		printf("\n\tProblemas al abrir\n");
	}
	fclose(archivo);
	
	printf("\n\t\tBusqueda de libro \n\tAutor:  ");
	puts(autor);
	for(int i=0;i<50;i++){ 
		aux=strcmp(autor,(*pun).autor);
		if (aux==0){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			a=1;
		}
		pun++;
	}
	if (a==0){
		printf("\n\tLibro inexisistente\n");
	}
}

void buscar_ano_archivo(struct datos *pun){
	int a=0;
	int ano=0;
	
	FILE *archivo;	
	archivo = fopen("ano.txt","r");
	if(archivo!=NULL){
		fscanf(archivo,"%d",&ano);
		
	}
	else{
		printf("\n\tProblemas al abrir\n");
	}
	fclose(archivo);
	
	printf("\n\t\tBusqueda de libro \n\tAño:  %d",ano);
	
	for(int i=0;i<50;i++){ 
		if (ano==(*pun).ano){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			a=1;
		}
		pun++;
	}
	if (a==0){
		printf("\n\tLibro inexisistente\n");
	}
}
