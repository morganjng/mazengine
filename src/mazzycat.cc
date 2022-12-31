#include "mazengine/mazengine.h"

namespace mazengine {
	Mazzydata *Mazzycat::getData() {
		if (Mazzycat::data == nullptr) {
			YAML::Node node = YAML::LoadFile("Mazzycat");
			Mazzycat::data = new Mazzydata(
				node["name"].as<String>(), node["window_width"].as<int>(),
				node["window_height"].as<int>(), node["framerate"].as<int>(),
				node["data_path"].as<String>(), node["img_path"].as<String>(),
				node["audio_path"].as<String>(),
				node["settings_path"].as<String>());
		}
		return Mazzycat::data;
	}
} // namespace mazengine
