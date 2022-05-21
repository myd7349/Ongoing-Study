using System;

namespace Common
{
    public static class GuidHelper
    {
        public static string ToBase64String(this Guid guid)
        {
            return Convert.ToBase64String(guid.ToByteArray());
        }

        public static string ToUrlFriendlyBase64String(this Guid guid)
        {
            return guid.ToBase64String()
                .Replace("/", "_")
                .Replace("+", "-")
                .TrimEnd('=');
        }
    }
}


// References:
// [Writing C# without allocating ANY memory](https://www.youtube.com/watch?v=B2yOjLyEZk0)
// [Is there any difference between a GUID and a UUID?](https://stackoverflow.com/questions/246930/is-there-any-difference-between-a-guid-and-a-uuid)
// [Guids](https://github.com/StephenCleary/Guids)
