namespace GetWeChatGroupMembers
{
    class GroupMember
    {
        public GroupMember(string name, string nickName)
        {
            Name = name;
            NickName = nickName;
        }

        public string Name { get; private set; }

        public string NickName { get; private set; }
    }
}
