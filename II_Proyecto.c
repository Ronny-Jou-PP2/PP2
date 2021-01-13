//Librerias usadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//------------------------------------STRUCT NIÑOS-----------------------------------
//Estructura general de los ninos 
/*Entradas: Nivel de acceso, nombre, cedula, correo y demas datos de cada miembro
Salidas: un nuevo nodo en lista Simple 
Restricciones: Solo tiene puntero a siguiente */
typedef struct nino
{
	char nombre[30], cedula[30], correo[30], necs[100], residencia[30];
	int dia, mes, anio, edad;
	struct nino* sig_Nino;
} nino;

//Variables generales de primer y ultimo miembro
nino* primer_Nino=NULL;
nino* ultimo_Nino=NULL;

/*Entradas: variables para la creacion de un registro con los miembros 
Salidas: un nuevo nodo con los datos del nuevo miembro
Restricciones: solo funciona para miembros  */
int nuevoNino(char *cedula, char  *nombre, char *correo,char *necesidades, int dia, int mes, int anio, int edad) //Funcion para insertar
{ 
	nino *nuevo=(nino*) malloc(sizeof(nino));
	
	strcpy(nuevo->nombre, nombre);
	strcpy(nuevo->cedula, cedula);
    strcpy(nuevo->correo, correo);
    strcpy(nuevo->necs, necesidades);
    nuevo->dia=dia;
    nuevo->mes=mes;
    nuevo->anio=anio;  
	nuevo->edad=edad;  
    //--------------------------FALTA RESIDENCIA-------------------	
    //--------------------------FALTA USUARIO DEL SISTEMA (AYUDANTE DE SANTA)

	if(primer_Nino==NULL)	
	{
		primer_Nino=nuevo;
		primer_Nino->sig_Nino=NULL;
		ultimo_Nino=nuevo;
	}
	ultimo_Nino->sig_Nino=nuevo;
	nuevo->sig_Nino=NULL;
	ultimo_Nino=nuevo;
}


//MOSTRAR TODOS LOS NINOS
/*Entradas: datos del struct
Salidas: imprime los datos del miembro en cuestion 
Restricciones: Solo miembros antes inscritos */
void mostrar_Ninos()//Imprime 
{
	nino* actual = (nino*) malloc(sizeof(nino)); // crea nodos 
	actual = primer_Nino;
	
	if(primer_Nino != NULL)
	{
		while(actual != NULL)
		{
		
			printf("\t\n    ----Informacion del Nino(a)----\n");
			printf("\n   -Nombre completo: %s\n   -Cedula: %s\n   -Correo electronico: %s\n   -Necesidades especiales: %s\n   -Residencia: %s\n   -Edad: %i\n   -Fecha de nacimiento: %i/%i/%i\n", actual->nombre, actual->cedula, actual->correo, actual->necs, actual->residencia, actual->edad, actual->dia, actual->mes, actual->anio);
			actual = actual->sig_Nino;// siguiente puntero en lista
		}
	}
	else
	{
		printf("\nUps! Parece que no hay ninos registrados\n\n");
	}
}

//MODIFICAR DATOS DE LOS NINOS
/*Entradas: datos del struct
Salidas: imprime los datos del miembro en cuestion 
Restricciones: Solo miembros antes inscritos */
int modificar_Nino() 
{
	char id[12], nombre[30], elecc[3]="Si";
	int dato, encontrado;
	
	nino* actual = (nino*) malloc(sizeof(nino)); // crea nodos 
	actual = primer_Nino;
	
	printf("Digite la identificacion del nino(a) del cual desea modificar sus datos (X-XXXX-XXXX): "); 
	fflush(stdin);
	scanf("%[^\n]", &id);
	while (strlen(id)!=11) //Comparar la cantidad de caracteres
	{
		printf("Digite nuevamente el id del nino(a), con el formato solicitado (X-XXXX-XXXX): ");
		fflush(stdin);
		scanf("%[^\n]", &id);
	}
	
	if(primer_Nino!=NULL)
	{
		while(actual!=NULL && encontrado!=1)
		{
			if (strcmp(actual->cedula, id)==0)
			{
				printf("\t\n    ----Informacion del Nino(a)----\n");
				printf("\n   1-Nombre completo: %s\n   2-Cedula: %s\n   3-Correo electronico: %s\n   4-Necesidades especiales: %s\n   5-Residencia: %s\n   6-Edad: %i\n   7-Fecha de nacimiento: %i/%i/%i\n", actual->nombre, actual->cedula, actual->correo, actual->necs, actual->residencia, actual->edad, actual->dia, actual->mes, actual->anio);
				encontrado=1;
			}
			else
			{
				actual=actual->sig_Nino;// siguiente puntero en lista	
			}
			
		}
	}
	else
	{
		printf("\nUps! Parece que el nino(a) que busca no esta registrado\n\n");
	}
	
	while (strcmp(elecc,"Si")==0 || strcmp(elecc,"si")==0)
	{
		printf("\nDigite el numero correspondiente al dato que desea modificar: ");
		scanf("%i",&dato);
		
		if (dato==1)
		{
			printf("Digite el nombre completo del nino(a): ");
			fflush(stdin); //limpia buffer de espacios y saltos
			scanf("%[^\n]",&actual->nombre);
		}
		else if (dato==2)
		{
			printf("Digite el numero de identificacion del nino(a) (formato X-XXXX-XXXX): ");
			fflush(stdin);
			scanf("%[^\n]", &actual->cedula);
			while (strlen(actual->cedula)!=11) //Comparar la cantidad de caracteres
			{
				printf("Digite nuevamente el id del nino(a), con el formato solicitado (X-XXXX-XXXX): ");
				fflush(stdin);
				scanf("%[^\n]", &actual->cedula);
			}
		}
		else if (dato==3)
		{
			printf("Digite el nuevo correo electronico: ");
			scanf("%s",&actual->correo);
		}
		else if (dato==4)
		{
			printf("Digite las necesidades particulares del nino(a), en caso de que este las posea, de no ser asi digite 'No posee': ");
			fflush(stdin);
			scanf("%[^\n]", &actual->necs);
		}
		else if (dato==5)
		{
			printf("Digite la residencia del nino(a): **HAY QUE VALIDAR**");
			fflush(stdin);
			scanf("%[^\n]", &actual->residencia);
		}
		else if (dato==6)
		{
			printf("Digite la edad del nino(a): ");
			scanf("%i",&actual->edad);
		}
		else if (dato==7)
		{
			int diaActual, mesActual, anioActual, edad;
			char  diaSTR[3], mesSTR[3], anioSTR[5]; 
			
			time_t tiempo = time(0);
			struct tm *tlocal = localtime(&tiempo);
		
			strftime(mesSTR,3,"%m",tlocal);
			strftime(anioSTR,5,"%Y",tlocal);
			strftime(diaSTR,3,"%d",tlocal);
		
			diaActual=atoi(diaSTR);
			mesActual=atoi(mesSTR);
			anioActual=atoi(anioSTR);
			
			printf("Digite el ANIO de nacimiento del nino(a): "); //-------------Validar que sea un numero
			scanf("%i", &actual->anio);
			while (actual->anio>anioActual) 
			{
				printf(">>Digite nuevamente el ANIO del nacimiento del nino(a): ");
				scanf("%i", &actual->anio);
			}
			if (actual->anio==anioActual)
			{
				printf("Digite el MES de nacimiento del nino(a): "); //-------------Validar que sea un numero
				scanf("%i", &actual->mes);
				while (actual->mes>mesActual || actual->mes<1)//Se valida que no sea un mes mayor a Enero
				{
					printf(">>Digite nuevamente el MES del nacimiento del nino(a): ");
					scanf("%i", &actual->mes);
				}
				
				printf("Digite el DIA de nacimiento del nino(a): "); //-------------Validar que sea un numero
				scanf("%i", &actual->dia);
				while (actual->dia>diaActual || actual->dia<1)
				{
					printf(">>Digite nuevamente el DIA del nacimiento del nino(a): ");
					scanf("%i", &actual->dia);
				}
			}
			else
			{
				printf("Digite el MES de nacimiento del nino(a): "); //-------------Validar que sea un numero
				scanf("%i", &actual->mes);
				while (actual->mes>12 || actual->mes<1)
				{
					printf(">>Digite nuevamente el MES del nacimiento del nino(a): ");
					scanf("%i", &actual->mes);
				}
				
				printf("Digite el DIA de nacimiento del nino(a): "); //-------------Validar que sea un numero
				scanf("%i", &actual->dia);
				while (actual->dia>31 || actual->dia<1)
				{
					printf(">>Digite nuevamente el DIA del nacimiento del nino(a): ");
					scanf("%i", &actual->dia);
				}
			}
		}
		printf("Si desea modificar otro dato, digite 'Si', digite 'No' en caso contrario: ");
		scanf("%s",&elecc);
	}
	return 0;
}


//ELIMINAR NINO

void eliminarNino(char *id_nino)
{
	nino* actual=(nino*) malloc(sizeof(nino));
	actual=primer_Nino;
	nino* anterior=(nino*) malloc(sizeof(nino));
	anterior=NULL;
	int encontrado=0;
	
	if(primer_Nino!=NULL)
	{
		while(actual!=NULL && encontrado!=1)
		{
			
			if(strcmp(actual->cedula,id_nino)==0)
			{
	
				if(actual==primer_Nino)
				{
					primer_Nino=primer_Nino->sig_Nino;
				}
				else if(actual==ultimo_Nino)
				{
					anterior->sig_Nino=NULL;
					ultimo_Nino=anterior;
				}
				else
				{
					anterior->sig_Nino=actual->sig_Nino;
				}
				
				printf("\nNino eliminado con exito");
				encontrado=1;
			}
			anterior=actual;
			actual=actual->sig_Nino;
		}
		if(encontrado==0)
		{
			printf("\nEl nino(a) no fue encontrado\n\n");
		}
		else
		{
			free(anterior);
		}
	}
	else
	{
		printf("\nLa lista se encuentra vacia\n\n");
	}
}

/*Entradas: menu general del miembros 
Salidas: todas las opciones de MIEMBROS
Restricciones: solo datos de miembros */
int Ninos()
{
	system("color 01");
	int opc, verificar, dia, mes, anio, diaActual, mesActual, anioActual, edad;
	char  nombre[30], correo[30], cedula[30], temp_cedula[30], neces[100], id_nino[12], diaSTR[3], mesSTR[3], anioSTR[5]; 
	
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);

	strftime(mesSTR,3,"%m",tlocal);
	strftime(anioSTR,5,"%Y",tlocal);
	strftime(diaSTR,3,"%d",tlocal);

	diaActual=atoi(diaSTR);
	mesActual=atoi(mesSTR);
	anioActual=atoi(anioSTR);
	
	while(opc!=5)
	{
	    printf("\n\t\t____________________________________");
	    printf("\n\t\t|         >>NINOS Y NINAS<<        |");
		printf("\n\t\t|  1. Agregar nino(a)              |");
		printf("\n\t\t|  2. Mostrar ninos(as)            |");
	    printf("\n\t\t|  3. Modificar datos de nino(a)   |");
		printf("\n\t\t|  4. Eliminar nino(a)             |");
	    printf("\n\t\t|  5. Volver al menu principal     |");
	    printf("\n\t\t|__________________________________|");
		printf("\n\nDigite el numero de la opcion a revisar:  ");
	    scanf("%d",&opc);
	
		if(opc==1)
		{
			nino* actual=(nino*) malloc(sizeof(nino));
			actual=primer_Nino;
			
			printf("Ingrese el nombre completo del nino(a): ");
			fflush(stdin); //limpia buffer de espacios y saltos
			scanf("%[^\n]",&nombre);

			
			printf("Ingrese la cedula del nino(a) (formato X-XXXX-XXXX): ");
			fflush(stdin);
			scanf("%[^\n]", &temp_cedula);
			while (strlen(temp_cedula)!=11) //Comparar la cantidad de caracteres
			{
				printf("Digite nuevamente el id del nino(a), con el formato solicitado (X-XXXX-XXXX): ");
				fflush(stdin);
				scanf("%[^\n]", &temp_cedula);
			}
			
			while(actual!=NULL)
			{
				if (strcmp(actual->cedula , temp_cedula)==0)
				{ 
					verificar++;
				}
				actual = actual->sig_Nino;
			}
			
			printf("Ingrese la direccion de correo electronico: ");
			scanf("%s", correo);
			
			printf("Ingrese las necesidades particulares del nino(a), en caso de que este las posea, de no ser asi digite 'No posee': ");
			fflush(stdin);
			scanf("%[^\n]", &neces);
			
			printf(">>Digite el numero que corresponde a lo que se le solicita a continuacion<<\n");
			printf("Digite el ANIO de nacimiento del nino(a): "); //-------------Validar que sea un numero
			scanf("%i", &anio);
			while (anio>anioActual) 
			{
				printf(">>Digite nuevamente el ANIO del nacimiento del nino(a): ");
				scanf("%i", &anio);
			}
			if (anio==anioActual)
			{
				printf("Digite el MES de nacimiento del nino(a): "); //-------------Validar que sea un numero
				scanf("%i", &mes);
				while (mes>mesActual || mes<1)//Se valida que no sea un mes mayor a Enero
				{
					printf(">>Digite nuevamente el MES del nacimiento del nino(a): ");
					scanf("%i", &mes);
				}
				
				printf("Digite el DIA de nacimiento del nino(a): "); //-------------Validar que sea un numero
				scanf("%i", &dia);
				while (dia>diaActual || dia<1)
				{
					printf(">>Digite nuevamente el DIA del nacimiento del nino(a): ");
					scanf("%i", &dia);
				}
			}
			else
			{
				printf("Digite el MES de nacimiento del nino(a): "); //-------------Validar que sea un numero
				scanf("%i", &mes);
				while (mes>12 || mes<1)
				{
					printf(">>Digite nuevamente el MES del nacimiento del nino(a): ");
					scanf("%i", &mes);
				}
				
				printf("Digite el DIA de nacimiento del nino(a): "); //-------------Validar que sea un numero
				scanf("%i", &dia);
				while (dia>31 || dia<1)
				{
					printf(">>Digite nuevamente el DIA del nacimiento del nino(a): ");
					scanf("%i", &dia);
				}
			}
			
			edad=anioActual-anio-1;
			if(mes<mesActual)
			{
				edad++;
			}
			else if(mes==mesActual && dia<=diaActual)
			{
				edad++;
			}
			                
			if(verificar==0)
			{
				strcpy(cedula, temp_cedula);
				nuevoNino(cedula, nombre, correo, neces, dia, mes, anio, edad);
				printf("\n**Muy bien! Se ha logrado registrar al nino(a) con exito!**\n");
			}
			else 
			{
				printf("\nOh! Parece que ya se ha registrado a este nino(a) anteriormente\n");
			}
		}
		else if(opc==2)
		{
			mostrar_Ninos();
		}
		else if(opc==3)
		{
			modificar_Nino();
		}
		else if(opc==4)
		{
			printf("Ingrese el numero de identificacion del nino(a) a eliminar (formato X-XXXX-XXXX): ");
			fflush(stdin);
			scanf("%[^\n]", &id_nino);
			while (strlen(id_nino)!=11) //Comparar la cantidad de caracteres
			{
				printf("Digite nuevamente el id del nino(a), con el formato solicitado (X-XXXX-XXXX): ");
				fflush(stdin);
				scanf("%[^\n]", &id_nino);
			}
			eliminarNino(id_nino);
		}
	}
}	


//------------------------------------STRUCT AYUDANTES-----------------------------------
//Estructura general de los ayudantes de Santa
/*Entradas: Nivel de acceso, nombre, cedula, correo y demas datos de cada miembro
Salidas: un nuevo nodo en lista Simple 
Restricciones: Solo tiene puntero a siguiente */
typedef struct ayudante
{
	char nombre[30], cedula[30], puesto[30], funcs[100];
	int dia, mes, anio;
	struct nino* sig_Ayudante;
} ayudante;

//Variables generales de primer y ultimo miembro
ayudante* primer_Ayudante=NULL;
ayudante* ultimo_Ayudante=NULL;

/*Entradas: variables para la creacion de un registro con los miembros 
Salidas: un nuevo nodo con los datos del nuevo miembro
Restricciones: solo funciona para miembros  */
int nuevoAyudante(char *cedula, char  *nombre, char *puesto,char *funcs, int dia, int mes, int anio) //Funcion para insertar
{ 
	ayudante *nuevo=(ayudante*) malloc(sizeof(ayudante));
	
	strcpy(nuevo->nombre, nombre);
	strcpy(nuevo->cedula, cedula);
    strcpy(nuevo->puesto, puesto);
    strcpy(nuevo->funcs, funcs);
    nuevo->dia=dia;
    nuevo->mes=mes;
    nuevo->anio=anio;  
    
	if(primer_Ayudante==NULL)	
	{
		primer_Ayudante=nuevo;
		primer_Ayudante->sig_Ayudante=NULL;
		ultimo_Ayudante=nuevo;
	}
	ultimo_Ayudante->sig_Ayudante=nuevo;
	nuevo->sig_Ayudante=NULL;
	ultimo_Ayudante=nuevo;
}


//MOSTRAR TODOS LOS AYUDANTES DE SANTA
/*Entradas: datos del struct
Salidas: imprime los datos del miembro en cuestion 
Restricciones: Solo miembros antes inscritos */
void mostrar_Ayudantes()//Imprime 
{
	ayudante* actual=(ayudante*) malloc(sizeof(ayudante)); // crea nodos 
	actual=primer_Ayudante;
	
	if(primer_Ayudante!=NULL)
	{
		while(actual!=NULL)
		{
		
			printf("\t\n    ----Informacion del Ayudante de Santa----\n");
			printf("\n   -Nombre completo: %s\n   -Cedula: %s\n   -Puesto: %s\n   -Funciones: %s\n   -Fecha de inicio de labores: %i/%i/%i\n", actual->nombre, actual->cedula, actual->puesto, actual->funcs, actual->dia, actual->mes, actual->anio);
			actual=actual->sig_Ayudante;// siguiente puntero en lista
		}
	}
	else
	{
		printf("\nUps! Parece que no hay ayudantes registrados\n\n");
	}
}

//MODIFICAR DATOS DE LOS AYUDANTES
/*Entradas: datos del struct
Salidas: imprime los datos del miembro en cuestion 
Restricciones: Solo miembros antes inscritos */
int modificar_Ayudante() 
{
	char id[12], nombre[30], elecc[3]="Si";
	int dato, encontrado;
	
	ayudante* actual=(ayudante*) malloc(sizeof(ayudante)); // crea nodos 
	actual=primer_Ayudante;
	
	printf("Digite la identificacion del ayudante del cual desea modificar sus datos (X-XXXX-XXXX): "); 
	fflush(stdin);
	scanf("%[^\n]", &id);
	while (strlen(id)!=11) //Comparar la cantidad de caracteres
	{
		printf("Digite nuevamente el id del ayudante, con el formato solicitado (X-XXXX-XXXX): ");
		fflush(stdin);
		scanf("%[^\n]", &id);
	}
	
	if(primer_Ayudante!=NULL)
	{
		while(actual!=NULL && encontrado!=1)
		{
			if (strcmp(actual->cedula, id)==0)
			{
				printf("\t\n    ----Informacion del Ayudante de Santa----\n");
				printf("\n   1-Nombre: %s\n   2-Cedula: %s\n   3-Puesto: %s\n   4-Funciones: %s\n   5-Fecha de inicio de labores: %i/%i/%i\n", actual->nombre, actual->cedula, actual->puesto, actual->funcs, actual->dia, actual->mes, actual->anio);
				encontrado=1;
			}
			else
			{
				actual=actual->sig_Ayudante;// siguiente puntero en lista	
			}
			
		}
	}
	else
	{
		printf("\nUps! Parece que el ayudante que busca no esta registrado\n\n");
	}
	
	while (strcmp(elecc,"Si")==0 || strcmp(elecc,"si")==0)
	{
		printf("\nDigite el numero correspondiente al dato que desea modificar: ");
		scanf("%i",&dato);
		
		if (dato==1)
		{
			printf("Digite el nombre completo del ayudante: ");
			fflush(stdin); //limpia buffer de espacios y saltos
			scanf("%[^\n]",&actual->nombre);
		}
		else if (dato==2)
		{
			printf("Digite el numero de identificacion del ayudante de santa (formato X-XXXX-XXXX): ");
			fflush(stdin);
			scanf("%[^\n]", &actual->cedula);
			while (strlen(actual->cedula)!=11) //Comparar la cantidad de caracteres
			{
				printf("Digite nuevamente el id del ayudante, con el formato solicitado (X-XXXX-XXXX): ");
				fflush(stdin);
				scanf("%[^\n]", &actual->cedula);
			}
		}
		else if (dato==3)
		{
			printf("Digite el nuevo puesto: ");
			scanf("%s",&actual->puesto);
		}
		else if (dato==4)
		{
			printf("Describa las funciones que desempeña: ");
			fflush(stdin);
			scanf("%[^\n]", &actual->funcs);
		}
		
		else if (dato==5)
		{
			int diaActual, mesActual, anioActual, edad;
			char  diaSTR[3], mesSTR[3], anioSTR[5]; 
			
			time_t tiempo = time(0);
			struct tm *tlocal = localtime(&tiempo);
		
			strftime(mesSTR,3,"%m",tlocal);
			strftime(anioSTR,5,"%Y",tlocal);
			strftime(diaSTR,3,"%d",tlocal);
		
			diaActual=atoi(diaSTR);
			mesActual=atoi(mesSTR);
			anioActual=atoi(anioSTR);
			
			printf("Digite el ANIO en el que inicio labores con Santa: "); //-------------Validar que sea un numero
			scanf("%i", &actual->anio);
			while (actual->anio>anioActual) 
			{
				printf(">>Digite nuevamente el ANIO en el que inicio labores con Santa: ");
				scanf("%i", &actual->anio);
			}
			if (actual->anio==anioActual)
			{
				printf("Digite el MES en el que inicio labores con Santa: "); //-------------Validar que sea un numero
				scanf("%i", &actual->mes);
				while (actual->mes>mesActual || actual->mes<1)//Se valida que no sea un mes mayor a Enero
				{
					printf(">>Digite nuevamente el MES en el que inicio labores con Santa: ");
					scanf("%i", &actual->mes);
				}
				
				printf("Digite el DIA en el que inicio labores con Santa: "); //-------------Validar que sea un numero
				scanf("%i", &actual->dia);
				while (actual->dia>diaActual || actual->dia<1)
				{
					printf(">>Digite nuevamente el DIA en el que inicio labores con Santa: ");
					scanf("%i", &actual->dia);
				}
			}
			else
			{
				printf("Digite el MES en el que inicio labores con Santa: "); //-------------Validar que sea un numero
				scanf("%i", &actual->mes);
				while (actual->mes>12 || actual->mes<1)
				{
					printf(">>Digite nuevamente el MES en el que inicio labores con Santa: ");
					scanf("%i", &actual->mes);
				}
				
				printf("Digite el DIA en el que inicio labores con Santa: "); //-------------Validar que sea un numero
				scanf("%i", &actual->dia);
				while (actual->dia>31 || actual->dia<1)
				{
					printf(">>Digite nuevamente el DIA en el que inicio labores con Santa: ");
					scanf("%i", &actual->dia);
				}
			}
		}
		printf("Si desea modificar otro dato, digite 'Si', digite 'No' en caso contrario: ");
		scanf("%s",&elecc);
	}
	return 0;
}


//ELIMINAR AYDANTE

void eliminarAyudante(char *id_ayudante)
{
	ayudante* actual=(ayudante*) malloc(sizeof(ayudante));
	actual=primer_Ayudante;
	ayudante* anterior=(ayudante*) malloc(sizeof(ayudante));
	anterior=NULL;
	int encontrado=0;
	
	if(primer_Ayudante!=NULL)
	{
		while(actual!=NULL && encontrado!=1)
		{
			
			if(strcmp(actual->cedula,id_ayudante)==0)
			{
	
				if(actual==primer_Ayudante)
				{
					primer_Ayudante=primer_Ayudante->sig_Ayudante;
				}
				else if(actual==ultimo_Ayudante)
				{
					anterior->sig_Ayudante=NULL;
					ultimo_Ayudante=anterior;
				}
				else
				{
					anterior->sig_Ayudante=actual->sig_Ayudante;
				}
				
				printf("\nAyudante de Santa eliminado con exito");
				encontrado=1;
			}
			anterior=actual;
			actual=actual->sig_Ayudante;
		}
		if(encontrado==0)
		{
			printf("\nEl ayudante no fue encontrado\n\n");
		}
		else
		{
			free(anterior);
		}
	}
	else
	{
		printf("\nLa lista se encuentra vacia\n\n");
	}
}

/*Entradas: menu general del miembros 
Salidas: todas las opciones de MIEMBROS
Restricciones: solo datos de miembros */
int Ayudantes()
{
	system("color 03");
	int opc, verificar, dia, mes, anio, diaActual, mesActual, anioActual;
	char  nombre[30], puesto[30], cedula[30], temp_cedula[30], funcs[100], id_ayudante[12], diaSTR[3], mesSTR[3], anioSTR[5]; 
	
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);

	strftime(mesSTR,3,"%m",tlocal);
	strftime(anioSTR,5,"%Y",tlocal);
	strftime(diaSTR,3,"%d",tlocal);

	diaActual=atoi(diaSTR);
	mesActual=atoi(mesSTR);
	anioActual=atoi(anioSTR);
	
	while(opc!=5)
	{
	    printf("\n\t\t____________________________________");
	    printf("\n\t\t|       >>AYUDANTES DE SANTA<<     |");
		printf("\n\t\t|  1. Agregar ayudante             |");
		printf("\n\t\t|  2. Mostrar ayudantes            |");
	    printf("\n\t\t|  3. Modificar datos de ayudante  |");
		printf("\n\t\t|  4. Eliminar ayudante            |");
	    printf("\n\t\t|  5. Volver al menu principal     |");
	    printf("\n\t\t|__________________________________|");
		printf("\n\nDigite el numero de la opcion a revisar:  ");
	    scanf("%d",&opc);
	
		if(opc==1)
		{
			ayudante* actual=(ayudante*) malloc(sizeof(ayudante));
			actual=primer_Ayudante;
			
			printf("Ingrese el nombre completo del ayudante: ");
			fflush(stdin); //limpia buffer de espacios y saltos
			scanf("%[^\n]",&nombre);

			
			printf("Ingrese el numero de identificacion (formato X-XXXX-XXXX): ");
			fflush(stdin);
			scanf("%[^\n]", &temp_cedula);
			while (strlen(temp_cedula)!=11) //Comparar la cantidad de caracteres
			{
				printf("Digite nuevamente el id, siguiendo el formato solicitado (X-XXXX-XXXX): ");
				fflush(stdin);
				scanf("%[^\n]", &temp_cedula);
			}
			
			while(actual!=NULL)
			{
				if (strcmp(actual->cedula , temp_cedula)==0)
				{ 
					verificar++;
				}
				actual=actual->sig_Ayudante;
			}
			
			printf("Puesto: ");
			fflush(stdin);
			scanf("%[^\n]", &puesto);
			
			printf("Funciones que desempenia: ");
			fflush(stdin);
			scanf("%[^\n]", &funcs);
			
			printf(">>Digite el numero que corresponde a lo que se le solicita a continuacion<<\n");
			printf("Digite el ANIO en el que inicio labores con Santa: "); //-------------Validar que sea un numero
			scanf("%i", &anio);
			while (anio>anioActual) 
			{
				printf(">>Digite nuevamente el ANIO en el que inicio labores con Santa: ");
				scanf("%i", &anio);
			}
			if (anio==anioActual)
			{
				printf("Digite el MES en el que inicio labores con Santa: "); //-------------Validar que sea un numero
				scanf("%i", &mes);
				while (mes>mesActual || mes<1)//Se valida que no sea un mes mayor a Enero
				{
					printf(">>Digite nuevamente el MES en el que inicio labores con Santa: ");
					scanf("%i", &mes);
				}
				
				printf("Digite el DIA en el que inicio labores con Santa: "); //-------------Validar que sea un numero
				scanf("%i", &dia);
				while (dia>diaActual || dia<1)
				{
					printf(">>Digite nuevamente el DIA en el que inicio labores con Santa: ");
					scanf("%i", &dia);
				}
			}
			else
			{
				printf("Digite el MES en el que inicio labores con Santa: "); //-------------Validar que sea un numero
				scanf("%i", &mes);
				while (mes>12 || mes<1)
				{
					printf(">>Digite nuevamente el MES en el que inicio labores con Santa: ");
					scanf("%i", &mes);
				}
				
				printf("Digite el DIA en el que inicio labores con Santa: "); //-------------Validar que sea un numero
				scanf("%i", &dia);
				while (dia>31 || dia<1)
				{
					printf(">>Digite nuevamente el DIA en el que inicio labores con Santa: ");
					scanf("%i", &dia);
				}
			}
			                
			if(verificar==0)
			{
				strcpy(cedula, temp_cedula);
				nuevoAyudante(cedula, nombre, puesto, funcs, dia, mes, anio);
				printf("\n**Muy bien! Se ha logrado registrar al nuevo ayudante de Santa con exito!**\n");
			}
			else 
			{
				printf("\nOh! Parece que ya se ha registrado a este ayudante anteriormente\n");
			}
		}
		else if(opc==2)
		{
			mostrar_Ayudantes();
		}
		else if(opc==3)
		{
			modificar_Ayudante();
		}
		else if(opc==4)
		{
			printf("Ingrese el numero de identificacion del ayudante a eliminar (formato X-XXXX-XXXX): ");
			fflush(stdin);
			scanf("%[^\n]", &id_ayudante);
			while (strlen(id_ayudante)!=11) //Comparar la cantidad de caracteres
			{
				printf("Digite nuevamente el id ayudante, con el formato solicitado (X-XXXX-XXXX): ");
				fflush(stdin);
				scanf("%[^\n]", &id_ayudante);
			}
			eliminarAyudante(id_ayudante);
		}
	}
}	


/*------------------------------------STRUCT COMPORTAMIENTOS-----------------------------------
Estructura general de los comportamientos 
Entradas: nombrePadre, id_nino, fecha, descripcion; 
Salidas: un nuevo nodo en lista Simple 
Restricciones: Solo tiene puntero a siguiente */
typedef struct comportamientos
{
	char nombrePadre[30], id_nino[12], fecha[30], descripcion[100]; 
	int comportamientos_buenos, comportamientos_malos;
	struct comportamientos* sig_compor;
} comportamientos;

//Variables generales de primer y ultimo comportamiento
comportamientos* primer_compor=NULL;
comportamientos* ultimo_compor=NULL;

/*Entradas: variables para la creacion de un registro con los comportamientos 
Salidas: un nuevo nodo con los datos del nuevo comportamiento
Restricciones: solo funciona para comportamientos  */
int nuevoComportamiento(char *nombrePadre, char  *id_nino, char *fecha, char *descripcion, int conducta) //Funcion para insertar
{ 
	comportamientos *nuevo=(comportamientos*) malloc(sizeof(comportamientos));
	
	strcpy(nuevo->nombrePadre, nombrePadre);
	strcpy(nuevo->id_nino, id_nino);
    strcpy(nuevo->fecha, fecha);
    strcpy(nuevo->descripcion, descripcion);
    
	if (conducta == 1)
	{
		nuevo->comportamientos_buenos++;
	}
	else
	{
		nuevo->comportamientos_malos++;
	} 
    
	if(primer_compor==NULL)	
	{
		primer_compor=nuevo;
		primer_compor->sig_compor=NULL;
		ultimo_compor=nuevo;
	}
	ultimo_compor->sig_compor=nuevo;
	nuevo->sig_compor=NULL;
	ultimo_compor=nuevo;
}


/*Entradas: menu general de comportamientos
Salidas: todas las opciones de comportamientos
Restricciones: solo datos de comportamientos */
int comportamiento()
{
	//system("color 01");
	int opc, verificar, conducta;
	char  nombrePadre[30], id_nino[12], fecha[30], descripcion[100],temp_cedula[30]; 

	nino* actual=(nino*) malloc(sizeof(nino));
	actual=primer_Nino;
	
	printf("Ingrese el nombre del padre o madre del nino: ");
	fflush(stdin); //limpia buffer de espacios y saltos
	scanf("%[^\n]",&nombrePadre);

	
	printf("Ingrese la cedula del nino(a) (formato X-XXXX-XXXX): "); 
	fflush(stdin);
	scanf("%[^\n]", &temp_cedula);
	while (strlen(temp_cedula)!=11) //Comparar la cantidad de caracteres
	{
		printf("Digite nuevamente el id del nino(a), con el formato solicitado (X-XXXX-XXXX): ");
		fflush(stdin);
		scanf("%[^\n]", &temp_cedula);
	}
	while(actual!=NULL)
	{
		if (strcmp(actual->cedula , temp_cedula)==0)
		{ 
			verificar++;
		}
		actual = actual->sig_Nino;
	}
		
	printf("Ingrese una descripcion del comportamiento del nino(a): ");
	fflush(stdin);
	scanf("%[^\n]", &descripcion);
	
	while (conducta != 1 && conducta != 2)
	{
		printf("Ingrese 1 si el comportamiento a registrar es *BUENO* o 2 si es *MALO*: ");
		scanf("%d",&conducta);
	}
	
	if(verificar==1)
	{
		nuevoComportamiento(nombrePadre, id_nino, fecha, descripcion, conducta);
		int dia,mes,anio,fecha_F;
	    char diaSTR[3],mesSTR[3],anioSTR[3],fecha_C[30];
	    
	    time_t tiempo = time(0);
		struct tm *tlocal = localtime(&tiempo);
		
		strftime(mesSTR,3,"%m",tlocal);
		strftime(anioSTR,5,"%Y",tlocal);
		strftime(diaSTR,3,"%d",tlocal);
	
		dia=atoi(diaSTR);
		mes=atoi(mesSTR);
		anio=atoi(anioSTR);
		
		snprintf(fecha_C, sizeof fecha_C, "%s/%s/%s", diaSTR, mesSTR, anioSTR);
		printf("\nFecha del registro: %s \n",fecha_C);
		printf("\n**Muy bien! Se ha logrado registrar el comportamiento con exito!**\n");	
	}
	else
	{
		printf("\nOh! Parece que este nino(a) no esta registrado en el sistema \n");
	}
	
}

int main (void)
{
	int opc;
	
	while (opc!=10)
	{
		printf("\n\t\t______________________________________");
	    printf("\n\t\t|           >>MENU PRINCIPAL<<        |");
		printf("\n\t\t|  1. Registro de ninos(as)           |");
		printf("\n\t\t|  2. Registro de ayudantes de Santa  |");
		printf("\n\t\t|  3. Registro de juguetes            |");
		printf("\n\t\t|  4. Lugares de domicilio            |");
		printf("\n\t\t|  5. Registro comportamiento de niños|");
		printf("\n\t\t|  6. Carta a Santa                   |");
		printf("\n\t\t|  7. Procesar cartas para Santa      |");
		printf("\n\t\t|  8. Entregar regalos                |");
	    printf("\n\t\t|  9. Analisis de datos               |");
	    printf("\n\t\t|  10. Finalizar programa             |");
	    printf("\n\t\t|__________________________________ __|");
		printf("\n\nDigite el numero de la opcion a revisar:  ");     
	    scanf("%i", &opc);
	    
	    if (opc==1)
	    {
	    	Ninos();    	
		}
		else if(opc==2)
		{
			Ayudantes();
		}
		else if(opc==3)
		{
			//registro jugetes
		}
		else if(opc==4)
		{
			//catalogo de lugares
		}
		else if(opc==5)
		{
			comportamiento();
		}
		else if(opc==6)
		{
			//carta santa
		}
		else if(opc==7)
		{
			//procesar carta
		}
		else if(opc==8)
		{
			//entrega juguetes
		}
		else if(opc==9)
		{
			// estadisticas
		}
		else
		{
			break;
		}
	}
	return 0;
	system("PAUSE");
}
