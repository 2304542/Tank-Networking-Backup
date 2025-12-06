#include "projectile.h"

Projectile::Projectile(std::shared_ptr<sf::Texture> projectileTexture) {

	projectile = std::make_unique<sf::Sprite>(*projectileTexture);

	projectile->setOrigin((sf::Vector2f)projectile->getTextureRect().getCenter());

	projectile->setPosition(projectilePosition);
	
	projectile->setRotation(fireDirection);
}

void Projectile::Update(float dt) {

	sf::Vector2f shoot_direction = {

		std::cos((fireDirection - sf::degrees(90)).asRadians()),
		std::sin((fireDirection - sf::degrees(90)).asRadians())
	};

	if (isFired) {
		projectilePosition += shoot_direction * shootSpeed * dt;
	}

	projectile->setPosition(projectilePosition);
}

const void Projectile::Render(sf::RenderWindow& window) {
	window.draw(*projectile);
	
}
