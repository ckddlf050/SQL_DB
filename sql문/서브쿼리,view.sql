-- where절 서브쿼리
use codingon_store_db;


select name,price
from products
where Price>(select avg(price) from products);

-- FROM절 서브쿼리
-- 카테고리별 평균 가격을 구하고, 평균이 100,000원 이상인 카테고리만 출력

select category,avg_price
from(
	select category,avg(price) avg_price
	from products
		group by category
) category_products
where avg_price >30000;

-- select 절 서브쿼리
-- 각 고객의 이름과 해당 고객의 총 주문 수를 함께 출력
select name,
	(select count(*)
		from orders
		where customer_id = customers.customer_id
    ) order_count
from customers;

-- 실습1. 서브쿼리연습하기(1)
-- 카테고리가 '전자기기'인 상품 중, 가장 가격이 높은 상품의 이름과 가격을 조회하시오.
select name,price
from products
where category = "전자기기" and price = (select max(price) from products where category = "전자기기"); 

-- 2 결제가 '신용카드'로 이루어진 주문을 한 고객의 이름과 ID를 조회하시오
select name ,customer_id
from customers
where customer_id in (select customer_id from orders where payment_method = "신용카드");

-- 3. 1회 이상 주문한 고객 중 가장 최근에 주문한 고객의 이름과 주문일을 출력하시오

select name,order_date
from customers c
	join orders o on c.customer_id = o.customer_id
where order_date = (
select max(order_date) from orders
);

-- 4 서브쿼리를 사용하여, 주문별 총 결제 금액(수량 ×단가 ×할인 반영 합계)이 30만 원 이상인 주문의 주문 ID와 금액을 출력하시오
-- • total_price는 정수형으로 출력(출력 예시 참조)
-- • 할인율은 (1 -discount_rate/ 100)로 계산
select order_id,total_price
from(
	select order_id,
    round(sum(quantity*unit_price*(1-discount_rate/100))) total_price
	from order_items
	group by order_id
) sub
where total_price >= 300000;

-- 뷰 생성및 조회

create view v_customers as
	select customer_id, name from customers;

select customer_id, name from customers;
select * from v_customers;


