# -*- coding: utf-8 -*-

# pip install sqlalchemy sqlalchemy-access

import os.path
import urllib

import sqlalchemy
import sqlalchemy.ext.declarative
import sqlalchemy.orm


Base = sqlalchemy.ext.declarative.declarative_base()


class Case(Base):
    __tablename__ = 'Case'

    id = sqlalchemy.Column('ID', sqlalchemy.Integer, primary_key=True, autoincrement=True)
    name = sqlalchemy.Column('PatientName', sqlalchemy.String(255))
    age = sqlalchemy.Column('Age', sqlalchemy.Integer)
    case_number = sqlalchemy.Column('CaseNumber', sqlalchemy.String(255), nullable=False)

    studies = sqlalchemy.orm.relationship('Data', backref='case')
    
    def __repr__(self):
        return f"Case('{self.id}', '{self.name}', {self.age}, '{self.case_number}')\n\t{self.studies}"


class Data(Base):
    __tablename__ = 'Data'

    id = sqlalchemy.Column('ID', sqlalchemy.Integer, primary_key=True, autoincrement=True)
    case_number = sqlalchemy.Column('CaseNumber', sqlalchemy.String(255), sqlalchemy.ForeignKey(Case.case_number))
    description = sqlalchemy.Column('Description', sqlalchemy.String(255))
    study_date = sqlalchemy.Column('StudyDate', sqlalchemy.String(255))
    study_time = sqlalchemy.Column('StudyTime', sqlalchemy.String(255))
    
    #case = sqlalchemy.orm.relation('Case',
    #                               backref=sqlalchemy.orm.backref('studies', uselist=True, cascade='delete,all'))
    
    def __repr__(self):
        return f"Data('{self.id}', '{self.case_number}', {self.description}, '{self.study_date}', '{self.study_time}')"


CONNECTION_STRING_FORMAT = 'DRIVER={{Microsoft Access Driver (*.mdb)}};DBQ={0};UID=admin;PWD=;'


def create_connection_string(db_path):
    return CONNECTION_STRING_FORMAT.format(db_path)


def create_connection_uri(db_path):
    connection_string = create_connection_string(db_path)
    return f"access+pyodbc:///?odbc_connect={urllib.parse.quote_plus(connection_string)}"


def main():
    db_path = os.path.join(os.path.dirname(__file__), r'..\testdb.mdb')
    engine = sqlalchemy.create_engine(create_connection_uri(db_path))
    
    #session = sqlalchemy.orm.sessionmaker()
    #session.configure(bind=engine)
    #for case in session().query(Case).all():
    #    print(case.id, case.name, case.age, case.case_number)

    session = sqlalchemy.orm.Session(engine)
    for case in session.query(Case).all():
        print(case)
    
    engine.dispose()


if __name__ == '__main__':
    main()


# References:
# [Python ORM for MS-Access](https://stackoverflow.com/questions/5262387/python-orm-for-ms-access)
# https://github.com/gordthompson/sqlalchemy-access/wiki/Getting-Connected
# https://www.pythoncentral.io/sqlalchemy-orm-examples/
# [Basic Relationship Patterns](https://docs.sqlalchemy.org/en/13/orm/basic_relationships.html)
# [sqlalchemy : Could not determine join condition between parent/child tables](https://stackoverflow.com/questions/45406332/sqlalchemy-could-not-determine-join-condition-between-parent-child-tables)
# [Association Proxy](https://docs.sqlalchemy.org/en/13/orm/extensions/associationproxy.html#simplifying-association-objects)
# [Flask and SQLalchemy NoForeignKeysError](https://stackoverflow.com/questions/34234964/flask-and-sqlalchemy-noforeignkeyserror-could-not-determine-join-condition-betw)
# [sqlalchemy foreign key relationship attributes](https://stackoverflow.com/questions/18807322/sqlalchemy-foreign-key-relationship-attributes)
# [sqlalchemy.exc.InvalidRequestError: One or more mappers failed to initialize](https://stackoverflow.com/questions/63005317/sqlalchemy-exc-invalidrequesterror-one-or-more-mappers-failed-to-initialize)
# [Could not assemble any primary key columns for mapped table](https://stackoverflow.com/questions/24872541/could-not-assemble-any-primary-key-columns-for-mapped-table)
# [SQLAlchemy multiple foreign keys in one mapped class to the same primary key](https://stackoverflow.com/questions/22355890/sqlalchemy-multiple-foreign-keys-in-one-mapped-class-to-the-same-primary-key)
# [Clean-up database connection with SQLAlchemy in Pandas](https://stackoverflow.com/questions/51170169/clean-up-database-connection-with-sqlalchemy-in-pandas)
