#pragma once
#include <stdio.h>
#include <map>
#include<unordered_map>
#include <memory>
namespace ly
{
	template< typename T>
	using unique = std::unique_ptr<T>;

	template <typename T>
	using shared = std::shared_ptr<T>;

	template <typename T> 
	using weak = std::weak_ptr<T>;

	template <typename T>
	using List = std::vector<T>;
	template <typename keytype , typename valType , typename pr = std::less<keytype>>
	using Map = std::map<keytype, valType,pr>;

	template <typename keytype, typename valType, typename hasher = std::less<keytype>>
	using Dictionary = std::unordered_map<keytype, valType, hasher>;
	#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}