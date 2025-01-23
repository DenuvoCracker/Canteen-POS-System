void managerFunctions() {
    int choice;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

    while (1) {
        printf("\n--- Manager Menu ---\n");
        printf("1. Display Menu\n");
        printf("2. Add Menu Item\n");
        printf("3. Restock Item\n");
        printf("4. Check Low Stock\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                addMenuItem();
                break;
            case 3:
                restockItem();
                break;
            case 4:
                checkLowStock();
                break;
            case 5:
                printf("Logging out...\n");
                login();
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Cashier Functions
void cashierFunctions() {
    int choice;

    while (1) {
        printf("\n--- Cashier Menu ---\n");
        printf("1. Display Menu\n");
        printf("2. Process Order\n");
        printf("3. Generate Bill\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                processOrder();
                break;
            case 3:
                generateBill();
                break;
            case 4:
                printf("Logging out...\n");
                login();
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}