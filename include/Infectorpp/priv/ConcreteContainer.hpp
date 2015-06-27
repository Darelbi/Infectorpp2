/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "InfectorTypes.hpp"
#include "../InfectorTraits.hpp"
#include "InfectorAbstractContainer.hpp"
#include "InfectorAbstractContext.hpp"
#include "DependencyDAG.hpp"
#include "GenericBinding.hpp"

#include <memory>
#include <tuple>

namespace Infector {
namespace priv {

class ConcreteContainer: public Container{

public:

    /** Bind a concrete type to multiple types. */
    virtual void bindSingleAs( 	TypeInfoP concrete,
								TypeInfoP * interfaces,
								InstanceSignature * upcasts,
								std::size_t size) override;
								
	/** Bind a component to its type registering metainfo. */
    virtual void bindComponent( 	TypeInfoP concrete,
									TypeInfoP interface,
									UpcastSignature upcast,
									std::size_t size) override;

	/** Register a factory function for given type. */
    virtual void wire( 	TypeInfoP type, 
						TypeInfoP * dependencies, 
						std::size_t size,
						BuildSignature func) override;
						
	/** Split the container. */
	ContainerPointer split( ContainerPointer p);
	
	/** Create a context (effectively freeze the type hierarchy).*/
	virtual ContextPointer createContext() override;

    /**========================================
                       DETAILS:
    ===========================================*/

    ConcreteContainer( priv::ContainerPointer p, DependencyDAG  * d);
	ConcreteContainer();
    virtual ~ConcreteContainer();

	using TypeBinding	 	= GenericBinding< RebindEx,
					std::tuple< TypeInfoP, UpcastSignature, std::size_t> >;
	using SymbolTable		= GenericBinding< RebindEx, BuildSignature>;
	using InstanceTable 	= GenericBinding< RebindEx, InstanceSignature>;
	
	virtual TypeInfoP getConcreteFromInterface( TypeInfoP interface) override;
	
	DependencyDAG * getGraph();

private:

	template< typename T>
    void bindingRollback( T& binding, TypeInfoP * interfaces, std::size_t max){

		for(std::size_t i = 0; i<=max; i++)
			binding.remove( interfaces[i]);

	}
	
	void rollbackWire( TypeInfoP p);
	
	ContainerPointer	Parent = nullptr;
	TypeBinding			Bindings;
	SymbolTable			Symbols;
	InstanceTable		Instances;
	DependencyDAG		Dependencies;
};

} // namespace priv
} // namespace Infector