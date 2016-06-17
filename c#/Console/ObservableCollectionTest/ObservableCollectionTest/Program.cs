// 2016-06-17T14:03+08:00
using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Text;

using Common;

namespace ObservableCollectionTest
{
    class Program
    {
        static void Main(string[] args)
        {
            TestCase2();
            TestCase1();
            TestCase3();

            Util.Pause();
        }

        private static void TestCase1()
        {
            ObservableCollection<int> coll = new ObservableCollection<int>();
            coll.CollectionChanged += OnCollectionChanged1;

            coll.Add(1);
            coll.Add(2);
            coll.Remove(1);

            coll.Clear(); // Reset
        }

        private static void TestCase2()
        {
            ObservableCollection<Person> coll = new ObservableCollection<Person>();
            coll.CollectionChanged += OnCollectionChanged2;

            var eric = new Person("Eric");
            var charles = new Person("Charles");

            coll.Add(eric);
            coll.Add(charles);

            coll.Remove(eric);

            coll.Clear(); // Will Charles say 'goodbye' to us?
        }

        private static void TestCase3()
        {
            ObservableCollectionEx<Person> coll = new ObservableCollectionEx<Person>();
            coll.CollectionChanged += OnCollectionChanged2;

            var eric = new Person("Eric");
            var charles = new Person("Charles");

            coll.Add(eric);
            coll.Add(charles);

            coll.Remove(eric);

            coll.Clear(); // Will Charles say 'goodbye' to us?
        }

        private static void OnCollectionChanged1(object sender, NotifyCollectionChangedEventArgs e)
        {
            Console.WriteLine("========================================");
            Console.WriteLine("Action: " + e.Action.ToString());
            Console.WriteLine("Old Items: " + e.OldItems.ToReadableString());
            Console.WriteLine("New Items: " + e.NewItems.ToReadableString());
        }

        private static void OnCollectionChanged2(object sender, NotifyCollectionChangedEventArgs e)
        {
            switch (e.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    Console.WriteLine(e.NewItems.ToReadableString() + " say(s) hello!");
                    break;
                case NotifyCollectionChangedAction.Remove:
                    Console.WriteLine(e.OldItems.ToReadableString() + " say(s) goodbye!");
                    break;
            }
        }
    }

    public static class IListExtensions
    {
        public static string ToReadableString(this IList coll, string separator = ",",
            string open = "[", string close = "]")
        {
            if (coll == null)
                return "null";

            StringBuilder sb = new StringBuilder();
            sb.Append(open);

            foreach (var item in coll)
            {
                if (item == null)
                    sb.Append("null" + separator);
                else
                    sb.Append(item.ToString() + separator);
            }

            string str = sb.ToString();
            if (str.EndsWith(separator))
                sb.Remove(sb.Length - separator.Length, separator.Length);

            sb.Append(close);

            return sb.ToString();
        }
    }

    class Person
    {
        public Person(string name)
        {
            this.name = name;
        }

        public override string ToString()
        {
            return name;
        }

        private string name;
    }
}
