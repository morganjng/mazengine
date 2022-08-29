#include <SDL_render.h>
#include <tile_renderer.h>

void tile_renderer::clear(int color) {
  SDL_RenderClear(renderer);
  SDL_FillRect(internal_surface, NULL, color);
  // std::cout << SDL_GetError() << std::endl;
};

void tile_renderer::draw_sprite(std::string key, int id, int x, int y) {
  tile_set *set = tilesets[key];
  SDL_Rect dest_rect;
  SDL_Rect src_rect;
  dest_rect.x = x;
  dest_rect.y = y;
  dest_rect.w = set->tile_size_x;
  dest_rect.h = set->tile_size_y;
  src_rect.x = set->tile_size_x * (id % (set->width / set->tile_size_x));
  src_rect.y = set->tile_size_y * (id / (set->width / set->tile_size_x));
  src_rect.w = set->tile_size_x;
  src_rect.h = set->tile_size_y;
  // std::cout << id << " FROM " << src_rect.x << ", " << src_rect.y <<
  // src_rect.w
  //           << "x" << src_rect.h << " TO " << dest_rect.x << ", " <<
  //           dest_rect.y
  //           << std::endl;
  SDL_BlitSurface(set->texture, &src_rect, this->internal_surface, &dest_rect);
}

void tile_renderer::draw_layer(tile_layer *layer, int player_position_x,
                               int player_position_y) {
  int offset_x = player_position_x / tile_size_x - (tile_width + 4 - 1) / 2;
  int offset_y = player_position_y / tile_size_y - (tile_height + 4 - 1) / 2;
  tile_set *layer_set = tilesets[layer->tile_type];
  SDL_Rect dest_rect;
  dest_rect.x = 0;
  dest_rect.y = 0;
  dest_rect.w = tile_size_x;
  dest_rect.h = tile_size_y;
  SDL_Rect src_rect;
  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.w = layer_set->tile_size_x;
  src_rect.h = layer_set->tile_size_y;
  for (int i = offset_y; i < layer->height && i < offset_y + tile_height + 4;
       i++) {
    for (int j = offset_x; j < layer->width && j < offset_x + tile_width + 4;
         j++) {
      if (i >= 0 && j >= 0) {
        int tile_id = layer->tile_ids[i][j];
        if (tile_id != -1) {
          src_rect.x =
              layer_set->tile_size_x *
              ((tile_id) % (layer_set->width / layer_set->tile_size_x));
          src_rect.y =
              layer_set->tile_size_y *
              ((tile_id) / (layer_set->width / layer_set->tile_size_y));
          SDL_BlitSurface(layer_set->texture, &src_rect, this->internal_surface,
                          &dest_rect);
          // std::cout << tile_id << " FROM " << src_rect.x << ", " <<
          // src_rect.y
          //           << " TO " << dest_rect.x << ", " << dest_rect.y <<
          //           std::endl;
        }
      }
      dest_rect.x += tile_size_x;
    }
    dest_rect.x = 0;
    dest_rect.y += tile_size_y;
  }
};

void tile_renderer::draw_to_renderer(int player_position_x,
                                     int player_position_y) {
  render_rect.x =
      player_position_x % tile_size_x + tile_size_x + tile_size_x / 2;
  render_rect.y = player_position_y % tile_size_y + 3 * tile_size_y;
  SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, internal_surface);
  SDL_RenderCopy(renderer, text, &render_rect, NULL);
  SDL_DestroyTexture(text);
}

void tile_renderer::present() { SDL_RenderPresent(renderer); };

// tile_set *tile_renderer::get_tile_set(std::string key) { return
// tilesets[key]; }
