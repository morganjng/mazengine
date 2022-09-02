#ifndef U_GAME_H_
#define U_GAME_H_

#include "mazengine.h"
#include <map>

using namespace mazengine;

class u_game : public game {
private:
    std::map<int, game> games;

public:
    int cursor;
    int set_game(int key, game game);

    SDL_Renderer *renderer;
    u_game() { renderer = nullptr; }
    int initial_tick();
    int tick(std::vector<button> *presses, std::vector<button> *releases);
    int draw();
    int present();
};

#endif // U_GAME_H_
