drop table if exists meals;
create table meals (
    dt date not null primary key,
    dishes text not null,
    soup text,
    description text
);

drop table if exists roles;
create table roles (
    role int primary key,
    description text
);

drop table if exists departments;
create table departments (
    department text not null primary key
);

drop table if exists employees;
create table employees (
    user text not null primary key,
    pwd text not null,
    name text not null,
    department text not null references departments (department),
    role int not null references roles (role)
);

insert into roles values 
(0, 'Administrator account'), 
(1, 'Normal user account');

insert into departments values ('<Unknown>');
