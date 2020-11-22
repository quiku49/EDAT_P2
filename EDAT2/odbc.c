#include <stdlib.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

/* REPORT OF THE MOST RECENT ERROR USING HANDLE handle */
void odbc_extract_error(char *fn, SQLHANDLE handle, SQLSMALLINT type)
{
    SQLINTEGER i = 0;
    SQLINTEGER native = 0;
    char state[7] = "";
    char text[256] = "";
    SQLSMALLINT len = 0;
    SQLRETURN ret = 0;

    fprintf(stderr, "\nThe driver reported the following diagnostics while running %s\n\n", fn);

    do
    {
        ret = SQLGetDiagRec(type, handle, (SQLSMALLINT)++i, (SQLCHAR *)state, &native, (SQLCHAR *)text, (SQLSMALLINT)sizeof(text), &len);
        if (SQL_SUCCEEDED(ret))
        {
            printf("%s:%d:%d:%s\n", state, i, native, text);
        }
    } while (ret == SQL_SUCCESS);
}

/* STANDARD CONNECTION PROCEDURE */
int odbc_connect(SQLHENV *env, SQLHDBC *dbc)
{
    SQLRETURN ret;

    /* Allocate an environment handle */
    ret = SQLAllocHandle(SQL_HANDLE_ENV, (SQLHANDLE)SQL_NULL_HANDLE, env);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", *env, SQL_HANDLE_ENV);
        return ret;
    }

    /* We want ODBC 3 support */
    ret = SQLSetEnvAttr(*env, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", *env, SQL_HANDLE_ENV);
        return ret;
    }

    /* Allocate a connection handle */
    ret = SQLAllocHandle(SQL_HANDLE_DBC, *env, dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", *dbc, SQL_HANDLE_DBC);
        return ret;
    }

    /* Connect to the DSN mydsn */
    /* You will need to change mydsn to one you have created and tested */
    ret = SQLDriverConnect(*dbc, NULL, (SQLCHAR *)CONNECTION_PARS, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", *dbc, SQL_HANDLE_DBC);
        return ret;
    }

    return ret;
}

/* STANDARD DISCONNECTION PROCEDURE */
int odbc_disconnect(SQLHENV env, SQLHDBC dbc)
{
    SQLRETURN ret;

    /* Disconnect from database */
    ret = SQLDisconnect(dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", dbc, SQL_HANDLE_DBC);
        return ret;
    }

    /* Free connection handle */
    ret = SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", dbc, SQL_HANDLE_DBC);
        return ret;
    }

    /* Free environment handle */
    ret = SQLFreeHandle(SQL_HANDLE_ENV, env);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", env, SQL_HANDLE_ENV);
        return ret;
    }

    return ret;
}