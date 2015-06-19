/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
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
								UpcastSignature * upcasts,
								std::size_t size) override;
								
	/** Bind a component to its type registering metainfo. */
    virtual void bindComponent( 	TypeInfoP concrete,
									TypeInfoP interface,
									UpcastSignature * upcast,
									std::size_t size) override;

	/** Register a factory function for given type. */
    virtual void wire( TypeInfoP type,
                       BuildSignature func) override;
					   
	/** Update dependency graph. */
	virtual void touch( TypeInfoP type,
						TypeInfoP * dependencies,
						std::size_t size) override;
						
	/** Split the container. */
	virtual std::shared_ptr<Infector::Container> split() override;
	
	/** Create a new context. */
	virtual std::shared_ptr<Infector::Context> createContext() override;

    /**========================================
                       DETAILS:
    ===========================================*/

    ConcreteContainer( std::shared_ptr<ConcreteContainer> parent) = default;
	ConcreteContainer() = default;
    virtual ~ConcreteContainer() = default;

	using TypeBinding	 	= GenericBinding< RebindEx,
					std::tuple< TypeInfoP, UpcastSignature, std::size_t> >;
	using SymbolTable		= GenericBinding< RebindEx, BuildSignature>;
	
	TypeInfoP getConcreteFromInterface( TypeInfoP interface);

private:

	template< typename T>
    void bindingRollback( T& binding, TypeInfoP * interfaces, std::size_t max){

		for(std::size_t i = 0; i<=max; i++)
			binding.remove( interfaces[i]);

	}
	
	
	TypeBinding			Bindings;
	SymbolTable			Symbols;
	DependencyDAG		Dependencies;
};

} // namespace priv
} // namespace Infector