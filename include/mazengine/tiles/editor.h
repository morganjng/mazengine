#ifndef EDITOR_H_
#define EDITOR_H_

#include "entity.h"

namespace mazengine {
	namespace tiles {
		class Display;

		/**
		 * Class added to a tile Display to signal that it is being edited.
		 * */
		class EditorFollow : public Entity {
		public:
			int map_w;		   /**< Width of map in tiles. */
			int map_h;		   /**< Height of map in tiles. */
			int clicked;	   /**< Current clicked status. */
			int current_brush; /**< Tile to replace clicked tiles with. */
			Display *display;  /**< Pointer to display being operated on. */

			/**
			 * Contructor for EditorFollow. Called by Display::Editor().
			 * */
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
			/**
			 * Function to execute on move.
			 * */
			void Move();
			/**
			 * Function to execute on click/hold.
			 * */
			void Paint();
		};

		/**
		 * Wrapper for EditorFollow python implementation. Somewhat of a proof
		 * of concept.
		 * */
		class EFWrapper {
		public:
			mazengine::tiles::EditorFollow
				*ef; /**< Pointer for wrapped entity. */
			/**
			 * Contsructor.
			 * */
			EFWrapper(mazengine::tiles::EditorFollow *ef) { this->ef = ef; }
			/**
			 * Wrapped version of EditorFollow::Paint().
			 * */
			void Paint() { ef->Paint(); }
			/**
			 * Wrapped version of EditorFollow::Move().
			 * */
			void Move() { ef->Move(); }
		};
	} // namespace tiles
} // namespace mazengine

#endif // EDITOR_H_
