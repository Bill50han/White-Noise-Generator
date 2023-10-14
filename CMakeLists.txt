cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "J:/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(White_Noise_Generator
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "White_Noise_Generator VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(White_Noise_Generator
    source/version.h
    source/myplugincids.h
    source/mypluginprocessor.h
    source/mypluginprocessor.cpp
    source/myplugincontroller.h
    source/myplugincontroller.cpp
    source/mypluginentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
    target_sources(White_Noise_Generator
        PRIVATE
            resource/myplugineditor.uidesc
    )
    target_link_libraries(White_Noise_Generator
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(White_Noise_Generator
        RESOURCES
            "resource/myplugineditor.uidesc"
    )
endif(SMTG_ADD_VSTGUI)
# -------------------

smtg_target_add_plugin_snapshots (White_Noise_Generator
    RESOURCES
        resource/3D332BC808475EEB832A453EDBC774C9_snapshot.png
        resource/3D332BC808475EEB832A453EDBC774C9_snapshot_2.0x.png
)

target_link_libraries(White_Noise_Generator
    PRIVATE
        sdk
)

smtg_target_configure_version_file(White_Noise_Generator)

if(SMTG_MAC)
    smtg_target_set_bundle(White_Noise_Generator
        BUNDLE_IDENTIFIER com.bill50han.whitenoise
        COMPANY_NAME "Bill50han"
    )
    smtg_target_set_debug_executable(White_Noise_Generator
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(White_Noise_Generator PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT White_Noise_Generator)

        smtg_target_set_debug_executable(White_Noise_Generator
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
