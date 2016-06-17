// 2016-06-17T15:49+08:00
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace Common
{
    public class ObservableCollectionEx<T> : ObservableCollection<T>
    {
        public ObservableCollectionEx() : base() { }
        public ObservableCollectionEx(IEnumerable<T> collection) : base(collection) { }
        public ObservableCollectionEx(List<T> list) : base(list) { }

        protected override void ClearItems()
        {
            this.CheckReentrancy();
            List<T> oldItems = new List<T>(this);
            Items.Clear();

            this.OnPropertyChanged(new System.ComponentModel.PropertyChangedEventArgs("Count"));
            this.OnPropertyChanged(new System.ComponentModel.PropertyChangedEventArgs("Item[]"));
            this.OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, oldItems, 0));
        }
    }
}

// References:
// [When calling ObservableCollection.Clear OldItems is empty](http://geekswithblogs.net/DavidVallens/archive/2011/04/01/when-calling-observablecollection.clear-olditems-is-empty.aspx)