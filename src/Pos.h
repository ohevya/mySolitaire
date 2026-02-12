#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <array>

constexpr sf::Vector2f StockPos{ 50.f, 300.f };
constexpr sf::Vector2f WastePos{ 250.f, 300.f };

constexpr float TableauHeight = 300.f;
constexpr float TableauX =      500.f;

constexpr std::size_t FoundationSize = 4;
constexpr std::size_t TableauSize = 7;

constexpr std::array<sf::Vector2f, FoundationSize> FoundationPos{
    sf::Vector2f{700.f,100.f},
    sf::Vector2f{850.f,100.f},
    sf::Vector2f{1000.f,100.f},
    sf::Vector2f{1150.f,100.f}
};

constexpr float CardHeightOffset =  35.f;
constexpr float CardXoffset         = 150.f;

constexpr sf::FloatRect WasteArea{ WastePos, {125.f, 181.5f} };
