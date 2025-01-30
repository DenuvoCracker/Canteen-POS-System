# Team

**SAMRIDH RAJ**   RVIT24BCS118
**HRISHIT RAI**   RVIT24BCS097

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
