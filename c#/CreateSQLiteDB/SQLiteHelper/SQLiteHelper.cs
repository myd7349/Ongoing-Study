// 2016-03-24T15:58+08:00
using System.IO;
using System.Data.SQLite; // Install-Package System.Data.SQLite
using System.Diagnostics.Contracts;

// In Python 3.x, class sqlite3.Connection contains a method named
// 'executescript' which makes it very convenient to create a cursor
// object from a piece of SQL script. I love the way it works, so
// here we go!

namespace SQLiteHelper
{
    public static class SQLiteConnectionHelper
    {
        public static SQLiteConnection ExecuteScript(
            this SQLiteConnection connection,
            string scriptSnippet)
        {
            Contract.Requires(connection.State == System.Data.ConnectionState.Open);
            Contract.Requires(!string.IsNullOrEmpty(scriptSnippet));

            using (SQLiteCommand command = connection.CreateCommand())
            {
                command.CommandText = scriptSnippet;
                command.ExecuteNonQuery();
            }

            return connection;
        }

        public static SQLiteConnection ExecuteScriptFile(
            this SQLiteConnection connection,
            string scriptFilename)
        {
            Contract.Requires(!string.IsNullOrEmpty(scriptFilename));
            Contract.Requires(Directory.Exists(scriptFilename));

            return connection.ExecuteScript(File.ReadAllText(scriptFilename));
        }
    }
}

// References:
// [create sqlite database with c# by using external ramin.sql file](http://stackoverflow.com/questions/13353476/create-sqlite-database-with-c-sharp-by-using-external-ramin-sql-file)
