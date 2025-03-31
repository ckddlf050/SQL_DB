DROP DATABASE IF EXISTS codingon_db;
CREATE DATABASE codingon_db DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

use codingon_db;

create table class (
class_id char(5) primary key not null,
class_name varchar(30) not null,
category varchar(20),
room char(5) not null,
start_date date
);

create table student
(
student_id int auto_increment primary key,
name varchar(20) not null,
age int,
gender enum("남","여"),
class_id char(5) not null ,
join_date date,
FOREIGN KEY (class_id) REFERENCES class(class_id)
ON DELETE CASCADE
ON UPDATE CASCADE
);

SHOW TABLES;
DESC class;


INSERT INTO class (class_id, class_name, category, room, start_date) VALUES
('CLS01', '프론트엔드 12기', '프론트엔드', 'B-101', '2024-01-08'),
('CLS02', '백엔드 8기', '백엔드', 'B-102', '2024-02-05'),
('CLS03', 'AI 엔지니어 3기', 'AI', 'C-201', '2024-03-01'),
('CLS04', '모바일 앱 개발 5기', '모바일', 'A-301', '2024-04-10'),
('CLS05', 'UI/UX 디자인 6기', '디자인', 'D-401', '2024-05-15'),
('CLS06', '데이터 분석 2기', '데이터분석', 'B-201', '2024-06-03'),
('CLS07', '클라우드 인프라 1기', '클라우드', 'E-102', '2024-06-24'),
('CLS08', '게임 프로그래밍 4기', '게임개발', 'G-301', '2024-07-15');

DESC student;
 
INSERT INTO student(name, age, gender, class_id, join_date) VALUES
 ('정국', 25, '남', 'CLS01', '2024-01-08'),
 ('장원영', 21, '여', 'CLS01', '2024-01-09'),
 ('변우석', NULL, '남', 'CLS02', '2024-02-05'),
 ('고윤정', 24, '여', 'CLS02', '2024-02-06'),
 ('안유진', 23, '여', 'CLS03', '2024-03-01'),
 ('이도현', 26, '남', 'CLS03', '2024-03-02'),
 ('박채영', NULL, '여', 'CLS04', '2024-04-10'),
 ('박보검', 29, '남', 'CLS04', '2024-04-11'),
 ('이지은', NULL, '여', 'CLS05', '2024-05-15'),
 ('오해원', 22, '여', 'CLS05', '2024-05-16');


 

