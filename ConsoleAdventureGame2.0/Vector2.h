// Coordonnees et directions de la grille : x avance horizontalement, y verticalement.
#pragma once

struct Vector2 {
    int x = 0;
    int y = 0;
    constexpr Vector2() = default;
    constexpr Vector2(int xValue, int yValue) : x(xValue), y(yValue) {}
    constexpr Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }
    constexpr Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
    constexpr bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
    constexpr bool operator!=(const Vector2& other) const { return !(*this == other); }
};
