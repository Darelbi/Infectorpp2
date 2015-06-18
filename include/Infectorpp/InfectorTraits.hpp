/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2015 Oliveri Dario

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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

template< typename T>
void isMultiBaseVariadic(){

}

template <typename T, typename I, typename... Contracts>
void isMultiBaseVariadic(){
    static_assert( std::is_abstract< I>::value,
                    "T must implement an abstract class");
    static_assert( std::is_base_of< I, T>::value,
                    "I must be base class for T");

    static_assert(  std::is_destructible< I>::value
                      , " I must be destructible");

    isMultiBaseVariadic< T, Contracts...>();
}

template< typename T, typename... Contracts>
void isMultiBase(){
    //prevent service locator antipattern
    static_assert( !std::is_same< T, Infector::Container>::value
                  , "Cannot Inject Infector::Container!");

    //prevent service locator antipattern
    static_assert( !std::is_base_of< Infector::Container, T>::value
                  , "Cannot Inject Infector::Container or its subclasses!");

    static_assert(  sizeof...( Contracts)>0 //if no contracts don't use "bind X As"
                      , " There must be at least 1 interface ");

    static_assert(  std::is_destructible< T>::value
                      , " T must be destructible");

    isMultiBaseVariadic< T, Contracts...>();
}

template< typename T>
void isWireable(){
        // These tests are not redundant because wiring and binding could happen
        // in different compile units
        static_assert( !std::is_same< T, Infector::Container>::value
                      , "Cannot wire Infector::Container!");

        //prevent service locator
        static_assert( !std::is_base_of< Infector::Container, T>::value
                      , "Cannot wire Infector::Container or its subclasses!");

        static_assert(  std::is_destructible<T>::value
                      , " T must be destructible");
}


template< typename Impl, typename... SmartPointers>
static void * factoryFunction( priv::Context * ctx){
    return static_cast<void*>(
        new Impl( std::forward< typename SmartPointers::pointerType>( 
	
				SmartPointers::resolve(ctx))... // hook to potentially inject
				) 			);					// anything...
}

template< typename T>
struct Shared{
    using pointerType = std::shared_ptr<T>;
	using Type = T;
    static std::shared_ptr<T> resolve( priv::Context * ctx){
        return std::static_pointer_cast<T>( ctx->instance( &typeid(T)) );
    }
};

template< typename T>
struct Unique{
    using pointerType = std::unique_ptr<T>;
	using Type = T;
    static std::unique_ptr<T> resolve( priv::Context * ctx){
        //return static_cast<T*> (ctx->create(&typeid(T)));  //can return plain pointer now :D
		return std::unique_ptr<T>(static_cast<T*> (ctx->create(&typeid(T))));
    }
};

} // namespace Infector
