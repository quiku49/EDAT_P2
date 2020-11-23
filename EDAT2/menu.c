#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"
#include "orders.h"
#include "customers.h"

#define LEN 255

int ShowMainMenu();

void ShowProductsMenu(SQLHDBC dbc);

void ShowOrdersMenu(SQLHDBC dbc);

void ShowCustomersMenu(SQLHDBC dbc);

int ShowProductsSubMenu();

int ShowOrdersSubMenu();

int ShowCustomersSubMenu();


int main(void)
{

    SQLHENV env = 0;
    SQLHDBC dbc = 0;
    SQLRETURN ret; /* ODBC API return status */
    int nChoice = 0;

    ret = (SQLRETURN)odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        return EXIT_FAILURE;
    }

    do
    {
        nChoice = ShowMainMenu();
        switch (nChoice)
        {
        case 1:
        {
            ShowProductsMenu(dbc);
        }
        break;

        case 2:
        {
            ShowOrdersMenu(dbc);
        }
        break;

        case 3:
        {
            ShowCustomersMenu(dbc);
        }
        break;
        case 4:
        {
            printf("Bye Bye\n\n");
        }
        break;
        }
    } while (nChoice != 4);

    ret = (SQLRETURN)odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        return EXIT_FAILURE;
    }

    return 0;
}

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

        printf(" (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Exit\n\n"
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

/**
 *
 * @Funcion ShowProductsMenu
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el menu de products
 * 		
 */
void ShowProductsMenu(SQLHDBC dbc)
{
    int nChoice = 0;
    ;
    do
    {
        nChoice = ShowProductsSubMenu();
        switch (nChoice)
        {

        case 1:
        {
            Stock(dbc);
        }
        break;

        case 2:
        {
            FindProducts(dbc);
        }
        break;

        case 3:
        {
            printf("Bye\n\n");
        }
        break;
        }
    } while (nChoice != 3);
}

/**
 *
 * @Funcion ShowOrdersMenu
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el menu de orders
 * 		
 */
void ShowOrdersMenu(SQLHDBC dbc)
{
    int nChoice = 0;

    do
    {
        nChoice = ShowOrdersSubMenu();
        switch (nChoice)
        {

        case 1:
        {
            Open(dbc);
        }
        break;

        case 2:
        {
            Range(dbc);
        }
        break;

        case 3:
        {
            Detail(dbc);
        }
        break;

        case 4:
        {
            printf("Bye\n\n");
        }
        break;
        }
    } while (nChoice != 4);
}

/**
 *
 * @Funcion ShowCustomersMenu
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el menu de los clientes
 * 		
 */
void ShowCustomersMenu(SQLHDBC dbc)
{
    int nChoice = 0;

    do
    {
        nChoice = ShowCustomersSubMenu();
        switch (nChoice)
        {

        case 1:
        {
            FindCustomers(dbc);
        }
        break;

        case 2:
        {
            ListProducts(dbc);
        }
        break;

        case 3:
        {
            Balance(dbc);
        }
        break;

        case 4:
        {
            printf("Bye\n\n");
        }
        break;
        }
    } while (nChoice != 4);
}

/**
 *
 * @Funcion ShowProductsSubMenu
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el sub menu de Products
 * 		
 */
int ShowProductsSubMenu()
{
    int nSelected = 0;
    char buf[16];

    do
    {

        printf(" (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n\n");
        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected = 0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 3))
        {
            printf("Has metido un número incorrecto. Número incorrecto, vuelva a intentarlo por favor\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 3));

    return nSelected;
}
/**
 *
 * @Funcion ShowOrdersSubMenu
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el el sub menu de Orders
 * 		
 */
int ShowOrdersSubMenu()
{
    int nSelected = 0;
    char buf[16];

    do
    {

        printf(" (1) Open\n"
               " (2) Range\n"
               " (3) Detail\n"
               " (4) Back\n\n");
        printf("Enter a number that corresponds to your choice > ");
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

/**
 *
 * @Funcion ShowCustomersSubMenu
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el sub menu de Customers
 * 		
 */
int ShowCustomersSubMenu()
{
    int nSelected = 0;
    char buf[16];

    do
    {

        printf(" (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
               " (4) Back\n\n");
        printf("Enter a number that corresponds to your choice > ");
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
