#include <SFML/Graphics.hpp>
#include <iostream>
#include "settings.h"
#include "func.h"
#include <ctime>
using namespace sf;


int main()
{
   

    srand(time(nullptr));

 
    //создание объектов
    RectangleShape bat;
    init_bat(bat, bat_collor, bat_startpos);
    CircleShape ball;
    init_ball(ball, ball_color, ball_startpos);

    //скорость мяча
    float arr_speed[]{ 1.f,2.f,3.f,4.f,5.f ,- 5.f,-4.f,-3.f,-2.f,-1.f };
    int index = rand() % 10;
    float speedx = arr_speed[index];
    index = rand() % 5;
    float speedy = arr_speed[index];


    //счет
    int player_score = 0;
    Font font;
    font.loadFromFile("DS-DIGIB.ttf");
    Text player_score_text;
    init_text(player_score_text, player_score, font, char_size, text_start_pos);
   
    // Объект, который, собственно, является главным окном приложения
    RenderWindow window(VideoMode(window_size, window_size), "SFML Works!");

    window.setFramerateLimit(fps);

    // Главный цикл приложения. Выполняется, пока открыто окно
    while (window.isOpen())
    {
        // Обрабатываем очередь событий в цикле
        Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed)
                // тогда закрываем его
                window.close();
        }

        //движение мяча
        ball.move(speedx, speedy);

        //отскок мяча от боковых стенок

        //от левой
        if (ball.getPosition().x <= 0) {
            speedx *= -1;
        }
        //от правой
        if (ball.getPosition().x + 2*ball_r>= window_size) {
            speedx *= -1;
        }

        //отскок от верхней стенки
        if (ball.getPosition().y <= 0) {
            speedy *= -1;
        }

        //отскок от ракетки
        Vector2f mid_left{ ball.getPosition().x, ball.getPosition().y + ball_r };
        Vector2f mid_right{ ball.getPosition().x + 2*ball_r, ball.getPosition().y + ball_r };
        Vector2f mid_bottom{ ball.getPosition().x + ball_r, ball.getPosition().y + 2*ball_r};
        //от верхней
        if (point_in_rect(bat,mid_bottom)) {
            speedy *= -1;
            player_score++;
           player_score_text.setString(std::to_string(player_score));
        }
        //от левой
        if (point_in_rect(bat, mid_left)) {
            speedx *= -1;  
        }
        //от правой
        if (point_in_rect(bat, mid_right)) {
            speedx *= -1;
        }
        
        //управление ракеткой
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            bat.move(bat_speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            bat.move(-bat_speed,0);
        }

        //границы для ракетки
        if (bat.getPosition().x < 0) {
           bat.move(bat_speed, 0);
        }
        if (bat.getPosition().x + bat_size.x > window_size) {
            bat.move(-bat_speed, 0);
        }


        //условие конца игры
        if (ball.getPosition().y + 2 * ball_r >= window_size) {
            window.close();
        }

        // Отрисовка окна 
        window.clear();
        //отрисовка объектов
        window.draw(bat);
        window.draw(ball);
        window.draw(player_score_text);
        
        window.display();
    }
    return 0;
}