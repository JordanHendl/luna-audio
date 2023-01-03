set(luna_audio_interface_headers device.hpp
                               manager.hpp
                               format.hpp
                               sound.hpp
                               stream.hpp
)

set(luna_audio_interface_sources device.cpp
                               manager.cpp
                               sound.cpp
                               stream.cpp
                               ../impl/impl.cpp
)

add_library(audio_interface STATIC ${luna_audio_interface_sources})
target_link_libraries(audio_interface PRIVATE OpenAL::OpenAL)
install(FILES ${luna_audio_interface_headers} DESTINATION ${header_install_dir}/interface COMPONENT devel)