/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/
#pragma once
#include <memory>


namespace Infector {
namespace priv{

	class Context;
	using FuncP = void(*)(void*);
	using ContextPointer = std::shared_ptr< Context>;

class Context{

public:

    /** Creates a mock for a global function pointer and push into a stack
        a lambda that restores original function value (the restore stuff
        is useless for simple tests, but may come in handy for complex tests).*/
    virtual void mockFunctionAndPushDownRestore
                                    ( FuncP * toBeMocked, FuncP newFunc) = 0;

    /** Creates an instance if not already present and return a shared pointer
        to that instance. */
    virtual std::shared_ptr<void> instance( TypeInfoP type) = 0;

    /** Creates a new object of given type*/
    virtual void * create( TypeInfoP type) = 0;

    /** allows calling destructor of derived classes from interfaces pointers.*/
    virtual ~Context() = default;
};

} // namespace priv
} // namespace Infector
