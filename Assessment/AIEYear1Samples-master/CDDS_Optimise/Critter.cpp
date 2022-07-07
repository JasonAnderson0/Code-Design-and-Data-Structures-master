#include "Critter.h"


Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_radius = 0;
	m_isDirty = false;
}

Critter::~Critter()
{
	//UnloadTexture(m_texture);
}

void Critter::Init( Vector2 position, Vector2 velocity, float radius, const char* texture)
{
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;
	
	m_texture = LoadTexture(texture);
}

void Critter::Destroy()
{
	UnloadTexture(m_texture);
}

void Critter::Update(float dt)
{

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_isDirty = false;
}


void Critter::Draw()
{

	DrawTexture(m_texture, m_position.x, m_position.y, WHITE);
}
