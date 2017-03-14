#ifndef __generator_hpp__
#define __generator_hpp__

//|
//| micro generator/coroutine/continuation for C++
//| author: Andrew @ sciter.com
//| idea borrowed from: "coroutines in C" by Simon Tatham,
//| http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
//|
//| License: BSD
//|
namespace generator
{
  //++ coroutine, generator, continuation for C++

  struct instance
  {
  protected:
    int _line;
  public:
    instance() { rewind(); }
    void rewind() { _line = 0; } // restart the generator
    
  private: 
    instance( const instance& ); // non-copyable
    instance& operator=( const instance& ); // non-assignable
  };

  // Declaration 
  #define $generator(NAME) struct NAME : public generator::instance

  // Start of generator's body, value[s] emmiter. 
  // Shall end with $stop and contain at least one $emit[n] 
  #define $emit(T)            bool operator()(T& _rv) { switch(_line) { case 0:;
  #define $emit2(T1,T2)       bool operator()(T1& _rv1, T2& _rv2) { switch(_line) { case 0:;
  #define $emit3(T1,T2,T3)    bool operator()(T1& _rv1, T2& _rv2, T3& _rv3 ) { switch(_line) { case 0:;
  #define $emit4(T1,T2,T3,T4) bool operator()(T1& _rv1, T2& _rv2, T3& _rv3, T4& _rv4 ) { switch(_line) { case 0:;
  
  // yields next value(s)  
  #define $yield(V)            { _line=__LINE__; _rv = (V); return true; case __LINE__: _line=__LINE__; }
  #define $yield2(V1,V2)       { _line=__LINE__; _rv1 = (V1); _rv2 = (V2); return true; case __LINE__: _line=__LINE__; }
  #define $yield3(V1,V2,V3)    { _line=__LINE__; _rv1 = (V1); _rv2 = (V2); _rv3 = (V3); return true; case __LINE__: _line=__LINE__; }  
  #define $yield4(V1,V2,V3,V4) { _line=__LINE__; _rv1 = (V1); _rv2 = (V2); _rv3 = (V3); _rv4 = (V4); return true; case __LINE__: _line=__LINE__; }

  // end of value[s] emmiter
  #define $stop  } _line = 0; return false; }

  //-- coroutine, generator, continuation for C++

}

#endif
