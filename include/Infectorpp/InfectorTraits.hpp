/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include <type_traits>


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

    static_assert(  sizeof...( Contracts)>0 //if no contracts don't use "As"
                      , " There must be at least 1 interface ");

    static_assert(  std::is_destructible< T>::value
                      , " T must be destructible");

    /// Commented out since this is referred to default constructor only
    /*static_assert(  std::is_constructible<T>::value
                      , " T must be constructible");*/

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

        /// Commented out since this is referred to default constructor only
        /*static_assert(  std::is_constructible<T>::value
                      , " T must be constructible");*/
}

} // namespace Infector
