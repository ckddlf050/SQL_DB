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

insert into departments values(1,"교육팀");
insert into departments values(2,"개발팀");

select * from departments;

insert into employee_cascade values
(1,"김다운",1),
(2,"최창일",2);
select * from employee_cascade;

insert into employee_setnull values
(1,"김소은",1),
(2,"이해린",2);
select * from employee_setnull;

delete from departments
where department_id =1;

select * from departments;
select * from employee_cascade;
select * from employee_setnull;


