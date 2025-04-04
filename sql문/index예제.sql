USE index_db;
CREATE TABLE table1 (
	col1 INT PRIMARY KEY,
    col2 INT,
    col3 INT
);
SHOW INDEX FROM table1;
CREATE TABLE table2 (
	col1 INT PRIMARY KEY,
    col2 INT UNIQUE,  -- 테이블에 UNIQUE 넣으면 자동으로 보조형 인덱스가 생성됨
    col3 INT UNIQUE
);
SHOW INDEX FROM table2;

create table cluster(
mem_id char(8),
mem_name varchar(20)

);

INSERT INTO cluster VALUES('NMX', '엔믹스');
INSERT INTO cluster VALUES('LSR', '르세라핌');
INSERT INTO cluster VALUES('IVE', '아이브');
INSERT INTO cluster VALUES('BBZ', '베이비몬스터');
INSERT INTO cluster VALUES('GID', '(여자)아이들');
INSERT INTO cluster VALUES('TRP', '트리플에스');
INSERT INTO cluster VALUES('ESP', '에스파');
INSERT INTO cluster VALUES('BLK', '블랙핑크');
INSERT INTO cluster VALUES('QWR', 'QWER');
INSERT INTO cluster VALUES('ILL', '아일릿');

select * from cluster;

alter table cluster add  constraint
primary key (men_id);	-- 기본키는 자동으로 알파벳 순

select * from cluster;

create table second(
mem_id char(8),
mem_name varchar(20)

);

INSERT INTO second VALUES('NMX', '엔믹스');
INSERT INTO second VALUES('LSR', '르세라핌');
INSERT INTO second VALUES('IVE', '아이브');
INSERT INTO second VALUES('BBZ', '베이비몬스터');
INSERT INTO second VALUES('GID', '(여자)아이들');
INSERT INTO second VALUES('TRP', '트리플에스');
INSERT INTO second VALUES('ESP', '에스파');
INSERT INTO second VALUES('BLK', '블랙핑크');
INSERT INTO second VALUES('QWR', 'QWER');
INSERT INTO second VALUES('ILL', '아일릿');

alter table second add  constraint
unique (men_id);	-- 기본키는 자동으로 알파벳 순

select * from second;

select * from member;

create index idx_member_addr
	on member(addr);
    
show index from member;
analyze table member;
show table status like 'member' ;
DROP INDEX idx_member_name ON member;
create index idx_member_name
on member(mem_name);

show index from member;

select mem_id,mem_name,addr from member
where mem_name = "블랙핑크";

select mem_id,mem_name,mem_number from member
where mem_number >=7 ;

-- drop 삭제
drop index idx_member_num on member;







