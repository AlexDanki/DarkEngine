#pragma once

namespace math
{

	class Math {
	public:
		bool isPowerOfTwo(int x) {
			return (x & (x - 1)) == 0;
		}

		int nextPowerOfTwo(int n) {
			int power = 1;
			while (power < n) power *= 2;
			return power;
		};

	};
}