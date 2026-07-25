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

#include "utility/system_io/file.hpp"

#include <algorithm>
#include <limits>

utility::File::File(const std::string &path, const std::string &content)
	: _content(content)
	, _path(path)
{
}

utility::File::~File() = default;

size_t utility::File::write(const void *ptr, size_t size, size_t nmemb)
{
	if (ptr == nullptr || size == 0 || nmemb == 0) {
		return 0;
	}

	if (size > std::numeric_limits<size_t>::max() / nmemb) {
		return 0;
	}

	if (_pos > _content.size()) {
		_pos = _content.size();
	}

	const size_t bytesToWrite = size * nmemb;
	size_t lenBefore		  = _content.size();
	size_t newLen			  = lenBefore + bytesToWrite;
	if (newLen > _content.capacity()) {
		_content.reserve(newLen);
	}

	_content.insert(_pos, static_cast<const char *>(ptr), bytesToWrite);
	_pos += bytesToWrite;
	return (_content.size() - lenBefore) / size;
}

size_t utility::File::read(void *ptr, size_t size, size_t count)
{
	if (ptr == nullptr || size == 0 || count == 0 || _pos >= _content.size()) {
		return 0;
	}

	if (size > std::numeric_limits<size_t>::max() / count) {
		return 0;
	}

	size_t toRead = size * count;
	toRead		  = std::min(toRead, _content.size() - _pos);
	std::memcpy(ptr, _content.c_str() + _pos, toRead);
	_pos += toRead;
	return toRead / size;
}

size_t utility::File::read(std::string &str, size_t size, size_t count)
{
	if (size == 0 || count == 0 || _pos >= _content.size()) {
		str.clear();
		return 0;
	}

	if (size > std::numeric_limits<size_t>::max() / count) {
		str.clear();
		return 0;
	}

	size_t toRead = std::min(size * count, _content.size() - _pos);
	str.resize(toRead);
	std::memcpy(str.data(), _content.data() + _pos, toRead);
	_pos += toRead;
	return toRead / size;
}

int utility::File::seek(long offset, Seek whence)
{
	long newPos = 0;

	switch (whence) {
		case File::Seek::SET:
			newPos = offset;
			break;
		case File::Seek::CUR:
			newPos = static_cast<long>(_pos) + offset;
			break;
		case File::Seek::END:
			newPos = static_cast<long>(_content.size()) + offset;
			break;
		default:
			return -1;
	}

	if (newPos < 0) {
		return -1;
	}

	_pos = std::min(static_cast<size_t>(newPos), _content.size());
	return 0;
}

size_t utility::File::tell() const
{
	return _pos;
}

void utility::File::clear()
{
	_content.clear();
	_pos = 0;
}

size_t utility::File::remove(size_t count)
{
	if (count == 0 || _pos >= _content.size()) {
		return 0;
	}

	size_t toRemove = std::min(count, _content.size() - _pos);
	_content.erase(_pos, toRemove);
	return toRemove;
}