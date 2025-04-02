SELECT *
FROM customers
	INNER JOIN orders
    ON customers.customer_id = orders.customer_id;
    
SELECT *
FROM customers
	JOIN orders
    ON customers.customer_id = orders.customer_id;
    
SELECT c.customer_id, name, email, order_date, order_status
FROM customers c
	JOIN orders o
    ON c.customer_id = o.customer_id;

SELECT c.customer_id, name, email, order_date, order_status
FROM customers c
	JOIN orders o
    ON c.customer_id = o.customer_id
WHERE order_status IS NOT NULL
ORDER BY order_date DESC;

select * from customers;
select * from orders;
    
    
    
    
    
    
    
    
    
    