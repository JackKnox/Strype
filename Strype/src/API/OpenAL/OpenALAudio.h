#pragma once

#include "Strype/Core/Audio.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace Strype {

    class OpenALAudio : public Audio
    {
    protected:
        void PlaySoundImpl(std::string& filepath) override;

        void InitImpl() override;
        void ShutdownImpl() override;
    private:
        ALCdevice* m_ALCDevice;
        ALCcontext* m_ALCContext;
    };

}