use codingon_store_db;
-- 외부조인
select c.customer_id,name,email,order_date,order_status 
from customers c
	join orders o
	on c.customer_id=o.customer_id;
-- 왼쪽 외부조인
select c.customer_id,name,email,order_date,order_status 
from customers c
	left join orders o
	on c.customer_id=o.customer_id;
-- 오른쪽 외부조인
select c.customer_id,name,email,order_date,order_status 
from customers c
	right join orders o
	on c.customer_id=o.customer_id;
-- FULL OUTER 조인
-- union
select c.customer_id,name,email,order_date,order_status 
from customers c
	left join orders o
	on c.customer_id=o.customer_id
union
select c.customer_id,name,email,order_date,order_status 
from customers c
	right join orders o
	on c.customer_id=o.customer_id;
    
-- 어떤 고객이 
-- 어떤 주문을 했으며(주문 id)
-- 어떤 상품을 주문했고(상품id)
-- 몇개 샀고 (수령)
-- 상품의 이름은 무었이며 
-- 얼마에 샀는가
    
select c.name, o.order_id,p.product_id,p.name,oi.quantity,p.price
from customers c
	join orders o on c.customer_id = o.order_id
    join order_items oi on o.order_id = oi.order_id
	join products p on oi.product_id = p.product_id;
    
    
-- cross join

use codingon_db;

select * from class
cross join student;

-- self join
select e.name,m.name 
from employees e
	left join employees m 
    on e.manager_id = m.employee_id;

-- 실습2.join 연습하기 
-- 1
select c.name,o.order_date
from customers c
	join orders o 
    on c.customer_id = o.customer_id;
    
-- 2
select c.name
from customers c
	left join orders o 
    on c.customer_id = o.customer_id
where o.customer_id is null;

-- 3
select c.name,o.order_id
from customers c
	left join orders o 
    on c.customer_id = o.customer_id;

-- 4 
select c.name,p.name
from customers c
	cross join products p;
    
-- 5
select e.name, m.name
from employees e
	left join employees m
    on e.manager_id = m.employee_id;

-- 6 
select c.name,o.order_date
from customers c
	left join orders o 
    on c.customer_id = o.customer_id
union
select c.name,o.order_date
from customers c
	right join orders o 
    on c.customer_id = o.customer_id;
    
-- 7
select p.name "product_name",sum(oi.quantity) "total_quantity"
from order_items oi
	join products p on p.product_id = oi.product_id
where unit_price is not null
group by p.name;

-- 8
select c.name 'customer_name',p.name 'product_name',oi.quantity,oi.unit_price
from customers c
	join orders o on c.customer_id = o.customer_id
    join order_items oi on o.order_id = oi.order_id
    join products p on oi.product_id = p.product_id
where unit_price is not null;






