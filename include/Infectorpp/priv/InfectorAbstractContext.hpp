/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "InfectorTypes.hpp"


namespace Infector {
namespace priv{

	class Context;
	using FuncP = void(*)(void*);
	using ContextPointer = std::shared_ptr< Context>;

class Context{

public:

	/** Register an instance so that such instance is returned instead of being
		lazily created for a given type. Note that if an instance of given type
		is already registerd then the program abort/throw exception.*/
	virtual void registerInstance( std::shared_ptr<void> inst, TypeInfoP type) = 0;

    /** Creates an instance if not already present and return a shared pointer
        to that instance (any dependency required is lazily created now). */
    virtual std::shared_ptr<void> instance( TypeInfoP type) = 0;

    /** Creates a new object of given type (any dependency required is lazily
		created now).*/
    virtual void * buildComponent( TypeInfoP interface) = 0;

	/** Creates a new object of given type (any dependency required is lazily
		created now).*/
    virtual void * buildComponentAs(TypeInfoP interface) = 0;

	/** Fork the context. */
	virtual ContextPointer fork() const = 0;

    /** allows calling destructor of derived classes from interfaces pointers.*/
    virtual ~Context() = default;
};

} // namespace priv
} // namespace Infector
