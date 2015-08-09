/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <unordered_map>
#include <typeindex>
#include "InfectorTypes.hpp"
#include "InfectorAbstractContext.hpp"


namespace Infector {
namespace priv {
	
	class Container;
	class DependencyDAG;
	using ContainerPointer = std::shared_ptr< Container>;

/** Dependency Injection container.. Do not user this class directly
	It can be cumbersome. Use instead the very convenient wrapper:
	InfectorContainer.hpp.
	*/
class Container{

public:

    /** Bind a concrete type to multiple types. */
    virtual void bindSingleAs( 	TypeInfoP concrete,
								TypeInfoP * interfaces,
								SharedUpcastSignature * upcasts,
								std::size_t size) = 0;
								
	/** Bind a component to its type registering metainfo. */
    virtual void bindComponent( 	TypeInfoP concrete,
									TypeInfoP interface,
									UpcastSignature upcast,
									std::size_t size) = 0;
	
	/** Update dependency graph.*/
	virtual void wire( 	TypeInfoP type, 
						TypeInfoP * dependencies, 
						std::size_t size,
						BuildSignature func,
						InstanceSignature inst) = 0;
	
	/** Create a context (effectively freeze the type hierarchy).*/
	virtual ContextPointer createContext() = 0;
	
	/** Needed by ConcreteContainer to get rid of this I need to let it access derived
		pointer, possible but require some extra complessity. LATER (do that only
		as optimization: probably not needed since it is called ONLY at initialization
		time during application wiring.))*/
	virtual TypeInfoP getConcreteFromInterface( std::type_index & interface) = 0;
	
    /** allows calling destructor of derived classes from interfaces pointers.*/
    virtual ~Container() = default;
};

// Decouple user from most implementations details to reduce compile time
// and separate "typechecking" from library logic
ContainerPointer createContainer();

} // namespace priv
} // namespace Infector
