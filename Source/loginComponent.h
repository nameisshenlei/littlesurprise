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

#ifndef __JUCE_HEADER_44138888F04232D8__
#define __JUCE_HEADER_44138888F04232D8__

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
class loginComponent  : public Component,
                        public ButtonListener
{
public:
    //==============================================================================
    loginComponent ();
    ~loginComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
	ScopedPointer<ImageButton> m_btnLogin;
    ScopedPointer<Label> label;
    ScopedPointer<TextEditor> m_txtUserName;
    ScopedPointer<TextEditor> m_txtPwd;
//     ScopedPointer<TextEditor> m_txtMask;
    ScopedPointer<ImageButton> m_imgLoginMain;
    ScopedPointer<ImageButton> m_imgLoginLogo;
//     ScopedPointer<ImageButton> m_btnMask;
    ScopedPointer<ImageButton> m_imgT2;
    ScopedPointer<ImageButton> m_imgT1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (loginComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_44138888F04232D8__
