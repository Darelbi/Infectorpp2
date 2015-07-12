/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "ConcreteContext.hpp"

namespace Infector{
namespace priv{
	
void ConcreteContext::mockFunctionAndPushDownRestore
							( FuncP * toBeMocked, FuncP newFunc){
								
}
								
void ConcreteContext::registerInstance( std::shared_ptr<void> inst,
							TypeInfoP interface)
{
	auto mapit = instances.find( std::type_index(*interface));
	
	if(mapit == instances.end()){
		InstanceTableEntry entry;
		entry.instance = inst;
		instances[std::type_index(*interface)] = entry;
		return;
	}
	
	auto &it = mapit->second;
	
	throwingAssertion
		< InstanceAlreadyRegisteredEx>( it.instance == nullptr);
		
	it.instance = inst;
}

std::shared_ptr<void> ConcreteContext::instance( TypeInfoP interface){
	
	auto mapit = instances.find( std::type_index(*interface));
	throwingAssertion< TypeNotWiredEx>( mapit != instances.end());
	
	auto &it = mapit->second;
	
	if (it.instance != nullptr)
		return it.instance;
	
	throwingAssertion< InstantiatingComponentEx>( it.size==0);
	
	//TODO: multiple interfaces require one instance, need to map it (else each
	//interface generate a new instance.. no good)
	propagate(
		it.instance = it.toSharedBaseConversion(
											it.sharedConstructor( this)  
		//TODO: what if type is not wired? should detect it somewhere and throw
		// (at initialization time is better than at runtime) YES BUT
		// users could still ask for wrong types to context. So check at runtime
		// at least (at initialization time would be a DESIRED plus.
		// but would still count as code duplication)
											), interface);

	return it.instance;
}

void * ConcreteContext::buildComponent( TypeInfoP interface){
	auto mapit = instances.find( std::type_index(*interface));
	throwingAssertion< TypeNotWiredEx>( mapit != instances.end());
	
	auto &it = mapit->second;
	
	return it.toBaseConversion(
								it.constructor(this)
				);
}

void ConcreteContext::propagate( std::shared_ptr<void> inst, TypeInfoP type){
	auto linked_deps = multiples[ std::type_index(*type)];
	auto it = linked_deps.begin();
		while(it!=linked_deps.end())
			instances[ std::type_index(*(*it))].instance = inst;
}

void ConcreteContext::collectDependencies( 	std::type_index & index,
											DependencyDAG & dag	)
{
	auto deps = dag.getDependencies(index);
	if(deps.size()>1){
		auto it = deps.begin();
		while(it!=deps.end())
			multiples[ std::type_index(*(*it))] = deps;
	}
}

ConcreteContext::ConcreteContext(	ConcreteContainer::TypeBinding types,
									ConcreteContainer::SymbolTable symbols,
									ConcreteContainer::InstanceTable instas,
									DependencyDAG & dag		){

	auto it = types.begin();
	
	while( it != types.end()){
		auto interface = it->first;
		auto typei = std::type_index(*std::get<0>(it->second));
		collectDependencies( typei, dag);
		
		InstanceTableEntry entry;
		entry.size 	 = std::get<3>( it->second);
		
		/** Size will be used for emplacement of components (means faster 
		*	allocation, and thus is useless for shared instances, so when
		*	size is 0 we assume it must be a shared instance)*/
		if( entry.size==0){
			entry.sharedConstructor     = instas.getVal(interface);
			entry.toSharedBaseConversion= std::get<2>( it->second);
		}
		else{
			entry.constructor 			= symbols.getVal(interface);
			entry.toBaseConversion		= std::get<1>( it->second);
		}
		instances.emplace( std::make_pair( interface, entry));
	}
	
	//here memory  of container released only context exists now
}
	
} // namespace priv
} // namespace Infector
