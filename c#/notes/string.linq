<Query Kind="Statements" />

("Hello, world!" + '\0').Dump();

var config = new KeyValuePair<string, string>[]
{
    new KeyValuePair<string, string>("IP", "127.0.0.1"),
    new KeyValuePair<string, string>("Port", "80"),
    new KeyValuePair<string, string>("User", ""),
};

var lines = config.Select(kv => string.Format("{0}={1}", kv.Key, kv.Value));
lines.Dump();

var oneLine = string.Join("\0", lines);
oneLine.Dump();

('a' + "\0\0").Dump();

// References:
// [How to convert string to null-terminated one?](https://stackoverflow.com/questions/15929998/how-to-convert-string-to-null-terminated-one)