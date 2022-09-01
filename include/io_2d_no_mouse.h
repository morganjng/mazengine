#ifndef TWODXPUT_NO_MOUSE_H_
#define TWODXPUT_NO_MOUSE_H_

#include "SDL_keycode.h"
#include "mazengine.h"
#include <map>
#include <string>
#include <vector>

class io_2d_no_mouse : public mazengine::io {
  private:
    std::string settings_path;
    std::map<SDL_Keycode, mazengine::button> *controls;
    std::map<SDL_Keycode, mazengine::button>::iterator iter;

  public:
    io_2d_no_mouse() {
        settings_path = "UNSET";
        controls = nullptr;
    };
    void set_controls_map(std::map<SDL_Keycode, mazengine::button> *contr);
    void set_settings_path(std::string path);
    int read_settings();
    int parse(SDL_Event *event, std::vector<mazengine::button> *presses,
              std::vector<mazengine::button> *releases);
};

#endif // TWODXPUT_NO_MOUSE_H_
