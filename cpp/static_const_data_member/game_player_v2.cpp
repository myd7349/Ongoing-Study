// 2015-05-31T16:52+08:00
#include "game_player_v2.h"

// Though the standard says that a definition should be provided in the .cpp
// file for an odr-used static const data member. In VS2013, however, cause
// a bug is still not fixed, code below will cause a redifiniton error.
#if !defined(_MSC_VER) || (_MSC_VER > 1800)
const int GamePlayerV2::NumTurns;
#endif


// ISO C++11 Standard ¡ì9.4.2/3
// Static data members of a class in namespace scope have external linkage.
int GamePlayerV2::MeaningOfLife = 42;


// References:
// [VS2013 - static const already defined](http://www.stackoverflow.com/questions/31074546/vs2013-static-const-already-defined)
// [LNK2005 when defining static const member](https://connect.microsoft.com/VisualStudio/feedbackdetail/view/933699/lnk2005-when-defining-static-const-member)

