file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    string(MAKE_C_IDENTIFIER "${name}" target_name)
    add_executable(${target_name} ${src})
    set_target_properties(${target_name} PROPERTIES OUTPUT_NAME "${name}")
endforeach()
