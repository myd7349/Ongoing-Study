namespace Common
{
    public static class SwapHelper
    {
        public static void Swap<T>(ref T lhs, ref T rhs)
        {
            T temp = lhs;
            lhs = rhs;
            rhs = temp;
        }
    }
}

// References:
// [Swap two variables without using a temporary variable](https://stackoverflow.com/questions/804706/swap-two-variables-without-using-a-temporary-variable)
// [How to swap property values in ViewModel? Can't pass by ref](https://stackoverflow.com/questions/40566202/how-to-swap-property-values-in-viewmodel-cant-pass-by-ref)
// [Is there a generic swap method in the framework?](https://stackoverflow.com/questions/922505/is-there-a-generic-swap-method-in-the-framework)
// [How do I atomically swap 2 ints in C#?](https://stackoverflow.com/questions/3855671/how-do-i-atomically-swap-2-ints-in-c)
