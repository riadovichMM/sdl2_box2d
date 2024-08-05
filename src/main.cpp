#include <iostream>
#include <vector>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2_image/SDL_image.h"
#include "../include/box2d/box2d.h"
#include "./entity.hpp"

int window_width = 800;
int window_height = 640;
int scale = 20; // 1 metr = 20 pixels


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* p_window = SDL_CreateWindow("Box2d practice 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
    SDL_Renderer* p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);

    // load texture
    SDL_Surface* bmp = IMG_Load("./texture.jpeg");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(p_renderer, bmp);
    SDL_FreeSurface(bmp);
    bmp = nullptr;



    // init box2d world
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);


    // create static body

    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    float ground_x = 0.0f;
    float ground_y = -10.0f;
    groundDef.position.Set(ground_x, ground_y);
    
    b2Body* groundBody = world.CreateBody(&groundDef);

    b2PolygonShape groundShape;
    float ground_hw = 15.0f;
    float ground_hh = 5.0f;
    // hw = 20
    // hh = 5
    groundShape.SetAsBox(ground_hw, ground_hh);

    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    
    groundBody->CreateFixture(&groundFixtureDef);


    SDL_Rect groundRepresent;

    groundRepresent.x = (window_width / 2) + (ground_x * scale) - (ground_hw * scale);
    groundRepresent.y = (window_height / 2) - (ground_y * scale) - (ground_hh * scale);
    groundRepresent.h = ground_hh * 2 * scale; 
    groundRepresent.w = ground_hw * 2 * scale;


    std::vector<Entity> vectorOfEntity;

    // Entity entity1(p_renderer, texture, &world, window_width, window_height, scale);



    SDL_Rect rect;
    rect.h = 50;
    rect.w = 50;
    rect.x = 50;
    rect.y = 50;




    int start = 0;
    int frameCountForShowFPS = 0;
    int frameCountForUpdateState = 0;
    SDL_Event event;
    bool run = true;
    while(run) {
        start = SDL_GetTicks();
        // user input
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = false;
            }


            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    std::cout << event.button.x << " " << event.button.y << std::endl;
                    Entity entity(p_renderer, texture, &world, window_width, window_height, scale, static_cast<float>(event.button.x), static_cast<float>(event.button.y));
                    vectorOfEntity.push_back(entity);
                }
            }
        }

        // update state
        frameCountForUpdateState++;
        if (frameCountForUpdateState == 100) {
            world.Step(1.0f / 60.0f, 6, 6);
            for (int i = 0; i < vectorOfEntity.size(); i++) {
                vectorOfEntity[i].update();
            }
            // entity1.update();
            frameCountForUpdateState = 0;
        }




        // drawing
        SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
        SDL_RenderClear(p_renderer);

        SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, 0);

        // entity1.draw();

        for (int i = 0; i < vectorOfEntity.size(); i++) {
            vectorOfEntity[i].draw();
        }
        
        SDL_RenderDrawRect(p_renderer, &groundRepresent);
        SDL_RenderPresent(p_renderer);

        frameCountForShowFPS++;
        if (frameCountForShowFPS == 500) {
            int end = SDL_GetTicks();
            int delta = end - start;
            // std::cout << delta << std::endl;
            if (delta > 0) {
                std::cout << 1000.0f / delta << std::endl;
            }
            frameCountForShowFPS = 0;
        }
    }

    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyWindow(p_window);
    SDL_Quit();

    return 0;
}
