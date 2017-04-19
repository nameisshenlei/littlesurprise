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

#include "loginComponent.h"
#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
loginComponent::loginComponent ()
{
	String strImagesPath = File::getSpecialLocation(File::currentApplicationFile).getParentDirectory().getFullPathName();
	strImagesPath += L"\\images\\";

    addAndMakeVisible (label = new Label ("new label",
                                          CharPointer_UTF8 ("\xe5\xaf\xbc\xe6\x92\xad\xe5\x91\x98\xe7\x9b\xb8\xe5\x85\xb3\xe4\xbf\xa1\xe6\x81\xaf\xe8\xaf\xb7\xe6\x9f\xa5\xe8\xaf\xa2\xe5\xbe\xae\xe4\xbf\xa1\xe6\x88\x96\xe6\x9f\xa5\xe8\xaf\xa2\xe5\xae\xa2\xe6\x88\xb7\xe7\xab\xaf\xe7\x9a\x84\xe7\x9b\xb8\xe5\x85\xb3\xe4\xbf\xa1\xe6\x81\xaf")));
    label->setFont (Font (16.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xff928e8e));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_txtUserName = new TextEditor ("new text editor"));
    m_txtUserName->setMultiLine (false);
    m_txtUserName->setReturnKeyStartsNewLine (false);
    m_txtUserName->setReadOnly (false);
    m_txtUserName->setScrollbarsShown (false);
    m_txtUserName->setCaretVisible (true);
    m_txtUserName->setPopupMenuEnabled (true);
    m_txtUserName->setText (String::empty);
	m_txtUserName->setTextToShowWhenEmpty(L"导播员姓名", Colours::slategrey);

    addAndMakeVisible (m_txtPwd = new TextEditor ("new text editor"));
    m_txtPwd->setMultiLine (false);
    m_txtPwd->setReturnKeyStartsNewLine (false);
    m_txtPwd->setReadOnly (false);
    m_txtPwd->setScrollbarsShown (true);
    m_txtPwd->setCaretVisible (true);
    m_txtPwd->setPopupMenuEnabled (true);
    m_txtPwd->setText (String::empty);
	m_txtPwd->setTextToShowWhenEmpty(L"导播员手机号码", Colours::slategrey);

//     addAndMakeVisible (m_txtMask = new TextEditor ("new text editor"));
//     m_txtMask->setMultiLine (false);
//     m_txtMask->setReturnKeyStartsNewLine (false);
//     m_txtMask->setReadOnly (false);
//     m_txtMask->setScrollbarsShown (true);
//     m_txtMask->setCaretVisible (true);
//     m_txtMask->setPopupMenuEnabled (true);
//     m_txtMask->setText (String::empty);
// 	m_txtMask->setTextToShowWhenEmpty(L"验证码", Colours::slategrey);

    addAndMakeVisible (m_imgLoginMain = new ImageButton ("new button"));
    m_imgLoginMain->addListener (this);

	Image imgLoginMain = ImageFileFormat::loadFrom(File(strImagesPath + L"loginMain.png"));
    m_imgLoginMain->setImages (false, true, true,
		imgLoginMain, 1.000f, Colour(0x00000000),
		imgLoginMain, 1.000f, Colour(0x00000000),
		imgLoginMain, 1.000f, Colour(0x00000000));
    addAndMakeVisible (m_imgLoginLogo = new ImageButton ("new button"));
    m_imgLoginLogo->addListener (this);

	Image imgLoginLogo = ImageFileFormat::loadFrom(File(strImagesPath + L"loginLogo.png"));
	m_imgLoginLogo->setImages(false, true, true,
		imgLoginLogo, 1.000f, Colour(0x00000000),
		imgLoginLogo, 1.000f, Colour(0x00000000),
		imgLoginLogo, 1.000f, Colour(0x00000000));

//     addAndMakeVisible (m_btnMask = new ImageButton ("new button"));
//     m_btnMask->addListener (this);
// 
//     m_btnMask->setImages (false, true, true,
//                           Image(), 1.000f, Colour (0x00000000),
//                           Image(), 1.000f, Colour (0x00000000),
//                           Image(), 1.000f, Colour (0x00000000));

    addAndMakeVisible (m_imgT2 = new ImageButton ("new button"));
    m_imgT2->addListener (this);

	Image imgLoginT2 = ImageFileFormat::loadFrom(File(strImagesPath + L"loginT2.png"));
	m_imgT2->setImages(false, true, true,
		imgLoginT2, 1.000f, Colour(0x00000000),
		imgLoginT2, 1.000f, Colour(0x00000000),
		imgLoginT2, 1.000f, Colour(0x00000000));
    addAndMakeVisible (m_imgT1 = new ImageButton ("new button"));
    m_imgT1->addListener (this);

	Image imgLoginT1 = ImageFileFormat::loadFrom(File(strImagesPath + L"loginT1.png"));
	m_imgT1->setImages(false, true, true,
		imgLoginT1, 1.000f, Colour(0x00000000),
		imgLoginT1, 1.000f, Colour(0x00000000),
		imgLoginT1, 1.000f, Colour(0x00000000));

	addAndMakeVisible(m_btnLogin = new ImageButton("new button"));
	m_btnLogin->addListener(this);

	m_btnLogin->setImages(false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"loginNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"loginOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"loginDown.png")), 1.000f, Colour(0x00000000));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

loginComponent::~loginComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    m_btnLogin = nullptr;
    label = nullptr;
    m_txtUserName = nullptr;
    m_txtPwd = nullptr;
//     m_txtMask = nullptr;
    m_imgLoginMain = nullptr;
    m_imgLoginLogo = nullptr;
//     m_btnMask = nullptr;
    m_imgT2 = nullptr;
    m_imgT1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void loginComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setGradientFill (ColourGradient (Colour (0xffec396f),
                                       static_cast<float> ((getWidth() / 2)), static_cast<float> ((getHeight() / 2)),
                                       Colour (0xff160509),
                                       0.0f, 0.0f,
                                       true));
    g.fillRect (0, 0, getWidth() - 0, getHeight() - 0);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void loginComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    m_btnLogin->setBounds (getWidth() - 364, getHeight() - 120, 250, 45);
    label->setBounds (getWidth() - 344, getHeight() - 56, 216, 40);
    m_txtUserName->setBounds (getWidth() - 364, getHeight() - 312, 250, 45);
    m_txtPwd->setBounds (getWidth() - 364, getHeight() - 248, 250, 45);
//     m_txtMask->setBounds (getWidth() - 364, getHeight() - 184, 120, 45);
	m_imgLoginMain->setBounds((getWidth() / 2) + -314, (getHeight() / 2) + -296, 542, 445);
	m_imgLoginLogo->setBounds(64, getHeight() - 64 - 116, 116, 116);
//     m_btnMask->setBounds (getWidth() - 236, getHeight() - 184, 120, 45);
	m_imgT2->setBounds(getWidth() - 332, getHeight() - 368, 193, 30);
	m_imgT1->setBounds(getWidth() - 284, getHeight() - 488, 95, 95);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void loginComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == m_btnLogin)
    {
        //[UserButtonCode_m_btnLogin] -- add your button handler code here..
		MainContentComponent* pMain = findParentComponentOfClass<MainContentComponent>();
		if (pMain)
		{
			pMain->showMainshow(true);
		}
        //[/UserButtonCode_m_btnLogin]
    }
    else if (buttonThatWasClicked == m_imgLoginMain)
    {
        //[UserButtonCode_m_imgLoginMain] -- add your button handler code here..
        //[/UserButtonCode_m_imgLoginMain]
    }
    else if (buttonThatWasClicked == m_imgLoginLogo)
    {
        //[UserButtonCode_m_imgLoginLogo] -- add your button handler code here..
        //[/UserButtonCode_m_imgLoginLogo]
    }
//     else if (buttonThatWasClicked == m_btnMask)
//     {
//         //[UserButtonCode_m_btnMask] -- add your button handler code here..
//         //[/UserButtonCode_m_btnMask]
//     }
    else if (buttonThatWasClicked == m_imgT2)
    {
        //[UserButtonCode_m_imgT2] -- add your button handler code here..
        //[/UserButtonCode_m_imgT2]
    }
    else if (buttonThatWasClicked == m_imgT1)
    {
        //[UserButtonCode_m_imgT1] -- add your button handler code here..
        //[/UserButtonCode_m_imgT1]
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

<JUCER_COMPONENT documentType="Component" className="loginComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff">
    <RECT pos="0 0 0M 0M" fill=" radial: 0C 0C, 0 0, 0=ffec396f, 1=ff160509"
          hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="new button" id="cfa96c9219183ea3" memberName="m_btnLogin"
              virtualName="" explicitFocusOrder="0" pos="364R 120R 250 45"
              buttonText="new button" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="58415bd38b778a0c" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="344R 56R 216 40" textCol="ff928e8e"
         edTextCol="ff000000" edBkgCol="0" labelText="&#23548;&#25773;&#21592;&#30456;&#20851;&#20449;&#24687;&#35831;&#26597;&#35810;&#24494;&#20449;&#25110;&#26597;&#35810;&#23458;&#25143;&#31471;&#30340;&#30456;&#20851;&#20449;&#24687;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16" bold="0" italic="0" justification="36"/>
  <TEXTEDITOR name="new text editor" id="bf3d135738e4391e" memberName="m_txtUserName"
              virtualName="" explicitFocusOrder="0" pos="364R 312R 250 45"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="53df169d712166d" memberName="m_txtPwd"
              virtualName="" explicitFocusOrder="0" pos="364R 248R 250 45"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="a780d61e6cbf3e8" memberName="m_txtMask"
              virtualName="" explicitFocusOrder="0" pos="364R 184R 120 45"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <IMAGEBUTTON name="new button" id="a735a9fd11000b0e" memberName="m_imgLoginMain"
               virtualName="" explicitFocusOrder="0" pos="-648 -456 542 445"
               posRelativeX="bf3d135738e4391e" posRelativeY="bf3d135738e4391e"
               buttonText="new button" connectedEdges="0" needsCallback="1"
               radioGroupId="0" keepProportions="1" resourceNormal="" opacityNormal="1"
               colourNormal="0" resourceOver="" opacityOver="1" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="9566e1e75eeaaf32" memberName="m_imgLoginLogo"
               virtualName="" explicitFocusOrder="0" pos="64 64Rr 234 234" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="e3e850955967c1a4" memberName="m_btnMask"
               virtualName="" explicitFocusOrder="0" pos="236R 184R 120 45"
               buttonText="new button" connectedEdges="0" needsCallback="1"
               radioGroupId="0" keepProportions="1" resourceNormal="" opacityNormal="1"
               colourNormal="0" resourceOver="" opacityOver="1" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="a4e4bc8e0252a76f" memberName="m_imgT2"
               virtualName="" explicitFocusOrder="0" pos="1064 576 193 30" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="25f8a86f87cca573" memberName="m_imgT1"
               virtualName="" explicitFocusOrder="0" pos="284R 488R 95 95" buttonText="new button"
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
