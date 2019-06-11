project(soil)

set(LIB_SOURCES
    src/image_dxt.cpp
    src/image_helper.cpp
    src/soil.cpp
    src/stb_image_aug.cpp
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES} )
add_library(tobanteGaming::Soil ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS=1)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
