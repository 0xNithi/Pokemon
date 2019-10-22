#include "stdafx.h"
#include "SoundEffectComponent.h"

SoundEffectComponent::SoundEffectComponent()
{
}

SoundEffectComponent::~SoundEffectComponent()
{
	for (auto& i : this->soundeffects)
	{
		delete i.second;
	}
}

void SoundEffectComponent::addSoundEffect(const std::string key, float sound_effect_timer, std::string path)
{
	this->soundeffects[key] = new SoundEffect(sound_effect_timer, path);
}

void SoundEffectComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max)
{
	this->soundeffects[key]->play(dt, (modifier / modifier_max));
}
