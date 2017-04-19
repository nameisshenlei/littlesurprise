/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "loginComponent.h"
#include "mainShowComponent.h"
// #include "settingParams.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class gstSharedMemoryBin;

class MainContentComponent 
	: public Component
	, public AsyncUpdater
	, public Thread
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
	void showMainshow(bool showMain);

	void run();

// 	virtual void buttonClicked(Button* btn);
// 
// 	void paramsChanged();
// 
	virtual void handleAsyncUpdate();
protected:
// 	ScopedPointer<TextButton>				m_btnSetting;
// 	ScopedPointer<TextButton>				m_btnPlay;
// 	ScopedPointer<settingParams>			m_settingComponent;
// 	ScopedPointer<Component>				m_videoShow;
// 	ScopedPointer<gstSharedMemoryBin>		m_gstSharedMemoryBin;

	ScopedPointer<loginComponent>			m_login;
	ScopedPointer<mainShowComponent>		m_mainShow;

	GMainLoop*								m_gstMainLoop;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
