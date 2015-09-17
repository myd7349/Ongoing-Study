// 2015-09-16T10:43+08:00

// javac EnclosingClass.java
// java EnclosingClass

// Algorithms Fourth Edition P139
// >Note that this nested class can access the instance variables of the enclosing class, in
// >this case a[]  and N (this ability is the main reason we use nested classes for iterators).

public class EnclosingClass {
    private int N = 100;

    public EnclosingClass() {
        System.out.println("In EnclosingClass(), N = " + N);
    }

    private class NestedClass {
        private NestedClass(int n) {
            N = n;
            System.out.println("In NestedClass(), N = " + N);
        }
    }

    void foo() {
        NestedClass nested = new NestedClass(2333);
        System.out.println("In Enclosing::foo(), N is: " + N);
    }

    public static void main(String[] args) {
        EnclosingClass enclosing = new EnclosingClass();
        enclosing.foo();
    }
}