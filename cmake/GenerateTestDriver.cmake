
macro( generate_test_driver   arg1  )

  file(GLOB sourceFiles
      "*.cpp")

  foreach(path ${sourceFiles})
    get_filename_component( FileName ${path} NAME)
    list(APPEND FileNames ${FileName})
  endforeach()

  #I'd liked to do Unity compile also for tests, but if one fails to compile
  #we don't know wich other tests are passing.
  create_test_sourcelist( Tests
    ${arg1}.cpp
    ${FileNames} 
  )

  add_executable( ${arg1} ${Tests})
  #add_dependencies(build_and_test ${arg1})

  set(TestsToRun ${Tests})
  list(REMOVE_ITEM TestsToRun ${arg1}.cpp)

  foreach( test ${TestsToRun})
    get_filename_component( TestName ${test} NAME_WE)
    add_test( ${TestName}  ${arg1}  ${TestName})
  endforeach()
  
  #cleanup, generate_test_driver could be called multiple times
  unset(FileNames)
  unset(Tests)

endmacro( generate_test_driver)