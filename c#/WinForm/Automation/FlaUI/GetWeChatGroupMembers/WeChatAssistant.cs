#define USING_UIA3

namespace GetWeChatGroupMembers
{
    using System;
    using System.Diagnostics;
    using System.Linq;

    using FlaUI.Core;
    using FlaUI.Core.AutomationElements;
    using FlaUI.Core.Definitions;
#if USING_UIA3
    using FlaUI.UIA3;
#else
    using FlaUI.UIA2;
#endif

    using FlaUI.Extensions;

    class WeChatAssistant : IDisposable
    {
        public WeChatAssistant()
        {
            var wechatProcess = Process.GetProcessesByName("WeChat").FirstOrDefault();
            if (wechatProcess == null)
                throw new Exception("WeChat is not running.");

            Application = Application.Attach(wechatProcess.Id);

#if USING_UIA3
            automation_ = new UIA3Automation();
#else
            automation_ = new UIA2Automation();
#endif

            MainWindow = Application.GetMainWindow(automation_, TimeSpan.FromSeconds(3));
            if (MainWindow == null)
                throw new Exception("Could not find WeChat main window.");
        }

        public Application Application
        {
            get;
            private set;
        }

        public Window MainWindow
        {
            get;
            private set;
        }

        public AutomationElement[] GetChatListElements()
        {
            MainWindow.SetForeground();
            MainWindow.WaitUntilClickable();

            var chatButton = MainWindow.FindFirstDescendant("聊天", ControlType.Button).AsButton();
            if (chatButton == null)
                throw new Exception("Could not find chat button.");

#if false
            chatButton.DrawHighlight();
            chatButton.Invoke(); // Doesn't work for me.
#else
            chatButton.LeftClick();
#endif

            var chatList = FlaUIHelper.WaitForElement(
                () => MainWindow.FindFirstDescendant("会话", ControlType.List));
            if (chatList == null)
                throw new Exception("Could not find chat list.");

            chatList.DrawHighlight();

            return chatList.FindAllChildren();
        }

        public Tuple<AutomationElement, AutomationElement>[] GetGroupMemberElements(AutomationElement group)
        {
            group.LeftClick();

            var groupPane = FlaUIHelper.WaitForElement(
                () => MainWindow.FindFirstByXPath("/Pane[2]/Pane[2]/Pane[3]/Pane/Pane/Pane/Pane"));
            if (groupPane == null)
                throw new Exception("Could not find group pane.");

            groupPane.DrawHighlight();

            var groupInformationButton = groupPane.FindFirstDescendant("聊天信息", ControlType.Button);
            if (groupInformationButton == null)
                throw new Exception("Could not find group information button.");

            groupInformationButton.LeftClick();

            var groupInformationWindow = FlaUIHelper.WaitForElement(
                () => MainWindow.FindFirstChild("聊天信息", ControlType.Window));
            if (groupInformationWindow == null)
                throw new Exception("Could not find group information window.");

            groupInformationWindow.DrawHighlight();

            var showMoreGroupMembersButton = groupInformationWindow.FindFirstDescendant(
                "查看更多群成员", ControlType.Button);
            if (showMoreGroupMembersButton != null)
                showMoreGroupMembersButton.LeftClick();

            var memberList = FlaUIHelper.WaitForElement(
                () => groupInformationWindow.FindFirstDescendant("聊天成员", ControlType.List));
            if (memberList == null)
                throw new Exception("Could not find member list.");

            memberList.DrawHighlight();

            var groupMemberElements = memberList.FindAllDescendants(
                conditionFactory => conditionFactory.ByControlType(ControlType.Button));
            return groupMemberElements
                .Where((e, i) => i % 2 == 0)
                .Zip(
                    groupMemberElements.Where((e, i) => i % 2 != 0),
                    (a, b) => Tuple.Create(a, b)
                )
                .Where((member, i) => !IsAddOrDeleteButton(member, i))
                .ToArray();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private bool IsAddOrDeleteButton(Tuple<AutomationElement, AutomationElement> groupMember, int i)
        {
            return i < 2 && groupMember.Item1.Name == string.Empty &&
                (groupMember.Item2.Name == "添加" || groupMember.Item2.Name == "删除");
        }

        private void Dispose(bool disposing)
        {
            if (disposed_)
                return;

            if (disposing)
            {
                automation_.Dispose();
                Application.Dispose();
            }

            disposed_ = true;
        }

        private bool disposed_ = false;
#if USING_UIA3
        private UIA3Automation automation_;
#else
        private UIA2Automation automation_;
#endif
    }
}


// References:
// [Adding checkbox controls to list box](https://stackoverflow.com/questions/20581272/adding-checkbox-controls-to-list-box)
// [InvokedEvent doesn't work properly](https://github.com/FlaUI/FlaUI/issues/76)
// [How can I do click Windows form MessageBox ok button](https://github.com/FlaUI/FlaUI/issues/255)
// [Unable to select Save as from IE download notification bar](https://github.com/FlaUI/FlaUI/issues/296)
// [GetClickablePoint is not working for UI Automation](https://stackoverflow.com/questions/11933223/getclickablepoint-is-not-working-for-ui-automation)
// [UI Automation - InvokePattern.Invoke() blocking execution until user interaction in integration tests](https://stackoverflow.com/questions/68713216/ui-automation-invokepattern-invoke-blocking-execution-until-user-interaction)
// [UIAutomation Click button without making window take focus and GetCurrentPattern() returning unsupported pattern](https://stackoverflow.com/questions/22290668/uiautomation-click-button-without-making-window-take-focus-and-getcurrentpattern)
// [MenuItem Invoke() is blocking](https://github.com/FlaUI/FlaUI/issues/203)
// [Pair-wise iteration in C# or sliding window enumerator](https://stackoverflow.com/questions/577590/pair-wise-iteration-in-c-sharp-or-sliding-window-enumerator)
