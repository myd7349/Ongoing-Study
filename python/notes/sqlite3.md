Web Scraping with Python: Collecting Data from the Modern Web
>The connection/cursor model is commonly used in database programming, although some users might find it tricky to differentiate the two at first. The connection is responsible for,well, connecting to the database of course, but also sending the database information,handling rollbacks (when a query or set of queries needs to be aborted and the database needs to be returned to its previous state), and creating new cursor objects.
>
>A connection can have many cursors. A cursor keeps track of certain state information,such as which database it is using. If you have multiple databases and need to write information across all of them, you might have multiple cursors to handle this. A cursor also contains the results of the latest query it has executed. By calling functions on the cursor, such as cur.fetchone() , you can access this information.

In fact, a [sqlite3.Cursor](https://docs.python.org/3/library/sqlite3.html#sqlite3.Cursor.connection) object contains a read-only attribute named `connection` which provides the SQLite database Connection used by the Cursor object.
