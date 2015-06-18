#include <Headers/ToolClasses/Singleton.h>
#include <Headers/ApplicationStates/AbstractApplicationState.h>
#include <Headers/ToolClasses/FinalClass.h>

class IntroState : public Singleton<IntroState>, AbstractApplicationState, virtual FinalClass {
	SET_SINGLETON(IntroState)	
protected:
	IntroState();
	virtual ~IntroState() override;
public:	
	virtual Bool init() override;
	virtual void draw() override;
	virtual Bool update() override;
	virtual void shutdown() override;
	virtual void render() override;
	std::string getId() const;
};