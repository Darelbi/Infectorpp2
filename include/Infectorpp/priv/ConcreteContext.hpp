/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "InfectorTypes.hpp"
#include "InfectorAbstractContext.hpp"
#include "ConcreteContainer.hpp"
#include "ExceptionHandling.hpp"
#include <unordered_map>


namespace Infector{
namespace priv{
	
class ConcreteContext: public Context{
	struct InstanceTableEntry{
		std::size_t				size;
		BuildSignature			constructor;
		UpcastSignature			toBaseConversion;
		std::shared_ptr<void>	instance;
	};
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
	
	using InstanceTable	 	=  std::unordered_map< std::type_index,
												InstanceTableEntry >;
					
	ConcreteContext(	ConcreteContainer::TypeBinding types,
						ConcreteContainer::SymbolTable symbols );

private:

	InstanceTable	instances;
	
};
	
} // namespace priv
} // namespace Infector