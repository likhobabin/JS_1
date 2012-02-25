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

template<class TPtr > static void stPtrCloser(TPtr*& __ClosePtr) {
 if (NULL != __ClosePtr) {
  //free memory
  delete[] __ClosePtr;
  //pointer is assigned by default value 
  __ClosePtr = NULL;
 }
}
//

Foo::Foo(unsigned int j) :
length(j),
i(NULL) {
    try {
        i = new int[length];
        //
        unsigned int nSize=length*sizeof(i[0]);
        memset(i, 0x0, nSize);
    //catch exception raised from new operator
    } catch (std::bad_alloc& ex) {
        printf("\nError Foo::Foo(unsigned int ) \
                    [%s] <= [ raised bad alloc exception ]\n", ex.what());
    //catch a standard exception 
    } catch (std::exception& ex) {
        printf("\nError Foo::Foo(unsigned int ) \
                   [%s] <= [ raised exception ]\n", ex.what());
    //catch an unexpected exception
    } catch (...) {
        printf("\nError Foo::Foo(unsigned int ) \
                   [ raised unexpected exception ]\n");
    }
}
//
//use for processing following expression
//*f = *b;
//where f and b are Foo and Bar object
//*b => returns reference to Foo part of b 
Foo& Foo::operator=(const Foo& __From) {
    if((&__From) == this )
        return(*this);
    //
    const int* cpData = NULL;
    //getting const pointer to i 
    cpData = __From.getDataPtr();
    //
    //to pass corresponding arguments to copy data from __From Object
    copy(cpData, __From.getLength());
    //
    return (*this);
}
//

Foo::~Foo(void) {
    //free data memory
    stPtrCloser<int >(i);
}
//
//copying data 
void Foo::copy(const int __InData[], unsigned int __InLength) {
    unsigned int maxCpSize = 0x0;
    unsigned int inSize=0x0;
    //
    //convert to byte
    maxCpSize = length * sizeof (i[0]); 
    inSize = __InLength * sizeof(__InData[0]);
    //
    //if input data size 
    //is smaller or bigger than 
    //data into array i
    //resize array i 
    if (inSize != maxCpSize) {
        //do resize
        resize(inSize);
    }
    // and copy data
    memcpy(i, __InData, length);
}
//

void Foo::resize(unsigned int __NewSize) {
    unsigned int rsLength = 0x0;
    rsLength = __NewSize / sizeof (i[0]);
    //
    //free old data memory
    stPtrCloser<int >(i);
    //get new data memory corresponding 
    //length
    i = new int[rsLength];
    length = rsLength;
    //
    memset(i, 0x0, __NewSize);
}
//

////

Bar::Bar(unsigned int j) :
//Foo part of Bar object will has data with j length
Foo(j),
i(NULL) {
    try {
        i = new char[j];
        unsigned int nSize = j * sizeof(i[0]);
        memset(i, '0', nSize);
    } catch (std::bad_alloc& ex) {
        printf("\nError Bar::Bar(unsigned int ) \
                    [%s] <= [ raised bad alloc exception ]\n", ex.what());
    } catch (std::exception& ex) {
        printf("\nError Bar::Bar(unsigned int ) \
                   [%s] <= [ raised exception ]\n", ex.what());
    } catch (...) {
        printf("\nError Bar::Bar(unsigned int ) \
                   [ raised unexpected exception ]\n");
    }
}
//

Bar::~Bar(void) {
    stPtrCloser<char >(i);
}
//