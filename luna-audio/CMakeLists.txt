add_subdirectory(interface)

add_library(audio STATIC audio.cpp)
target_link_libraries(audio PUBLIC audio_interface)