-- 트리거
use codingon_store_db;
create table order_logs (
	log_id int auto_increment primary key,
    order_id int,
    log_message varchar(255),
    created_ad datetime default current_timestamp
);
-- 트리거 생성
delimiter //
create trigger trg_after_insert_orders
after insert on orders
for each row
begin
	insert into order_logs (order_id, log_message)
    values (new.order_id, concat("신규 주문이 생성되었습니다. 상태: ", new.order_status));
end //
delimiter ;
-- 주문 생성
insert orders(customer_id, order_date, order_status) values (1, now(), "처리중");
select * from order_logs;

-- 2
use index_db;
create table trigger_table(
	id int,
    txt varchar(10)
);

insert into trigger_table values(1,"르세라핌");
insert into trigger_table values(2,"에스파");
insert into trigger_table values(3,"답퍼플");

create table delete_logs (
	log_id int auto_increment primary key,
    id int,
    log_message varchar(255),
    created_at datetime default current_timestamp
);

delimiter //
create trigger trg_before_delete
before delete on trigger_table
for each row
begin
	insert into delete_logs (id, log_message)
    values (OLD.id, concat("데이터가 삭제되었습니다. 이름: ", OLD.txt));
end; //
delimiter ;

delete from trigger_table where id = 3;
select * from delete_logs;








