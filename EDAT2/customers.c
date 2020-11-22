#include "customers.h"

/**
 *
 * @Funcion FindCustomers
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra informacion de los clientes junto con sus contactos donde cuyos nombres sean los introducidos por la terminal
 * 		
 */
void FindCustomers(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    char contactfirstname[MAX_STRING] = "", contactlastname[MAX_STRING] = "", customername[MAX_STRING] = "";
    SQLINTEGER customernumber = 0;
    SQLRETURN cont = 0;

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select customernumber, customername, contactfirstname, contactlastname from customers where contactfirstname like '%'||?||'%' or contactlastname like '%'||?||'%'", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    printf("Enter customer name > ");

    if (scanf("%s", customername) == EOF)
    {
        return;
    }

    if (getchar() == -1)
    {
        return;
    }

    cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, customername, 0, NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, customername, 0, NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 1, SQL_C_LONG, &customernumber, (SQLLEN)sizeof(customernumber), NULL);

    cont = SQLBindCol(stmt, 2, SQL_C_CHAR, customername, (SQLLEN)sizeof(customername), NULL);

    cont = SQLBindCol(stmt, 3, SQL_C_CHAR, contactfirstname, (SQLLEN)sizeof(contactfirstname), NULL);

    cont = SQLBindCol(stmt, 4, SQL_C_CHAR, contactlastname, (SQLLEN)sizeof(contactlastname), NULL);

    while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
    {
        printf("%d %s %s %s\n", customernumber, customername, contactfirstname, contactlastname);
    }
    printf("\n");

    cont = SQLCloseCursor(stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }
    (void)fflush(stdout);

    cont = SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    return;
}

/**
 *
 * @Funcion ListProducts
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el nombre, el codigo y la cantidad de productos pedidos por los clientes
 * se agrupa por codigo de producto y se ordena por codigo de producto
 * 		
 */
void ListProducts(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    char productname[MAX_STRING] = "", productcode[MAX_STRING] = "";
    SQLINTEGER customernumber = 0, sum = 0;
    SQLRETURN cont = 0;

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select p.productname, sum(od.quantityordered), p.productcode from customers c join orders o on c.customernumber=o.customernumber join orderdetails od on o.ordernumber=od.ordernumber join products p on od.productcode=p.productcode where c.customernumber=? group by p.productcode order by p.productcode", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    printf("Enter customer number > ");

    if (scanf("%d", &customernumber) == EOF)
    {
        return;
    }

    if (getchar() == -1)
    {
        return;
    }

    cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLExecute(stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 1, SQL_C_CHAR, productname, (SQLLEN)sizeof(productname), NULL);

    cont = SQLBindCol(stmt, 2, SQL_C_LONG, &sum, (SQLLEN)sizeof(sum), NULL);

    cont = SQLBindCol(stmt, 3, SQL_C_CHAR, productcode, (SQLLEN)sizeof(productcode), NULL);

    while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
    {
        printf("%s %d %s\n", productname, sum, productcode);
    }
    printf("\n");

    cont = SQLCloseCursor(stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }
    (void)fflush(stdout);

    cont = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    return;
}

/**
 *
 * @Funcion Balance
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra la cantidad de dinero pagado para un customernumber dado,
 * agrupado por numero del customer
 * 		
 */
void Balance(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    SQLINTEGER customernumber = 0;
    SQLDOUBLE amon = 0, sum = 0;
    SQLRETURN cont = 0;

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select sum(pay.amount) from payments pay where pay.customernumber = ? group by pay.customernumber", SQL_NTS);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    printf("Enter customer number > ");

    if (scanf("%d", &customernumber) == EOF)
    {
        return;
    }

    if (getchar() == -1)
    {
        return;
    }

    cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLExecute(stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 1, SQL_C_DOUBLE, &amon, (SQLLEN)sizeof(amon), NULL);

    while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
        ;

    cont = SQLCloseCursor(stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }
    (void)fflush(stdout);

    cont = SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select sum(od.quantityordered*priceeach) from orderdetails od join orders o on od.ordernumber= o.ordernumber where o.customernumber = ?", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 1, SQL_C_DOUBLE, &sum, (SQLLEN)sizeof(sum), NULL);

    while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
        ;

    printf("Balance = %.2f\n", amon - sum);

    printf("\n\n");

    cont = SQLCloseCursor(stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }
    (void)fflush(stdout);

    cont = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    return;
}