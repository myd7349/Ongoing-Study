// Install-Package Google.Protobuf -Version 3.9.1
// Install-Package Newtonsoft.Json -Version 12.0.2

namespace DataInfo
{
    using static System.Console;

    using pb = Google.Protobuf;
    using Newtonsoft.Json;

    class Program
    {
        static void Main(string[] args)
        {
            var dataMetaInfo = new DataModel.DataMetaInfo
            {
                JobInfo = new DataModel.JobInfo
                {
                    Name = "R&D",
                    Department = "Tech. Department",
                },
                PersonInfo = new DataModel.PersonInfo
                {
                    Name = "Tom",
                    Age = 22,
                    Gender = DataModel.PersonInfo.Types.Gender.Male,
                },
                Channels = 20,
                SamplingRate = 16000,
                DataWidth = DataModel.DataMetaInfo.Types.DataWidth.Custom,
                CustomDataWidth = 6,
            };

            var json = JsonConvert.SerializeObject(dataMetaInfo, Formatting.Indented);
            WriteLine(json);

            var json2 = new pb.JsonFormatter(pb.JsonFormatter.Settings.Default).Format(dataMetaInfo);
            WriteLine(json2);

            var jsonParserSettings = new pb.JsonParser.Settings(10).WithIgnoreUnknownFields(true);
            var dataMetaInfo2 = new pb.JsonParser(jsonParserSettings).Parse<DataModel.DataMetaInfo>(json);
            var json3 = JsonConvert.SerializeObject(dataMetaInfo2, Formatting.Indented);
            WriteLine(json3);
            WriteLine(json == json3);

            ReadKey();
        }
    }
}


// References:
// https://stackoverflow.com/questions/39907232/compiling-proto3-files-in-vs2015-c-sharp-project
// https://stackoverflow.com/questions/49791478/use-protobuf-net-to-convert-json-into-object
// https://damienbod.com/2014/01/09/comparing-protobuf-json-bson-xml-with-net-for-file-streams/
