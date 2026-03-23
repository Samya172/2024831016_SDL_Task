#include <SDL3/SDL.h>

void Circle(SDL_Renderer* renderer, int x, int y, int r)
{
    for (int w = -r; w <= r; w++) {
        for (int h = -r; h <= r; h++) {
            if (w*w + h*h <= r*r) {
                SDL_RenderPoint(renderer, x + w, y + h);
            }
        }
    }
}

bool Collision(int x1, int y1, int x2, int y2, int r1, int r2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx*dx + dy*dy <= (r1 + r2) * (r1 + r2);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window =
        SDL_CreateWindow("Task", 800, 600, 0);

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, NULL);

    int task = 3;

    int x1 = 100, y1 = 300, r1 = 25;
    int x2 = 400, y2 = 300, r2 = 25;

    int speed = 5;

    SDL_Event event;
    int running = 1;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = 0;

            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                SDL_Keycode key = event.key.key;

                if (key == SDLK_1) task = 1;
                if (key == SDLK_2) task = 2;
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

        
        x1 += speed;
        if (x1 > 800) x1 = 0;

        
        bool hit = Collision(x1, y1, x2, y2, r1, r2);

      
        if (hit)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderClear(renderer);

        
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        Circle(renderer, x1, y1, r1);

        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        Circle(renderer, x2, y2, r2);

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}