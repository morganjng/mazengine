#include "mazengine/mazengine.h"
#include <yaml-cpp/node/parse.h>

namespace mazengine {
	void Mazzycat::Init() {
		if (Mazzycat::mazzycat.size() > 0) {
			return;
		}
		mazzycat.push_back(YAML::LoadFile("Mazzycat"));
	}

	String Mazzycat::GetName() {
		Init();
		return Mazzycat::mazzycat[0]["name"].as<String>();
	}

	IntPair Mazzycat::GetWindowSize() {
		Init();
		IntPair ip;
		ip.first = Mazzycat::mazzycat[0]["window_width"].as<int>();
		ip.second = Mazzycat::mazzycat[0]["window_height"].as<int>();
		return ip;
	}

	int Mazzycat::GetFramerate() {
		Init();
		return Mazzycat::mazzycat[0]["framerate"].as<int>();
	}

	StringMap Mazzycat::GetPaths() {
		Init();
		StringMap sm;
		sm["data"] = Mazzycat::mazzycat[0]["data_path"].as<String>();
		sm["audio"] = Mazzycat::mazzycat[0]["audio_path"].as<String>();
		sm["img"] = Mazzycat::mazzycat[0]["img_path"].as<String>();
		sm["settings"] = Mazzycat::mazzycat[0]["settings_path"].as<String>();
		return sm;
	}
} // namespace mazengine
