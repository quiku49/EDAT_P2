#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#define MAX_STRING 1000

int ShowMainMenu();
void ShowProductsMenu(SQLHDBC dbc);
void ShowOrdersMenu();
void ShowCustomersMenu();
int ShowProductsSubMenu();
int ShowOrdersSubMenu();
int ShowCustomersSubMenu();
int Stock(SQLHDBC dbc);
int FindProducts(SQLHDBC dbc);
int Open(SQLHDBC dbc);
int Range(SQLHDBC dbc);
void Detail();
int FindCustomers(SQLHDBC dbc);
int ListProducts(SQLHDBC dbc);
void Balance();


int main(void){

    SQLHENV env;
    SQLHDBC dbc;
    SQLRETURN ret; /* ODBC API return status */
    int nChoice = 0;


    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    do {
        nChoice = ShowMainMenu();
        switch (nChoice) {
            case 1: {
                ShowProductsMenu(dbc);
            }
                break;

            case 2: {
                ShowOrdersMenu(dbc);
            }
                break;

            case 3: {
                ShowCustomersMenu(dbc);
            }
                break;
            case 4: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);

    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)){
        return EXIT_FAILURE;
    }

    return 0;
}

int ShowMainMenu(){
    int nSelected = 0;
    char buf[16];

    do {
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

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("Has metido un número incorrecto. Número incorrecto, vuelva a intentarlo por favor\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

void ShowProductsMenu(SQLHDBC dbc){
    int nChoice = 0;
    ;
    do {
        nChoice = ShowProductsSubMenu();
        switch (nChoice) {

            case 1: {
                Stock(dbc);
            }
                break;

            case 2: {
                FindProducts(dbc);
            }
                break;

            case 3: {
                printf("Bye\n\n");
            }
                break;
        }
    } while (nChoice != 3);

}

void ShowOrdersMenu(SQLHDBC dbc){
    int nChoice = 0;
    
    do {
        nChoice = ShowOrdersSubMenu();
        switch (nChoice) {

            case 1: {
                Open(dbc);
            }
                break;

            case 2: {
                Range(dbc);
            }
                break;

            case 3: {
                Detail();
            }
                break;

            case 4: {
                printf("Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);

}

void ShowCustomersMenu(SQLHDBC dbc){
    int nChoice = 0;
    
    do {
        nChoice = ShowCustomersSubMenu();
        switch (nChoice) {

            case 1: {
                FindCustomers(dbc);
            }
                break;

            case 2: {
                ListProducts(dbc);
            }
                break;

            case 3: {
                Balance();
            }
                break;

            case 4: {
                printf("Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);

}

int ShowProductsSubMenu(){
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n\n");
        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");


        if ((nSelected < 1) || (nSelected > 3)) {
            printf("Has metido un número incorrecto. Número incorrecto, vuelva a intentarlo por favor\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 3));

    return nSelected;
}   

int ShowOrdersSubMenu(){
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Open\n"
               " (2) Range\n"
               " (3) Detail\n"
               " (4) Back\n\n");
        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");


        if ((nSelected < 1) || (nSelected > 4)) {
            printf("Has metido un número incorrecto. Número incorrecto, vuelva a intentarlo por favor\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

int ShowCustomersSubMenu(){
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
               " (4) Back\n\n");
        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");


        if ((nSelected < 1) || (nSelected > 4)) {
            printf("Has metido un número incorrecto. Número incorrecto, vuelva a intentarlo por favor\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}   

int Stock(SQLHDBC dbc){

    SQLHSTMT stmt;
    SQLCHAR x[MAX_STRING];
    SQLINTEGER stock;


    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"SELECT quantityinstock FROM products WHERE productcode = ?", SQL_NTS);

    printf("Enter productcode > ");

    if (scanf("%s", x) != EOF){
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, x, 0, NULL);
    
        SQLExecute(stmt);

        SQLBindCol(stmt, 1, SQL_INTEGER, &stock, sizeof(stock), NULL);

        printf("\nProductcode\tQuantitiInStock\n");

    while(SQL_SUCCEEDED(SQLFetch(stmt))){
        printf("%s\t%d\n", x, stock);
    }
        printf("\n");

        SQLCloseCursor(stmt);
        fflush(stdout);
    }

    getchar();
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return EXIT_SUCCESS;
}

int FindProducts(SQLHDBC dbc){
    SQLHSTMT stmt;
    SQLCHAR productcode[MAX_STRING], productname[MAX_STRING];


    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"select productcode, productname from products where productname like '%'||?||'%' order by productcode", SQL_NTS);

    printf("Enter productname > ");

    if (scanf("%s", productname) != EOF){
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, productname, 0, NULL);
    
        SQLExecute(stmt);

        SQLBindCol(stmt, 1, SQL_C_CHAR, productcode, sizeof(productcode), NULL);

        SQLBindCol(stmt, 2, SQL_C_CHAR, productname, sizeof(productname), NULL);

        printf("\nProductcode\tproductname\n");

    while(SQL_SUCCEEDED(SQLFetch(stmt))){
        printf("%s\t%s\n", productcode, productname);
    }
        printf("\n");

        SQLCloseCursor(stmt);
        fflush(stdout);
    }

    getchar();
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return EXIT_SUCCESS;
}

int Open(SQLHDBC dbc){
    SQLHSTMT stmt;
    SQLINTEGER ordernumber;


    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"select ordernumber from orders where shippeddate is null order by ordernumber", SQL_NTS);
   
        SQLExecute(stmt);

        SQLBindCol(stmt, 1, SQL_INTEGER, &ordernumber, sizeof(ordernumber), NULL);

        printf("\nOrdernumber\n");

    while(SQL_SUCCEEDED(SQLFetch(stmt))){
        printf("%d\n", ordernumber);
    }
        printf("\n");

        SQLCloseCursor(stmt);
        fflush(stdout);

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return EXIT_SUCCESS;
}

/**HACERLO SOLO CON UN SCANF, Y VER SI ESTA BIEN LO DE LAS FECHAS**/

int Range(SQLHDBC dbc){
    SQLHSTMT stmt;
    SQLCHAR orderdate[MAX_STRING], shipperdate[MAX_STRING], date1[MAX_STRING], date2[MAX_STRING], aux[MAX_STRING];
    SQLINTEGER ordernumber;


    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"select ordernumber, orderdate, shippeddate from orders where orderdate between ? and ? and shippeddate is not null order by ordernumber", SQL_NTS);

    printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");
    scanf("%s %s %s", date1, aux, date2);

        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, date1, 0, NULL);

        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, date2, 0, NULL);
    
        SQLExecute(stmt);

        SQLBindCol(stmt, 1, SQL_INTEGER, &ordernumber, sizeof(ordernumber), NULL);

        SQLBindCol(stmt, 2, SQL_C_CHAR, orderdate, sizeof(orderdate), NULL);

        SQLBindCol(stmt, 3, SQL_C_CHAR, shipperdate, sizeof(shipperdate), NULL);


    while(SQL_SUCCEEDED(SQLFetch(stmt))){
        printf("%d %s %s\n", ordernumber, orderdate, shipperdate);
    }
        printf("\n");

        SQLCloseCursor(stmt);
        fflush(stdout);
        
    

    getchar();
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return EXIT_SUCCESS;
}

void Detail(){

}

int FindCustomers(SQLHDBC dbc){
    SQLHSTMT stmt;
    SQLCHAR contactfirstname[MAX_STRING], contactlastname[MAX_STRING], customername[MAX_STRING];
    SQLINTEGER customernumber;


    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"select customernumber, customername, contactfirstname, contactlastname from customers where contactfirstname like '%'||?||'%' or contactlastname like '%'||?||'%'", SQL_NTS);

    printf("Enter customer name > ");
    
    scanf("%s", customername);
    
    getchar();

        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, customername, 0, NULL);

        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, customername, 0, NULL);
    
        SQLExecute(stmt);

        SQLBindCol(stmt, 1, SQL_C_LONG, &customernumber, sizeof(customernumber), NULL);

        SQLBindCol(stmt, 2, SQL_C_CHAR, customername, sizeof(customername), NULL);

        SQLBindCol(stmt, 3, SQL_C_CHAR, contactfirstname, sizeof(contactfirstname), NULL);

        SQLBindCol(stmt, 4, SQL_C_CHAR, contactlastname, sizeof(contactlastname), NULL);


    while(SQL_SUCCEEDED(SQLFetch(stmt))){
        printf("%d %s %s %s\n", customernumber, customername, contactfirstname, contactlastname);
    }
        printf("\n");

        SQLCloseCursor(stmt);
        fflush(stdout);
        
    
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return EXIT_SUCCESS;
}

int ListProducts(SQLHDBC dbc){
    SQLHSTMT stmt;
    SQLCHAR productname[MAX_STRING], productcode[MAX_STRING];
    SQLINTEGER customernumber, sum;


    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, (SQLCHAR *)"select p.productname, sum(od.quantityordered), p.productcode from customers c join orders o on c.customernumber=o.customernumber join orderdetails od on o.ordernumber=od.ordernumber join products p on od.productcode=p.productcode where c.customernumber=? group by p.productcode order by p.productcode", SQL_NTS);

    printf("Enter customer number > ");
    
    scanf("%d", &customernumber);
    
    getchar();

        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
    
        SQLExecute(stmt);

        SQLBindCol(stmt, 1, SQL_C_CHAR, productname, sizeof(productname), NULL);

        SQLBindCol(stmt, 2, SQL_C_LONG, &sum, sizeof(sum), NULL);

        SQLBindCol(stmt, 3, SQL_C_CHAR, productcode, sizeof(productcode), NULL);


    while(SQL_SUCCEEDED(SQLFetch(stmt))){
        printf("%s %d %s\n", productname, sum, productcode);
    }
        printf("\n");

        SQLCloseCursor(stmt);
        fflush(stdout);
        
    
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return EXIT_SUCCESS;
}

void Balance(){

}


