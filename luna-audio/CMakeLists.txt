add_subdirectory(interface)

add_library(audio STATIC audio.cpp)
target_link_libraries(audio PUBLIC audio_interface)
install(FILES audio.hpp DESTINATION ${header_install_dir} COMPONENT devel)