#include "projectile.h"

Projectile::Projectile(std::shared_ptr<sf::Texture> projectileTexture) {

	projectile = std::make_unique<sf::Sprite>(*projectileTexture);

	projectile->setOrigin((sf::Vector2f)projectile->getTextureRect().getCenter());

	//projectile->setPosition(projectilePosition);

	//projectile->setRotation(fireDirection);
}

void Projectile::Update(float dt) {


	//if (isFired) {
	projectilePosition += projectileSpawn * shootSpeed * dt;


	projectileCounter = projectileClock.restart().asSeconds();
	projectileTimer += projectileCounter;
	if (projectileTimer >= projectileLifespan) {
		isFired = false;
	}

	if (projectilePosition.x >= 640 || projectilePosition.y > 480) {
		isFired = false;
	}


	projectile->setPosition(projectilePosition);
}



const void Projectile::Render(sf::RenderWindow& window) {
	window.draw(*projectile);

}
