UPDATE student 
SET age = 26
WHERE name = '정국';
	
UPDATE student
SET age = age + 1
WHERE class_id = "CLS01" and age < 25;

DELETE FROM class
WHERE room LIKE "G%";

DELETE FROM student
WHERE join_date < "2024-03-01";

select * from class;
select * from student;