#ifndef __SKYCOLOURSYSTEM_H__
#define __SKYCOLOURSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Environment/SunHeightChangedEvent.h>

namespace pan {
	class SkyColourSystem : public BaseEventHandler {
	public:
		explicit SkyColourSystem();		
		void update(const SunHeightChangedEvent* event);

	private:
		/**
		 * Possible sun height over horizont (= 2 * R)
		 * Where R = 1 (see "pos" member comment in Astro.h in Esenthel Engine)
		 * Because sun circle can have offset \in [-1; 1] 
		 * (see StarsSystem::calculateBaryCenterOffset())
		 * real sun height in highest point is 1 + 1 = 2
		 * and in lowest point is -1 + (-1) = -2
		*/
		const UShort SUN_HEIGHT = 2;

		Flt getHeightOverHorizont(Flt hour) const;
		void initializeHorisonColourInterpolator();
		void initializeSkyColourInterpolator();
		void setSkyColour(Flt sunHeightOverHorizont);
		Vec4 createColour(Byte r, Byte g, Byte b, Byte a = 255);
		Interpolator<Vec4> horizonColors;
		Interpolator<Vec4> skyColors;
	};
}

#endif
