#ifndef PRODUCTS_H
#define PRODUCTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#define MAX_STRING 1000

void Stock(SQLHDBC dbc);

void FindProducts(SQLHDBC dbc);

#endif