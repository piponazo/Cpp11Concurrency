message( STATUS "------------------ General configuration for ${PROJECT_NAME} ${VERSION} -----------------")
message( STATUS )
message( STATUS "Build mode:                ${CMAKE_BUILD_TYPE}")
message( STATUS "CMake Generator:           ${CMAKE_GENERATOR}")
message( STATUS "Compiler:                  ${CMAKE_CXX_COMPILER_ID}")
message( STATUS "C++ flags (Release):       ${CMAKE_CXX_FLAGS_RELEASE}")
message( STATUS "C++ flags (Debug):         ${CMAKE_CXX_FLAGS_DEBUG}")
message( STATUS "C++ flags (Both):          ${CMAKE_CXX_FLAGS}")
message( STATUS "CMAKE_INSTALL_PREFIX=      ${CMAKE_INSTALL_PREFIX}" )
message( STATUS )
