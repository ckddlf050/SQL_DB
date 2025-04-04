use codingon_store_db;

create view v_cusomers as 
select customer_id, name from customers;

select * from v_customers;

-- view 수정 
create OR replace view v_customer_orders as
select c.name 이름, o.order_id 주문아이디,o.order_Date 주문일
from customers c
join orders o on c.customer_id = o.customer_id;

alter view v_customer_orders as
select c.name 이름,email 이메일, o.order_id "주문 아이디",o.order_Date 주문일 -- 띄어쓰기는  "" 묶어서 사용
from customers c
join orders o on c.customer_id = o.customer_id;

select * from v_customer_orders;

-- select 유의사항
select `주문 아이디` from v_customer_orders; -- 탭 위에 `` 로 감싸기

-- 뷰의 구조 및 정의 확인
desc v_customer_orders;
show create view v_customer_orders;

-- veiw로 데이터 입력
create OR replace view v_customers as 
select customer_id,name from customers
where customer_id < 20
with check option;

update v_customers
set name = "홍길남"
where customer_id = 1;

select * from v_customers;
select * from customers;

insert into v_customers(customer_id,name)
values (10,"텍스티");

-- view 삭제
drop view v_customers;

select * from v_customers;

-- 실습2. VIEW 연습하기
-- 고객 주문 내역을 나타내는 v_order_summary 뷰를 생성하세요.
-- • 포함할 컬럼: customer_id, customer_name, product_name, quantity, order_date
-- • 사용해야 할 테이블: customers, orders, order_items, products
create view v_order_summary as
select c.customer_id, c.name customer_name , p.name product_name, quantity, order_date
from customers c
	join orders o on c.customer_id = o.customer_id
	join order_items oi on o.order_id = oi.order_id
	join products p on oi.product_id = p.product_id;

-- 실습2-2. 생성한 뷰를 조회하여 고객 이름과 주문일 기준으로 정렬해보세요. 주문일은 내림차순으로 정렬합니다
select * from v_order_summary order by customer_name, order_date desc;

-- 3. Step 3. 뷰에 order_status 컬럼을 추가한 후, 주문 상태가 '완료'인 주문만 포함되도록 뷰를 수정하세요.
-- • 최종 컬럼 구성: customer_id, customer_name, product_name, quantity, order_date, order_status
alter view v_order_summary as
select c.customer_id, c.name customer_name , p.name product_name, quantity, order_date,order_status
from customers c
	join orders o on c.customer_id = o.customer_id
	join order_items oi on o.order_id = oi.order_id
	join products p on oi.product_id = p.product_id
where order_status = "완료"
order by customer_id;

select * from v_order_summary;

-- FK 연습
drop database if exists test_db;
create database test_db;
use test_db;

create table departments (
	department_id int primary key,
    department_name varchar(50)
);

create table employee_cascade(
	employee_id int primary key,
    name varchar(50),
    department_id int,
    
    constraint cascade_fk
    foreign key(department_id)
    references departments(department_id)
    on delete cascade 
);

create table employee_setnull(
	employee_id int primary key,
    name varchar(50),
    department_id int,
    
    constraint setnull_fk
    foreign key(department_id)
    references departments(department_id)
    on delete set null
);



