#include <mazengine.h>
#include <yaml-cpp/node/parse.h>

namespace mazengine {
	std::vector<YAML::Node> Mazzycat::data;

	void Mazzycat::Init() {
		if (Mazzycat::data.size() > 0) {
			return;
		}
		Mazzycat::data.push_back(YAML::LoadFile("Mazzycat"));
	}

	std::string Mazzycat::GetName() {
		Init();
		return Mazzycat::data[0]["name"].as<std::string>();
	}

	std::pair<int, int> Mazzycat::GetWindowSize() {
		Init();
		std::pair<int, int> ip;
		ip.first = Mazzycat::data[0]["window_width"].as<int>();
		ip.second = Mazzycat::data[0]["window_height"].as<int>();
		return ip;
	}

	int Mazzycat::GetFramerate() {
		Init();
		return Mazzycat::data[0]["framerate"].as<int>();
	}

	std::map<std::string, std::string> Mazzycat::GetPaths() {
		Init();
		std::map<std::string, std::string> sm;
		sm["data"] = Mazzycat::data[0]["data_path"].as<std::string>();
		sm["audio"] = Mazzycat::data[0]["audio_path"].as<std::string>();
		sm["img"] = Mazzycat::data[0]["img_path"].as<std::string>();
		sm["settings"] = Mazzycat::data[0]["settings_path"].as<std::string>();
		return sm;
	}
} // namespace mazengine
