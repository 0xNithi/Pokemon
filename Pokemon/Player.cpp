#include "Player.h"

// Initializer functions

void Player::initVariables()
{
}

void Player::initComponents()
{
}

// Constructors / Destructors

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setTexture(texture_sheet);
	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 0, 0, 32, 64);
}

Player::~Player()
{
}

// Functions

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->animationComponent->play("IDLE_LEFT", dt);
}
