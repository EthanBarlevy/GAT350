#include "audioChannel.h"
#include "Core/logger.h"
#include "fmod.hpp"

namespace vl
{
    bool AudioChannel::IsPlaying()
    {
        if (!m_channel) 
        { 
            LOG("Error, channel is null");
            return false; 
        }

        bool isPlaying;
        m_channel->isPlaying(&isPlaying);

        return isPlaying;
    }

    void AudioChannel::Stop()
    {
        if (IsPlaying()) { m_channel->stop(); }
    }

    void AudioChannel::SetPitch(float pitch)
    {
        if (IsPlaying()) { m_channel->setPitch(pitch); }
    }

    void AudioChannel::SetVolume(float volume)
    {
        if (IsPlaying()) { m_channel->setVolume(volume); }
    }

    float AudioChannel::GetPtich()
    {
        float pitch{ 0 };
        if (IsPlaying()) { m_channel->getPitch(&pitch); }
        return pitch;
    }

    float AudioChannel::GetVolume()
    {
        float volume{ 0 };
        if (IsPlaying()) { m_channel->getPitch(&volume); }
        return volume;
    }
}

