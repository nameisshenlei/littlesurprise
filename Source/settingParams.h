/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_3C1649DF30DB746C__
#define __JUCE_HEADER_3C1649DF30DB746C__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainContentComponent;
class settingParams  : public Component,
                       public ButtonListener
{
public:
    //==============================================================================
	settingParams(MainContentComponent* pMain);
    ~settingParams();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
	void initParams();


	TextPropertyComponent* m_videoBufferName;
	ChoicePropertyComponent* m_videoSize;
	SliderPropertyComponent* m_videoBuffers;

	TextPropertyComponent* m_audioBufferName;
	SliderPropertyComponent* m_audioChannels;
	ChoicePropertyComponent* m_audioFreq;
	TextPropertyComponent* m_audioBufferSize;
	SliderPropertyComponent* m_audioBuffers;

	ScopedPointer<ToggleButton> m_btnUsingURI;
	ScopedPointer<ToggleButton> m_btnUsingMEM;
	ScopedPointer<TextEditor> m_txtURI;
private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MainContentComponent* m_pMain;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<PropertyPanel> m_memParams;
    ScopedPointer<TextButton> m_btnOK;
    ScopedPointer<TextButton> m_btnClose;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (settingParams)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_3C1649DF30DB746C__
