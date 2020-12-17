#include "menu.h"

/**
 *
 * @Funcion ShowMainMenu
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el menu principal
 * 		
 */
int ShowMainMenu()
{
    int nSelected = 0;
    char buf[16];

    do
    {
        printf("Esto es el menú principal\n");
        printf("Puedes elegir cualquiera de las opciones para acceder a otra pestaña\n\n");

        printf(" (1) Use\n"
               " (2) Insert(no implementado)\n"
               " (3) print\n"
               " (4) exit\n\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected = 0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4))
        {
            printf("Has metido un número incorrecto. Número incorrecto, vuelva a intentarlo por favor\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

int main(void)
{

    int nChoice = 0;
    char nombreTabla[LEN] = " ";
    char indexName[LEN];


    do
    {
        nChoice = ShowMainMenu();
        switch (nChoice)
        {
        case 1:
        {   
            printf("Nombre de la tabla a crear:");
            scanf("%s", nombreTabla);
            getchar();
            createTable(nombreTabla);
            replaceExtensionByIdx(nombreTabla, indexName);
        }
        break;

        case 2:
        {   
            if(strcmp(nombreTabla, " ")== 0)
            {
                printf("Primero debes hacer Use(1)\n");
                break;
            }
           
            printf("No implementado :(\n");
        }
        break;

        case 3:
        {
            if(strcmp(nombreTabla, " ")== 0)
            {
                printf("Primero debes hacer Use(1)\n");
                break;
            }
            printTree(LEN, indexName);
            printf("no imprime nada porque las funciones add no estan implementadas\n");
        }
        break;
        case 4:
        {
            printf("Bye Bye\n\n");
        }
        break;
        }
    } while (nChoice != 4);
    return 0;
}

