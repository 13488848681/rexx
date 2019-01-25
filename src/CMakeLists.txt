cmake_minimum_required(VERSION 2.8)

project(rexx)
add_compile_options(-g -O2)
add_definitions(-DSVNVERSION=\"${SVNVERSION}\")
message(STATUS "-DSVNVERSION="${SVNVERSION})

set( V8_LIB_PATH "linux")
set( OS_NAME "OS_LINUX")
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
    MESSAGE(STATUS "current platform: Linux ")  
	set( OS_NAME "OS_LINUX")
	set(REXX_LINKER_FLAGS "-Wl,-dy -lpthread -lrt -ldl")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")  
    MESSAGE(STATUS "current platform: Darwin")  
	set( OS_NAME "OS_MAC")
	set(REXX_LINKER_FLAGS "-Wl, -lpthread -ldl")
	set( V8_LIB_PATH "mac")
ELSE ()  
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")  
ENDIF ()  

set(REXXCHAIN rexxchain)
set(REXX_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(REXX_ROOT_DIR ${REXX_SRC_DIR}/..)
set(LIBRARY_OUTPUT_PATH ${REXX_ROOT_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${REXX_ROOT_DIR}/bin)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

execute_process(COMMAND make all WORKING_DIRECTORY ${REXX_SRC_DIR}/3rd)

include_directories(
    ${REXX_SRC_DIR}
    ${REXX_SRC_DIR}/3rd/basic/include/v8
    ${REXX_SRC_DIR}/3rd/protobuf/src
    ${REXX_SRC_DIR}/3rd/jsoncpp/include
    ${REXX_SRC_DIR}/3rd/sqlite
    ${REXX_SRC_DIR}/3rd/rocksdb/include
    ${REXX_SRC_DIR}/3rd/pcre-8.39
    ${REXX_SRC_DIR}/3rd/websocketpp
    ${REXX_SRC_DIR}/3rd/bzip2-1.0.6
    ${REXX_SRC_DIR}/3rd/zlib-1.2.8
    ${REXX_SRC_DIR}/3rd/asio/include
    ${REXX_SRC_DIR}/3rd/openssl/include
    ${REXX_SRC_DIR}/3rd/http
    ${REXX_SRC_DIR}/3rd/libscrypt
)

link_directories(
    ${REXX_SRC_DIR}/3rd/protobuf/src/.libs
    ${REXX_SRC_DIR}/3rd/rocksdb
    ${REXX_SRC_DIR}/3rd/pcre-8.39/.libs
    ${REXX_SRC_DIR}/3rd/jsoncpp/libs
    ${REXX_SRC_DIR}/3rd/openssl
    ${REXX_SRC_DIR}/3rd/zlib-1.2.8
    ${REXX_SRC_DIR}/3rd/libscrypt
    ${REXX_SRC_DIR}/3rd/bzip2-1.0.6
    ${REXX_SRC_DIR}/3rd/basic/lib
    ${REXX_SRC_DIR}/3rd/curl/lib/.libs/
    ${REXX_SRC_DIR}/3rd/v8_target/${V8_LIB_PATH}/
    ${LIBRARY_OUTPUT_PATH}
)

set(REXX_DEPENDS_LIBS protobuf rocksdb pcreposix pcrecpp pcre json ssl crypto z bz2 scrypt)

add_subdirectory(3rd/http)
add_subdirectory(3rd/ed25519-donna)
add_subdirectory(glue)
add_subdirectory(utils)
add_subdirectory(proto)
add_subdirectory(ledger)
add_subdirectory(common)
add_subdirectory(librexx_tools)
add_subdirectory(overlay)
add_subdirectory(consensus)
add_subdirectory(monitor)
add_subdirectory(main)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
	add_subdirectory(daemon)
	set(REXX_SCRIPTS ${REXX_ROOT_DIR}/deploy)
	install(
		PROGRAMS ${REXX_SCRIPTS}/rexx ${REXX_SCRIPTS}/rexxd ${REXX_SCRIPTS}/start-stop-daemon
		DESTINATION ${REXXCHAIN}/scripts
	)
ENDIF ()  

install(
    DIRECTORY ${REXX_ROOT_DIR}/bin/
    DESTINATION ${REXXCHAIN}/bin
    FILES_MATCHING PATTERN "*.bin" PATTERN "*.dat"
)

install(
    DIRECTORY ${REXX_ROOT_DIR}/build/win32/config/
    DESTINATION ${REXXCHAIN}/config
    FILES_MATCHING PATTERN "rexx-mainnet.json" PATTERN "rexx-testnet.json" PATTERN "rexx-single.json"
)

install(
    DIRECTORY ${REXX_ROOT_DIR}/build/win32/jslib/
    DESTINATION ${REXXCHAIN}/jslib
    FILES_MATCHING PATTERN "*.js"
)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
	set(SUPPLEMENT ${REXX_ROOT_DIR}/build/linux/MakeSupplement)
	set(FIX_DIR ${CMAKE_INSTALL_PREFIX}/${REXXCHAIN})
	message(STATUS "install dir: ${FIX_DIR}")

	file(WRITE ${SUPPLEMENT} "soft_link:\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s ${FIX_DIR}/scripts/rexx /etc/init.d/rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s ${FIX_DIR}/scripts/rexxd /etc/init.d/rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexx /etc/rc1.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexx /etc/rc1.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexx /etc/rc2.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexx /etc/rc3.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexx /etc/rc4.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexx /etc/rc5.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexxd /etc/rc1.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexxd /etc/rc1.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexxd /etc/rc2.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexxd /etc/rc3.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexxd /etc/rc4.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo ln -s -f /etc/init.d/rexxd /etc/rc5.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\tsudo mkdir -p ${FIX_DIR}/data;\n")
	file(APPEND ${SUPPLEMENT} "\tsudo mkdir -p ${FIX_DIR}/coredump;\n")

	file(APPEND ${SUPPLEMENT} "\nuninstall:\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc1.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc2.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc3.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc4.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc5.d/S99rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/init.d/rexx;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc1.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc2.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc3.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc4.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/rc5.d/S50rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -f /etc/init.d/rexxd;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -rf ${FIX_DIR}/bin;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -rf ${FIX_DIR}/cfca;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -rf ${FIX_DIR}/config;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -rf ${FIX_DIR}/scripts\n")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")  
    set(SUPPLEMENT ${REXX_ROOT_DIR}/build/mac/MakeSupplement)
	set(FIX_DIR ${CMAKE_INSTALL_PREFIX}/${REXXCHAIN})
	message(STATUS "install dir: ${FIX_DIR}")

	file(WRITE ${SUPPLEMENT} "soft_link:\n")
	file(APPEND ${SUPPLEMENT} "\tsudo mkdir -p ${FIX_DIR}/data;\n")
	file(APPEND ${SUPPLEMENT} "\tsudo mkdir -p ${FIX_DIR}/coredump;\n")

	file(APPEND ${SUPPLEMENT} "\nuninstall:\n")
	file(APPEND ${SUPPLEMENT} "\trm -rf ${FIX_DIR}/bin;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -rf ${FIX_DIR}/cfca;\\\n")
	file(APPEND ${SUPPLEMENT} "\trm -rf ${FIX_DIR}/config;\\\n")
ELSE ()  
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")  
ENDIF ()  
