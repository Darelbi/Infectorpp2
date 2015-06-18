/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/
#pragma once
#include <unordered_map>
#include <list>
#include <tuple>


namespace Infector {
namespace priv {
class ConcreteContainer;
	
/** Dependency Direct Acyclic Graph.
	This collect dependencies between concrete types only ( A bit pointless
	tracing dependencies between interfaces since interfaces has no ctor).
	A Dependency DAG lives in one context only (Context inheritance is resolved
	by context only by creating a SymbolTable)*/
class DependencyDAG{
	
	/** Coloring of nodes when touched during a visit.*/
	enum class Color: int{
		BLACK,  //
		BLUE,	// interface without concrete type
		PURPLE, // marked before a visit to detect circular dependency
		WHITE   // touched during a visit (no need to revisit)
	};
	
	using Concrete = TypeInfoP;
	using Abstract = TypeInfoP;
	using Edge =  std::tuple< Color, Concrete, Abstract>;
	
	using EdgeMap = std::unordered_map< std::type_index, 
										std::list<  Edge> >;

	EdgeMap 	concretes;
	TypeInfoP 	guard = nullptr;

public:
	
	void setGuard( TypeInfoP g);
	
								//type resolution is container responsibility
	void dependOn( TypeInfoP wired, TypeInfoP abstractDep, 
					ConcreteContainer * container);
	
	void remove( TypeInfoP concrete);
	
	DependencyDAG() = default;
	~DependencyDAG() = default;
	
private:

	void checkGuardBreaking( TypeInfoP);
};
	

} // namespace priv
} // namespace Infector