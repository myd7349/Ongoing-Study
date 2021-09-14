namespace Common
{
    using System;
    using System.Windows.Automation;

    public static class AutomationHelper
    {
        public static AutomationElement FindFirstChild(this AutomationElement element, Condition condition)
        {
            return element.FindFirst(TreeScope.Children, condition);
        }

        public static AutomationElement FindFirstChild(this AutomationElement element, ControlType controlType)
        {
            return element.FindFirstChild(
                new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
        }

        public static AutomationElement FindFirstChild(this AutomationElement element, string title)
        {
            return element.FindFirstChild(
                new PropertyCondition(AutomationElement.NameProperty, title));
        }

        public static AutomationElement FindFirstChild(this AutomationElement element, string title, ControlType controlType)
        {
            var condition = new AndCondition(
                new PropertyCondition(AutomationElement.NameProperty, title),
                new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
            return element.FindFirstChild(condition);
        }

        public static AutomationElement FindFirstDescendant(this AutomationElement element, Condition condition)
        {
            return element.FindFirst(TreeScope.Descendants, condition);
        }

        public static AutomationElement FindFirstDescendant(this AutomationElement element, ControlType controlType)
        {
            return element.FindFirstDescendant(
                new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
        }

        public static AutomationElement FindFirstDescendant(this AutomationElement element, string title)
        {
            return element.FindFirstDescendant(
                new PropertyCondition(AutomationElement.NameProperty, title));
        }

        public static AutomationElement FindFirstDescendant(this AutomationElement element, string title, ControlType controlType)
        {
            var condition = new AndCondition(
                new PropertyCondition(AutomationElement.NameProperty, title),
                new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
            return element.FindFirstDescendant(condition);
        }

        public static AutomationElementCollection FindAllChildren(this AutomationElement element, Condition condition)
        {
            return element.FindAll(TreeScope.Children, condition);
        }

        public static AutomationElementCollection FindAllChildren(this AutomationElement element, ControlType controlType)
        {
            return element.FindAllChildren(
                new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
        }

        public static AutomationElementCollection FindAllChildren(this AutomationElement element, string title)
        {
            return element.FindAllChildren(
                new PropertyCondition(AutomationElement.NameProperty, title));
        }

        public static AutomationElementCollection FindAllChildren(this AutomationElement element, string title, ControlType controlType)
        {
            var condition = new AndCondition(
                new PropertyCondition(AutomationElement.NameProperty, title),
                new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
            return element.FindAllChildren(condition);
        }

        public static AutomationElementCollection FindAllDescendants(this AutomationElement element, Condition condition)
        {
            return element.FindAll(TreeScope.Descendants, condition);
        }

        public static AutomationElementCollection FindAllDescendants(this AutomationElement element, ControlType controlType)
        {
            return element.FindAllDescendants(
                new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
        }

        public static AutomationElementCollection FindAllDescendants(this AutomationElement element, string title)
        {
            return element.FindAllDescendants(
                new PropertyCondition(AutomationElement.NameProperty, title));
        }

        public static AutomationElementCollection FindAllDescendants(this AutomationElement element, string title, ControlType controlType)
        {
            var condition = new AndCondition(
                new PropertyCondition(AutomationElement.NameProperty, title),
                new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
            return element.FindAllDescendants(condition);
        }

        public static void Invoke(this AutomationElement element)
        {
            bool isInvokePatternAvailable = (bool)
                element.GetCurrentPropertyValue(AutomationElement.IsInvokePatternAvailableProperty);
            if (isInvokePatternAvailable)
            {
                var invokePattern = element.GetCurrentPattern(InvokePattern.Pattern) as InvokePattern;
                invokePattern.Invoke();
            }
            else
            {
                throw new NotImplementedException("Invoke pattern is unvailable for current element.");
            }
        }

        public static void Expand(this AutomationElement element)
        {
            bool isExpandCollapsePatternAvailable = (bool)
                element.GetCurrentPropertyValue(AutomationElement.IsExpandCollapsePatternAvailableProperty);
            if (isExpandCollapsePatternAvailable)
            {
                var expandCollapsePattern = element.GetCurrentPattern(ExpandCollapsePattern.Pattern) as ExpandCollapsePattern;
                if (expandCollapsePattern.Current.ExpandCollapseState == ExpandCollapseState.Collapsed)
                    expandCollapsePattern.Expand();
            }
            else
            {
                throw new NotImplementedException("ExpandCollapse pattern is unvailable for current element.");
            }
        }
    }
}


// References:
// [Invoke method not working on a windows open dialog box](https://stackoverflow.com/questions/58022941/invoke-method-not-working-on-a-windows-open-dialog-box)
