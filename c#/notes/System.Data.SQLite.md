* [System.Data.SQLite Close() not releasing database file](https://stackoverflow.com/questions/8511901/system-data-sqlite-close-not-releasing-database-file)

* [Why might SQLite insert be very slow? (Transactions used)](https://stackoverflow.com/questions/8339919/why-might-sqlite-insert-be-very-slow-transactions-used)

* [SQLite Insert very slow?](https://stackoverflow.com/questions/3852068/sqlite-insert-very-slow)

* [Is it okay to always leave a database connection open?](https://stackoverflow.com/questions/5474646/is-it-okay-to-always-leave-a-database-connection-open)

* [Does SQLite Connection needs to remain open(connected) to take advantage of Pragma Cache_size?](https://stackoverflow.com/questions/28577577/does-sqlite-connection-needs-to-remain-openconnected-to-take-advantage-of-prag)

  > Both in SQLite and in all other databases, opening a connection has some overhead. Using many short-lived connections is never a good idea.
  >
  > In situations where you do have many independent, short-lived pieces of work (such as a web server), you typically work around these inefficiencies by using connection pooling.

- [How do I list all tables/indices contained in an SQLite database](https://www.sqlite.org/faq.html#q7)

  > SELECT name FROM sqlite_schema
  > WHERE type='table'
  > ORDER BY name;

- [How can I list the tables in a SQLite database file that was opened with ATTACH?](https://stackoverflow.com/questions/82875/how-can-i-list-the-tables-in-a-sqlite-database-file-that-was-opened-with-attach)
