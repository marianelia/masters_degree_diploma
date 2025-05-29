set(CMAKE_MFC_FLAG 2)

set(ncad_include_dirs ${NCadSDK}/include/arxgate
                      ${NCadSDK}/include
                      ${NCadSDK}/include-x64
                      ${NCadSDK}/include-x64/Drawing/ActiveX
                      ${NCadSDK}/include-x64/Drawing/ActiveX/OdaX
                      ${NCadSDK}/include/MAPI
                      ${NCadSDK}/include/nrxgate
                      ${NCadSDK}/include/nrxdbgate
                      ${NCadSDK}/include/nrxhostgate
                      ${NCadSDK}/include/nrxuigate
                      ${NCadSDK}/include/nrxpropsgate)

set(ncad_lib_dirs     ${NCadSDK}/lib-x64
                      ${NCadSDK}/lib-x64/TD)

set(ncad_libs     nrxdbgate.lib
                      nrxhostgate.lib
                      nrxuigate.lib
                      nrxgatemgd.lib
                      nrxpropsgate.lib
                      mcgel.lib
                      hostopm.lib
                      hostQt.lib)

set(ncad_definitions NCAD UNICODE _USRDLL HOST_NO_MFC _UNICODE _WIN32_IE=0x060 WIN WIN32 _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1 _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT=1)

macro(ncad_setup_target target)
    target_link_libraries(${target} PRIVATE ${ncad_libs})
    target_link_directories(${target} PRIVATE ${ncad_lib_dirs})
    target_include_directories(${target} PRIVATE ${ncad_include_dirs})
    target_compile_definitions(${target} PRIVATE ${ncad_definitions})
    target_link_options(${target} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_compile_features(${target} PRIVATE cxx_std_14)
    set_target_properties(${target} PROPERTIES SUFFIX ".nrx")
endmacro(ncad_setup_target)

