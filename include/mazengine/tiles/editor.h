#ifndef EDITOR_H_
#define EDITOR_H_

#include "entity.h"

namespace mazengine {
	namespace tiles {
		class Display;

		class EditorFollow : public Entity {
		public:
			int **tiles_ptr;
			int map_w;
			int map_h;
			int clicked;
			int current_brush;
			Display *display;
			EditorFollow(int tile_w, int tile_h, int map_w, int map_h,
						 Display *display)
				: Entity() {
				current_brush = 1;
				texture = new Texture("color.png");
				this->location.x = 0;
				this->location.y = 0;
				this->map_w = map_w;
				this->map_h = map_h;
				this->location.w = tile_w;
				this->location.h = tile_h;
				this->display = display;
				clicked = 0;
				behaviors["onclick"] = "editor.Paint()\n";
				behaviors["onpress"] = "editor.Move()\n";
			}
			void Move();
			void Paint();
		};

		class EFWrapper {
		public:
			mazengine::tiles::EditorFollow *ef;
			EFWrapper(mazengine::tiles::EditorFollow *ef) { this->ef = ef; }
			void Paint() { ef->Paint(); }
			void Move() { ef->Move(); }
		};
	} // namespace tiles
} // namespace mazengine

#endif // EDITOR_H_
