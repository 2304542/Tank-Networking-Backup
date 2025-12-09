#include "game.h"

Game::Game()
{
	LoadTextures();
	// Initialis sprite for background.
	background = std::make_unique<sf::Sprite>(*textures["ground_sand"]);
	background->setTextureRect(sf::IntRect({ 0, 0 }, { 640, 480 }));

	// We're not loading the tank by default any more.

}


void Game::LoadTextures() {
	textures["ground_sand"] = std::make_shared<sf::Texture>("Assets/tileSand1.png");
	textures["ground_sand"]->setRepeated(true);
	textures["cannonball"] = std::make_shared<sf::Texture>("Assets/Cannonball.png");

	playerTextures[0] = std::make_shared<sf::Texture>("Assets/blackBarrel.png");
	playerTextures[0] = std::make_shared<sf::Texture>("Assets/blackTank.png");
	playerTextures[1] = std::make_shared<sf::Texture>("Assets/blueBarrel.png");
	playerTextures[1] = std::make_shared<sf::Texture>("Assets/blueTank.png");
	playerTextures[2] = std::make_shared<sf::Texture>("Assets/greenBarrel.png");
	playerTextures[2] = std::make_shared<sf::Texture>("Assets/greenTank.png");
}

void Game::FireBullet() {
	sf::Vector2f shoot_direction = {

			std::cos((tanks.at(0)->barrelRotation - sf::degrees(90)).asRadians()),
			std::sin((tanks.at(0)->barrelRotation - sf::degrees(90)).asRadians())
	};
	AddProjectile("cannonball", tanks.at(0)->position, -shoot_direction);
}

void Game::HandleEvents(const std::optional<sf::Event> event)
{
	// Handle key press events passed from window.
	if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
		if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
			tanks.at(0)->isMoving.forward = true;
			tanks.at(0)->isMoving.backward = false;
		}
		else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
			tanks.at(0)->isMoving.forward = false;
			tanks.at(0)->isMoving.backward = true;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
			tanks.at(0)->isMoving.left = true;
			tanks.at(0)->isMoving.right = false;
		}
		else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
			tanks.at(0)->isMoving.left = false;
			tanks.at(0)->isMoving.right = true;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Q) {
			tanks.at(0)->isRotating.clockwise = true;
			tanks.at(0)->isRotating.counterclockwise = false;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::E) {
			tanks.at(0)->isRotating.clockwise = false;
			tanks.at(0)->isRotating.counterclockwise = true;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
			FireBullet();
			projectiles.at(0)->isFired = true;
		}
	}

	// Handle key release events passed from window.
	else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
		if (keyReleased->scancode == sf::Keyboard::Scancode::W)
			tanks.at(0)->isMoving.forward = false;
		if (keyReleased->scancode == sf::Keyboard::Scancode::S)
			tanks.at(0)->isMoving.backward = false;
		if (keyReleased->scancode == sf::Keyboard::Scancode::A)
			tanks.at(0)->isMoving.left = false;
		if (keyReleased->scancode == sf::Keyboard::Scancode::D)
			tanks.at(0)->isMoving.right = false;
		if (keyReleased->scancode == sf::Keyboard::Scancode::Q)
			tanks.at(0)->isRotating.clockwise = false;
		if (keyReleased->scancode == sf::Keyboard::Scancode::E)
			tanks.at(0)->isRotating.counterclockwise = false;

	}


}

int Game::HandleCollision() {

	for (int i = 0; i < tanks.size(); i++) {
		for (int j = 0; j < projectiles.size(); j++) {
			if (projectiles[j].get()->projectile.get()->getGlobalBounds().findIntersection(tanks[i].get()->body.get()->getGlobalBounds())) {
				int playerID = tanks[i]->playerID;
				tanks.erase(tanks.begin() + i);
				projectiles.erase(projectiles.begin() + j);
				return playerID;
				break;
			}
		}
	}
}

void Game::Update(float dt)
{
	for (int i = 0; i < tanks.size(); i++) {
		tanks.at(0)->Update(dt);
	}
	for (int j = 0; j < projectiles.size(); j++) {
		projectiles.at(0)->Update(dt);
	}

}

void Game::NetworkUpdate(float dt, TankMessage tData) {
	// Force position updates from network data.
	tanks.at(tData.id)->position = tData.position;
	tanks.at(tData.id)->bodyRotation = tData.rotation;
	tanks.at(tData.id)->barrelRotation = tData.aim;
	// Update tank with new position.
	// NOTE: This assumets no inputs were detected and so the tank will only move according to 
	// network updates. This is not ideal and prone to unexpected behaviour if game is extended
	// to be fully multiplayer. 
	tanks.at(tData.id)->Update(dt);



}

void Game::Render(sf::RenderWindow& window)
{

	window.draw(*background);
	for (int i = 0; i < tanks.size(); i++) {
		tanks.at(i)->Render(window);
	}
	for (int j = 0; j < projectiles.size(); j++) {
		projectiles.at(j)->Render(window);
	}
}
void Game::AddTank(std::int32_t body_tex, std::int32_t barrel_tex, sf::Vector2f position)
{
	std::unique_ptr<Tank> tank = std::make_unique<Tank>(Tank(playerTextures[body_tex], playerTextures[barrel_tex]));
	tank->position = position;


	tanks.push_back(std::move(tank));
}

void Game::RemoveTank()
{
	for (int i = 0; i < tanks.size(); i++) {
		tanks.erase(tanks.begin() + i);
	}
}

void Game::AddProjectile(std::string projectile_tex, sf::Vector2f direction, sf::Vector2f position)
{
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(textures[projectile_tex]);
	projectile->projectilePosition = direction;
	projectile->projectileSpawn = position;

	projectiles.push_back(std::move(projectile));
}

TankMessage Game::GetNetworkUpdate()
{
	return { -1.f, 0, tanks.at(0)->position, tanks.at(0)->bodyRotation, tanks.at(0)->barrelRotation };
}


