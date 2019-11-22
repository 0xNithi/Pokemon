#include "stdafx.h"
#include "Pokemon.h"

Pokemon::Pokemon(unsigned id, unsigned level)
{
	std::stringstream ss;
	ss << "Resources/Images/Sprites/Pokemon/Followers/" << id << ".png";

	if (!this->buddyTexture.loadFromFile(ss.str()))
	{
		throw "ERROR::POKEMON::FAILED_TO_LOAD_BUDDY_TEXTURE";
	}

	this->createHitboxComponent(this->sprite, 20.f, 50.f, 24.f, 14.f);
	this->createMovementComponent(300.f, 1500.f, 1000.f);
	this->createAnimationComponent(this->buddyTexture);
	this->createPokemonAttributeComponent(id, level);
	this->createSoundEffectComponent();

	this->animationComponent->addAnimation("WALK_UP", 10.f, 2, 0, 2, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 1, 0, 1, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 0, 0, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 3, 0, 3, 1, 64, 64);
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 0, 0, 64, 64);

	this->soundeffectComponent->addSoundEffect("ATTACK", 15.f, "Resources/Audios/Effects/attack.ogg");
	this->soundeffectComponent->addSoundEffect("COUNTER", 15.f, "Resources/Audios/Effects/counter.ogg");
	this->soundeffectComponent->addSoundEffect("HEAL", 15.f, "Resources/Audios/Effects/heal.ogg");
	this->soundeffectComponent->addSoundEffect("ULTIMATE", 15.f, "Resources/Audios/Effects/ultimate.ogg");
}

Pokemon::~Pokemon()
{
}

PokemonAttributeComponent* Pokemon::getPokemonAttributeComponent()
{
	return this->pokemonAttributeComponent;
}

void Pokemon::playSound(std::string key)
{
	this->soundeffectComponent->play(key);
}

void Pokemon::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_UP))
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	else if (this->movementComponent->getState(MOVING_LEFT))
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	else if (this->movementComponent->getState(MOVING_DOWN))
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	else if (this->movementComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
}

void Pokemon::update(const float& dt)
{
	std::stringstream ss;
	ss << "Resources/Images/Sprites/Pokemon/Followers/" << this->pokemonAttributeComponent->id << ".png";

	if (!this->buddyTexture.loadFromFile(ss.str()))
	{
		throw "ERROR::POKEMON::FAILED_TO_LOAD_BUDDY_TEXTURE";
	}

	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Pokemon::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	//this->hitboxComponent->render(target);
}
