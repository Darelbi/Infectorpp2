#This file is borrowed from BadeEngine3D (C) 2015 Dario Oliveri

macro( add_library_type   name  type )

	set(Yellow      "${Esc}[33m")
	set(ColourReset "${Esc}[m")

	add_library( ${name} ${type}  
                                $<TARGET_OBJECTS:infectorObj> )
								
	set_target_properties( ${name}  PROPERTIES
                                  PREFIX ""   )

    if(SHARED_BUILD) # external variable setted outside the macro
	
		# BROKEN IN SOME WAY: NEED INVESTIGATION
        #target_compile_definitions( ${name}
        #                        PRIVATE   INFECTOR_EXPORT
        #                        PRIVATE   INFECTOR_EXPORT
        #                        INTERFACE INFECTOR_IMPORT
        #                        )
		
		add_definitions(-DINFECTOR_EXPORT)
		
    else()

        set_target_properties( ${name}  PROPERTIES
                                        PREFIX "static_"   )
		
    endif()
    
    #list( REMOVE_ITEM COMPILE_DEFINITIONS_RELEASE NDEBUG)
    
endmacro( add_library_type)