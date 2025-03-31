-- 1.select 기본 문법
use codingon_db;
-- 전체 출력
select * from codingon_db.class;
select * from codingon_db.student;
-- 선택한 컬럼만 출력 
select class_name,category from class;
select name, age,gender from student;

-- alias(별칭)
select name,age,gender as 성별 from student;
select class_name 반이름, category 분류 from class;

-- 2조건지정 where

select *from student where name = "이지은";
select *from student where student_id = 10;
select name,age from student where age >=25;
select name ,age from student where age >= 25 and age <=27;
select name,age from student where age between 25 and 27;
select name,age from student where age >27 or age <22;

-- 정렬
select name,age from student order BY age;
select class_id, class_name,start_date from class order BY class_name desc;

select class_id, class_name,start_date from class where category like "%엔드%" order BY class_name desc;
-- 여러기준 정렬
select name,gender from student order by gender desc ,name;

-- LIMIT
select * from student limit 3;

-- 가장최근 3개
select class_id,class_name,start_date from class order by start_date desc limit 1,2;
select name,age from student where age is null;

select distinct gender from student;
-- 1
select name,gender from student where age >=25;
-- 2
select distinct class_id from student;
-- 3
select name, age from student where gender = "남" order by age;
-- 4
select name,class_id from student where name like "이%"; 
-- 5 
select * from student where age is null;
-- 6
select *from student where join_date between "2024-03-01" and "2024-04-30";
-- 7
select * from class order by start_date desc limit 3;
-- 8
select name from student 
where (class_id="CLS01"or class_id="CLS02"or class_id="CLS03") and 
(name like "%정%" or name like "%영%") order by name;

-- 6.group by,having
use my_shop;
select cust_id,amount from orders order by cust_id;
select cust_id "고객 아이디",sum(amount) "총 구매 개수" from orders group by cust_id;
select cust_id "고객 아이디",sum(amount*price) "총 구매 금액" from orders group by cust_id;

select cust_id "고객 아이디",avg(amount) "평균 구매 개수" from orders group by cust_id;
select count(*) from customer;

use codingon_db;
select count(*) "나이가 입력된 수" from student where age is not null;

select cust_id "고객 아이디",sum(price * amount) "총 구매 금액" 
from orders 
group by cust_id
having sum(price * amount) >40000
order by sum(price * amount) desc;

use codingon_db;
-- 실습 3 
-- 1
select class_id, count(*) "student_count" from student group by class_id;
-- 2
select gender,avg(age) "avg_age" from student group by gender;
-- 3
select gender,avg(age) "avg_age" from student group by gender having avg(age)>=26;
-- 4
select class_id,min(join_date) "first_join" from student group by class_id;
-- 5
select class_id,min(age) "min_age" from student group by class_id having min(age) >=25;
-- 6 
select gender,max(age)-min(age) "age_gap" from student group by gender having max(age)-min(age) >=3;
-- 7
select class_id,avg(age) "avg_age" from student group by class_id having avg(age)>=24 order by avg(age) desc;

