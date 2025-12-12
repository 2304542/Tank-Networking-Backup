#pragma once
#include "tank.h"
#include "projectile.h"
class Game
{
public:
	Game();

	void LoadTextures();
	void HandleEvents(const std::optional<sf::Event> event);
	int HandleCollision();
	void FireBullet();
	void Update(float dt);
	// Network update now gets a collection of tank messages for multiple tanks.
	void NetworkUpdate(float dt, TankMessage tData);
	void Render(sf::RenderWindow& window);
	void AddTank(std::int32_t body_tex, std::int32_t barrel_tex, sf::Vector2f position);
	void RemoveTank();
	void AddProjectile(std::string projectile_tex, sf::Vector2f direction, sf::Vector2f position);
	TankMessage GetNetworkUpdate();

private:
	// We can now have more thank 1 tank in the game.
	std::vector<std::unique_ptr<Tank>> tanks;
	std::vector<std::unique_ptr<Projectile>> projectiles;
	std::unique_ptr<sf::Sprite> background;
	// We'll hold all textures here so we only need to load them once at game creation.
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::unordered_map<std::int32_t, std::shared_ptr<sf::Texture>> playerTextures;
	std::unordered_map<std::int32_t, std::shared_ptr<sf::Texture>>  barrelTextures;

};


