/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <filesystem>

#include "utility/system_io/default_system_io.hpp"

namespace
{
	std::string NormalizePath(const std::string &path)
	{
		return std::filesystem::path(path).lexically_normal().generic_string();
	}
}	 // namespace

bool utility::DefaultSystemIO::loadDirectory(const std::string &directory)
{
	std::error_code error;
	const std::filesystem::path directoryPath(directory);
	if (!std::filesystem::exists(directoryPath, error)
		|| !std::filesystem::is_directory(directoryPath, error)) {
		getLogger().warning()
			<< "Asset directory does not exist or is invalid: " << directory;
		return false;
	}

	bool success = true;
	for (const auto &entry:
		 std::filesystem::directory_iterator(directoryPath, error)) {
		if (error) {
			getLogger().warning()
				<< "Failed to iterate asset directory: " << directory;
			return false;
		}

		if (entry.is_regular_file(error) && !error) {
			const std::string path = entry.path().string();
			if (this->add(path) == nullptr) {
				getLogger().warning() << "Failed to load asset: " << path;
				success = false;
			}
		}
	}

	return success;
}

std::shared_ptr<utility::File>
	utility::DefaultSystemIO::add(const std::string &path)
{
	const std::string key = NormalizePath(path);
	if (this->exists(key)) {
		return this->open(key);
	}

	std::ifstream file(key, std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		getLogger().warning() << "Failed to open file: " << key;
		return nullptr;
	}

	const std::streamsize fileSize = file.tellg();
	if (fileSize < 0) {
		getLogger().warning() << "Failed to read file size: " << key;
		return nullptr;
	}

	std::string content;
	content.resize(static_cast<size_t>(fileSize));
	file.seekg(0, std::ios::beg);
	if (!content.empty()) {
		file.read(content.data(), static_cast<std::streamsize>(content.size()));
		if (!file) {
			getLogger().warning() << "Failed to read file content: " << key;
			return nullptr;
		}
	}
	file.close();

	auto asset = std::make_shared<utility::File>(path, content);
	if (!asset) {
		getLogger().warning() << "Failed to create File for: " << key;
		return nullptr;
	}

	_assets[key] = asset;
	return asset;
}

void utility::DefaultSystemIO::remove(const std::string &path, bool save)
{
	const std::string key = NormalizePath(path);
	auto it				  = _assets.find(key);
	if (it != _assets.end()) {
		if (save) {
			this->save(key);
		}
		_assets.erase(it);
	} else {
		getLogger().warning() << "Asset not found: " << key;
	}
}

bool utility::DefaultSystemIO::save(const std::string &path,
									const std::string &newPath)
{
	const std::string key = NormalizePath(path);
	auto it				  = _assets.find(key);
	if (it == _assets.end()) {
		getLogger().warning() << "Asset not found: " << key;
		return false;
	}

	const std::string &content = it->second->content();
	const std::string savePath = newPath.empty() ? key : newPath;

	std::error_code error;
	const auto parentPath = std::filesystem::path(savePath).parent_path();
	if (!parentPath.empty()) {
		std::filesystem::create_directories(parentPath, error);
		if (error) {
			getLogger().warning()
				<< "Failed to create parent directories for: " << savePath;
			return false;
		}
	}

	std::ofstream file(savePath, std::ios::binary);
	if (!file.is_open()) {
		getLogger().warning()
			<< "Failed to open file for writing: " << savePath;
		return false;
	}

	file.write(content.data(), content.size());
	if (!file) {
		getLogger().warning() << "Failed to write file content: " << savePath;
		return false;
	}
	file.close();

	return true;
}
