#include "odbc.h"
#include "customers.h"
#include "orders.h"
#include "products.h"
#include "menu.h"

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
