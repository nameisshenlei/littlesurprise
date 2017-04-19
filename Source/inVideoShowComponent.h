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

#ifndef __JUCE_HEADER_55A5488A0D9E9A64__
#define __JUCE_HEADER_55A5488A0D9E9A64__

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
class rtmpPlayeresManger;
class inVideoShowComponent  : public Component
{
public:
    //==============================================================================
	inVideoShowComponent(rtmpPlayeresManger* pMainShow, String strUri);
    ~inVideoShowComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
	void mouseDoubleClick(const MouseEvent& e);
	void showQRcode(bool needShow);
private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	rtmpPlayeresManger* m_pMainShow;
	String m_strUri;
	ScopedPointer<Drawable> m_imgQRCode;
    //[/UserVariables]
    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (inVideoShowComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_55A5488A0D9E9A64__
