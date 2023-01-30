#ifndef MAZENGINE_TEXTURE_H_
#define MAZENGINE_TEXTURE_H_

#include "geometry.h"

#include <string>
#include <vector>

#include <SDL_image.h>

namespace mazengine {
	/**
	 * Abstraction of SDL_Texture so that the engine has control over loading,
	 * making sure that it is loaded when the Game wants it to be drawn and
	 * whatnot. Users should only use raw SDL_Textures or interface with SDL
	 * directly if they are entirely comfortable with the uncertainties of it.
	 * */
	class Texture {
	public:
		/**
		 * Registry of all Textures. 
		 * */
		static std::vector<Texture *> registry;

		SDL_Texture
			*texture; /**< May be null, but will never be null when drawn. */
		std::string path; /**< Path of the texture intended to be loaded. */
		/**
		 * Texture constructor. Stores the path and loads texture when there is
		 * offtime or when a LoadTextures() is called.
		 * @param path Path of texture relative to images folder.
		 * */
		Texture(std::string path) {
			this->path = path;
			texture = nullptr;
			registry.push_back(this);
		}
		void Load(); /**< Load the texture if it isn't already loaded. */
		/**
		 * Draws Texture from src to dest.
		 * @param src Rectangle indicating where on texture is being copied.
		 * @param dest Rectangle indicating where on Engine::renderer the
		 * texture should be drawn.
		 * */
		void Draw(Rect *src, Rect *dest);
	};

} // namespace mazengine

#endif // TE0XTURE_H_
