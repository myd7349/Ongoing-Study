// 2016-03-24T11:58+08:00
using System;
using System.IO;
using System.Data.SQLite;

using Common;
using SQLiteHelper;

// Create a sqlite3 database from an external sql script file.

// TODO: Extended commandline options support.

class Program
{
    static void Main(string[] args)
    {
        if (args.Length < 2)
        {
            string usage = "Usage: {0} sql-script-file target-db-filename";
            Console.WriteLine(usage, Util.GetProgName());
            return;
        }

        string sqlScriptFile = args[0];
        string targetDBFile = args[1];

        string connectionStr = $"Data Source={targetDBFile};Version=3;";

        SQLiteConnection.CreateFile(targetDBFile);
        using (SQLiteConnection connection = new SQLiteConnection(connectionStr))
        {
            connection.Open();
            connection.ExecuteScriptFile(sqlScriptFile);
        }

        Util.Pause();
    }
}

// References:
// [Create SQLite Database and table](http://stackoverflow.com/questions/15292880/create-sqlite-database-and-table)
// [SQLite connection strings](http://www.connectionstrings.com/sqlite/)

