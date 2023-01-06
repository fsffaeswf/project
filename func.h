#pragma once
#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"

void init_bat(sf::RectangleShape& bat, const sf::Color BatCollor, const sf::Vector2f Batpos) {
	bat.setSize(bat_size);
	bat.setFillColor(BatCollor);
	bat.setPosition(Batpos);
}
void init_ball(sf::CircleShape& bat, const sf::Color BatCollor, const sf::Vector2f Batpos) {
	bat.setRadius(ball_r);
	bat.setFillColor(BatCollor);
	bat.setPosition(Batpos);
}
bool point_in_rect(sf::RectangleShape bat, sf::Vector2f point) {
	float batx = bat.getPosition().x;
	float baty = bat.getPosition().y;
	return(point.x >= batx && point.x <= batx + bat_size.x) &&
		(point.y >= baty && point.y <= baty + bat_size.y);
}
void init_text(sf::Text& scoreText, int score, sf::Font& font,
	const int charSize, const sf::Vector2f textStartPos) {
	scoreText.setString(std::to_string(score));
	scoreText.setFont(font);
	scoreText.setCharacterSize(charSize);
	scoreText.setPosition(textStartPos);
}