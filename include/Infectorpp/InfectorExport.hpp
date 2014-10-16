/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice at the end of this file
*******************************************************************************/
#pragma once

#if defined(BUILD_DLL)||defined(USE_DLL)
    #ifdef BUILD_DLL
        #define INFECTOR_API __declspec(dllexport)
    #else
        #define INFECTOR_API __declspec(dllimport)
    #endif
#else
    #define INFECTOR_API
#endif

/*******************************************************************************
   TODO: INSERT COPYRIGHT NOTICE
*******************************************************************************/
