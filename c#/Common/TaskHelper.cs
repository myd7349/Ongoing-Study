using System;
using System.Threading;
using System.Threading.Tasks;

namespace Common
{
    public static class TaskHelper
    {
        public static async Task TimeoutAfter(this Task task, TimeSpan timeout)
        {
            if (task == null)
                throw new ArgumentNullException(nameof(task));

            using (var timeoutCancellationTokenSource = new CancellationTokenSource())
            {
                var completedTask = await Task.WhenAny(task, Task.Delay(timeout, timeoutCancellationTokenSource.Token));
                if (completedTask == task)
                {
                    timeoutCancellationTokenSource.Cancel();
                    await task;  // Very important in order to propagate exceptions
                }
                else
                {
                    throw new TimeoutException("The operation has timed out.");
                }
            }
        }

        public static async Task<TResult> TimeoutAfter<TResult>(this Task<TResult> task, TimeSpan timeout)
        {
            if (task == null)
                throw new ArgumentNullException(nameof(task));

            using (var timeoutCancellationTokenSource = new CancellationTokenSource())
            {
                var completedTask = await Task.WhenAny(task, Task.Delay(timeout, timeoutCancellationTokenSource.Token));
                if (completedTask == task)
                {
                    timeoutCancellationTokenSource.Cancel();
                    return await task;  // Very important in order to propagate exceptions
                }
                else
                {
                    throw new TimeoutException("The operation has timed out.");
                }
            }
        }
    }
}


// References:
// [TcpListener: how to stop listening while awaiting AcceptTcpClientAsync()?](https://stackoverflow.com/questions/19220957/tcplistener-how-to-stop-listening-while-awaiting-accepttcpclientasync)
// [Asynchronously wait for Task<T> to complete with timeout](https://stackoverflow.com/questions/4238345/asynchronously-wait-for-taskt-to-complete-with-timeout)
// > From .Net 6 (Preview 7) or later, there is a new build-in method Task.WaitAsync to achieve this.
