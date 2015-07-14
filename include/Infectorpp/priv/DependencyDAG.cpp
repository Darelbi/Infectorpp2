/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "DependencyDAG.hpp"
#include "ExceptionHandling.hpp"
#include "ConcreteContainer.hpp"
#include <algorithm>    // std::find


namespace Infector {
namespace priv {
	
DependencyDAG::DependencyDAG( DependencyDAG * p){
	parent = p;
}

DependencyDAG::~DependencyDAG(){
	clean();
}


void DependencyDAG::setGuard( TypeInfoP g){
	throwingAssertion< NotReachableEx>(dependencies !=nullptr);
	guard = g;
}

void DependencyDAG::dependOn( TypeInfoP wired, TypeInfoP abstractDep,
									ConcreteContainer * container){
	throwingAssertion< NotReachableEx>(dependencies !=nullptr);
	
	addDependency( wired, abstractDep);
	addDependant( wired, abstractDep);
	
	const int HARD_RECURSION_LIMIT = 40; //lower better
	checkGuardBreaking( wired, container, HARD_RECURSION_LIMIT);
}

void DependencyDAG::addDependency( TypeInfoP wired, TypeInfoP abstractDep){
	// Concrete type has XXX dependencies (interfaces)
	auto map_it = dependencies->find( std::type_index(*wired));
	
	auto & depList = 
				(map_it == dependencies->end())?
						((*dependencies)[  std::type_index(*wired)] = std::list< TypeInfoP>()):
						(*dependencies)[  std::type_index(*wired)];
	
	auto edge = std::find (depList.begin(), depList.end(), abstractDep);

	if (edge == depList.end())
		depList.push_back( abstractDep);
}


void DependencyDAG::addDependant( TypeInfoP wired, TypeInfoP abstractDep){
	// An interface is used by XXX concrete types
	auto map_it = dependants->find( std::type_index(*abstractDep));
	
	auto & depList = 
				(map_it == dependants->end())?
						((*dependants)[  std::type_index(*abstractDep)] = std::list< TypeInfoP>()):
						(*dependants)[  std::type_index(*abstractDep)];
	
	auto edge = std::find (depList.begin(), depList.end(), wired);

	if (edge == depList.end())
		depList.push_back( wired);
}


void DependencyDAG::checkGuardBreaking( TypeInfoP currentNode,
									ConcreteContainer * container,
									int HARD_RECURSION_LIMIT){
	HARD_RECURSION_LIMIT--;
	if(HARD_RECURSION_LIMIT<=0)
			throwOrBreak< TooDeepRecursionEx>();
		
	//check dependencies of a particular wired type.
	auto result = getDependencies( currentNode);
	for (auto interface : result){
		std::type_index interfaceType(*interface);
		
		auto resolvedType = container->getConcreteFromInterface(interfaceType);
		if( resolvedType == nullptr)
			continue;
		if( resolvedType == guard)
			throwOrBreak< CircularDependencyEx>();
		checkGuardBreaking( resolvedType, container, 
							HARD_RECURSION_LIMIT);
	}
}

std::list<TypeInfoP> DependencyDAG::getDependencies( TypeInfoP concrete){
	auto typei =  std::type_index(*concrete);
	return getDependencies( typei);
}

std::list<TypeInfoP> DependencyDAG::getDependencies( std::type_index & concrete){
	if( dependencies->find( concrete) != dependencies->end())
		return std::list<TypeInfoP>((*dependencies)[ concrete]);
	
	if(parent == nullptr)
		return std::list<TypeInfoP>();

	return parent->getDependencies(concrete);
}

void DependencyDAG::remove( TypeInfoP wired){
	throwingAssertion< NotReachableEx>(dependencies !=nullptr);
	
	auto concrete = dependencies->find( std::type_index(*wired) );
	if(concrete!=dependencies->end()){
		for( TypeInfoP abstractDep: concrete->second)
			removeDependant( wired, abstractDep);
		
		dependencies->erase(  std::type_index(*wired));
		return;
	}
	
	throwOrBreak< NotReachableEx>();
}

void DependencyDAG::removeDependant( TypeInfoP wired, TypeInfoP abstractDep){
	auto & abstract = dependants->find( std::type_index(*abstractDep) )->second;
	abstract.remove( wired);
	if(abstract.empty())
		dependants->erase( std::type_index(*abstractDep));
}

// actually the only way to free the memory held by unordered_map is by destroying the map
void DependencyDAG::clean(){						// for some funny reason even calling "clear" does not free the memory 
	dependencies 	= nullptr;		// and even calling "clear" followed by "rehash" leave some bytes allocated
	dependants		= nullptr;		// so we actually destroy the map to really free all possible memory
}


} // namespace priv
} // namespace Infector