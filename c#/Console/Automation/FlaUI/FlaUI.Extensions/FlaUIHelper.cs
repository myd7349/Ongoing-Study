namespace FlaUI.Extensions
{
    using System;

    using FlaUI.Core.AutomationElements;
    using FlaUI.Core.Conditions;
    using FlaUI.Core.Definitions;
    using FlaUI.Core.Input;
    using FlaUI.Core.Tools;

    using Common;

    public static class FlaUIHelper
    {
        public static AutomationElement[] FindAllChildren(this AutomationElement element, ControlType controlType)
        {
            return element.FindAllChildren(conditionFactory => conditionFactory.ByControlType(controlType));
        }

        public static AutomationElement FindFirstChild(this AutomationElement element, ControlType controlType)
        {
            return element.FindFirstChild(conditionFactory => conditionFactory.ByControlType(controlType));
        }

        public static AutomationElement FindFirstChild(this AutomationElement element, string title, ControlType controlType)
        {
            return element.FindFirstChild(conditionFactory => conditionFactory.By(title, controlType));
        }

        public static AutomationElement FindFirstDescendant(this AutomationElement element, ControlType controlType)
        {
            return element.FindFirstDescendant(conditionFactory => conditionFactory.ByControlType(controlType));
        }

        public static AutomationElement FindFirstDescendant(this AutomationElement element, string title, ControlType controlType)
        {
            return element.FindFirstDescendant(conditionFactory => conditionFactory.By(title, controlType));
        }

        public static ConditionBase By(this ConditionFactory conditionFactory, string title, ControlType controlType)
        {
            return conditionFactory.ByControlType(controlType).And(conditionFactory.ByText(title));
        }

        public static T WaitForElement<T>(Func<T> getter, TimeSpan? timeout = null)
            where T : AutomationElement
        {
            var retry = Retry.WhileNull(getter, timeout);
            if (!retry.Success)
                return null;

            return retry.Result;
        }

        public static AutomationElement FindFirstChild(this AutomationElement element, Predicate<AutomationElement> predicate)
        {
            var controlViewTreeWalker = element.Automation.TreeWalkerFactory.GetControlViewWalker();
            var firstChild = controlViewTreeWalker.GetFirstChild(element);
            if (firstChild == null)
                return null;

            if (predicate(firstChild))
                return firstChild;

            var current = firstChild;
            while (true)
            {
                var next = controlViewTreeWalker.GetNextSibling(current);
                if (next == null)
                    return null;

                if (predicate(next))
                    return next;

                current = next;
            }
        }

        public static AutomationElement LeftClick(this AutomationElement element, bool highlight = true)
        {
            if (highlight)
                element.DrawHighlight();

            var point = element.BoundingRectangle.CentralPoint();

            Mouse.LeftClick(point);

            Wait.UntilInputIsProcessed();

            return element;
        }
    }
}
