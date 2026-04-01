#include <SDL3/SDL.h>

void Circle(SDL_Renderer* renderer, int x, int y, int r)
{
    for (int w = -r; w <= r; w++) {
        for (int h = -r; h <= r; h++) {
            if (w * w + h * h <= r * r) {
                SDL_RenderPoint(renderer, (float)(x + w), (float)(y + h));
            }
        }
    }
}

bool Collision(int x1, int y1, int x2, int y2, int r1, int r2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx * dx + dy * dy <= (r1 + r2) * (r1 + r2);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Task Selection", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    int task = 1;

    
    int x1 = 100, y1 = 300, r1 = 25;
    int x2 = 400, y2 = 300, r2 = 25;
    int speed = 5;

   
    int r_task2 = 10;

    SDL_Event event;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;

            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                SDL_Keycode key = event.key.key;

                if (key == SDLK_1) task = 1;
                if (key == SDLK_2) { task = 2; r_task2 = 10; } 
                if (key == SDLK_3) task = 3;

              
                if (task == 3)
                {
                    if (key == SDLK_LEFT)  x2 -= 10;
                    if (key == SDLK_RIGHT) x2 += 10;
                    if (key == SDLK_UP)    y2 -= 10;
                    if (key == SDLK_DOWN)  y2 += 10;
                }
            }
        }

        -
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        SDL_RenderClear(renderer);

       
        if (task == 1) 
        {
            
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            Circle(renderer, 400, 300, 50);
        }
        else if (task == 2) 
        {
            
            r_task2 += 2;
            if (r_task2 > 300) r_task2 = 10; 

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            Circle(renderer, 400, 300, r_task2);
        }
        else if (task == 3) 
        {
            
            x1 += speed;
            if (x1 > 800) x1 = 0;

            bool hit = Collision(x1, y1, x2, y2, r1, r2);

           
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            Circle(renderer, x1, y1, r1);

            
            if (hit)
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            else
                SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
            
            Circle(renderer, x2, y2, r2);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}