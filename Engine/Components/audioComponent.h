#pragma once
#include "Audio/audioChannel.h"
#include "includes.h"

namespace vl
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;
		~AudioComponent();

		CLASS_CLONE(AudioComponent);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Initialize() override;
		void Update() override;

		void Play();
		void Stop();

	public:
		AudioChannel m_channel;

		std::string sound_name;
		bool play_on_start{ false };
		bool loop{ false };
		float volume{ 1 };
		float pitch{ 1 };



	};
}