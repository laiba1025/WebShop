#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void menu() {
    printf("1. Load file\n");
    printf("2. Write to filee\n");
    printf("3. Insert an item to cart\n");
    printf("4. Get the price of cart\n");
    printf("5. Buy products\n");
    printf("6. Exit the program\n");
    printf("Enter your choice: ");
}

int main() {
    Store store;
    store.numProducts = 0;
    Cart cart;
    cart.numProducts = 0;
    char filename[20];
    int choice;

    menu();
    scanf("%d", &choice);

    while(1){
        if(choice == 6){
            printf("Thank you for using the store!!!\n\n");
            break;
        }
        else if(choice == 1){
            printf("Provide a valid filename: ");
            scanf("%s", filename);
            load(&store, filename);
        }
        else if(choice == 2){
            printf("Provide a valid filename: ");
            scanf("%s", filename);
            write(&store, filename);
        }
        else if(choice == 3){
            insert(&cart, &store);
            printf("Cart Items\nName\tQuantity\tPrice\n");
            for(int i = 0; i < cart.numProducts; i++){
                printf("%s\t%d\t%.2f\n", cart.items[i].name, cart.items[i].quantity, cart.items[i].price);
            }
        }
        else if(choice == 4){
            double totalCartPrice = getPrice(&cart);
            printf("The total Cart price is %.2f\n\n",totalCartPrice);
        }
        else if(choice == 5){
            buyProducts(&cart,&store);
        }
        else{
            printf("Invalid option - please select an option between 1 - 6\n\n");
        }

        menu();
        scanf("%d", &choice);
    }
    return 0;
}
