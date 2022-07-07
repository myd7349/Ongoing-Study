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

        public bool SupressNotification
        {
            get
            {
                return _supressNotification;
            }
            set
            {
                _supressNotification = value;
                if (_supressNotification == false && _notificationSupressed)
                {
                    OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Reset));
                    _notificationSupressed = false;
                }
            }
        }

        protected override void OnCollectionChanged(NotifyCollectionChangedEventArgs e)
        {
            if (SupressNotification)
            {
                _notificationSupressed = true;
                return;
            }

            base.OnCollectionChanged(e);
        }

        protected override void ClearItems()
        {
            this.CheckReentrancy();
            List<T> oldItems = new List<T>(this);
            Items.Clear();

            this.OnPropertyChanged(new System.ComponentModel.PropertyChangedEventArgs("Count"));
            this.OnPropertyChanged(new System.ComponentModel.PropertyChangedEventArgs("Item[]"));
            this.OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, oldItems, 0));
        }

        private bool _notificationSupressed = false;
        private bool _supressNotification = false;
    }
}

// References:
// [When calling ObservableCollection.Clear OldItems is empty](http://geekswithblogs.net/DavidVallens/archive/2011/04/01/when-calling-observablecollection.clear-olditems-is-empty.aspx)
// [When Clearing an ObservableCollection, There are No Items in e.OldItems](https://stackoverflow.com/questions/224155/when-clearing-an-observablecollection-there-are-no-items-in-e-olditems)
// [Can I somehow temporarily disable WPF data binding changes?](https://stackoverflow.com/questions/10572522/can-i-somehow-temporarily-disable-wpf-data-binding-changes)
// [what is notifycollectionchangedaction reset value](https://stackoverflow.com/questions/4495904/what-is-notifycollectionchangedaction-reset-value)
// [WPF TreeListView Control](https://www.codeproject.com/Articles/30721/WPF-TreeListView-Control)
