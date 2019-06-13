https://www.sqlite.org/datatype3.html
> Note that numeric arguments in parentheses that following the type name (ex: "VARCHAR(255)") are ignored by SQLite - SQLite does not impose any length restrictions (other than the large global SQLITE_MAX_LENGTH limit) on the length of strings, BLOBs or numeric values.

But I found that FluentData version 3.0.1.0 will raise an exception if it thoughts the value is too long.
