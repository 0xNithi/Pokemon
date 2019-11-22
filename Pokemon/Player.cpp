#include "stdafx.h"
#include "Player.h"

// Initializer functions

void Player::initVariables()
{
	this->coins = 0;
}

void Player::initComponents(float x, float y, sf::Texture& texture_sheet)
{
	this->setTexture(this->sprite, texture_sheet);
	this->setPosition(this->sprite, x, y);

	this->createHitboxComponent(this->sprite, 8.f, 50.f, 16.f, 14.f);
	this->createMovementComponent(300.f, 1500.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createSoundEffectComponent();

	this->animationComponent->addAnimation("WALK_UP", 10.f, 2, 0, 2, 3, 32, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 1, 0, 1, 3, 32, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 0, 0, 3, 32, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 3, 0, 3, 3, 32, 64);
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 0, 0, 32, 64);

	this->soundeffectComponent->addSoundEffect("WALKING", 15.f, "Resources/Audios/Effects/walk.ogg");
	this->soundeffectComponent->addSoundEffect("HEALING", 15.f, "Resources/Audios/Effects/healing.ogg");
}

// Constructors / Destructors

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->initComponents(x, y, texture_sheet);
}

Player::~Player()
{
}

// Functions

const unsigned long& Player::getCoins() const
{
	return this->coins;
}

void Player::setCoins(int value)
{
	this->coins += value;
}

void Player::playHeal()
{
	this->soundeffectComponent->play("HEALING");
}

void Player::updateAnimation(const float& dt)
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

void Player::updateSoundEffect(const float& dt)
{
	if (this->movementComponent->getState(MOVING))
	{
		this->soundeffectComponent->play("WALKING", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->updateSoundEffect(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	//this->hitboxComponent->render(target);
}
