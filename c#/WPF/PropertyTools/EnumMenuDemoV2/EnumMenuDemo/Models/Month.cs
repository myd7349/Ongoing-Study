using System.ComponentModel;

namespace EnumMenuDemo.Models
{
    public enum Month
    {
        [Description("Jan")]
        January,

        [Description("Feb")]
        February,

        [Description("Mar")]
        March,

        [Description("Apr")]
        April,

        [Description("May")]
        May,

        [Description("Jun")]
        June,

        [Description("Jul")]
        July,

        [Description("Aug")]
        August,

        [Description("Sep")]
        September,

        [Description("Oct")]
        October,

        [Description("Nov")]
        November,

        [Description("Dec")]
        December,
    }
}
