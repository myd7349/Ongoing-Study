namespace ObjectInspector
{
    using System;
    using System.Diagnostics;

    using FastReport;

    public static class TreeHelper
    {
        public static void Print(Base reportObject)
        {
            Debug.Assert(reportObject != null);
            Print(reportObject, "", true, true);
        }

        private static void Print(Base reportObject, string indent, bool root, bool last)
        {
            Console.Write(indent);

            if (root)
            {
                indent += "  ";
            }
            else if (last)
            {
                Console.Write("└─ ");
                indent += "    ";
            }
            else
            {
                Console.Write("├─ ");
                indent += "│    ";
            }

            if (string.IsNullOrEmpty(reportObject.Name))
                Console.WriteLine($"{reportObject.ClassName}");
            else
                Console.WriteLine($"{reportObject.Name}: {reportObject.ClassName}");

            for (int i = 0; i < reportObject.ChildObjects.Count; ++i)
                Print(reportObject.ChildObjects[i], indent, false, i == reportObject.ChildObjects.Count - 1);
        }
    }
}


// References:
// [How do I print out a tree structure?](https://stackoverflow.com/questions/1649027/how-do-i-print-out-a-tree-structure)
// [print directory tree](https://stackoverflow.com/questions/10655085/print-directory-tree)
// [How to “draw” a Binary Tree in Console?](https://stackoverflow.com/questions/43898440/how-to-draw-a-binary-tree-in-console/43903427)
// [How to print binary tree diagram in Java?](https://stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram-in-java)
