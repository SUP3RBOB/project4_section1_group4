create database Guberbase;
use Guberbase;

create table UserAccount (
	firstName varchar(40) not null,
    lastName varchar(40) not null,
    email varchar(40) primary key
);

create table CarBooking (
	booking_date DateTime not null,
    destination_address varchar(80) not null,
    coordinates varchar(20) not null,
    user_email varchar(40),
    is_cybertruck bool,
    foreign key (user_email) references UserAccount(email)
);

create table PlaneBooking(
	booking_date DateTime not null,
    destination_address varchar(80) not null,
    coordinates varchar(20) not null,
    user_email varchar(40),
    model varchar(20),
    foreign key (user_email) references UserAccount(email)
)

select count(email)
from UserAccount
where email like 'Email';