file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    file(RELATIVE_PATH relative_src "${CMAKE_CURRENT_SOURCE_DIR}" "${src}")
    string(MAKE_C_IDENTIFIER "data_structures_${relative_src}" target_name)
    add_executable(${target_name} ${src})
    set_target_properties(${target_name} PROPERTIES OUTPUT_NAME "${name}")
endforeach()
