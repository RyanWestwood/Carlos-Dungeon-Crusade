#pragma once
#include "engine/Texture.h"
#include <SDL2/SDL.h>
#include <memory>

class Attack
{
public:
  Attack()
  {
  }

public:
  Sprite m_Sprite;

protected:
  std::shared_ptr<float> m_Timer;
  float                  m_Cooldown;
  float                  m_Rotation;
  SDL_Point              m_Center;
  bool                   m_Action;
  SDL_RendererFlip       m_Flip;
};