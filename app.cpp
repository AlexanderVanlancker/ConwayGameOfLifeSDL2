#include <iostream>
#include <stdio.h>

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

// Utility macros
#define CHECK_ERROR(test, message) \
    do { \
        if((test)) { \
            fprintf(stderr, "%s\n", (message)); \
            exit(1); \
        } \
    } while(0)

// Get a random number from 0 to 255
int randInt(int rmin, int rmax) {
    return rand() % rmax + rmin;
}

bool twoNeighborcheck(int row, int col, const int grid[][100]){
    //add edges
    int n=0;
    for(int i=row-1;i<=row+1;i++){
        for(int j=col-1;j<=col+1;j++){
            if(grid[i][j]==1)
                n++;
        }
    }
    if(n > 2 && n <=4)
        return true;
    return false;
}


bool newCell(int row, int col, const int grid[][100]){
    //add edges
    int n=0;

    for(int i=row-1;i<=row+1;i++){
        for(int j=col-1;j<=col+1;j++){
            if(grid[i][j]==1)
                n++;
        }
    }
    if(row == 59 && col ==61){
        std::cout << n << "=n";
    }
    return n == 3 ? true : false;
}

int main(int argc, char * argv[]){
    // Initialize the random number generator
    srand((unsigned int)time(NULL));
    
    // Initialize SDL
    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    CHECK_ERROR(window == NULL, SDL_GetError());

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    
    CHECK_ERROR(renderer == NULL, SDL_GetError());

    // Initial renderer color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    bool running = true;
    SDL_Event event;

    int grid[100][100] = {0};
    grid[2][6] = 1;
    grid[2][7] = 1;
    grid[3][7] = 1;
    grid[3][6] = 1;
    grid[12][7] = 1;
    grid[13][6] = 1;
    grid[13][7] = 1;
    grid[13][8] = 1;
    grid[14][5] = 1;
    grid[14][6] = 1;
    grid[14][7] = 1;
    grid[14][8] = 1;
    grid[14][9] = 1;
    grid[15][4] = 1;
    grid[15][5] = 1;
    grid[15][9] = 1;
    grid[15][10] = 1;
    grid[16][5] = 1;
    grid[16][6] = 1;
    grid[16][7] = 1;
    grid[16][8] = 1;
    grid[16][9] = 1;
    grid[17][5] = 1;
    grid[17][9] = 1;
    grid[18][6] = 1;
    grid[18][8] = 1;
    grid[19][7] = 1;

    grid[22][5] = 1;
    grid[23][3] = 1;
    grid[23][4] = 1;
    grid[23][6] = 1;
    grid[23][7] = 1;
    grid[24][12] = 1;
    grid[25][13] = 1;
    grid[25][8] = 1;
    grid[25][2] = 1;
    grid[26][13] = 1;
    grid[26][12] = 1;
    grid[26][11] = 1;
    grid[27][2] = 1;
    grid[27][3] = 1;
    grid[27][5] = 1;
    grid[27][7] = 1;
    grid[27][8] = 1;


    while(running) {
        // Process events
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            } else if(event.type == SDL_KEYDOWN) {
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                if(strcmp(key, "N") == 0) {
                    int tempGrid[100][100] = {0};
                    std::copy(&grid[0][0], &grid[0][0]+100*100,&tempGrid[0][0]);
                    for(int row=1;row<99;row++){
                        for(int col=1;col<99;col++){
                            if(newCell(row, col, grid)){
                                tempGrid[row][col]=1;
                                std::cout << "new cell: " << row << " " << col << std::endl;
                            }
                            if(grid[row][col]==1){
                                if(!twoNeighborcheck(row, col, grid)){
                                    std::cout << row << " " << col << std::endl;
                                    tempGrid[row][col]=0;
                                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                                    SDL_RenderClear(renderer);
                                }
                                
                            }
                            
                        }
                    }
                    std::copy(&tempGrid[0][0], &tempGrid[0][0]+100*100,&grid[0][0]);
                    SDL_Delay(10);
                }                  
            } else if(event.type == SDL_KEYUP){

            }
        }

        // Clear screen
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Draw
        


        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        for(int row=0;row<100;row++){
            for(int col=0;col<100;col++){
                if(grid[row][col]==1){
                    SDL_Rect rec{row*10,col*10,10,10};
                    SDL_RenderFillRect(renderer, &rec);
                }
            }
        }

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


//grid square = 10x10
//grid size = 100x100