#ifndef TEST_H
#define TEST_H

namespace Foo {
    class A {
        int a1(); // 1
    };

    class B :public A {
        int b1(); // 2
    };

    class D :public X, private Y {
        int d(); // 3
    };

    struct E {
        int x; // 4
    };

    union F {
        int x;
        char y; // 5
    };
}

#endif // TEST_H
