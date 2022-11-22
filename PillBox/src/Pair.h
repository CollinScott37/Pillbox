#pragma once
#include "Types.h"

namespace Pillbox {

	class Pair : public std::pair<int, vec2> {
		public:
			bool operator<(const Pair &other) {
				if (this->first < other.first) {
					return true;
				}
				return false;
			}
	};
}
