#include "Entity.h"
#include "engine/Renderer.h"
#include "engine/Input.h"

Entity::Entity() {
	m_Collider = { { 0,0,0,0 }, {0,0} };
	m_Transform.m_Position = { 0,0 };
	m_Transform.m_Rotation = 0.f;
	m_Transform.m_Velocity = { 0, 0 };
	m_Transform.m_Direction = 0;
	m_Sprite = Sprite();
	m_FlipSprite = SDL_FLIP_NONE;
	m_AnimStep = 0;
}

void Entity::Initialize()
{
#if LOGGING
	m_DebugCollider = Texture::LoadSolidColourTexture({ 0,255,255,128 }, { 32,32 });
#endif // LOGGING
}

void Entity::Input()
{
#if LOGGING
	if (Input::GetKeyUp(SDL_SCANCODE_F3)) {
		m_DebugActivate = !m_DebugActivate;
	}
#endif // LOGGING
}

void Entity::UpdateAnimation()
{
	m_AnimStep >= m_NoOfAnims ? m_AnimStep = 0 : m_AnimStep++;
	m_Sprite.m_Source.x = m_Sprite.m_Source.w * m_AnimStep;
}

void Entity::Draw()
{
#if LOGGING
	if (m_DebugActivate){
		SDL_RenderCopy(Renderer::GetRenderer(), m_DebugCollider.m_Texture, &m_DebugCollider.m_Source, &m_Collider.m_Dimensions);
	}
#endif // LOGGING
}

SDL_Rect& Entity::GetCollider()
{
	return m_Collider.m_Dimensions;
}

Vector2 Entity::GetNodePosition()
{
	return { m_Transform.m_Position.x / 32, m_Transform.m_Position.y / 32 };
}