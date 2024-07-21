#include <fstream>
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"
#include <Fl/Fl.H>
#include <FL/Fl_draw.H>
#include <FL/Fl_Native_File_Chooser.H>

#include "JSONParser.h"
#include "MainWindow.h"
#include "ShapesVectorSingleton.h"

using json = nlohmann::json;
using std::string, std::string_view, std::to_string, std::optional;

json ReadJSONFromFile (const string_view path) {
	//path = "";
	json jsonData;
	std::ifstream file(path.data());
	if (!file) {
		spdlog::error("Couldn't open the JSON file!\n");
		return {};
	}
	try {
		file >> jsonData;
		spdlog::info("JSON file successfully loaded!\n");
	}
	catch (const json::exception& exc) {
		spdlog::error("Couldn't parse the JSON file! Description: {}\n", exc.what());
		std::exit(-2);
	}
	return jsonData;
}

optional<string> SelectFilePath() {
	//return {"test_examples/data.json"};
	Fl_Native_File_Chooser file_chooser;
	file_chooser.title("Pick a json file");
	file_chooser.type(Fl_Native_File_Chooser::BROWSE_FILE);
	file_chooser.filter("*.json");
	while (true) {
		switch (file_chooser.show()) {
		case -1:
			spdlog::error("{}\n", file_chooser.errmsg());
			exit(-1);
		case  1:
			spdlog::warn("File selecion cancelled\n");
			return {};
		default: return { file_chooser.filename() };
		}
	}
}

int main() {
	if (optional<string> filepath = SelectFilePath())
		ShapesVectorSingleton::Set(
			JSONParser::ParseShapesArray(ReadJSONFromFile(filepath.value())));
	MainWindow window(1000, 600, "Figures Viewer");
	window.show();
    return Fl::run();
}
