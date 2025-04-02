DROP DATABASE IF EXISTS codingon_store_db;
CREATE DATABASE codingon_store_db DEFAULT CHARACTER SET utf8mb4
COLLATE utf8mb4_unicode_ci;

USE codingon_store_db;

CREATE TABLE customers (
	customer_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, 
	name VARCHAR(50) NOT NULL, 
	email VARCHAR(100),
	city VARCHAR(50), 
	phone VARCHAR(20), 
	birth_date DATE, 
	membership_level VARCHAR(20)
);

CREATE TABLE orders (
	order_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT NOT NULL,
    order_date DATE,
    order_status VARCHAR(20),
    payment_method VARCHAR(30),
    delivery_fee INT DEFAULT 0,
    
    CONSTRAINT cust_fk
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

CREATE TABLE products (
	product_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100),
    price INT,
    stock_quantity INT,
    category VARCHAR(50),
    manufacturer VARCHAR(50)
);

CREATE TABLE order_items (
	order_item_id INT PRIMARY KEY AUTO_INCREMENT,
    quantity INT NOT NULL,
    unit_price INT,
    discount_rate DECIMAL(5,2),
    order_id INT,
    product_id INT,
    
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);

CREATE TABLE employees (
	employee_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL,
    hire_date DATE,
    department VARCHAR(50),
    position VARCHAR(50),
    manager_id INT,
    
    FOREIGN KEY (manager_id) REFERENCES employees(employee_id)
)




















