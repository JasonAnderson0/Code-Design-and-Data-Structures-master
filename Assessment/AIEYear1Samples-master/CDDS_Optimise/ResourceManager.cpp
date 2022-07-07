#include "ResourceManager.h"


int ResourceManager::Hash(const std::string& key) 
{
	unsigned int value = 0;
	for (int i = 0; i < key.length(); i++)
		value = value * 1313 + key[i];
	return value;
}

ResourceManager::~ResourceManager()
{
}



Texture2D ResourceManager::loadTexture(const char* path)
{
	//std::string key(path);
	//auto iter = m_textures.find(key);
	//if(iter != m_textures.end()){
	// //already loaded texture
	// return iter->second;
	//  }
	//else{
	// //load and store in hashtable
	//Texture2D tex = LoadTexture(path);
	//m_textures[key] = tex;
	//return tex;
	//}

	//check if its been loaded before
	int key = Hash(path);
	if (textureLoaded == false) {

		wantedTex[key] = LoadTexture(path);
		textureLoaded = true;
		return wantedTex[key];
	}
	else {

		return wantedTex[key];
	}	
}

