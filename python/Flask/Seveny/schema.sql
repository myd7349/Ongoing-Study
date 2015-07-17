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

drop table if exists employees;
create table employees (
    user text not null primary key,
    pwd text not null,
    name text not null,
    department text not null,
    role int not null references roles (role)
);
