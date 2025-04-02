USE my_shop;

SET @price = 1000;
SELECT @price;

SET @quantity = 3;
SET @total = @price * @quantity;
SELECT @total;

SET @greeting = "안녕하세요";
SELECT @greeting;

SELECT @amount := 1000;

SET @min_price = 10000;
SELECT * FROM orders 
WHERE price < @min_price;

DROP TABLE TOY;

-- 시스템 변수 사용법 : auto_increment
CREATE TABLE toy (
	toy_id INT AUTO_INCREMENT PRIMARY KEY,
    toy_name CHAR(4),
    price INT
);

INSERT INTO toy VALUES (NULL, "하츄핑", 100000);
INSERT INTO toy VALUES (NULL, "피카츄", 80000);

ALTER TABLE toy AUTO_INCREMENT=100;

INSERT INTO toy VALUES (NULL, "시나모롤", 50000);

SET @@auto_increment_increment=3;

INSERT INTO toy VALUES (NULL, "레고", 200000);
INSERT INTO toy VALUES (NULL, "레고2", 200000);
INSERT INTO toy VALUES (NULL, "레고3", 200000);

SELECT * FROM TOY;





