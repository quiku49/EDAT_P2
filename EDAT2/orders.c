#include "orders.h"

/**
 *
 * @Funcion Open
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion selecciona de orders los ordernumber que no tenga fecha de envio, se ordena por numero de order			
 */
void Open(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    SQLINTEGER ordernumber = 0;
    SQLRETURN cont = 0;

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select ordernumber from orders where shippeddate is null order by ordernumber", SQL_NTS);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }
    cont = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 1, SQL_INTEGER, &ordernumber, (SQLLEN)sizeof(ordernumber), NULL);

    printf("\nOrdernumber\n");

    while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
    {
        printf("%d\n", ordernumber);
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
 * @Funcion Range
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion selecciona de orders los ordernumber y las fechas de envio y de order que tenga fecha de envio, 
 * y que este entre dos fechas que introduce, se ordena por numero de order			
 */
void Range(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    char orderdate[MAX_STRING] = "", shipperdate[MAX_STRING] = "", date1[MAX_STRING] = "", date2[MAX_STRING] = "", aux[MAX_STRING] = "";
    SQLINTEGER ordernumber = 0;
    int cont = 0;

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select ordernumber, orderdate, shippeddate from orders where orderdate between ? and ? and shippeddate is not null order by ordernumber", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");
    if (scanf("%s %s %s", date1, aux, date2) == NULL)
    {
        return;
    }

    cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, date1, 0, NULL);

    cont = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, date2, 0, NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 1, SQL_INTEGER, &ordernumber, (SQLLEN)sizeof(ordernumber), NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 2, SQL_C_CHAR, orderdate, (SQLLEN)sizeof(orderdate), NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 3, SQL_C_CHAR, shipperdate, (SQLLEN)sizeof(shipperdate), NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    while (SQL_SUCCEEDED(SQLFetch(stmt)))
    {
        printf("%d %s %s\n", ordernumber, orderdate, shipperdate);
    }
    printf("\n");

    cont = SQLCloseCursor(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    (void)fflush(stdout);

    if (getchar() == NULL)
    {
        return;
    }
    cont = SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    return;
}

/**
 *
 * @Funcion Detail
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion devuelve detalles de productos		
 */
void Detail(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    SQLINTEGER ordernumber = 0, quantityorder = 0;
    SQLDOUBLE total = 0, price = 0;
    char productcode[MAX_STRING] = "";
    SQLRETURN cont = 0;

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select orderdate, status from orders where ordernumber = ?", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    printf("Enter ordernumber > ");

    if (scanf("%d", &ordernumber) == NULL)
    {
        return;
    }

    if (getchar() == NULL)
    {
        return;
    }

    cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    while (SQL_SUCCEEDED(SQLFetch(stmt)))
        ;

    cont = SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLCloseCursor(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    (void)fflush(stdout);

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select sum(od.quantityordered*od.priceeach) from orderdetails od join orders o on od.ordernumber=o.ordernumber where od.ordernumber=? group by od.ordernumber", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 1, SQL_DOUBLE, &total, (SQLLEN)sizeof(total), NULL);

    while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
        ;

    printf("Total sum = %.6f\n", total);

    cont = SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLCloseCursor(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    (void)fflush(stdout);

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select od.productcode, od.quantityordered, od.priceeach, od.orderlinenumber from orderdetails od where od.ordernumber = ? order by od.orderlinenumber", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLExecute(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLBindCol(stmt, 1, SQL_C_CHAR, productcode, (SQLLEN)sizeof(productcode), NULL);

    cont = SQLBindCol(stmt, 2, SQL_INTEGER, &quantityorder, (SQLLEN)sizeof(quantityorder), NULL);

    cont = SQLBindCol(stmt, 3, SQL_DOUBLE, &price, (SQLLEN)sizeof(price), NULL);

    while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
    {
        printf("%s %d %.2f\n", productcode, quantityorder, price);
    }

    printf("\n\n");

    cont = SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLCloseCursor(stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    (void)fflush(stdout);

    return;
}