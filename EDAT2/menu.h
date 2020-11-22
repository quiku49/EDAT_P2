#ifndef MENU_H
#define MENU_H

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

#endif /*MENU_H*/