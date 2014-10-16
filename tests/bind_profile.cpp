
#include <iostream>
#include <Infectorpp/InfectorContainer.hpp>

#define DECLARE(Imple,Interface1,Interface2)\
class Interface1 ##Imple{\
public:\
    virtual void doFaa() = 0;\
    virtual ~Interface1##Imple(){}\
};\
\
class Interface2 ##Imple{\
public:\
    virtual void baDoo() = 0;\
    virtual ~Interface2##Imple(){}\
};\
\
class Imple: public virtual Interface1 ## Imple, public virtual Interface2 ## Imple{\
public:\
    virtual void doFaa() override{std::cout<< #Interface1<<std::endl;}\
    virtual void baDoo() override{std::cout<< #Interface2<<std::endl;}\
    virtual ~Imple(){}\
};\
\

#define WIRE(Imple,Interface1,Interface2)\
IoC.bindSingleAs<Imple,Interface1##Imple,Interface2##Imple>();

DECLARE(C,A,B) //declare & define class "C" that implements "AC" and "AB"
DECLARE(D,A,B) //...
DECLARE(E,A,B)
DECLARE(F,A,B)
DECLARE(G,A,B)
DECLARE(H,A,B)
DECLARE(I,A,B)
DECLARE(J,A,B)
DECLARE(K,A,B)
DECLARE(L,A,B)
DECLARE(M,A,B)
DECLARE(N,A,B)
DECLARE(O,A,B)
DECLARE(P,A,B)
DECLARE(Q,A,B)
DECLARE(R,A,B)
DECLARE(S,A,B)
DECLARE(T,A,B)
DECLARE(U,A,B)
DECLARE(V,A,B)
DECLARE(Z,A,B)
DECLARE(X,A,B)
DECLARE(Y,A,B)
DECLARE(W,A,B)
DECLARE(CA,A,B)
DECLARE(CB,A,B)
DECLARE(CC,A,B)
DECLARE(CD,A,B)
DECLARE(CE,A,B)
DECLARE(CF,A,B)
DECLARE(ZC,A,B)
DECLARE(ZD,A,B)
DECLARE(ZE,A,B)
DECLARE(ZF,A,B)
DECLARE(ZG,A,B)
DECLARE(ZH,A,B)
DECLARE(ZI,A,B)
DECLARE(ZJ,A,B)
DECLARE(ZK,A,B)
DECLARE(ZL,A,B)
DECLARE(ZM,A,B)
DECLARE(ZN,A,B)
DECLARE(ZO,A,B)
DECLARE(ZP,A,B)
DECLARE(ZQ,A,B)
DECLARE(ZR,A,B)
DECLARE(ZS,A,B)
DECLARE(ZT,A,B)
DECLARE(ZU,A,B)
DECLARE(ZV,A,B)
DECLARE(ZZ,A,B)
DECLARE(ZX,A,B)
DECLARE(ZY,A,B)
DECLARE(ZW,A,B)
DECLARE(ZCA,A,B)
DECLARE(ZCB,A,B)
DECLARE(ZCC,A,B)
DECLARE(ZCD,A,B)
DECLARE(ZCE,A,B)
DECLARE(ZCF,A,B)

int main(){

Infector::Container IoC;

WIRE(C,A,B) //.. wire classes
WIRE(D,A,B)
WIRE(E,A,B)
WIRE(F,A,B)
WIRE(G,A,B)
WIRE(H,A,B)
WIRE(I,A,B)
WIRE(J,A,B)
WIRE(K,A,B)
WIRE(L,A,B)
WIRE(M,A,B)
WIRE(N,A,B)
WIRE(O,A,B)
WIRE(P,A,B)
WIRE(Q,A,B)
WIRE(R,A,B)
WIRE(S,A,B)
WIRE(T,A,B)
WIRE(U,A,B)
WIRE(V,A,B)
WIRE(Z,A,B)
WIRE(X,A,B)
WIRE(Y,A,B)
WIRE(W,A,B)
WIRE(CA,A,B)
WIRE(CB,A,B)
WIRE(CC,A,B)
WIRE(CD,A,B)
WIRE(CE,A,B)
WIRE(CF,A,B)
WIRE(ZC,A,B)
WIRE(ZD,A,B)
WIRE(ZE,A,B)
WIRE(ZF,A,B)
WIRE(ZG,A,B)
WIRE(ZH,A,B)
WIRE(ZI,A,B)
WIRE(ZJ,A,B)
WIRE(ZK,A,B)
WIRE(ZL,A,B)
WIRE(ZM,A,B)
WIRE(ZN,A,B)
WIRE(ZO,A,B)
WIRE(ZP,A,B)
WIRE(ZQ,A,B)
WIRE(ZR,A,B)
WIRE(ZS,A,B)
WIRE(ZT,A,B)
WIRE(ZU,A,B)
WIRE(ZV,A,B)
WIRE(ZZ,A,B)
WIRE(ZX,A,B)
WIRE(ZY,A,B)
WIRE(ZW,A,B)
WIRE(ZCA,A,B)
WIRE(ZCB,A,B)
WIRE(ZCC,A,B)
WIRE(ZCD,A,B)
WIRE(ZCE,A,B)
WIRE(ZCF,A,B)

return 0;
}

/*#include <Infectorpp/priv/InfectorConcreteBinding.hpp>
#include <Infectorpp/priv/InfectorContainer.hpp>
#include <Infectorpp/priv/InfectorTypes.hpp>
#include <memory>
#include <typeindex>
#include <functional>*/

/*
class A{
};

class B: public A{
};

class C: public A{
};

template <typename T>
void funct(T a){

}

template <typename T, typename ... Ts>
int VariadicTest(){

    Infector::priv::TypeInfoP types[ sizeof...( Ts)] { &typeid( Ts)...}; // OK!!!
    Infector::priv::DowncastSignature functions[ sizeof...(Ts)]
    { &Infector::priv::downcast<T,Ts>...};

    std::shared_ptr<Infector::priv::Container> ioc = nullptr;

    ioc->bindAs(&typeid(T),types, functions, sizeof...(Ts));

    return types[0]->hash_code();
}

using Reference = int&;
int main(){
    VariadicTest<A,B,C>();
    Infector::IoCContainer IoC;
    IoC.bindSingleAs<B,A>();
    //Infector::priv::ConcreteBinding bindin;
    //bindin.bind(&typeid(C),&typeid(A));

    //Reference refs[] {3,4,2};

    return 0;
}*/
