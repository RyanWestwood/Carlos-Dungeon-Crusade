#pragma once
#include "engine/Texture.h"
#include <array>
#include <vector>

class Tile
{
public:
  Tile(SDL_FRect, SDL_Point);

public:
  SDL_FRect m_Destination;
  SDL_Point m_Position;
};

class Tilemap
{
public:
  Tilemap();
  ~Tilemap();

  void Initialize(const char* filename, int src_tile_size);
  void Draw();

public:
  std::array<std::array<int, 48>, 27> MAP_DATA;
  std::vector<Tile>                   m_Tiles;
  texture::TextureData                m_TextureData;
  SDL_Texture*                        m_Map;
};