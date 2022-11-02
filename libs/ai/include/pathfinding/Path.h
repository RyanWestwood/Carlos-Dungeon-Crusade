#pragma once
#include <vector>
#include <memory>
#include "../Dll.h"
#include "../math/Vector2.h"
#include "Line.h"

namespace AI {
	namespace PATH {

		class Path;
		typedef std::shared_ptr<Path> PathPtr;

		class IPath {
		public:
			virtual void UpdatePath(std::vector<Vector2> waypoints, Vector2 start_pos, float turn_distance) = 0;
		};

		class Path : public IPath{
		public:
			Path() {}
			void UpdatePath(std::vector<Vector2> waypoints, Vector2 start_pos, float turn_distance);
		public:
			std::vector<Vector2> m_LookPoints;
			std::vector<Line> m_TurnBoundaries;
			int m_FinishLineIndex;
		};

		extern "C++" AI_API PathPtr CreatePath();
	} // namespace PATH
} // namespace AI