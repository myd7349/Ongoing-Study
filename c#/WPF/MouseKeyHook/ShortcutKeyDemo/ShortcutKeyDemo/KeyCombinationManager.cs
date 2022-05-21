using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

using Gma.System.MouseKeyHook;
using Gma.System.MouseKeyHook.Implementation;

using Common;

namespace ShortcutKeyDemo
{
    public class KeyCombinationManager : DisposableBase
    {
        public KeyCombinationManager(
            IKeyboardEvents source = null,
            IEnumerable<KeyValuePair<Combination, Action>> map = null)
        {
            SetSource(source);
            SetKeyCombinationMap(map);
        }

        public void Subscribe()
        {
            if (!subscribed_ &&
                source_ != null &&
                watchlists_ != null)
            {
                source_.KeyDown += OnKeyDown;
                subscribed_ = true;
            }

        }

        public void Unsubscribe()
        {
            if (subscribed_)
            {
                source_.KeyDown -= OnKeyDown;
                subscribed_ = false;
            }
        }

        public void SetSource(IKeyboardEvents source)
        {
            var subscribed = subscribed_;

            Unsubscribe();

            source_ = source;

            if (subscribed)
                Subscribe();
        }

        public void SetKeyCombinationMap(IEnumerable<KeyValuePair<Combination, Action>> map)
        {
            var subscribed = subscribed_;

            Unsubscribe();

            if (map != null)
            {
                watchlists_ = map.GroupBy(k => k.Key.TriggerKey)
                    .ToDictionary(g => g.Key, g => g.ToArray());
            }

            if (subscribed)
                Subscribe();
        }

        protected override void DisposeManaged()
        {
            Unsubscribe();
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            KeyValuePair<Combination, Action>[] element;
            var found = watchlists_.TryGetValue(e.KeyCode, out element);
            if (!found)
                return;

            var state = KeyboardState.GetCurrent();
            Action action = null;
            var maxLength = 0;
            foreach (var current in element)
            {
                var matches = current.Key.Chord.All(state.IsDown);
                if (!matches)
                    continue;
                if (maxLength > current.Key.ChordLength) continue;
                maxLength = current.Key.ChordLength;
                action = current.Value;
            }
            action?.Invoke();
        }

        private IKeyboardEvents source_;
        private Dictionary<Keys, KeyValuePair<Combination, Action>[]> watchlists_;
        private bool subscribed_ = false;
    }
}


// References:
// https://github.com/gmamaladze/globalmousekeyhook/blob/master/MouseKeyHook/KeyCombinationExtensions.cs
