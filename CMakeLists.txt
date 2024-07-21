cmake_minimum_required(VERSION 3.10)
project(sophon_stream)

set(CMAKE_CXX_STANDARD 17)

if (NOT DEFINED TARGET_ARCH)
    set(TARGET_ARCH pcie)
endif()

if (${TARGET_ARCH} STREQUAL "pcie")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -fprofile-arcs")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -rdynamic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -rdynamic")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

    # set(FFMPEG_DIR  /opt/sophon/sophon-ffmpeg-latest/lib/cmake)
    # find_package(FFMPEG REQUIRED)
    # include_directories(${FFMPEG_INCLUDE_DIRS})
    # link_directories(${FFMPEG_LIB_DIRS})

    # set(OpenCV_DIR  /opt/sophon/sophon-opencv-latest/lib/cmake/opencv4)
    # find_package(OpenCV REQUIRED)
    # include_directories(${OpenCV_INCLUDE_DIRS})
    # link_directories(${OpenCV_LIB_DIRS})
    # set(OPENCV_LIBS opencv_imgproc opencv_core opencv_highgui opencv_imgcodecs opencv_videoio)

    set(LIBSOPHON_DIR  /opt/sophon/libsophon-current/data/libsophon-config.cmake)
    find_package(LIBSOPHON REQUIRED)
    include_directories(${LIBSOPHON_INCLUDE_DIRS})
    link_directories(${LIBSOPHON_LIB_DIRS})

    link_libraries(pthread)
    link_libraries(dl)
    include_directories(./include)
    # set(profiler
    #     src/bmprofiler.cc
    #     src/log.c
    # )
    add_library(profiler SHARED
        src/bmprofiler.cc
        src/log.c
    )

    target_link_libraries(profiler -ldl ${OPENCV_LIBS} -lpthread)
    target_compile_options(profiler PRIVATE -g)


elseif(${TARGET_ARCH} STREQUAL "soc")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -fprofile-arcs -ftest-coverage -g -rdynamic")
    # set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  -fprofile-arcs -ftest-coverage -rdynamic")
    add_compile_options(-fPIC)
    set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
    set(CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc)
    set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
    set(BM_LIBS bmlib bmrt bmcv yuv)
    set(JPU_LIBS bmjpuapi bmjpulite)
    include_directories("${SOPHON_SDK_SOC}/include/")
    include_directories("${SOPHON_SDK_SOC}/include/opencv4")
    link_directories("${SOPHON_SDK_SOC}/lib/")

    # set(OPENCV_LIBS opencv_imgproc opencv_core opencv_highgui opencv_imgcodecs opencv_videoio)
    link_libraries(pthread)
    link_libraries(dl)
    include_directories(./include)

    add_library(profiler SHARED
        src/bmprofiler.cc
        src/log.c
    )

    target_link_libraries(profiler -ldl ${OPENCV_LIBS} -lpthread)
    target_compile_options(profiler PRIVATE -g)

endif()
