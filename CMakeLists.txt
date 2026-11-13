cmake_minimum_required(VERSION 3.20)
project(ZeninShowcase LANGUAGES C CXX OBJC OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJCXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")

# ImGui core sources
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_metal.mm
)

# App sources
set(APP_SOURCES
    src/MainApp.mm
    src/ZeninUI.cpp
    src/ZeninUI.h
)

add_executable(ZeninShowcase
    ${APP_SOURCES}
    ${IMGUI_SOURCES}
)

target_include_directories(ZeninShowcase PRIVATE
    src
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link iOS frameworks
target_link_libraries(ZeninShowcase PRIVATE
    "-framework Foundation"
    "-framework UIKit"
    "-framework Metal"
    "-framework MetalKit"
    "-framework QuartzCore"
)

# Configure iOS bundle properties
set_target_properties(ZeninShowcase PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/src/Info.plist"
    MACOSX_BUNDLE_BUNDLE_NAME "ZeninShowcase"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.zenin.ios.showcase"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.zenin.ios.showcase"
    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2" # iPhone, iPad
    XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
    XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ""
)
