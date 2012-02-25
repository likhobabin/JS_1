#include "jsPrecompile.h"
#include "jsFooBar.h"
////

#ifdef _MSC_VER
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#endif
/////

int main(int /*argc*/, const char* args[])
{
    Foo* f=new Foo(100);
    Foo* b=new Bar(200);
    //
    *f=*b;    
    //
    delete f;
    delete b;
    //
    return(0);    
}

