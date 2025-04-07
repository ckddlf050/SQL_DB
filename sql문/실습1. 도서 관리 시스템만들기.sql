-- 실습1. 도서 관리 시스템 만들기
-- 도서 관리 시스템은 도서, 회원, 대여 내역을 관리하는 시스템을구축합니다구현할 기능은 다음과 같습니다:
-- • 데이터 베이스 만들기 DB 이름: book_management_db
-- • 도서 등록, 수정, 삭제
-- • 회원 가입, 조회, 탈퇴
-- • 도서 대여 및 반납
-- • 대여 현황 조회

drop database if exists book_management_db;
create database book_management_db;
use book_management_db;

create table books (
	book_id int AUTO_INCREMENT primary key,
    title varchar(200),
    author varchar(100),
    published_at date,
    price int,
    status enum('대여가능','대여중')
);

create table members (
	member_id int AUTO_INCREMENT primary key,
    name varchar(100),
    email varchar(150),
    phone varchar(20),
    registered_at datetime
);

create table rentals (
	rental_id int AUTO_INCREMENT primary key,
    book_id int,
    member_id int,
	rented_at datetime,
    returned_at datetime,
    FOREIGN KEY (book_id) REFERENCES books(book_id) ON DELETE CASCADE,
    FOREIGN KEY (member_id) REFERENCES members(member_id) ON DELETE CASCADE
);