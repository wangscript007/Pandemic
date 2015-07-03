#ifndef __STARSSYSTEM_H__
#define __STARTSSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/IUpdatable.h>

namespace pan {
	class StarsSystem : public IUpdateable {
	public:
		explicit StarsSystem();
		void update() override;
		Flt getBarycenterHeightOverHorizont() const;		

	private:
		struct Star {
			SunClass sun;
			Flt radiusToBarycenter;	
			Flt angleSpeed;
			Flt angle;
		};

		// angle of full circle (whole degrees, that sun passes through day)
		const UShort FULL_CIRCLE_ANGLE = 360;

		Flt calculateDayLength(Flt worldLatitude) const;
		Flt calculateNightLength(Flt worldLatitude) const;

		/*
		This method is used to draw barycenter (and so as stars) in sunch way
		that arc of barycenter-circle movement will suffice length of day on this latitude in this day of year
		i.e: 
		Let we stand on equator (latitude = 0) and calculated sunrise/sunset times are 6h and 18h respectively
		We take sun sphere with radius 1 (see comment to "pos" field in Astro.h in Esenthel Engine headers)
		Thus angle of rising sun will be 0, and angle of setting sun will be 180
		
				   ...
		 /					   \
		/						\
		r - - - - - - - - - - - s - - - - horizont
		\						/
		 \					   /
				   ...

		where "r" is position of rising sun, "s" - position of setting sun

		As we go to the North or to the South sunrise/sunset times changes
		i.e:
		Let we stand on 45N deg and calculated sunrise/sunset times are 8h and 16h respectively
		So position of the sun (relative to equator circle) in this hours will be:

		  /					  \
		 r					   s
		/						\
		| - - - - - - - - - - - | - - - - horizont
		\						/
		 \					   /
					...

		BUT to manage fact that sun rise and set on line of horizont we adjust horizont line
		in a way that "r" and "s" positions will still be on horizont

		  /					  \
		 r - - - - - - - - - - s - - - - new horizont
		/			| r`		\
		| - - - - - - - - - - - | - - - - horizont
		\						/
		 \					   /

		 And this method calculate offset of this modified horizont "r`"
		 So, to get new real position of barycenter on 45N degree latitude,
		 we sutract "r`" from barycenter Y-position
		 Calculation formulae taken from http://mathworld.wolfram.com/CircularSector.html
		 in this link it is refereced as "h"
		*/
		Flt calculateBaryCenterOffset(Flt worldLatitude) const;
		void updateBarycenterOffset();

		// calculate hour on circle
		Flt calculateHourAngle(Flt hour) const;

		void setStarsRaysAndHeighlight();
		void setSunRaysAndHeighlight(SunClass* sun);

		void updateBarycenterPosition();
		void setStarsPositions();
		void setStarPosition(Star* star);

		void normalizeStartsPositionsAndHeightLight();
		void normalizeAndSetHeightLight(SunClass* sun);
		
		void createVigilantEye();
		void createAllSeeinggEye();

		// set barycenter position based on time
		void setBarycenterPosition(Flt time);

		Flt theta;
		Flt phi;
		Vec barycenterPosition;

		// see documentation to calculateBaryCenterOffset() method
		Flt barycenterOffset;
	
		Star vigilantEye;
		Star allSeeingEye;
	};
}

#endif
