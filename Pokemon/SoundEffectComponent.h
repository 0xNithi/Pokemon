#ifndef SOUNDEFFECTCOMPONENT_H
#define SOUNDEFFECTCOMPONENT_H

class SoundEffectComponent
{
private:

	class SoundEffect
	{
	public:

		// Variables

		sf::SoundBuffer buffer;
		sf::Sound sound;
		float soundEffectTimer;
		float timer;

		SoundEffect(float sound_effect_timer, std::string path)
			: soundEffectTimer(sound_effect_timer), timer(0.f)
		{
			if (!this->buffer.loadFromFile(path))
				throw "ERROR::PLAYER::FAILED_TO_LOAD_SOUND_EFFECTS";

			this->sound.setVolume(70.f);
			this->sound.setBuffer(buffer);
		}

		// Functions

		void play(const float& dt, float mod_percent)
		{
			// Update timer

			if (mod_percent < 0.5f)
				mod_percent = 0.5f;

			this->timer += mod_percent * 100.f * dt;
			if (this->timer >= this->soundEffectTimer)
			{
				// Reset timer

				this->timer = 0.f;

				// Sound effect

				this->sound.play();
			}
		}
	};
	
	std::map<std::string, SoundEffect*> soundeffects;

public:
	SoundEffectComponent();
	virtual ~SoundEffectComponent();

	// Functions

	void addSoundEffect(const std::string key, float sound_effect_timer, std::string path);

	void play(const std::string key, const float& dt, const float& modifier, const float& modifier_max);
};

#endif