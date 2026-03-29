get_filename_component(CONTEST_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SOURCES "Q*.cpp")

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(contest_${CONTEST_ID}_${name} ${src})
endforeach()
