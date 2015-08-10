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
#include <unordered_map>


namespace Infector{
namespace priv{

class ConcreteContext: public Context{
	struct InstanceTableEntry{
		std::size_t				size = 0;

		BuildSignature			constructor = nullptr;
		UpcastSignature			toBaseConversion = nullptr;

		InstanceSignature		sharedConstructor = nullptr;
		SharedUpcastSignature	toSharedBaseConversion = nullptr;

		std::shared_ptr<void>	instance = nullptr;
	};
public:

	virtual void registerInstance( std::shared_ptr<void> inst,
								TypeInfoP type) override;

    virtual std::shared_ptr<void> instance( TypeInfoP type) override;

    virtual void * buildComponent( TypeInfoP type) override;

	virtual void * buildComponentAs(TypeInfoP interface) override;

	virtual ContextPointer fork() const override;

    /** allows calling destructor of derived classes from interfaces pointers.*/
    virtual ~ConcreteContext() = default;

	using InstanceTable	 	=  std::unordered_map< std::type_index,
												InstanceTableEntry >;

	ConcreteContext(	ConcreteContainer::TypeBinding && types,
						ConcreteContainer::SymbolTable && symbols,
						ConcreteContainer::InstanceTable && instances,
						DependencyDAG & dag,
						ConcreteContainer & container);
						
	ConcreteContext( const ConcreteContext & other);

private:

	void propagate( std::shared_ptr<void> inst, std::type_index & type);

	InstanceTable			instances;
	DependencyDAG::EdgeMap	multiples; // instances with multiple interfaces
};

} // namespace priv
} // namespace Infector