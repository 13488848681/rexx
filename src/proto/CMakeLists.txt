#rexx proto module CmakeLists.txt -- librexx_proto.a

set(LIB_REXX_PROTO rexx_proto)
set(PROTO_SRC
    cpp/common.pb.cc cpp/consensus.pb.cc cpp/chain.pb.cc
 	cpp/overlay.pb.cc cpp/merkeltrie.pb.cc cpp/monitor.pb.cc
)

#Generate static library files
add_library(${LIB_REXX_PROTO} ${PROTO_SRC})

#Specify compiling options for target objects
target_compile_options(${LIB_REXX_PROTO}
    PUBLIC -std=c++11 
    PUBLIC -DASIO_STANDALONE
    PUBLIC -D${OS_NAME}
)
