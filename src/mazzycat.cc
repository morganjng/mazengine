#include "mazengine/mazengine.h"
#include <yaml-cpp/node/parse.h>

namespace mazengine {
	std::vector<YAML::Node> Mazzycat::data;

	void Mazzycat::Init() {
		if (Mazzycat::data.size() > 0) {
			return;
		}
		Mazzycat::data.push_back(YAML::LoadFile("Mazzycat"));
	}

	String Mazzycat::GetName() {
		Init();
		return Mazzycat::data[0]["name"].as<String>();
	}

	IntPair Mazzycat::GetWindowSize() {
		Init();
		IntPair ip;
		ip.first = Mazzycat::data[0]["window_width"].as<int>();
		ip.second = Mazzycat::data[0]["window_height"].as<int>();
		return ip;
	}

	int Mazzycat::GetFramerate() {
		Init();
		return Mazzycat::data[0]["framerate"].as<int>();
	}

	StringMap Mazzycat::GetPaths() {
		Init();
		StringMap sm;
		sm["data"] = Mazzycat::data[0]["data_path"].as<String>();
		sm["audio"] = Mazzycat::data[0]["audio_path"].as<String>();
		sm["img"] = Mazzycat::data[0]["img_path"].as<String>();
		sm["settings"] = Mazzycat::data[0]["settings_path"].as<String>();
		return sm;
	}
} // namespace mazengine
