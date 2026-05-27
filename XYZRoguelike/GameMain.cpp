// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include "LevelManager.h"
#include "Engine.h"
#include "Logger.h"
#include "Matrix2D.h"
#include "Player.h"
#include "ResourceSystem.h"

#include <SFML/Graphics.hpp>

using namespace XYZRoguelike;

int main() {
    // Configuring the logger
    auto logger = std::make_shared<Logger>();
    logger->addSink(std::make_shared<ConsoleSink>());
    logger->addSink(std::make_shared<FileSink>("log.txt"));
    LoggerRegistry::getInstance().registerLogger("global", logger);
    LoggerRegistry::getInstance().setDefaultLogger(logger);

    XYZEngine::RenderSystem::Instance()->SetMainWindow(
        new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike"));

    XYZEngine::ResourceSystem::Instance()->LoadTextureMap(
        "player", "Resources/MapsTexture/Player.png", {48, 63}, 4, false);
    XYZEngine::ResourceSystem::Instance()->LoadTexture(
        "ball", "Resources/Textures/ball.png");
    XYZEngine::ResourceSystem::Instance()->LoadTextureMap(
        "Walls", "Resources/MapsTexture/Walls.png", {16, 16}, 48, false);
    XYZEngine::ResourceSystem::Instance()->LoadTextureMap(
        "Floors", "Resources/MapsTexture/Floors.png", {16, 16}, 48, false);
    XYZEngine::ResourceSystem::Instance()->LoadTexture(
        "Explosion", "Resources/Textures/Explosion.png");

    ResourceSystem::Instance()->LoadSound(
        "BackgroundMusic", "Resources/Music/BackgroundMusic.wav");

    LevelManager::Instance()->LoadRandomLevels();

    XYZEngine::Engine::Instance()->Run();

    return 0;
}
