#include "products.h"

/**
 *
 * @Funcion Stock
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion devuelve la cantidad de productos que hay en stock donde el productcode se introduce por terminal
 * 		
 */
void Stock(SQLHDBC dbc)
{

    SQLHSTMT stmt = NULL;
    SQLRETURN cont = 0;
    char x[MAX_STRING] = "";
    SQLINTEGER stock = 0;

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"SELECT quantityinstock FROM products WHERE productcode = ?", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    printf("Enter productcode > ");

    if (scanf("%s", x) != EOF)
    {
        cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, x, 0, NULL);

        if (!SQL_SUCCEEDED(cont))
        {
            return;
        }

        cont = SQLExecute(stmt);

        if (!SQL_SUCCEEDED(cont))
        {
            return;
        }

        cont = SQLBindCol(stmt, 1, SQL_INTEGER, &stock, (SQLLEN)sizeof(stock), NULL);

        printf("\nProductcode\tQuantitiInStock\n");

        while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
        {
            printf("%s\t%d\n", x, stock);
        }
        printf("\n");

        cont = SQLCloseCursor(stmt);

        if (!SQL_SUCCEEDED(cont))
        {
            return;
        }

        (void)fflush(stdout);
    }

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
 * @Funcion FindProducts
 * @authors Rubén González Ruiz & Enrique Ciudad de Lara
 * @Descripcion muestra el codigo y nombre de los productos cuyo nombre se introduce por terminal, se ordena por codigo de producto
 * 		
 */
void FindProducts(SQLHDBC dbc)
{
    SQLHSTMT stmt = NULL;
    char productcode[MAX_STRING] = "", productname[MAX_STRING] = "";
    SQLRETURN cont = 0;

    cont = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    cont = SQLPrepare(stmt, (SQLCHAR *)"select productcode, productname from products where productname like '%'||?||'%' order by productcode", SQL_NTS);

    if (!SQL_SUCCEEDED(cont))
    {
        return;
    }

    printf("Enter productname > ");

    if (scanf("%s", productname) != EOF)
    {
        cont = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, productname, 0, NULL);

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

        cont = SQLBindCol(stmt, 2, SQL_C_CHAR, productname, (SQLLEN)sizeof(productname), NULL);

        printf("\nProductcode\tproductname\n");

        while (SQL_SUCCEEDED(cont = SQLFetch(stmt)))
        {
            printf("%s\t%s\n", productcode, productname);
        }
        printf("\n");

        cont = SQLCloseCursor(stmt);

        if (!SQL_SUCCEEDED(cont))
        {
            return;
        }

        (void)fflush(stdout);
    }

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
