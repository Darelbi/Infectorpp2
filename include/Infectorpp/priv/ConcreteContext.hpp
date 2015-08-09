/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "InfectorTypes.hpp"
#include "InfectorAbstractContext.hpp"
#include "ConcreteContainer.hpp"
#include "ExceptionHandling.hpp"
#include "DependencyDAG.hpp"
#include "InstanceTableEntry.hpp"
#include <unordered_map>


namespace Infector{
namespace priv{

class ConcreteContext: public Context{

public:

	/** Creates a mock for a global function pointer and push into a stack
        a lambda that restores original function value (the restore stuff
        is useless for simple tests, but may come in handy for complex tests).*/
	virtual void mockFunctionAndPushDownRestore
                                ( FuncP * toBeMocked, FuncP newFunc) override;

	/** Register an instance so that such instance is returned instead of being
		lazily created for a given type. Note that if an instance of given type
		is already registerd then the program abort/throw exception.*/
	virtual void registerInstance( std::shared_ptr<void> inst,
								TypeInfoP type) override;

    /** Creates an instance if not already present and return a shared pointer
        to that instance (any dependency required is lazily created now). */
    virtual std::shared_ptr<void> instance( TypeInfoP type) override;

    /** Creates a new object of given type (any dependency required is lazily
		created now).*/
    virtual void * buildComponent( TypeInfoP type) override;

    /** allows calling destructor of derived classes from interfaces pointers.*/
    virtual ~ConcreteContext() = default;

	ConcreteContext( 	ConcreteContainer::TypeBinding && types,
						ConcreteContainer::SymbolTable && symbols,
						ConcreteContainer::InstanceTable && instas,
						DependencyDAG & dag,
						ConcreteContainer & container
					);

private:

	void propagate( std::shared_ptr<void> inst, std::type_index & type);

	InstanceTable			instances;
	DependencyDAG::EdgeMap	multiples; // instances with multiple interfaces
};

} // namespace priv
} // namespace Infector