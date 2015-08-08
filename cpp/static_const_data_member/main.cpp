// 2015-05-31T16:42+08:00
// 2015-08-08T22:44+08:00
#include <algorithm>
#include <iostream>

#include "../common.h"
#include "game_player.h"
#include "game_player_v2.h"

int main()
{
    GamePlayer gp;

    // undefined reference to `GamePlayer::NumTurns'
    // ISO C++11 Standard ?.4.2/3
    // The member shall still be defined in a namespace scope if it is odr-used (3.2)
    // in the program and the namespace scope definition shall not contain an initializer.

    //std::cout << &gp.NumTurns << std::endl;
    //std::cout << std::min(gp.NumTurns, 3) << std::endl;

    GamePlayerV2 gp2;
    std::cout << gp2.NumTurns << std::endl;
    std::cout << &gp2.NumTurns << std::endl;

    std::cout << &GamePlayerV2::MeaningOfLife << std::endl;

    PAUSE();
    return 0;
}

// References:
// Effective C++ 3E: Item 02
// ISO/IEC 14882:2011(E)
// [When is a variable odr-used in C++14?](http://www.stackoverflow.com/questions/23491781/when-is-a-variable-odr-used-in-c14)
// [Undefined reference to static const int](http://stackoverflow.com/questions/5391973/undefined-reference-to-static-const-int)
// [Defining static const integer members in class definition](http://stackoverflow.com/questions/3025997/defining-static-const-integer-members-in-class-definition)
// [vector::push_back odr-uses the value, causing undefined reference to static class member](http://www.stackoverflow.com/questions/272900/vectorpush-back-odr-uses-the-value-causing-undefined-reference-to-static-clas)
// [undefined reference to "static const int" in class when passing as "const int &" to a function](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=42330)
// [Why does declaring a “static const?member in a header file cause linker errors?](http://www.stackoverflow.com/questions/5183703/why-does-declaring-a-static-const-member-in-a-header-file-cause-linker-errors)
// [Why the static data members have to be defined outside the class separately in C++ (unlike Java)?](http://programmers.stackexchange.com/questions/145299/why-the-static-data-members-have-to-be-defined-outside-the-class-separately-in-c)
