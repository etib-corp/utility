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

#pragma once

#include <map>
#include <optional>
#include <utility>
#include <functional>
#include <concepts>

namespace utility
{

	/**
	 * @brief Concept to constrain cache entry type.
	 * @tparam T Candidate entry type.
	 */
	template<typename T>
	concept CacheEntry = std::movable<T>;

	/**
	 * @brief Concept to constrain cache key type.
	 * @tparam Key Candidate key type.
	 * @tparam Compare Comparison function type for ordering keys.
	 */
	template<typename Key, typename Compare = std::less<Key>>
	concept CacheKey = requires(const Key &a, const Key &b, Compare comp) {
		{ comp(a, b) } -> std::convertible_to<bool>;
	};

	/**
	 * @brief A thread-safe cache for storing key-value pairs.
	 *
	 * This class provides a thread-safe cache that allows storing and
	 * retrieving key-value pairs. It uses a std::map internally to manage the
	 * entries and provides methods for adding, retrieving, and removing
	 * entries.
	 *
	 * @tparam Key Type of the keys used in the cache.
	 * @tparam Entry Type of the values stored in the cache.
	 * @tparam Compare Comparison function type for ordering keys (default is
	 * std::less<Key>).
	 */
	template<typename Key, CacheEntry Entry, typename Compare = std::less<Key>>
		requires CacheKey<Key, Compare>
	class Cache
	{
		private:
		std::map<Key, Entry, Compare>
			_entries;	 ///< Internal storage for cache entries, using a
						 ///< std::map to manage key-value pairs.

		public:
		/**
		 * @brief Default constructor for the Cache class.
		 */
		Cache(void) = default;

		/**
		 * @brief Default destructor for the Cache class.
		 */
		~Cache(void) = default;

		/**
		 * @brief Deleted copy constructor to prevent copying of the cache.
		 */
		Cache(const Cache &other) = delete;

		/**
		 * @brief Deleted copy assignment operator to prevent copying of the
		 * cache.
		 */
		Cache &operator=(const Cache &other) = delete;

		/**
		 * @brief Deleted move constructor to prevent moving of the cache.
		 */
		Cache(Cache &&other) noexcept = delete;

		/**
		 * @brief Deleted move assignment operator to prevent moving of the
		 * cache.
		 */
		Cache &operator=(Cache &&other) noexcept = delete;

		/**
		 * @brief Check if the cache contains a specific key.
		 * @param key The key to check for in the cache.
		 * @return True if the key exists in the cache, false otherwise.
		 */
		bool contains(const Key &key) const
		{
			return _entries.find(key) != _entries.end();
		}

		/**
		 * @brief Retrieve the value associated with a specific key.
		 * @param key The key to look up in the cache.
		 * @return An optional containing the value if the key exists, or
		 * std::nullopt if the key is not found.
		 */
		std::optional<Entry> get(const Key &key) const
		{
			auto it = _entries.find(key);
			if (it == _entries.end()) {
				return std::nullopt;
			}
			return it->second;
		}

		/**
		 * @brief Add or update a key-value pair in the cache.
		 * @param key The key to add or update.
		 * @param value The value associated with the key.
		 */
		void put(const Key &key, const Entry &value)
		{
			_entries.insert_or_assign(key, value);
		}

		/**
		 * @brief Add or update a key-value pair in the cache using move
		 * semantics.
		 * @param key The key to add or update (moved).
		 * @param value The value associated with the key (moved).
		 */
		void put(Key &&key, Entry &&value)
		{
			_entries.insert_or_assign(std::move(key), std::move(value));
		}

		/**
		 * @brief Emplace a new entry in the cache with the given key and
		 * constructor arguments.
		 * @tparam Args Types of the constructor arguments for the entry.
		 * @param key The key to associate with the new entry.
		 * @param args Constructor arguments for the entry.
		 * @return Reference to the newly emplaced entry.
		 */
		template<typename... Args>
		Entry &emplace(const Key &key, Args &&...args)
		{
			auto [it, inserted] =
				_entries.try_emplace(key, std::forward<Args>(args)...);
			return it->second;
		}

		/**
		 * @brief Emplace a new entry in the cache with the given key and
		 * constructor arguments using move semantics.
		 * @tparam Args Types of the constructor arguments for the entry.
		 * @param key The key to associate with the new entry (moved).
		 * @param args Constructor arguments for the entry.
		 * @return Reference to the newly emplaced entry.
		 */
		template<typename... Args> Entry &emplace(Key &&key, Args &&...args)
		{
			auto [it, inserted] = _entries.try_emplace(
				std::move(key), std::forward<Args>(args)...);
			return it->second;
		}

		/**
		 * @brief Remove an entry from the cache.
		 * @param key The key of the entry to remove.
		 * @return True if the entry was removed, false if it was not found.
		 */
		bool erase(const Key &key)
		{
			return _entries.erase(key) > 0;
		}

		/**
		 * @brief Remove entries from the cache based on a predicate.
		 * @param predicate A function that takes a key and entry and returns
		 * true if the entry should be removed.
		 */
		void erase_if(
			const std::function<bool(const Key &, const Entry &)> &predicate)
		{
			for (auto it = _entries.begin(); it != _entries.end();) {
				if (predicate(it->first, it->second)) {
					it = _entries.erase(it);
				} else {
					++it;
				}
			}
		}

		/**
		 * @brief Apply a function to each entry in the cache.
		 * @param function A function that takes a key and entry and performs
		 * an operation on them.
		 */
		void apply(const std::function<void(const Key &, Entry &)> &function)
		{
			for (auto &[key, entry]: _entries) {
				function(key, entry);
			}
		}

		/**
		 * @brief Clear all entries from the cache.
		 */
		void clear(void)
		{
			_entries.clear();
		}

		/**
		 * @brief Get the number of entries in the cache.
		 * @return The number of entries in the cache.
		 */
		std::map<Key, Entry, Compare>::size_type size(void) const
		{
			return _entries.size();
		}

		/**
		 * @brief Check if the cache is empty.
		 * @return True if the cache is empty, false otherwise.
		 */
		bool empty(void) const
		{
			return _entries.empty();
		}
	};

}	 // namespace utility