#ifndef MAZENGINE_H_
#define MAZENGINE_H_

#include <SDL2/SDL.h>
#include <string>
#include <vector>

namespace mazengine {

enum button { UP, DOWN, LEFT, RIGHT, A, B, START, SELECT, KILL };

class engine;
class io;
class game;
class entity;

class engine {
private:
  io *_io;
  game *_game;
  int window_width;
  int window_height;

public:
  engine(int width, int height) {
    window_width = width;
    window_height = height;
    _io = nullptr;
    _game = nullptr;
  };
  int set_io(io *io);
  int set_game(game *game);
  int start();
};

class io {
public:
  io(){};
  virtual int read_settings() = 0;
  virtual int parse(SDL_Event *event, std::vector<button> *presses,
                    std::vector<button> *releases) = 0;
};

class game {
public:
  SDL_Renderer *renderer;
  game() { renderer = nullptr; };
  virtual int initial_tick() = 0;
  virtual int tick(std::vector<button> *presses,
                   std::vector<button> *releases) = 0;
  virtual int draw() = 0;
  virtual int present() = 0;
};

class entity {
private:
  std::vector<void (*)(button)> press_hooks;
  std::vector<void (*)(button)> release_hooks;

public:
  entity() {
    press_hooks = *new std::vector<void (*)(button)>();
    release_hooks = *new std::vector<void (*)(button)>();
    type = "UNSET";
    id = -1;
    x = -1;
    y = -1;
  };
  entity(std::string type, std::string key, int id, int x, int y) {
    press_hooks = *new std::vector<void (*)(button)>();
    release_hooks = *new std::vector<void (*)(button)>();
    this->type = type;
    this->key = key;
    this->id = id;
    this->x = x;
    this->y = y;
  };
  std::string type;
  std::string key;
  int id;
  int x;
  int y;
  int push_press_hook(void func(button press));
  int push_release_hook(void func(button release));
  std::vector<void (*)(button)> *get_press_hooks();
  std::vector<void (*)(button)> *get_release_hooks();
};

} // namespace mazengine
#endif
