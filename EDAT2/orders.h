#ifndef ORDERS_H
#define ORDERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#define MAX_STRING 1000

void Open(SQLHDBC dbc);

void Range(SQLHDBC dbc);

void Detail(SQLHDBC dbc);

#endif