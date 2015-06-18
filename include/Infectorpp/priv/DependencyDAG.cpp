/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/
#pragma once
#include "DependencyDAG.hpp"
#include "ExceptionHandling.hpp"

// TODO: unittest this blob:: REFACTOR EXCEPTIONS (THEY MUST EXTEND std::exception_somthing)
namespace Infector {
namespace priv {
	
void DependencyDAG::setGuard( TypeInfoP g){
	guard = g;
	concretes[ std::type_index(*g)] = std::list< Edge>();
}

void DependencyDAG::dependOn( TypeInfoP wired, TypeInfoP abstractDep,
									ConcreteContainer * container){
										
	std::list< Edge> & inserted =
				concretes.find( std::type_index(*wired) )->second;
	
	for (auto it = inserted.begin(); it != inserted.end();  ++it )
	{
		auto & tup = *it; //check all pairs to see if abstractDep is present
		
		if( std::get<2>(tup) == abstractDep){  //dependency already in list

			
			if( std::get<0>(tup) == Color::BLUE){
				TypeInfoP p = container->getConcreteFromInterface( std::get<2>(tup));

				if(p != nullptr)
					std::get<0>(tup) = Color::WHITE;

				std::get<1>(tup) = p;
			}

			return; //skip to not add again same dependency
		}
	}

	//add new dependency
	TypeInfoP p = container->getConcreteFromInterface( abstractDep);
	inserted.push_back( std::make_tuple( p!=nullptr? Color::WHITE: Color::BLUE,
										p,
										abstractDep));

	//circular dependency check
	if(p!=nullptr)
		checkGuardBreaking(p);
}

void DependencyDAG::checkGuardBreaking( TypeInfoP currentNode){
	std::list< Edge> & inserted = 
		concretes.find( std::type_index(*currentNode) )->second;
		
	for (auto&& tup : inserted){
		if( std::get<0>(tup) == Color::WHITE){
			if( std::get<1>(tup) == guard)
				throwOrBreak< CircularDependencyEx>();
			
			checkGuardBreaking( std::get<1>(tup));
		}
	}
}

void DependencyDAG::remove( TypeInfoP concrete){
	auto it = concretes.find( std::type_index(*concrete) );
		if(it!=concretes.end())
			concretes.erase( it);
}


} // namespace priv
} // namespace Infector