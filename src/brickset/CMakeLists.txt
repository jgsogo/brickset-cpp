cmake_minimum_required(VERSION 2.8)


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/generated)

#Add application files and gsoap dependencies
SET(SRC_FILES
    brickset.h
    brickset.cpp
    set.h
    getSets.h
    ${CMAKE_BINARY_DIR}/generated/soapBricksetAPIv2SoapProxy.cpp
    ${CMAKE_BINARY_DIR}/generated/soapC.cpp
)
SET(INTERFACE_FILES
    ../include/set.h
    ../include/brickset.h
)
source_group("Interface Files" FILES ${INTERFACE_FILES})

#some files are generated by gsoap
#set_source_files_properties(${CMAKE_BINARY_DIR}/generated/soapBricksetAPIv2SoapProxy.cpp PROPERTIES GENERATED TRUE ) 
#set_source_files_properties(${CMAKE_BINARY_DIR}/generated/soapC.cpp PROPERTIES GENERATED TRUE ) 


# WSDL and proxy
# TODO: Do not do it LIVE, it is better to version it somewhere in the repo to deal with versions.
set(BRICKSET_WSDL "https://brickset.com/api/v2.asmx?WSDL")
set(HTTPS_PROXY_ARG "")
if(DEFINED ENV{HTTPS_PROXY})
    string(REGEX REPLACE "https?://" "" HTTPS_PROXY_ARG $ENV{HTTPS_PROXY})
    set(HTTPS_PROXY_ARG "-r${HTTPS_PROXY_ARG}")
    message(">>>> Use proxy ${HTTPS_PROXY_ARG}")
endif()

#Create a cmake target that generate gsoap files
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/generated/bindings.h
    COMMAND ${GSOAP_WSDL2H} ${HTTPS_PROXY_ARG} -o ${CMAKE_BINARY_DIR}/generated/bindings.h ${BRICKSET_WSDL}
    COMMENT "CREATING BINDING FILES"
)
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/generated/soapBricksetAPIv2SoapProxy.cpp ${CMAKE_BINARY_DIR}/generated/soapC.cpp
    COMMAND ${GSOAP_SOAPCPP2} -j -x -C -d ${CMAKE_BINARY_DIR}/generated ${CMAKE_BINARY_DIR}/generated/bindings.h -I ${GSOAP_IMPORT_DIR}
    DEPENDS ${CMAKE_BINARY_DIR}/generated/bindings.h
    COMMENT "CREATING STUBS AND GLUE CODE"
)
add_custom_target(GSOAP_GENERATION_TARGET DEPENDS ${CMAKE_BINARY_DIR}/generated/soapBricksetAPIv2SoapProxy.cpp)


add_library(brickset ${SRC_FILES} ${INTERFACE_FILES})
target_link_libraries(brickset PRIVATE ${CONAN_LIBS} ${GSOAP_SSL_CXX_LIBRARIES})
target_include_directories(brickset PRIVATE ${CMAKE_BINARY_DIR}/generated ${GSOAP_INCLUDE_DIR})
set_property(TARGET brickset PROPERTY CXX_STANDARD 17)
set_property(TARGET brickset PROPERTY CXX_STANDARD_REQUIRED ON)
#Make sure that the client is compiled only after gsoap has been processed
add_dependencies(brickset GSOAP_GENERATION_TARGET)
