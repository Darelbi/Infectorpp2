/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "priv/InfectorContext.hpp"


namespace Infector{

using ContextRaw		= priv::Context;
using destroyContext	= void(*)( ContextRaw*);
using ContextPointer	= std::unique_ptr< ContextRaw>;

template< typename Impl, typename... SmartPointers>
static void * factoryFunction(  const ContextPointer & ctx){
    return static_cast<void*>(
        new Impl( std::forward< typename SmartPointers::pointerType>( SmartPointers::resolve(ctx))...) );
}

template< typename T>
struct Shared{
    using pointerType = std::shared_ptr<T>;
    static std::shared_ptr<T> resolve( const ContextPointer & ctx){
        return std::static_pointer_cast<T>( ctx->instance( &typeid(T)) );
    }
};

template< typename T>
struct Unique{
    using pointerType = std::unique_ptr<T>;
    static std::unique_ptr<T> resolve( const ContextPointer & ctx){
        return std::unique_ptr<T>(static_cast<T*> (ctx->create(&typeid(T))));
    }
};

} // namespace Infector
