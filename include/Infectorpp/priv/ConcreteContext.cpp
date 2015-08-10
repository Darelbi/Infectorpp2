/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "ConcreteContext.hpp"
#include "ConcreteContainer.hpp"

namespace Infector{
namespace priv{


void ConcreteContext::registerInstance( std::shared_ptr<void> inst,
							TypeInfoP interface)
{
	auto mapit = instances.find( std::type_index(*interface));

	if(mapit == instances.end()){
		InstanceTableEntry entry;
		entry.instance = inst;
		entry.size = 0;
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
	throwingAssertion< TypeNotWiredEx>( mapit != instances.end()); //check only here for missing wire
																   //because instances could be provided later 
																   //that remove the need for a pre-emptive check ^^
	auto &it = mapit->second;

	if (it.instance != nullptr)
		return it.instance;

	throwingAssertion< InstantiatingComponentEx>( it.size==0);
	std::type_index interfaceType(*interface);

	propagate(
		it.toSharedBaseConversion(
						it.sharedConstructor( this)
											), interfaceType);
	return it.instance;
}

void * ConcreteContext::buildComponent( TypeInfoP interface) {
	auto mapit = instances.find( std::type_index(*interface));
	throwingAssertion< TypeNotWiredEx>( mapit != instances.end());

	auto &it = mapit->second;

	return it.toBaseConversion(
								it.constructor(this)
				);
}

void ConcreteContext::propagate( std::shared_ptr<void> inst, std::type_index & type){
	auto sameConcrete = multiples[ type];
	for( auto element: sameConcrete)
			if(instances[ std::type_index(*element)].instance != nullptr)
				throwOrBreak< PartiallyImplementedSharedType>();
			else
				instances[ std::type_index(*element)].instance = inst;
}

void * ConcreteContext::buildComponentAs( TypeInfoP interface) {
	
	// DO NOT refactor here: in future I could implement a safe check
	
	auto mapit = instances.find( std::type_index(*interface));
	throwingAssertion< TypeNotWiredEx>( mapit != instances.end());

	auto &it = mapit->second;
	
	return it.constructor(this);
}

ContextPointer ConcreteContext::fork() const{
	return std::make_shared<ConcreteContext>( *this);
}

ConcreteContext::ConcreteContext( const ConcreteContext & other){
	instances = other.instances;
	multiples = other.multiples;
}

ConcreteContext::ConcreteContext(	ConcreteContainer::TypeBinding && types,
									ConcreteContainer::SymbolTable && symbols,
									ConcreteContainer::InstanceTable && instas,
									DependencyDAG & dag,
									ConcreteContainer & container		){

	for( auto symbol : symbols){


		auto concrete = symbol.first; //type_index
		auto abstractions = container.getAbstractions( concrete);

		for( auto interface: abstractions){
			auto interfaceType = std::type_index(*interface);
			if( abstractions.size() > 1)
				multiples[interfaceType] = abstractions;

			auto typeinfo = types.get( interfaceType)->second;
			InstanceTableEntry entry;

			entry.size 				= std::get<3>( typeinfo);
			entry.constructor 		= symbol.second;
			entry.toBaseConversion  = std::get<1>( typeinfo);
			entry.sharedConstructor = instas.get( concrete)->second;
			entry.toSharedBaseConversion = std::get<2>( typeinfo);

			instances.emplace( std::make_pair( interfaceType, entry));
		}
	}
	//here memory of container released only context exists now
}

} // namespace priv
} // namespace Infector
