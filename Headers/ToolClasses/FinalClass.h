#ifndef __FINALCLASS_H__
#define __FINALCLASS_H__

/*
Usage:

class ClassThatWantToBeNonDerivable : private virtual FinalClass {
	....
}
*/

class FinalClass {
protected:
	FinalClass() {		
	};
	~FinalClass() {		
	};
};

#endif