using System;
using System.Collections.Generic;

using Gma.System.MouseKeyHook;

namespace ShortcutKeyDemo
{
    public static class KeyCombinationExtension
    {
        public static KeyCombinationManager OnCombination(
            this IKeyboardEvents source,
            IEnumerable<KeyValuePair<Combination, Action>> map, bool subscribe)
        {
            var manager = new KeyCombinationManager(source, map);
            if (subscribe)
                manager.Subscribe();

            return manager;
        }
    }
}


// References:
// https://github.com/gmamaladze/globalmousekeyhook/blob/master/examples/ConsoleHook/DetectCombinations.cs
