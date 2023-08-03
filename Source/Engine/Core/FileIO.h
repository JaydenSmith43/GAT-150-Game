#pragma once
#include <filesystem>
#include <string>

namespace kiko
{
	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& path); //:: scope? //& reference and address
	std::string getFileName(const std::filesystem::path& path);

	bool fileExists(const std::filesystem::path& path); //const because we dont want these to change
	bool getFileSize(const std::filesystem::path& path, size_t& size); //without reference it will not change var
	bool readFile(const std::filesystem::path& path, std::string& buffer); //buffer means a section of memory or block of data
}
