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

#include "inVideoShowComponent.h"
#include "mainShowComponent.h"
#include "gstHelpFunctions.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
inVideoShowComponent::inVideoShowComponent(rtmpPlayeresManger* pMainShow, String strUri)
: m_pMainShow(pMainShow)
, m_strUri(strUri)
{
    //[UserPreSize]
	m_imgQRCode = qrencodeCreateFromURI(m_strUri);
	addChildComponent(m_imgQRCode);
	setOpaque(true);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

inVideoShowComponent::~inVideoShowComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void inVideoShowComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::grey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void inVideoShowComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
// 	m_imgQRCode->setBounds(0, 0, getWidth(), getHeight());
	m_imgQRCode->setTransformToFit(Rectangle<float>(0.0, 0.0, (float)getWidth(), (float)getHeight()), RectanglePlacement::centred);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void inVideoShowComponent::mouseDoubleClick(const MouseEvent& /*e*/)
{
	mainShowComponent* mainShow = dynamic_cast<mainShowComponent*>(m_pMainShow);
	if (mainShow)
	{
		mainShow->selectedInVideo(this);
	}
}

void inVideoShowComponent::showQRcode(bool needShow)
{
	m_imgQRCode->setVisible(needShow);
	repaint();
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="inVideoShowComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff808080"/>
  <IMAGEBUTTON name="new button" id="7253287416c187e2" memberName="m_imgNum"
               virtualName="" explicitFocusOrder="0" pos="36R 36R 36 36" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
