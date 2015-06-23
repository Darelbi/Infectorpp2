/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/
#pragma once
#include "DependencyDAG.hpp"
#include "ExceptionHandling.hpp"
#include <algorithm>    // std::find


namespace Infector {
namespace priv {
	
DependencyDAG::DependencyDAG( DependencyDAG * p){
	parent = p;
}

void DependencyDAG::setGuard( TypeInfoP g){
	guard = g;
	//dependencies[ std::type_index(*g)] = std::list< TypeInfoP>();
}

void DependencyDAG::dependOn( TypeInfoP wired, TypeInfoP abstractDep,
									ConcreteContainer * container){
	addDependency( wired, abstractDep);
	//addDependant( wired, abstractDep);
	
	const int HARD_RECURSION_LIMIT = 40; //lower better
	checkGuardBreaking( wired, container, HARD_RECURSION_LIMIT);
	
	// do you really hit HARD_RECURSION_LIMIT? 
	// that probably means your code has too many nested dependencies
	// change that limit if you know what you are doing
}

void DependencyDAG::addDependency( TypeInfoP wired, TypeInfoP abstractDep){
	// Concrete type has XXX dependencies (interfaces)
	
	auto  & hashEntry = dependencies.insert( 
										std::make_pair(	std::type_index(*wired),
														std::list< TypeInfoP>() )
										).first->second;
	
	auto edge = std::find (hashEntry.begin(), hashEntry.end(), abstractDep);

	if (edge != hashEntry.end())
		hashEntry.push_back( abstractDep);		
}


void DependencyDAG::addDependant( TypeInfoP wired, TypeInfoP abstractDep){
	// An interface is used by XXX concrete types
	auto  & hashEntry = dependants.insert( 
										std::make_pair(	std::type_index(*abstractDep),
														std::list< TypeInfoP>() )
										).first->second;
	
	auto edge = std::find (hashEntry.begin(), hashEntry.end(), wired);

	if (edge != hashEntry.end())
		hashEntry.push_back( wired);
}


void DependencyDAG::checkGuardBreaking( TypeInfoP currentNode,
									ConcreteContainer * container,
									int HARD_RECURSION_LIMIT){
	
	HARD_RECURSION_LIMIT--;
	if(HARD_RECURSION_LIMIT<=0)
			throwOrBreak< TooDeepRecursionEx>();
		
	//check dependencies of a particular wired type.
	auto result = getDependencies( currentNode);
	if(result.second == false)
		return;
		
	for (auto interface : result.first){
		auto resolvedType = container->getConcreteFromInterface(interface);
		if( resolvedType == guard)
			throwOrBreak< CircularDependencyEx>();
		
		if( resolvedType != nullptr)
			checkGuardBreaking( resolvedType, container, 
								HARD_RECURSION_LIMIT);
	}
}

std::pair< std::list<TypeInfoP>, bool >
	DependencyDAG::getDependencies( TypeInfoP concrete){
	auto result = dependencies.find( std::type_index(*concrete));
	if(  result != dependencies.end())
		return std::make_pair( result->second, true);

	return parent? parent->getDependencies(concrete):
		std::make_pair( std::list<TypeInfoP>(), false);
}

void DependencyDAG::remove( TypeInfoP wired){
	auto concrete = dependencies.find( std::type_index(*wired) );
	if(concrete!=dependencies.end()){
		
		for( TypeInfoP abstractDep: concrete->second)
			removeDependant( wired, abstractDep);
		
		dependencies.erase(  std::type_index(*wired));
	}
	
	throwOrBreak< NotReachableEx>();
}

void DependencyDAG::removeDependant( TypeInfoP wired, TypeInfoP abstractDep){
	auto & abstract = dependants.find( std::type_index(*abstractDep) )->second;
	abstract.remove( wired);
	if(abstract.empty())
		dependants.erase( std::type_index(*abstractDep));
}


} // namespace priv
} // namespace Infector