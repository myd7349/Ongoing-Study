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
    patient_id = sqlalchemy.Column('ID', sqlalchemy.Integer, primary_key=True)
    name = sqlalchemy.Column('PatientName', sqlalchemy.Text)
    age = sqlalchemy.Column('Age', sqlalchemy.Integer)
    case_number = sqlalchemy.Column('CaseNumber', sqlalchemy.Text)


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
    #    print(case.patient_id, case.name, case.age, case.case_number)

    session = sqlalchemy.orm.Session(engine)
    for case in session.query(Case).all():
        print(case.patient_id, case.name, case.age, case.case_number)


if __name__ == '__main__':
    main()


# References:
# [Python ORM for MS-Access](https://stackoverflow.com/questions/5262387/python-orm-for-ms-access)
# https://github.com/gordthompson/sqlalchemy-access/wiki/Getting-Connected
# https://www.pythoncentral.io/sqlalchemy-orm-examples/
