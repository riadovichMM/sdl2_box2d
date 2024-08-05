#pragma once
#include "../include/SDL2/SDL.h"
#include "../include/SDL2_image/SDL_image.h"
#include "../include/box2d/box2d.h"

class Entity {
    public:
        Entity(SDL_Renderer* p_renderer, SDL_Texture* texture, b2World* world, int window_width, int window_height, int scale, float position_x, float position_y);
        ~Entity();

        void draw();
        void update();
    private:
        SDL_Renderer* p_renderer;
        b2World* world;
        b2BodyDef bodyDef;
        b2Body* body;
        b2PolygonShape shape;
        b2FixtureDef fixture;
        SDL_Rect rect;
        SDL_Texture* texture;
        float boxSize;
        float angle;
        b2Vec2 position;
        SDL_Point center;
        int window_width;
        int window_height;
        int scale;
};
