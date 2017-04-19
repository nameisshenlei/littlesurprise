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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "inFileVideoShowComponent.h"
#include "mainShowComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
inFileVideoShowComponent::inFileVideoShowComponent(mainShowComponent* pMainShow)
: m_pMainShow(pMainShow)
{
	setOpaque(true);
    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

inFileVideoShowComponent::~inFileVideoShowComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]
    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void inFileVideoShowComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);
    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void inFileVideoShowComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}
void inFileVideoShowComponent::mouseDoubleClick(const MouseEvent& /*e*/)
{
	if (m_pMainShow) m_pMainShow->selectedInVideo(this);
	//[UserCode_mouseDoubleClick] -- Add your code here...
	//[/UserCode_mouseDoubleClick]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="inFileVideoShowComponent"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff808080"/>
  <LABEL name="new label" id="54d2871fb71febd5" memberName="m_labelTotal"
         virtualName="" explicitFocusOrder="0" pos="128R 24R 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="8:88:88 / 8:88:88" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
