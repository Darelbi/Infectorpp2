#This file is borrowed from BadeEngine3D (C) 2015 Dario Oliveri

macro( add_library_type   name  type )

  add_library( ${name} ${type}  
                                $<TARGET_OBJECTS:infectorObj> )
								
  set_target_properties( ${name}  PROPERTIES
                                  PREFIX ""   )

    if(SHARED_BUILD)
    
        target_compile_definitions( ${name}
                                PRIVATE   INFECTOR_EXPORT
                                PRIVATE   INFECTOR_EXPORT
                                INTERFACE INFECTOR_IMPORT
                                )
    else()

        set_target_properties( ${name}  PROPERTIES
                                        PREFIX "static_"   )
    endif()
    
    #list( REMOVE_ITEM COMPILE_DEFINITIONS_RELEASE NDEBUG)
    
endmacro( add_library_type)