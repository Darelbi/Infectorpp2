/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/
#pragma once
#include "priv/InfectorAbstractContext.hpp"


namespace Infector {

/** A Context holds instances of shared objects of your application. You
    need at least 1 context to instantiate at least 1 class,
    and is suggested to use a different context for each running thread.
	A Context also keeps references to entries in symbol table*/
class Context{
public:

    /** Creates a new object each time is called. Type resolution may
        be recursive in parent Containers, but instances are created
        and owned only inside this context.*/
    template< typename Contract>
    std::unique_ptr<Contract> build();

    /** Return existing instance of an object (or create it if none exists)
        Type resolution may be recursive in parent Containers, but instances
        are created and owned only inside this context.*/
    template< typename Contract>
    std::shared_ptr<Contract> buildSingle();

    /**=====================================================================
                              FOREIGN INSTANCES:
    ------------------------------------------------------------------------
    A Context is (assumed to be) confined in a single thread, however
	instances created by users may access multiple contexts and hence are
	not guaranteed to live only in 1 thread. (you have to provide thread
	safety in that case.)
    =======================================================================*/


    /** Register an object that was already created by someoneelse.
    *   You DON'T need to bind or wire it.*/
    template< typename Contract>
    void registerInstance( std::shared_ptr<Contract> && inst);

    /** Get a shared Instance of an object from another Context
        You DON'T need to bind or wire it.*/
    template< typename Contract>
    void getInstance( std::shared_ptr<Context> & inst);


    /**=====================================================================
                              MOCKING:
    ------------------------------------------------------------------------
    Utility methods based on user feedback that make easy testing with 3rd
    party frameworks (CppUnitTest, GoogleMock etc.). Do not use these methods
    in production code, but only in your test suite.
    =======================================================================*/

    /** Like build, but returns concrete instance of given contract(interface).
        Usefull when you need to call methods on derived class for testing.*/
    template< typename Contract, typename Impl>
    std::unique_ptr<Impl> buildAs();

    /** Like buildSingle, but returns concrete instance of given contract.
        Usefull when you need to call methods on derived class for testing.*/
    template< typename Contract, typename Impl>
    std::shared_ptr<Impl> buildSingleAs();

    /** Replace a target function pointer with a defined implementation,
        You can mock a function multiple times, all previous function
        pointers are restored in reversed order (last mock is first removed)
        when this Context dies.*/
    template< typename Func>
    void mockFunctionPointer( Func * target, Func newFunc);

    /** Like build, but dependencies are not searched in parent Context
        (if any parent Context is present). If you forgot to mock something,
        you would get an exception. ;).*/
    template< typename Contract>
    std::unique_ptr<Contract> mock();

    /** Like buildSingle, but dependencies are not searched in parent Context
        (if any parent Context is present).If you forgot to mock something,
        you would get an exception. ;).*/
    template< typename Contract>
    std::shared_ptr<Contract> mockSingle();


    /**========================================
                       DETAILS:
    ===========================================*/



    //Context(ContextPointer && context_impl);
    inline ~Context() = default;
	
	using ContextPointer = std::shared_ptr<priv::Context>;

private:

	
	ContextPointer          context;


};

template< typename Contract>
void Context::registerInstance( std::shared_ptr<Contract> && inst){
    //TODO: Implement
}

template< typename Contract>
void Context::getInstance( std::shared_ptr<Context> & other){
    auto inst = other.buildSingle< Contract>();
    registerInstance(inst);
}

template< typename Func>
void Context::mockFunctionPointer( Func * toBeMocked, Func newFunc){
    context->mockFunctionAndPushDownRestore(
                // This cast is permitted, by 5.2.10 (6) so it is not undefined behaviour
                    reinterpret_cast<priv::FuncP*>(toBeMocked),
                    reinterpret_cast<priv::FuncP>(newFunc) );
}


} // namespace Infector
