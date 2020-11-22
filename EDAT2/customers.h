#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#define MAX_STRING 1000

void FindCustomers(SQLHDBC dbc);

void ListProducts(SQLHDBC dbc);

void Balance(SQLHDBC dbc);

#endif