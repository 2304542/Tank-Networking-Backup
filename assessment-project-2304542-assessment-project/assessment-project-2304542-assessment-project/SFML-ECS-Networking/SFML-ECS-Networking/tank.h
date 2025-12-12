#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "tank_message.h"
#include "projectile.h"
class Tank
{
public:
	// Colour string will be used in path for image texture loading. 
	// Will work with "red", "blue", "green" and "black".
	// 
	// FIXME: this is not the cleanest solution as you can make a typo which will cause
	// texture to fail to load. Ideally should use enum/map or similar solution.
	Tank(std::shared_ptr<sf::Texture> bodyTexture, std::shared_ptr<sf::Texture> barrelTexture);


	void Update(float dt);
	const void Render(sf::RenderWindow& window);

	sf::Vector2f position = { 0.f, 0.f };
	sf::Angle barrelRotation = sf::radians(0);
	sf::Angle bodyRotation = sf::radians(0);
	//float bodyRotationAngle = bodyRotation.asRadians();


	std::unique_ptr<sf::Sprite> body;
	std::unique_ptr<sf::Sprite> barrel;

	int playerID;


	struct {
		bool clockwise = false;
		bool counterclockwise = false;
	} isRotating;

	struct {
		bool forward = false;
		bool backward = false;
		bool left = false;
		bool right = false;
	} isMoving;

private:
	// Temporary placeholder texture, make sue to replace before rendering the sprite.
	//sf::Texture placeholder = sf::Texture(sf::Vector2u(1, 1));




	float movementSpeed = 150.f;
	float rotationSpeed = 200.f;

	// Saving current colour here in case we need to send elsewhere.
	std::string colorString = "";
};


