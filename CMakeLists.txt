cmake_minimum_required(VERSION 3.10)

# --- The Project Manifest ---
project(TankBattle_ChaosMaze VERSION 1.0.0 LANGUAGES CXX)

# --- The Standards (C++17) ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- The Supply Lines (Vendor Paths) ---
list(APPEND CMAKE_PREFIX_PATH 
    "${CMAKE_SOURCE_DIR}/vendor/SDL2"
    "${CMAKE_SOURCE_DIR}/vendor/SDL2_image"
    "${CMAKE_SOURCE_DIR}/vendor/SDL2_ttf"
)

# --- The Provisions (Dependencies) ---
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# --- The Blueprint (Include Paths) ---
include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# --- The Source Files ---
file(GLOB_RECURSE SOURCES "src/*.cpp")

# --- The Construction (Executable) ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- The Linkage (Libraries) ---
target_link_libraries(${PROJECT_NAME} 
    SDL2::SDL2 
    SDL2_image::SDL2_image 
    SDL2_ttf::SDL2_ttf 
    SDL2::SDL2main
)

# --- Post-Build: DLL Deployment ---
file(GLOB_RECURSE SDL2_DLLS   "${CMAKE_SOURCE_DIR}/vendor/SDL2/lib/x64/*.dll")
file(GLOB_RECURSE IMAGE_DLLS  "${CMAKE_SOURCE_DIR}/vendor/SDL2_image/lib/x64/*.dll")
file(GLOB_RECURSE TTF_DLLS    "${CMAKE_SOURCE_DIR}/vendor/SDL2_ttf/lib/x64/*.dll")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_DLLS}
        ${IMAGE_DLLS}
        ${TTF_DLLS}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Deploying strictly x64 DLLs to the target directory..."
)

# --- Post-Build: Assets ---
# We ensure the 'assets' folder is present. 
if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
        COMMENT "Provisioning assets to the target directory..."
    )
endif()

# --- The "Run" Command ---
add_custom_target(run
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Commencing the Game."
)