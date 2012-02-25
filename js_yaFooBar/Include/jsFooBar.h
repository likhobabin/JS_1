#ifndef __JSFOOBAR_H__
#define	__JSFOOBAR_H__

#include <string>

//
//Template stPtrCloser frees data from under optional type pointer  
//TPtr - pointer data optinal type 
//__ClosePtr - freeing pointer
template<class TPtr > static void stPtrCloser(TPtr*& /*__ClosePtr*/);
//

class Bar;
//

class Foo {
public:

    Foo(unsigned int /*j*/);
    //
    //accessor-method
    //length - Size of i array not byte
    unsigned int getLength(void) const {
        return (length);
    }
    //
    //accessor-method
    //return const pointer to array i
    const int* getDataPtr(void) const {
        return (i);
    }
    //
    //assignment statements 
    Foo& operator=(const Foo& /*__FFrom*/);
    //
    //Foo is a base class of Bar
    virtual ~Foo(void);

private:
    //data length 
    //length is how many elements of int type are there in i array
    //not byte 
    unsigned int length;
    int* i;
    //
    //copy data from input Foo Object
    //use in 
    //assignment statements 
    void copy(const int __InData[], unsigned int __inSize);
    //
    //resize array i
    //use in private method [copy(const int __InData[], unsigned int )]
    void resize(unsigned int /*__NewSize*/);
    //
 
};

class Bar : public Foo {
public:
    
    Bar(unsigned int /*j*/);
    //
    
    //accessor-method
    //return const pointer to array i
    //pointer i has char type
    const char* getDataPtr(void) const {
        return (i);
    }
    //

    virtual ~Bar(void);

private:
    //storage Bar data
    //data has length that was passed 
    //to Foo part of Bar Object
    char* i;
};


#endif	/* __JSFOOBAR_H__ */

