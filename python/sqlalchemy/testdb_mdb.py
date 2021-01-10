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
    print(Case.__table__.columns.keys())

    db_path = os.path.join(os.path.dirname(__file__), r'..\testdb.mdb')
    engine = sqlalchemy.create_engine(create_connection_uri(db_path))
    
    #session = sqlalchemy.orm.sessionmaker()
    #session.configure(bind=engine)
    #for case in session().query(Case).all():
    #    print(case.id, case.name, case.age, case.case_number)

    session = sqlalchemy.orm.Session(engine)
    for case in session.query(Case).all():
        print(case)

    session.close()
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
# [How can I select all rows with sqlalchemy?](https://stackoverflow.com/questions/2633218/how-can-i-select-all-rows-with-sqlalchemy)
# [Flask-SQLAlchemy how to delete all rows in a single table](https://stackoverflow.com/questions/16573802/flask-sqlalchemy-how-to-delete-all-rows-in-a-single-table)
# [Working with Engines and Connections](https://docs.sqlalchemy.org/en/13/core/connections.html)
# [Insert, Updates, Deletes](https://docs.sqlalchemy.org/en/14/core/dml.html)
# [SQLAlchemy: How do you delete multiple rows without querying](https://stackoverflow.com/questions/39773560/sqlalchemy-how-do-you-delete-multiple-rows-without-querying)
# [How to delete rows from a table using an SQLAlchemy query without ORM?](https://stackoverflow.com/questions/9882358/how-to-delete-rows-from-a-table-using-an-sqlalchemy-query-without-orm)
# [How to clone a sqlalchemy db object with new primary key](https://stackoverflow.com/questions/28871406/how-to-clone-a-sqlalchemy-db-object-with-new-primary-key)
# [sqlalchemy - how to copy deep copy a entry and all its foreign relation](https://stackoverflow.com/questions/44061006/sqlalchemy-how-to-copy-deep-copy-a-entry-and-all-its-foreign-relation)
# [How to duplicate an SQLAlchemy-mapped object the correct way?](https://stackoverflow.com/questions/29039635/how-to-duplicate-an-sqlalchemy-mapped-object-the-correct-way)
# https://gist.github.com/kennyledet/a6281d5ea70c50b5e731
# [How to use make_transient() to duplicate an SQLAlchemy mapped object?](https://stackoverflow.com/questions/30287042/how-to-use-make-transient-to-duplicate-an-sqlalchemy-mapped-object)
# [How to get column names from SQLAlchemy result (declarative syntax)](https://stackoverflow.com/questions/6455560/how-to-get-column-names-from-sqlalchemy-result-declarative-syntax)
# [SQLAlchemy Return All Distinct Column Values](https://stackoverflow.com/questions/22275412/sqlalchemy-return-all-distinct-column-values)
# [Selecting distinct column values in SQLAlchemy/Elixir](https://stackoverflow.com/questions/2175355/selecting-distinct-column-values-in-sqlalchemy-elixir)
# [Query for list of attribute instead of tuples in SQLAlchemy](https://stackoverflow.com/questions/48466959/query-for-list-of-attribute-instead-of-tuples-in-sqlalchemy)
# [SQLAlchemy and scalar values](https://stackoverflow.com/questions/2272917/sqlalchemy-and-scalar-values)
