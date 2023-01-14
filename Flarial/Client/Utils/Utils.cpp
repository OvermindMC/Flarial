#include "Utils.h"

std::string Utils::debugPath = Utils::getRoamPath();

auto Utils::getRoamPath(void) -> std::string {

	char* path = NULL;
	size_t length;

	_dupenv_s(&path, &length, "appdata");

	if (path == NULL)
		return "";

	return std::string(path) + "\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState";

};

auto Utils::getDebugPath(void) -> std::string {

	auto f = std::filesystem::path(Utils::debugPath);

	if (!std::filesystem::exists(f))
		std::filesystem::create_directories(f);

	return Utils::debugPath;

};

auto Utils::setDebugPath(std::string path) -> void {

	Utils::debugPath = std::string(Utils::getRoamPath() + "\\" + path);

};

auto Utils::debugOutput(std::string output) -> void {

	static bool init = false;
	static auto path = Utils::getDebugPath();

	auto file = std::string(path + "\\Output.txt");

	if (!init) {
		auto f = std::filesystem::path(file);

		if (std::filesystem::exists(f))
			std::filesystem::remove(f);

		init = true;
	};

	CloseHandle(CreateFileA(file.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

	std::ofstream fStream;
	fStream.open(file.c_str(), std::ios::app);

	if (fStream.is_open())
		fStream << output << "\n" << std::endl;

	return fStream.close();

};

auto Utils::isValidDomain(std::string str) -> bool {

	// Regex to check valid domain name.
	const std::regex pattern("^(?!-)[A-Za-z0-9-]+([\\-\\.]{1}[a-z0-9]+)*\\.[A-Za-z]{2,6}$");

	// If the domain name
	// is empty return false

	if (str.empty()) {
		return false;
	}

	// Return true if the domain name
	// matched the ReGex

	if (std::regex_match(str, pattern)) {
		return true;
	}
	else {
		return false;
	};

	return false;

};

auto Utils::reachOff(float* x, float xOff, float modifier) -> void {

	if (*x < xOff) {

		if (*x < (xOff - modifier))
			*x += modifier;
		else
			*x = xOff;

	}
	else if (*x > xOff) {

		if (*x > (xOff + modifier))
			*x -= modifier;
		else
			*x = xOff;

	};

};