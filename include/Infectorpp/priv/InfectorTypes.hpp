/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include <functional>
#include <typeinfo>
#include <memory>


namespace Infector {
namespace priv {

    using TypeInfoP = const std::type_info *;

    /** Convert from concrete class to abstract class. */
    template< typename Concrete, typename Interface> //Derived to Base
    void * upcast( void * concrete_ptr){
        Concrete * implem = static_cast<Concrete*>(concrete_ptr);
        Interface * interface = static_cast<Interface*>(implem); //trivial cast
        return static_cast<void *>(interface); //now to void*
    }

    /*template< typename Concrete, typename... Dependencies>
    std::shared_ptr<void*> create_shared(){

    }*/

    /** Nicer to look at than "returnType(*)(Args)" function pointer */
    using UpcastSignature  = void*(*)(void*);
    //using EmplaceSignature = std::function<void(void*)>;
    //using FactorySignature = std::function<void*(void)>;

    /** Simpler than std::pair.*/
    /*template< typename First, typename Second>
    class UnTypedPair{
    public:
        First       first;
        Second      second;
    };*/

    /** Used to type homogenous pairs to different types. */
    /*template< typename First, typename Second, typename Alias>
    class TypedPair{
    public:

        using first_type = First;
        using second_type = Second;
        using alias_type = Alias;
        using pair_type = TypedPair;

        First       first;
        Second      second;

        TypedPair( const UnTypedPair< First, Second> & p)
            :first ( p.first)
            ,second( p.second)
        { }
    };*/

    /** Most elegant piece of code of the library. NOW UNUSED*/
    /*template< typename T>
    using EmplacePairT = TypedPair< EmplaceSignature, UpcastSignature, T>;

    using EmplacePair = UnTypedPair< EmplaceSignature, UpcastSignature>;*/



    /*template< typename T>
    using FactoryPairT = TypedPair< FactorySignature, UpcastSignature, T>;

    using FactoryPair = UnTypedPair< FactorySignature, UpcastSignature>;

    template< typename TO, typename FROM>
    std::shared_ptr<TO> re_caster(const FROM & p){     //TODO: NICE:D!!!!!
        return p.operator TO(); //used in deprecated version. But suggest workaround for new version
    }

    template< typename TO, typename FROM>
    std::unique_ptr<TO> re_caster(const FROM & p){     //TODO: NICE:D!!!!!
        return p.operator TO(); //used in deprecated version. But suggest workaround for new version
    }*/

} // namespace priv
} // namespace Infector
