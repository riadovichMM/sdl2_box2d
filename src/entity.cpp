#include <iostream>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2_image/SDL_image.h"
#include "../include/box2d/box2d.h"
#include "./entity.hpp"


Entity::Entity(SDL_Renderer* p_renderer, SDL_Texture* texture, b2World* world, int window_width, int window_height, int scale, float position_x, float position_y) {
    std::cout << static_cast<float>(position_x) << " " << position_y << std:: endl;

    this->p_renderer = p_renderer;
    this->texture = texture;
    this->boxSize = 1.0f;
    this->angle = 0.0f;
    this->position.x = -((window_width / 2) - position_x) / scale;
    this->position.y = ((window_height / 2) - position_y) / scale;
    this->window_width = window_width;
    this->window_height = window_height;
    this->scale = scale;
    this->center.x = 0;
    this->center.y = 0;


    this->bodyDef.position.Set(this->position.x, this->position.y);
    this->bodyDef.angle = this->angle;
    this->bodyDef.type = b2_dynamicBody;
    this->body = world->CreateBody(&this->bodyDef);
    this->shape.SetAsBox(this->boxSize, this->boxSize);
    this->fixture.shape = &this->shape;
    this->fixture.density = 1.0f;
    this->fixture.friction = 0.3f;
    this->body->CreateFixture(&this->fixture);
    

}


void Entity::update() {
    b2Vec2 tempPosition = body->GetPosition();
    float tempAngle = body->GetAngle();

    // переводим из системы координат box2d в -> систему кординат sdl2
    this->rect.x = ((this->window_width / 2) + (tempPosition.x * this->scale)) - (this->boxSize * this->scale);
    this->rect.y = ((this->window_height / 2) - (tempPosition.y * this->scale)) - (this->boxSize * this->scale);
    this->rect.w = (this->boxSize * 2) * this->scale;
    this->rect.h = (this->boxSize * 2) * this->scale;

    this->center.x = this->rect.w / 2;
    this->center.y = this->rect.h / 2;

    this->position = tempPosition;
    this->angle = tempAngle;
    // std::cout << this->angle << std::endl;
}


void Entity::draw() {
    SDL_RenderCopyEx(this->p_renderer, this->texture, nullptr, &this->rect, -this->angle * 180 / M_PI, &this->center, SDL_FLIP_NONE);
}


Entity::~Entity() {}

