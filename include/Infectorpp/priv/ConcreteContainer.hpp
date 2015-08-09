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
#include <list>

namespace Infector {
namespace priv {

class ConcreteContainer: public Container{

public:

    /** Bind a concrete type to multiple types. */
    virtual void bindSingleAs( 	TypeInfoP concrete,
								TypeInfoP * interfaces,
								SharedUpcastSignature * upcasts,
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
						BuildSignature func,
						InstanceSignature inst) override;
	
	/** Create a context (effectively freeze the container hierarchy).*/
	virtual ContextPointer createContext() override;
	
	/** Get the current concrete type for an interface (recursive in parent)*/
	virtual TypeInfoP getConcreteFromInterface( 
							std::type_index & interface ) override;
	
	/** Return abstractions for a concrete type (only in this container)*/
	std::list<TypeInfoP> getAbstractions( std::type_index & concrete);

    /**========================================
                       DETAILS:
    ===========================================*/

    ConcreteContainer( 	priv::ContainerPointer p, 
						DependencyDAG  * d, 
						std::shared_ptr<bool> lock);
						
	ConcreteContainer();
    virtual ~ConcreteContainer();

	using TypeBinding	 	= GenericBinding< RebindEx,
						std::tuple< 
								TypeInfoP, 
								UpcastSignature, 
								SharedUpcastSignature, 
								std::size_t
								> 
							>;
								
	using SymbolTable		= GenericBinding< RebindEx, BuildSignature>;
	using InstanceTable 	= GenericBinding< RebindEx, InstanceSignature>;
	using Abstractions = GenericBinding< NotReachableEx, std::list<TypeInfoP>>;

	DependencyDAG * getGraph();

private:

	template< typename T>
    void bindingRollback( T& binding, TypeInfoP * interfaces, std::size_t max){

		for(std::size_t i = 0; i<=max; i++)
			binding.remove( interfaces[i]);

	}

	void rollbackWire( TypeInfoP p);
	
	void addAbstraction( TypeInfoP concrete, TypeInfoP interface);
	
	void removeAbstractions( TypeInfoP concr, TypeInfoP * interf, std::size_t);

	TypeBinding			bindings;
	SymbolTable			symbols;
	InstanceTable		instances;
	Abstractions		abstractions;
	DependencyDAG		dependencies;
};

} // namespace priv
} // namespace Infector