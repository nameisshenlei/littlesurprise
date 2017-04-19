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

#include "stopOutComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
stopOutComponent::stopOutComponent ()
{
	String strImagesPath = File::getSpecialLocation(File::currentApplicationFile).getParentDirectory().getFullPathName();
	strImagesPath += L"\\images\\";
	addAndMakeVisible(label = new Label("new label",
                                          CharPointer_UTF8 ("\xe6\x98\xaf\xe5\x90\xa6\xe5\x81\x9c\xe6\xad\xa2\xe7\x9b\xb4\xe6\x92\xad")));
    label->setFont (Font (24.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xfff33b72));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	addAndMakeVisible(m_btnCancel = new ImageButton("new button"));
	m_btnCancel->addListener(this);

	m_btnCancel->setImages(false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"cancelNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"cancelOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"cancelDown.png")), 1.000f, Colour(0x00000000));
    addAndMakeVisible (m_btnOK = new ImageButton ("new button"));
    m_btnOK->addListener (this);

    m_btnOK->setImages (false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"okNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"okOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"okDown.png")), 1.000f, Colour(0x00000000));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

stopOutComponent::~stopOutComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
	m_btnCancel = nullptr;
    m_btnOK = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void stopOutComponent::paint (Graphics& /*g*/)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void stopOutComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds ((getWidth() / 2) - (150 / 2), 104, 150, 24);
	m_btnCancel->setBounds((getWidth() / 2) + 22, 224, 82, 31);
    m_btnOK->setBounds ((getWidth() / 2) + -22 - 82, 224, 82, 31);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void stopOutComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

	if (buttonThatWasClicked == m_btnCancel)
    {
        //[UserButtonCode_m_btnCancle] -- add your button handler code here..
		DialogWindow* dw = findParentComponentOfClass<DialogWindow>();

		if (dw != nullptr)
			dw->exitModalState(2);
		//[/UserButtonCode_m_btnCancle]
    }
    else if (buttonThatWasClicked == m_btnOK)
    {
        //[UserButtonCode_m_btnOK] -- add your button handler code here..
		DialogWindow* dw = findParentComponentOfClass<DialogWindow>();

		if (dw != nullptr)
			dw->exitModalState(1);
		//[/UserButtonCode_m_btnOK]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="stopOutComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="300">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="new label" id="daba288ae85f6933" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0Cc 104 150 24" textCol="fff33b72"
         edTextCol="ff000000" edBkgCol="0" labelText="&#26159;&#21542;&#20572;&#27490;&#30452;&#25773;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="24" bold="0" italic="0" justification="36"/>
  <IMAGEBUTTON name="new button" id="a4011b7802ca4fca" memberName="m_btnCancle"
               virtualName="" explicitFocusOrder="0" pos="22C 224 82 31" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="19ee9b6f81e21892" memberName="m_btnOK"
               virtualName="" explicitFocusOrder="0" pos="-22Cr 224 82 31" buttonText="new button"
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
