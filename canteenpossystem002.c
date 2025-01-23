#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_ORDERS 100
#define LOW_STOCK_THRESHOLD 5
#define AUTO_REPLENISH_AMOUNT 20

// Structures
struct MenuItem {
    int id;
    char name[50];
    float price;
    int stock;
};

struct Order {
    int orderId;
    int itemId;
    int quantity;
    float totalCost;
};

// Global variables
struct MenuItem menu[MAX_ITEMS];
int menuSize = 0;

struct Order orders[MAX_ORDERS];
int orderCount = 0;

// Function prototypes
void displayMenu();
void addMenuItem();
void restockItem();
void processOrder();
void generateBill();
void login();
void managerFunctions();
void cashierFunctions();
void clearInputBuffer();
void loadMenuFromFile();
void saveMenuToFile();
void saveOrderToFile(struct Order order);
void checkLowStock();
void autoReplenishStock(int id);
void processCashPayment(float totalCost);

// Main function
int main() {
    printf("\n--- Canteen POS System with Role Management ---\n");
    loadMenuFromFile();
    login();
    return 0;
}

// Login function
void login() {
    char role[20];
    char password[20];

    printf("\nEnter role (Manager/Cashier/Exit): \nEnter Exit to end the program\n");
    scanf("%s", role);

    if (strcmp(role, "Manager") == 0) {
        printf("Enter manager password: ");
        scanf("%s", password);
        if (strcmp(password, "admin123") == 0) {
            managerFunctions();
        } else {
            printf("Invalid password!\n");
            login();
        }
    } else if (strcmp(role, "Cashier") == 0) {
        cashierFunctions();
    } else if (strcmp(role, "Exit") == 0) {
        exit(1);
    } else {
        printf("Invalid role! Please enter a valid role.\n");
        login();
        return;
    }
}

// Manager Functions
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

// Display Menu
void displayMenu() {
    if (menuSize == 0) {
        printf("The menu is currently empty.\n");
        return;
    }
    printf("\nID\tName\t\tPrice\tStock\n");
    for (int i = 0; i < menuSize; i++) {
        printf("%d\t%s\t\t%.2f\t%d\n", menu[i].id, menu[i].name, menu[i].price, menu[i].stock);
    }
}

// Add Menu Item
void addMenuItem() {
    if (menuSize >= MAX_ITEMS) {
        printf("Cannot add more items. Menu is full.\n");
        return;
    }

    struct MenuItem newItem;
    newItem.id = menuSize + 1;
    printf("Enter item name: ");
    clearInputBuffer();
    fgets(newItem.name, sizeof(newItem.name), stdin);
    newItem.name[strcspn(newItem.name, "\n")] = '\0'; // Remove newline

    printf("Enter item price: ");
    if (scanf("%f", &newItem.price) != 1 || newItem.price < 0) {
        printf("Invalid price. Operation cancelled.\n");
        return;
    }

    printf("Enter item stock: ");
    if (scanf("%d", &newItem.stock) != 1 || newItem.stock < 0) {
        printf("Invalid stock. Operation cancelled.\n");
        return;
    }

    menu[menuSize++] = newItem;
    saveMenuToFile();
    printf("Item added successfully!\n");
}

// Restock Item
void restockItem() {
    int id, restockQuantity;
    printf("Enter the ID of the item to restock: ");
    if (scanf("%d", &id) != 1 || id <= 0 || id > menuSize) {
        printf("Invalid item ID.\n");
        return;
    }

    printf("Enter the quantity to restock: ");
    if (scanf("%d", &restockQuantity) != 1 || restockQuantity < 0) {
        printf("Invalid quantity.\n");
        return;
    }

    menu[id - 1].stock += restockQuantity;
    saveMenuToFile();
    printf("Item restocked successfully!\n");
}

// Check Low Stock
void checkLowStock() {
    printf("\n--- Low Stock Items ---\n");
    int found = 0;
    for (int i = 0; i < menuSize; i++) {
        if (menu[i].stock <= LOW_STOCK_THRESHOLD) {
            printf("ID: %d, Name: %s, Stock: %d\n", menu[i].id, menu[i].name, menu[i].stock);
            autoReplenishStock(i);
            found = 1;
        }
    }
    if (!found) {
        printf("No items with low stock.\n");
    }
}

// Auto Replenish Stock
void autoReplenishStock(int id) {
    printf("Auto-replenishing stock for %s. Adding %d units.\n", menu[id].name, AUTO_REPLENISH_AMOUNT);
    menu[id].stock += AUTO_REPLENISH_AMOUNT;
    saveMenuToFile();
}

// Process Order
void processOrder() {
    if (menuSize == 0) {
        printf("The menu is empty. Add items first.\n");
        return;
    }

    struct Order newOrder;
    printf("Enter order ID: ");
    if (scanf("%d", &newOrder.orderId) != 1 || newOrder.orderId <= 0) {
        printf("Invalid order ID.\n");
        return;
    }

    printf("Enter item ID: ");
    if (scanf("%d", &newOrder.itemId) != 1 || newOrder.itemId <= 0 || newOrder.itemId > menuSize) {
        printf("Invalid item ID.\n");
        return;
    }

    printf("Enter quantity: ");
    if (scanf("%d", &newOrder.quantity) != 1 || newOrder.quantity <= 0) {
        printf("Invalid quantity.\n");
        return;
    }

    if (newOrder.quantity > menu[newOrder.itemId - 1].stock) {
        printf("Insufficient stock.\n");
        return;
    }

    newOrder.totalCost = newOrder.quantity * menu[newOrder.itemId - 1].price;
    menu[newOrder.itemId - 1].stock -= newOrder.quantity;
    orders[orderCount++] = newOrder;

    saveOrderToFile(newOrder);
    saveMenuToFile();
    processCashPayment(newOrder.totalCost);
    printf("Order processed successfully!\n");
}

// Process Cash Payment
void processCashPayment(float totalCost) {
    float cashGiven, change;
    printf("\nTotal Cost: %.2f\n", totalCost);
    printf("Enter cash given: ");
    if (scanf("%f", &cashGiven) != 1 || cashGiven < totalCost) {
        printf("Insufficient cash. Order cannot be completed.\n");
        return;
    }

    change = cashGiven - totalCost;
    printf("Change to return: %.2f\n", change);
}

// Generate Bill
void generateBill() {
    if (orderCount == 0) {
        printf("No orders to generate a bill for.\n");
        return;
    }

    printf("\n--- Bill Summary ---\n");
    printf("Order ID\tItem ID\tQuantity\tTotal Cost\n");

    for (int i = 0; i < orderCount; i++) {
        printf("%d\t\t%d\t%d\t\t%.2f\n", orders[i].orderId, orders[i].itemId, orders[i].quantity, orders[i].totalCost);
    }
}

// Load Menu from File
void loadMenuFromFile() {
    FILE *file = fopen("menu.txt","r");
    if (file == NULL) {
        printf("Menu file not found. Starting with an empty menu.\n");
        return;
    }

    menuSize = 0;
    while (fscanf(file, "%d,%49[^,],%f,%d\n", &menu[menuSize].id, menu[menuSize].name, &menu[menuSize].price, &menu[menuSize].stock) == 4) {
        menuSize++;
    }
    fclose(file);
}

// Save Menu to File
void saveMenuToFile() {
    FILE *file = fopen("menu.txt", "w");
    if (file == NULL) {
        printf("Error saving menu to file.\n");
        return;
    }

    for (int i = 0; i < menuSize; i++) {
        fprintf(file, "%d,%s,%.2f,%d\n", menu[i].id, menu[i].name, menu[i].price, menu[i].stock);
    }
    fclose(file);
}

// Save Order to File
void saveOrderToFile(struct Order order) {
    FILE *file = fopen("orders.txt", "a");
    if (file == NULL) {
        printf("Error saving order to file.\n");
        return;
    }

    fprintf(file, "%d,%d,%d,%.2f\n", order.orderId, order.itemId, order.quantity, order.totalCost);
    fclose(file);
}

// Clear input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}
