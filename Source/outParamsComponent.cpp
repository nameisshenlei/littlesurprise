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

#include "outParamsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
outParamsComponent::outParamsComponent ()
{
	addAndMakeVisible(m_btn720P = new DrawableButton("720P", DrawableButton::ImageRaw));
	{
		DrawableText* normalTxt = new DrawableText();
		normalTxt->setText(L"超清 720P");
		normalTxt->setFont(
			Font(32.00f, Font::plain),
			true);
		normalTxt->setColour(Colour(0xfff7f7f7));
		normalTxt->setJustification(Justification::centred);
		normalTxt->setBoundingBox(RelativeParallelogram(Rectangle<float>(0.0f, 16.0f, 400.0f, 32.0f)));

		DrawableText* overTxt = new DrawableText();
		overTxt->setText(L"超清 720P");
		overTxt->setFont(
			Font(32.00f, Font::plain),
			true);
		overTxt->setColour(Colour(0xfff33b72));
		overTxt->setJustification(Justification::centred);
		overTxt->setBoundingBox(RelativeParallelogram(Rectangle<float>(0.0f, 16.0f, 400.0f, 32.0f)));

		m_btn720P->setImages(normalTxt, overTxt);

		deleteAndZero(normalTxt);
		deleteAndZero(overTxt);
	}
    m_btn720P->setRadioGroupId (100);
    m_btn720P->addListener (this);

	addAndMakeVisible(m_btn360P = new DrawableButton("360P", DrawableButton::ImageRaw));
	{
		DrawableText* normalTxt = new DrawableText();
		normalTxt->setText(L"高清 360P");
		normalTxt->setFont(
			Font(32.00f, Font::plain),
			true);
		normalTxt->setColour(Colour(0xfff7f7f7));
		normalTxt->setJustification(Justification::centred);
		normalTxt->setBoundingBox(RelativeParallelogram(Rectangle<float>(0.0f, 16.0f, 400.0f, 32.0f)));

		DrawableText* overTxt = new DrawableText();
		overTxt->setText(L"高清 360P");
		overTxt->setFont(
			Font(32.00f, Font::plain),
			true);
		overTxt->setColour(Colour(0xfff33b72));
		overTxt->setJustification(Justification::centred);
		overTxt->setBoundingBox(RelativeParallelogram(Rectangle<float>(0.0f, 16.0f, 400.0f, 32.0f)));

		m_btn360P->setImages(normalTxt, overTxt);
		deleteAndZero(normalTxt);
		deleteAndZero(overTxt);

	}
    m_btn360P->setRadioGroupId (100);
    m_btn360P->addListener (this);

	addAndMakeVisible(m_btn270P = new DrawableButton("270P", DrawableButton::ImageRaw));
	{
		DrawableText* normalTxt = new DrawableText();
		normalTxt->setText(L"标清 270P");
		normalTxt->setFont(
			Font(32.00f, Font::plain),
			true);
		normalTxt->setColour(Colour(0xfff7f7f7));
		normalTxt->setJustification(Justification::centred);
		normalTxt->setBoundingBox(RelativeParallelogram(Rectangle<float>(0.0f, 16.0f, 400.0f, 32.0f)));

		DrawableText* overTxt = new DrawableText();
		overTxt->setText(L"标清 270P");
		overTxt->setFont(
			Font(32.00f, Font::plain),
			true);
		overTxt->setColour(Colour(0xfff33b72));
		overTxt->setJustification(Justification::centred);
		overTxt->setBoundingBox(RelativeParallelogram(Rectangle<float>(0.0f, 16.0f, 400.0f, 32.0f)));

		m_btn270P->setImages(normalTxt, overTxt);
		deleteAndZero(normalTxt);
		deleteAndZero(overTxt);

	}
    m_btn270P->setRadioGroupId (100);
    m_btn270P->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          CharPointer_UTF8 ("\xe5\xbb\xba\xe8\xae\xae\xe5\x9c\xa8\xe7\xbd\x91\xe7\xbb\x9c\xe6\xb5\x81\xe7\x95\x85\xe7\x9a\x84\xe6\x83\x85\xe5\x86\xb5\xe4\xb8\x8b\xe9\x80\x89\xe6\x8b\xa9")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::lightgrey);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           CharPointer_UTF8 ("\xe5\xbb\xba\xe8\xae\xae\xe5\x9c\xa8\xe7\xbd\x91\xe7\xbb\x9c\xe4\xb8\x80\xe8\x88\xac\xe6\x83\x85\xe5\x86\xb5\xe4\xb8\x8b\xe9\x80\x89\xe6\x8b\xa9")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
	label2->setColour(Label::textColourId, Colours::lightgrey);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           CharPointer_UTF8 ("\xe5\xbb\xba\xe8\xae\xae\xe5\x9c\xa8\xe7\xbd\x91\xe7\xbb\x9c\xe7\xb3\x9f\xe7\xb3\x95\xe7\x9a\x84\xe6\x83\x85\xe5\x86\xb5\xe4\xb8\x8b\xe9\x80\x89\xe6\x8b\xa9")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
	label3->setColour(Label::textColourId, Colours::lightgrey);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

outParamsComponent::~outParamsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    m_btn720P = nullptr;
    m_btn360P = nullptr;
    m_btn270P = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void outParamsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1b1b1b));

    g.setColour (Colours::grey);
    g.fillRect (18, 90, getWidth() - 36, 1);

    g.setColour (Colours::grey);
    g.fillRect (18, 181, getWidth() - 36, 1);

    g.setColour (Colours::grey);
    g.fillRect (18, 272, getWidth() - 36, 1);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void outParamsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    m_btn720P->setBounds (0, 0, getWidth() - 0, 64);
    m_btn360P->setBounds (0, 91, getWidth() - 0, 64);
    m_btn270P->setBounds (0, 182, getWidth() - 0, 64);
    label->setBounds (0, 64, getWidth() - 0, 24);
    label2->setBounds (0, 155, getWidth() - 0, 24);
    label3->setBounds (0, 246, getWidth() - 0, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void outParamsComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == m_btn720P)
    {
        //[UserButtonCode_m_btn720P] -- add your button handler code here..
		DialogWindow* dw = findParentComponentOfClass<DialogWindow>();

		if (dw != nullptr)
			dw->exitModalState(720);
		//[/UserButtonCode_m_btn720P]
    }
    else if (buttonThatWasClicked == m_btn360P)
    {
        //[UserButtonCode_m_btn360P] -- add your button handler code here..
		DialogWindow* dw = findParentComponentOfClass<DialogWindow>();

		if (dw != nullptr)
			dw->exitModalState(360);
		//[/UserButtonCode_m_btn360P]
    }
    else if (buttonThatWasClicked == m_btn270P)
    {
        //[UserButtonCode_m_btn270P] -- add your button handler code here..
		DialogWindow* dw = findParentComponentOfClass<DialogWindow>();

		if (dw != nullptr)
			dw->exitModalState(270);
		//[/UserButtonCode_m_btn270P]
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

<JUCER_COMPONENT documentType="Component" className="outParamsComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="300">
  <BACKGROUND backgroundColour="ff1b1b1b">
    <RECT pos="18 90 36M 1" fill="solid: ff808080" hasStroke="0"/>
    <RECT pos="18 181 36M 1" fill="solid: ff808080" hasStroke="0"/>
    <RECT pos="18 272 36M 1" fill="solid: ff808080" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="new button" id="eb570ba60dcae93b" memberName="m_btn720P"
              virtualName="" explicitFocusOrder="0" pos="0 0 0M 64" bgColOff="0"
              bgColOn="0" textCol="fff7f7f7" textColOn="fff33b72" buttonText="&#36229;&#28165;720P"
              connectedEdges="3" needsCallback="1" radioGroupId="100"/>
  <TEXTBUTTON name="new button" id="9d52129ad0fe5f37" memberName="m_btn360P"
              virtualName="" explicitFocusOrder="0" pos="0 91 0M 64" bgColOff="0"
              bgColOn="0" textCol="fff33b72" textColOn="fff33b72" buttonText="&#36229;&#28165;360P"
              connectedEdges="3" needsCallback="1" radioGroupId="100"/>
  <TEXTBUTTON name="new button" id="aee4f6e322515cef" memberName="m_btn270P"
              virtualName="" explicitFocusOrder="0" pos="0 182 0M 64" bgColOff="0"
              bgColOn="0" textCol="fff33b72" textColOn="fff33b72" buttonText="&#36229;&#28165;270P"
              connectedEdges="3" needsCallback="1" radioGroupId="100"/>
  <LABEL name="new label" id="44ac931a8da7fbd2" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 64 0M 24" textCol="fff0f8ff" edTextCol="ff000000"
         edBkgCol="0" labelText="&#24314;&#35758;&#22312;&#32593;&#32476;&#27969;&#30021;&#30340;&#24773;&#20917;&#19979;&#36873;&#25321;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a8a4b6d2155d9208" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0 155 0M 24" textCol="fff0f8ff" edTextCol="ff000000"
         edBkgCol="0" labelText="&#24314;&#35758;&#22312;&#32593;&#32476;&#19968;&#33324;&#24773;&#20917;&#19979;&#36873;&#25321;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="f385e6e87d400732" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="0 246 0M 24" textCol="fff0f8ff" edTextCol="ff000000"
         edBkgCol="0" labelText="&#24314;&#35758;&#22312;&#32593;&#32476;&#31967;&#31957;&#30340;&#24773;&#20917;&#19979;&#36873;&#25321;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
