#include "stypch.h"
#include "OpenALAudio.h"

namespace Strype {

    Audio* Audio::s_Instance = new OpenALAudio();

    void OpenALAudio::InitImpl()
    {
        STY_CORE_INFO("Initializing OpenAL");

        m_ALCDevice = alcOpenDevice(nullptr);
        STY_CORE_ASSERT(m_ALCDevice, "Could not get sound device");

        m_ALCContext = alcCreateContext(m_ALCDevice, nullptr);
        STY_CORE_ASSERT(m_ALCContext, "Could not init OpenAL");

        int sucess = alcMakeContextCurrent(m_ALCContext);
        STY_CORE_ASSERT(sucess, "Can't make context current");

        const ALCchar* name = nullptr;
        if (alcIsExtensionPresent(m_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
            name = alcGetString(m_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
        if (!name || alcGetError(m_ALCDevice) != AL_NO_ERROR)
            name = alcGetString(m_ALCDevice, ALC_DEVICE_SPECIFIER);
        
        STY_CORE_INFO("Opened Audio Device: \"{0}\"", name);
    }

    void OpenALAudio::ShutdownImpl()
    {
        STY_CORE_INFO("Terminating OpenAL");

        alcMakeContextCurrent(nullptr);
        alcDestroyContext(m_ALCContext);
        alcCloseDevice(m_ALCDevice);
    }

    void OpenALAudio::PlaySoundImpl(std::string& filepath)
    {
    }
}
