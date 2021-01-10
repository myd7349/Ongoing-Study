import pprint

import pyodbc


def main():
    pprint.pprint(pyodbc.drivers())


if __name__ == '__main__':
    main()


# References:
# [Pyodbc error Data source name not found and no default driver specified paradox](https://stackoverflow.com/questions/32662123/pyodbc-error-data-source-name-not-found-and-no-default-driver-specified-paradox)
