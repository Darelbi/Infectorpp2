/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <list>
#include <typeindex>
#include <unordered_map>
#include "InfectorTypes.hpp"


namespace Infector {
namespace priv {
class ConcreteContainer;
	
/** Dependency Direct Acyclic Graph.
	This collect dependencies between concrete types only ( A bit pointless
	tracing dependencies between interfaces since interfaces has no ctor).
	A Dependency DAG lives in one context only (Context inheritance is resolved
	by context only by creating a SymbolTable)*/
class DependencyDAG{

public:

	DependencyDAG( DependencyDAG * parent);
	~DependencyDAG();
	
	void setGuard( TypeInfoP g);
	
								//type resolution is container responsibility
	void dependOn( TypeInfoP wired, TypeInfoP abstractDep, 
					ConcreteContainer * container);
	
	void remove( TypeInfoP concrete);
	
	/** clean memory used by DAG.*/
	void clean();
	
	using EdgeMap = std::unordered_map< std::type_index, 
										std::list< TypeInfoP> >;
	
	std::list<TypeInfoP> getDependencies( TypeInfoP concrete);

	//
	//when you realize your Typo was "TypO" instead of "TypE" u.u ...
	std::list<TypeInfoP> getDependencies( std::type_index & concrete);
	
private:

	using EdgeMapPtr = std::shared_ptr<EdgeMap>;

	EdgeMapPtr 	dependencies 	= std::make_shared<EdgeMap>();
	EdgeMapPtr	dependants		= std::make_shared<EdgeMap>();
	
	TypeInfoP 		guard = nullptr;
	DependencyDAG*	parent = nullptr;

	void removeDependant( TypeInfoP wired, TypeInfoP abstractDep);

	void addDependency( TypeInfoP wired, TypeInfoP abstractDep);
	
	void addDependant( TypeInfoP wired, TypeInfoP abstractDep);

	void checkGuardBreaking( 	TypeInfoP currentNode,
								ConcreteContainer * container,
								int HARD_RECURSION_LIMIT);
};
	

} // namespace priv
} // namespace Infector