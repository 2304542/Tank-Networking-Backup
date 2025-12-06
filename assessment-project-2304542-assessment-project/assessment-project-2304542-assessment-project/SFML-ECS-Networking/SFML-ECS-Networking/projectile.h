#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "tank.h"
#include "projectile_message.h"
class Projectile
{
	
public:
	Projectile(std::shared_ptr<sf::Texture> projectileTexture);

	void Update(float dt);
	const void Render(sf::RenderWindow& window);

	
	
	sf::Vector2f projectilePosition = { 0.f, 0.f };

	

	bool isFired = false;

private:
	std::unique_ptr<sf::Sprite> projectile;
	sf::Angle fireDirection = sf::degrees(0);
	
	float shootSpeed = 250.f;


};

