namespace NetMan
{
    using System.Data;

    using FastMember;

    public class NetworkAdaptersModel
    {
        public NetworkAdaptersModel()
        {
            Update("Name", "NetConnectionID", "Index", "AdapterType", "Description", "MACAddress", "IsNetEnabledNull", "NetEnabled");
        }


        public DataTable Results
        {
            get
            {
                return dataTable;
            }
        }

        public void Update(params string[] columns)
        {
            dataTable = new DataTable();
            using (var reader = ObjectReader.Create(NetworkAdapterUtility.EnumerateNetworkAdapters(), columns))
            {
                dataTable.Load(reader);
            }
        }

        private DataTable dataTable;
    }
}
