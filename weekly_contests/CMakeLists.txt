file(GLOB CONTEST_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")

foreach(contest_dir ${CONTEST_DIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${contest_dir}")
        add_subdirectory(${contest_dir})
    endif()
endforeach()
