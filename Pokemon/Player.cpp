#include "stdafx.h"
#include "Player.h"

// Initializer functions

void Player::initVariables()
{
	this->timer = 0.f;
	this->soundTimer = 30.f;
}

void Player::initComponents()
{
}

void Player::initSoundEffects()
{
	if (!this->buffer.loadFromFile("Resources/Audios/Effects/walk.ogg"))
		throw "ERROR::PLAYER::FAILED_TO_LOAD_SOUND_EFFECTS";

	this->walkSound.setVolume(40.f);
	this->walkSound.setBuffer(buffer);
}

// Constructors / Destructors

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->initSoundEffects();

	this->setTexture(texture_sheet);
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 8.f, 50.f, 16.f, 14.f);
	this->createMovementComponent(300.f, 15.f, 10.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("WALK_UP", 10.f, 2, 0, 2, 3, 32, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 1, 0, 1, 3, 32, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 0, 0, 3, 32, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 3, 0, 3, 3, 32, 64);
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 0, 0, 32, 64);
}

Player::~Player()
{
}

// Functions

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

void Player::updateSound(const float& dt)
{
	if (this->movementComponent->getVelocity().x || this->movementComponent->getVelocity().y)
	{
		this->timer += 100.f * dt;
		std::cout << this->timer << "\n";
		if (this->timer >= this->soundTimer)
		{
			// Reset timer

			this->timer = 0.f;
			this->walkSound.play();
		}
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
