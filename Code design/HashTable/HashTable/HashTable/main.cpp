#include <iostream>
#include "raylib.h"
#include <string>
#include <vector>


class HashTable
{
public:
	HashTable(int size) : m_size(size), textures(new Texture2D[size]) {}
	~HashTable() { delete[] textures; }


	unsigned int hash(const char* data, unsigned int length) 
	{
		unsigned int hash = 0;

		for (unsigned int i = 0; i < length; i++)
			hash = ((hash * 1313) + data[i]) % m_size;

		return (hash & 0x7FFFFFFF);
	}


	int loadTexture(const char* sprite, int length)
	{
		int key = hash(sprite, length);
		Texture2D texture;
		Texture2D* tempcheck = &textures[key];
		if(tempcheck != nullptr)
		{
			return key;
		}
		else
		{
			texture = LoadTexture(sprite);
			textures[key] = texture;
			return key;
		}


	}

	Texture2D* textures;
	int m_size;

};



int main()
{
	int ScreenWidth = 800;
	int ScreenHeight = 500;

	InitWindow(ScreenWidth, ScreenHeight, "Hashtable");

	SetTargetFPS(60);

	int size = 100;

	HashTable table(size);
	int key = table.loadTexture("ship_0000.png", 20);
	int Okey = table.loadTexture("ship_0001.png", 20);


	while(!WindowShouldClose())
	{
		BeginDrawing();


		DrawTexture(table.textures[key], ScreenWidth/2, ScreenHeight/2, RAYWHITE);
		//DrawTexture(table.textures[Okey], ScreenWidth, ScreenHeight, RAYWHITE);

		ClearBackground(RAYWHITE);
		EndDrawing();
	}
	CloseWindow();
}
