/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "priv/InfectorTypes.hpp"
#include "priv/InfectorAbstractContext.hpp"
#include <type_traits>
#include <typeindex>
#include <memory>
#include <utility>

namespace Infector{

class Container;
class Context;

template< typename T>
void isMultiBaseVariadic(){

}

template <typename T, typename I, typename... Contracts>
void isMultiBaseVariadic(){
    static_assert( std::is_abstract< I>::value,
                    "T must implement an abstract class (forgot '= 0' in method declaration?)");
    static_assert( std::is_base_of< I, T>::value,
                    "I must be base class for T");

    isMultiBaseVariadic< T, Contracts...>();
}

template< typename T, typename... Contracts>
void isMultiBase(){
    //prevent service locator antipattern
    static_assert( !std::is_same< T, Infector::Container>::value
                  , "Cannot Inject Infector::Container!");
				  
	static_assert( !std::is_same< T, Infector::Context>::value
                  , "Cannot Inject Infector::Context!");

    //prevent service locator antipattern
    static_assert( !std::is_base_of< Infector::Container, T>::value
                  , "Cannot Inject Infector::Container or its subclasses!");
				  
	static_assert( !std::is_base_of< Infector::Context, T>::value
                  , "Cannot Inject Infector::Context or its subclasses!");

    static_assert(  sizeof...( Contracts)>0 //if no contracts don't use "bind X As"
                      , " There must be at least 1 interface ");

    isMultiBaseVariadic< T, Contracts...>();
}

template< typename T>
void isWireable(){
        // These tests are not redundant because wiring and binding could happen
	// in different compile units
	static_assert( !std::is_same< T, Infector::Container>::value
				  , "Cannot wire Infector::Container!");

			  
	static_assert( !std::is_same< T, Infector::Context>::value
			  , "Cannot wire Infector::Context!");
			  
	//prevent service locator
	static_assert( !std::is_base_of< Infector::Container, T>::value
				  , "Cannot wire Infector::Container or its subclasses!");
				  
	static_assert( !std::is_base_of< Infector::Context, T>::value
                  , "Cannot wire Infector::Context or its subclasses!");
}


template< typename Impl, typename... SmartPointers>
static void * factoryFunction( priv::Context * ctx){
    return static_cast<void*>(
        new Impl( std::forward< typename SmartPointers::pointerType>( 
	
				SmartPointers::resolve(ctx))... // hook to potentially inject
				) 			);					// anything...
}

template< typename Impl, typename... SmartPointers>
static std::shared_ptr<void> instancesFactoryFunction( priv::Context * ctx){
    return std::static_pointer_cast<void>( std::make_shared<Impl>(
	
					std::forward< typename SmartPointers::pointerType>( 
				SmartPointers::resolve(ctx))... 
				) 			);
}

template< typename T>
struct Shared{
    using pointerType = std::shared_ptr<T>;
	using type = T;
    static std::shared_ptr<T> resolve( priv::Context * ctx){
        return std::static_pointer_cast<T>( ctx->instance( &typeid(T)) );
    }
};

template< typename T>
struct Unique{
    using pointerType = std::unique_ptr<T>;
	using type = T;
    static std::unique_ptr<T> resolve( priv::Context * ctx){
        //return static_cast<T*> (ctx->create(&typeid(T)));  //can return plain pointer now :D
		return std::unique_ptr<T>(static_cast<T*> (ctx->buildComponent(&typeid(T)))); 
    }
};

} // namespace Infector
