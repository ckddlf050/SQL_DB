use function_db;

select name,birth_date,
	concat(name, "(");
-- 문자열 추출
select product_name,left(product_name,3)from products;

-- substring 지정한 위치의 부분 문자열
select name,substring(name,2,2)
from users;

-- upper 대문자 변환
select name,upper(email) 'upper_name' from users;

-- release 특정 문자열 변경
select name,replace(name,'이',"LEE")  from users;

-- substring_idex
select product_name ,substring_index(product_name," ",1) from products;

-- 실습1 문자열 함수
-- 사용자 이름과 이메일을 결합하여 "홍길동(hong@example.com)" 형식으로 출력하시오.
select name,email,concat(name,"(",email,")") "formated_contact" from users;

-- 실습1-2
-- 이메일 주소에서 도메인(@ 뒤 문자열)만 추출하여 email_domain컬럼으로 출력하시오
select email,substring_index(email,"@",-1) "email_domain" from users;

select email,substring(email,locate('@',email)+1) "email_domain" from users;

-- 실습 1-3 
-- 상품명에서 마지막 단어(공백 기준)를 추출하여 category_keyword컬럼으로 출력하시오
select product_name,substring_index(product_name," ",-1) 'category_keyword' from products;

-- 수학 함수
-- round:반올림 , ceil: 올림, floor: 내림
select round(14.562);
-- 날짜함수
select now();
select CURDATE();
select  DATEDIFF(now(),"2025-03-01");
select DATE_ADD('2025-03-20', interval 7 day );
select date_sub('2025-03-20', interval 7 day );


-- 실습 2.수학 함수, 날짜 함수(1)
--  1. 상품 가격의 평균을 계산하고, 소수 첫째 자리까지 반올림하여 출력하시오.
 -- • 출력 컬럼명: avg_price_rounded
select round(AVG(price),1) "avg_price_rounded" 
from products;

--  2. 최근 7일 이내에 주문된 주문건을 조회하고, 경과일을 출력하시오.
-- • 출력 컬럼명: days_ago
select order_id, created_at,datediff(now(),created_at) "days_ago" 
from orders where datediff(now(),created_at)<=7;

-- 3. 사용자 ID가 홀수이면서, 이름에 '김' 또는 '이'가 포함된 사용자만 조회하시오.
select user_id, name, email from users where mod(user_id,2) = 1  and (left(name,1) = "김" or left(name,1) = "이");

-- 4. 배송완료된 주문 중, 주문일로부터 7일 이상 경과한 주문을 조회하시오
select order_id,order_status,created_at  ,datediff(now(),created_at) "days_since_orderwhere"
from orders
where order_status = "배송완료" and datediff(now(),created_at) >=7;




