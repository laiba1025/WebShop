#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_PRODUCTS 100

typedef struct {
    char name[50];
    double price;
    int quantity;
} Product;

typedef struct store{
    Product products[MAX_PRODUCTS];
    int numProducts;
} Store;

typedef struct cart{
    Product items[MAX_PRODUCTS];
    int numProducts;
} Cart;

void load(Store* store, char filename[]);
void write(const Store* store, char filename[]);
void insert(Cart* cart, const Store* store);
double getPrice(const Cart* cart);
void buyProducts(Cart* cart, Store* store);

#endif // FUNCTIONS_H
