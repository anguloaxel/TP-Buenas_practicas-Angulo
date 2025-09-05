#include <stdio.h>
#include <string.h>
/*Se cambia variable "s" por "sel"*/
/*Se cambia variable "n" por "pos_tab"*/
/*Se cambia variable "a" en funciones por "existencia"*/
/*Se agregan comentarios a el rol que cumplen cada una de las funciones*/
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
	
	int sel;//selección de switch
	int pos_tab=0;//posición de tabla de libros
	struct datos libro[50];
	
	FILE *archivo;
	
	inicializar(&libro[0]); //deja todos los datos de la tabla en 0
	
	printf("\n\t\tBase de datos Libros\n\n");
	
	do{
		do{
			menu();
			scanf("%d",&sel); //selección de opción
			
			while(getchar() != '\n' && sel != EOF);// Limpia buffer para evitar falla en gets proximo
			
			switch(sel){
				case 1 : //Ingresar un nuevomotor a la lista
					nuevo(&libro[pos_tab]);
					pos_tab++;
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
		} while(sel<0 && sel>9);
	} while(sel != 0);
}

void inicializar(struct datos *pun){  //deja todos los datos de la tabla en 0
	for(int i=0;i<50;i++){ 
		strcpy((*pun).titulo,"0");
		strcpy((*pun).autor,"0");
		(*pun).ano=0;
		pun++;
	}
}

//Se imprime menú a través del cual se va a manipular la información
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

//Realiza la toma de infomración, para generar un item de libro nuevo en la lista
void nuevo(struct datos *pun){ 
	printf("\n\tTitulo:            ");	
	gets((*pun).titulo);
	printf("\tAutor:            ");	
	gets((*pun).autor);
	printf("\tAño de Publicación:    ");
	scanf("%d",&(*pun).ano);
	
}
	
//Muestra listado de todos los libros cargados
void lista(struct datos *pun){ 
	printf("\n\t\tLibros cargados:\n\n");
	for(int i=0;i<50;i++){
		if(((*pun).ano)!=0){
			mostrar(pun);
		}
		pun++;
	}
}

//Se muestra en pantalla la información de solo un libro segun puntero
void mostrar(struct datos *pun){	
	printf("\n\tTítulo: ");
	puts((*pun).titulo);
	printf("\tAutoro: ");
	puts((*pun).autor);
	printf("\tAño:    %d \n",(*pun).ano);
}	

//Busca en toda la lista de libros, el indicado a través del título ingresado por teclado
void buscar_titulo_teclado(struct datos *pun){
	int aux=1,existencia=0;
	char titulo[100];
	printf("\n\t\tBusqueda de libro \n\tTítulo:  ");
	gets(titulo);
	for(int i=0;i<50;i++){ 
		aux=strcmp(titulo,(*pun).titulo);
		if (aux==0){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			existencia=1;
		}
		pun++;
	}
	if (existencia==0){
		printf("\n\tLibro inexisistente\n");
	}
}

//Busca en toda la lista de libros, el indicado a través del autor ingresado por teclado
void buscar_autor_teclado(struct datos *pun){
	int aux=1,existencia=0;
	char autor[50];
	printf("\n\t\tBusqueda de libro \n\tAutor:  ");
	gets(autor);
	for(int i=0;i<50;i++){ 
		aux=strcmp(autor,(*pun).autor);
		if (aux==0){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			existencia=1;
		}
		pun++;
	}
	if (existencia==0){
		printf("\n\tLibro inexisistente\n");
	}
}

//Busca en toda la lista de libros, el indicado a través del año ingresado por teclado
void buscar_ano_teclado(struct datos *pun){
	int existencia=0;
	int ano;
	printf("\n\t\tBusqueda de libro \n\tAño:  ");
	scanf("%d",&ano);
	for(int i=0;i<50;i++){ 
		if (ano==(*pun).ano){
			printf("\n\tLibro encontrado\n\n");
			mostrar(pun);
			existencia=1;
		}
		pun++;
	}
	if (existencia==0){
		printf("\n\tLibro inexisistente\n");
	}
}


//Busca en toda la lista de libros, el indicado a través del título ingresado en el archivo de texto
void buscar_titulo_archivo(struct datos *pun){
	int aux=1,existencia=0;
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
			existencia=1;
		}
		pun++;
	}
	if (existencia==0){
		printf("\n\tLibro inexisistente\n");
	}
}

//Busca en toda la lista de libros, el indicado a través del autor ingresado en el archivo de texto
void buscar_autor_archivo(struct datos *pun){
	int aux=1,existencia=0;
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
			existencia=1;
		}
		pun++;
	}
	if (existencia==0){
		printf("\n\tLibro inexisistente\n");
	}
}

//Busca en toda la lista de libros, el indicado a través del año ingresado en el archivo de texto
void buscar_ano_archivo(struct datos *pun){
	int existencia=0;
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
			existencia=1;
		}
		pun++;
	}
	if (existencia==0){
		printf("\n\tLibro inexisistente\n");

	}
}



