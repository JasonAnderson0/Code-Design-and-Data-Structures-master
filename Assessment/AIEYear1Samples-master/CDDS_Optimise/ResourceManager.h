#pragma once
#include "raylib.h"
#include <vector>
#include "Hashtable.h"
#include <string>


class ResourceManager
{
public:
	int Hash(const std::string& key);

	~ResourceManager();


	Texture2D loadTexture(const char* path);
	
private:
	bool textureLoaded = false;
	Texture2D wantedTex[];
	//Hashtable<std::string, Texture2D> m_textures[];

}; 