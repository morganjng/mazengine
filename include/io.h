#ifndef MAZENGINE_IO_H_
#define MAZENGINE_IO_H_

#include <SDL2/SDL_events.h>
#include <vector>

namespace mazengine {
	/**
	 * Enumeration of input-types. Should be expanded or redefined as need be.
	 * */
	enum Button {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		A,
		B,
		START,
		SELECT,
		KILL,
		MOUSE_CLICK,
		MOUSE_MOTION
	};

	/**
	 * IO class represents how the program should read in inputs, and how it
	 * should parse those into output buttons. Users should use provided
	 * implementations or write their own.
	 * */
	class IO {
	public:
		static std::vector<Button> *presses;  /**< Button presses this tick. */
		static std::vector<Button> *releases; /**< Button releases this tick. */
		static double
			*cursor_x; /**< X position of cursor as % of window width. */
		static double
			*cursor_y;		/**< Y position of cursor as % of window height. */
		int *window_width;	/**< Pixel width of window. */
		int *window_height; /**< Pixel height of window. */

		IO(){}; /**< Constructor. Doesn't do anything right now. */
		virtual int ReadSettings() = 0; /**< Load settings based on file
										   provided in Mazzycat. */
		/**
		 * Parses a single SDL_Event and puts the corresponding press/release
		 * into presses/releases.
		 * @param event SDL_Event * from Engine instance.
		 * */
		virtual int Parse(SDL_Event *event) = 0;
	};
} // namespace mazengine

#endif
