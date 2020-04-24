namespace TaskCancellationTest
{
    using System;
    using System.Collections.Generic;
    using System.Threading;
    using System.Threading.Tasks;

    class Program
    {
        private static void TestV0()
        {
            var tasks = new List<Task<int>>();
            var source = new CancellationTokenSource();
            var token = source.Token;
            int completedIterations = 0;

            for (int n = 0; n <= 19; n++)
                tasks.Add(Task.Factory.StartNew(() => {
                    int iterations = 0;

                    for (int ctr = 1; ctr <= 2000000; ctr++)
                    {
                        token.ThrowIfCancellationRequested();
                        iterations++;
                    }

                    Interlocked.Increment(ref completedIterations);
                    if (completedIterations >= 10)
                        source.Cancel();

                    return iterations;
                }));

            Console.WriteLine("Waiting for the first 10 tasks to complete...\n");
            try
            {
                Task.WaitAll(tasks.ToArray());
            }
            catch (AggregateException)
            {
                Console.WriteLine("Status of tasks:\n");
                Console.WriteLine("{0,10} {1,20} {2,14:N0} {3,10} {4,10} {5,10}", "Task Id",
                                  "Status", "Iterations", "IsCompleted", "IsCanceled", "IsFaulted");
                foreach (var t in tasks)
                    Console.WriteLine("{0,10} {1,20} {2,14} {3,10} {4,10} {5,10}",
                                      t.Id, t.Status,
                                      (t.Status != TaskStatus.Canceled && !t.IsFaulted) ? t.Result.ToString("N0") : "n/a",
                                      t.IsCompleted, t.IsCanceled, t.IsFaulted);
            }
        }

        private static void TestV1()
        {
            var tasks = new List<Task<int>>();
            var source = new CancellationTokenSource();
            var token = source.Token;
            int completedIterations = 0;

            for (int n = 0; n <= 19; n++)
                // Here, we pass the cancellation token as the second
                // parameter of `StartNew`, so that `task.IsCanceled == true`
                // once the task is canceled via `ThrowIfCancellationRequested`.
                // If we do not pass the cancellation token, then we will
                // got: task.IsCanceled == false, task.IsFaulted == true
                // once the task is cancelled via `ThrowIfCancellationRequested`.
                // In this case, we can check whether `task.Exception.InnerException is OperationCanceledException`
                // to distinguish between task cancellation via `ThrowIfCancellationRequested` and
                // task failure caused by some other exceptions.
                tasks.Add(Task.Factory.StartNew(() => {
                    int iterations = 0;

                    for (int ctr = 1; ctr <= 2000000; ctr++)
                    {
                        token.ThrowIfCancellationRequested();
                        iterations++;
                    }

                    Interlocked.Increment(ref completedIterations);
                    if (completedIterations >= 10)
                        source.Cancel();

                    return iterations;
                }, token));

            Console.WriteLine("Waiting for the first 10 tasks to complete...\n");
            try
            {
                Task.WaitAll(tasks.ToArray());
            }
            catch (AggregateException)
            {
                Console.WriteLine("Status of tasks:\n");
                Console.WriteLine("{0,10} {1,20} {2,14:N0} {3,10} {4,10} {5,10}", "Task Id",
                                  "Status", "Iterations", "IsCompleted", "IsCanceled", "IsFaulted");
                foreach (var t in tasks)
                    Console.WriteLine("{0,10} {1,20} {2,14} {3,10} {4,10} {5,10}",
                                      t.Id, t.Status,
                                      t.Status != TaskStatus.Canceled ? t.Result.ToString("N0") : "n/a",
                                      t.IsCompleted, t.IsCanceled, t.IsFaulted);
            }
        }

        public static void Main()
        {
            TestV0();
            Console.ReadKey();

            TestV1();
            Console.ReadKey();
        }
    }
}

/*
Waiting for the first 10 tasks to complete...

Status of tasks:

   Task Id               Status     Iterations IsCompleted IsCanceled  IsFaulted
         1      RanToCompletion      2,000,000       True      False      False
         2      RanToCompletion      2,000,000       True      False      False
         3      RanToCompletion      2,000,000       True      False      False
         4      RanToCompletion      2,000,000       True      False      False
         5      RanToCompletion      2,000,000       True      False      False
         6      RanToCompletion      2,000,000       True      False      False
         7      RanToCompletion      2,000,000       True      False      False
         8      RanToCompletion      2,000,000       True      False      False
         9      RanToCompletion      2,000,000       True      False      False
        10      RanToCompletion      2,000,000       True      False      False
        11              Faulted            n/a       True      False       True
        12              Faulted            n/a       True      False       True
        13              Faulted            n/a       True      False       True
        14              Faulted            n/a       True      False       True
        15              Faulted            n/a       True      False       True
        16              Faulted            n/a       True      False       True
        17              Faulted            n/a       True      False       True
        18              Faulted            n/a       True      False       True
        19              Faulted            n/a       True      False       True
        20              Faulted            n/a       True      False       True

Waiting for the first 10 tasks to complete...

Status of tasks:

   Task Id               Status     Iterations IsCompleted IsCanceled  IsFaulted
        21      RanToCompletion      2,000,000       True      False      False
        22      RanToCompletion      2,000,000       True      False      False
        23      RanToCompletion      2,000,000       True      False      False
        24      RanToCompletion      2,000,000       True      False      False
        25      RanToCompletion      2,000,000       True      False      False
        26      RanToCompletion      2,000,000       True      False      False
        27      RanToCompletion      2,000,000       True      False      False
        28      RanToCompletion      2,000,000       True      False      False
        29      RanToCompletion      2,000,000       True      False      False
        30      RanToCompletion      2,000,000       True      False      False
        31             Canceled            n/a       True       True      False
        32             Canceled            n/a       True       True      False
        33             Canceled            n/a       True       True      False
        34             Canceled            n/a       True       True      False
        35             Canceled            n/a       True       True      False
        36             Canceled            n/a       True       True      False
        37             Canceled            n/a       True       True      False
        38             Canceled            n/a       True       True      False
        39             Canceled            n/a       True       True      False
        40             Canceled            n/a       True       True      False
*/

// References:
// C# 6.0 in a Nutshell
// https://stackoverflow.com/questions/20782110/why-is-task-iscanceled-not-true
// > Yes of course and that's why microsoft calls this pattern as cooperative cancellation.
// https://docs.microsoft.com/en-us/dotnet/api/system.threading.tasks.taskstatus?view=netframework-4.8#System_Threading_Tasks_TaskStatus_RanToCompletion
// https://stackoverflow.com/questions/21520869/proper-way-of-handling-exception-in-task-continuewith
// https://stackoverflow.com/questions/32067034/how-to-handle-task-run-exception
