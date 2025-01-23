# Canteen POS System with Role Management

This project is a **Canteen Point of Sale (POS) System** implemented in C. It provides an efficient way to manage menu items, process customer orders, handle payments, and track stock levels. The system includes role-based access control, allowing functionality tailored to **Managers** and **Cashiers**.

## Features

### Manager Functions
- **Display Menu**: View all menu items, including prices and stock levels.
- **Add Menu Items**: Add new items to the menu.
- **Restock Items**: Update the stock of menu items.
- **Low Stock Alerts**: Automatically detect and replenish items with stock below a threshold.
- **Role-Based Access**: Secured with a password for manager access.

### Cashier Functions
- **Process Orders**: Record customer orders and reduce stock accordingly.
- **Generate Bills**: Display order summaries with total costs.
- **Cash Payment Handling**: Calculate change and validate cash transactions.

### Additional Features
- **Persistent Storage**:
  - Menu data is stored in `menu.txt`.
  - Order history is recorded in `orders.txt`.
- **Automatic Stock Replenishment**: Automatically adds stock when items fall below a threshold.
- **Interactive CLI**: User-friendly command-line interface for menu management and order processing.

## Usage

### Compilation and Execution
1. Compile the program:
   ```bash
   gcc -o canteenpos canteenpossystem002.c
Run the executable:
bash
Copy
Edit
./canteenpos
Roles and Login
Manager:
Enter the role as Manager.
Use the password: admin123.
Cashier:
Enter the role as Cashier (no password required).
Exit:
Type Exit to terminate the program.
Manager Menu Options
Display the menu.
Add menu items.
Restock items.
Check for low stock (auto-replenishment included).
Logout.
Cashier Menu Options
Display the menu.
Process customer orders.
Generate a bill for processed orders.
Logout.
File Structure
menu.txt: Stores menu items in the format:
php
Copy
Edit
<ID>,<Item Name>,<Price>,<Stock>
orders.txt: Logs orders in the format:
mathematica
Copy
Edit
<Order ID>,<Item ID>,<Quantity>,<Total Cost>
System Design
Stock Management
Items with stock below LOW_STOCK_THRESHOLD (default: 5) are flagged.
Automatically replenishes stock by AUTO_REPLENISH_AMOUNT (default: 20).
Payment Processing
Accepts cash payments and calculates change.
Ensures cash provided is sufficient to cover the total cost.
Data Persistence
Menu and order data are saved to files for future use.
The system loads the menu on startup.
Code Overview
main(): Entry point; loads menu and handles login.
Role Management:
managerFunctions()
cashierFunctions()
Core Functions:
displayMenu()
addMenuItem()
restockItem()
processOrder()
generateBill()
File Operations:
loadMenuFromFile()
saveMenuToFile()
saveOrderToFile()
Example Usage
Adding a Menu Item (Manager)
Login as Manager.
Select "Add Menu Item".
Enter item details:
makefile
Copy
Edit
Name: Coffee
Price: 2.5
Stock: 50
Item is added successfully and saved to menu.txt.
Processing an Order (Cashier)
Login as Cashier.
Select "Process Order".
Enter order details:
mathematica
Copy
Edit
Order ID: 101
Item ID: 1
Quantity: 2
Confirm cash payment:
yaml
Copy
Edit
Total Cost: 5.0
Cash Given: 10.0
Change returned and order logged in orders.txt.
Future Enhancements
Add support for multiple payment methods.
Implement graphical user interface (GUI).
Add analytics and sales reporting.
