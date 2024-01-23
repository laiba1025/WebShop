#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void load(Store* store, char filename[]) {

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error opening file.\n");
        return;
    }

    Product product;
    int num = 0;
    
    while (fscanf(file, "%s %lf %d", product.name, &product.price, &product.quantity) == 3) {

        int duplicateFound = 0;
        for(int i = 0; i < store->numProducts; i++){
            if(strcmp(store->products[i].name, product.name) == 0){
                duplicateFound = 1;
                break;
            }
        }

        if(!duplicateFound){
            store->products[store->numProducts] = product;
            store->numProducts++;
        }
        else{
            printf("Duplicate item name '%s' found. Not adding to store.\n", product.name);
        }
    }
    fclose(file);

    printf("\nHere are the Items loaded into the store:\n");
    for(int i = 0; i < store->numProducts; i++){
        printf("%s %.2f %d\n", store->products[i].name, store->products[i].price, store->products[i].quantity);
    }
    
    printf("\n");
}

/*void load(Store* store, char filename[]) {

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error opening file.\n");
        return;
    }

    Product product;
    int num = 0;
    
    while (fscanf(file, "%s %lf %d", product.name, &product.price, &product.quantity) == 3) {

        if(store->numProducts == 0){
            store->products[store->numProducts] = product;
            store->numProducts++;
        }
        else{
            for(int i = 0; i < store->numProducts; i++){
                //printf("%s\n",product.name);
                if(strcmp(store->products[i].name, product.name) == 0){
                    //if(store->products[i].quantity != product.quantity){
                        store->products[i].price = product.price;
                        store->products[i].quantity += product.quantity;
                        break;
                    //}
                }
                else{
                    store->products[store->numProducts] = product;
                    store->numProducts++;
                    break;
                }
            }
        }
    }
    fclose(file);

    printf("\nHere are the Items loaded into the store:\n");
    for(int i = 0; i < store->numProducts; i++){
        printf("%s %.2f %d\n", store->products[i].name, store->products[i].price, store->products[i].quantity);
    }
    
    printf("\n");
}*/

void write(const Store* store, char filename[]) {

    FILE* file = fopen(filename, "a");
    if(file == NULL){
        printf("Error opening file.\n\n");
        return;
    }
        for (int i = 0; i < store->numProducts; i++) {
            fprintf(file, "%s %.2lf %d\n", store->products[i].name, store->products[i].price, store->products[i].quantity);
        }
        fclose(file);
        printf("Data saved successfully\n\n");
}

void insert(Cart* cart, const Store* store) {
    char productName[50];
    int quantity;

    printf("Enter product name: ");
    scanf("%s", productName);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    for (int i = 0; i < store->numProducts; i++) {
        if (strcmp(store->products[i].name, productName) == 0) {
            Product cartItem = store->products[i];
            /*
            if (quantity < store->products[i].quantity) {
                cartItem.quantity = quantity;
            } else {
                cartItem.quantity = store->products[i].quantity;
            }*/
            cartItem.quantity = quantity;
            cartItem.price *= cartItem.quantity;
            cart->items[cart->numProducts++] = cartItem;
            printf("Item added to cart.\n\n");
            return;
        }
    }

    printf("Product not found.\n\n");
}

double getPrice(const Cart* cart){
    double totalPrice = 0;

    for(int i = 0; i < cart->numProducts; i++){
        totalPrice += cart->items[i].price;
    }
    return totalPrice;
}

void buyProducts(Cart* cart, Store* webshop) {
    for (int i = 0; i < cart->numProducts; i++) {
        for (int j = 0; j < webshop->numProducts; j++) {
            if (strcmp(cart->items[i].name, webshop->products[j].name) == 0) {
                if (webshop->products[j].quantity >= cart->items[i].quantity) {
                    webshop->products[j].quantity -= cart->items[i].quantity;
                } else {
                    printf("%d %s are missing.\n", cart->items[i].quantity - webshop->products[j].quantity, cart->items[i].name);
                    //webshop->products[j].quantity = 0;
                    return;
                }
                break;
            }
        }
    }

    cart->numProducts = 0;
    printf("Products bought successfully.\n");
}
