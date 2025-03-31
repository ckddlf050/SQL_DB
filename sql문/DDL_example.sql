DROP DATABASE IF EXISTS my_shop;
CREATE DATABASE my_shop DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

USE my_shop;

-- customer table 생성
CREATE TABLE customer (
	cust_id CHAR(10) NOT NULL PRIMARY KEY,
    cust_name VARCHAR(10) NOT NULL,
    address CHAR(10) NOT NULL,
    phone CHAR(11),
    birth DATE
);

-- orders table 생성
CREATE TABLE orders (
	order_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    cust_id CHAR(10) NOT NULL, 
    prod_name CHAR(6) NOT NULL,
    price INT NOT NULL,
    amount SMALLINT NOT NULL,
    FOREIGN KEY (cust_id) REFERENCES customer(cust_id)
	ON DELETE CASCADE
	ON UPDATE CASCADE
);

SHOW TABLES;
DESC customer;
DESC orders;

-- 제약조건을 확인하는 쿼리
SELECT CONSTRAINT_NAME
FROM information_schema.KEY_COLUMN_USAGE
WHERE TABLE_NAME = 'orders';

-- ALTER로 FK 추가
-- ALTER TABLE orders ADD CONSTRAINT fk_customer
-- FOREIGN KEY (cust_id) REFERENCES customer(cust_id)
-- ON DELETE CASCADE
-- ON UPDATE CASCADE;

-- FK 삭제
-- ALTER TABLE orders DROP FOREIGN KEY orders_ibfk_1;

-- 인덱스에서 FK지우기
-- ALTER TABLE orders
-- DROP INDEX cust_id;

DESC orders;
