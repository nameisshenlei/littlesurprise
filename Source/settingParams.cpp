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

#include "settingParams.h"
#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
settingParams::settingParams(MainContentComponent* pMain)
: m_pMain(pMain)
{
    addAndMakeVisible (m_btnUsingURI = new ToggleButton ("usingURI"));
    m_btnUsingURI->setButtonText (TRANS("using URI"));
    m_btnUsingURI->setRadioGroupId (100);
    m_btnUsingURI->addListener (this);

    addAndMakeVisible (m_btnUsingMEM = new ToggleButton ("usingMEM"));
    m_btnUsingMEM->setButtonText (TRANS("using shared-memory"));
    m_btnUsingMEM->setRadioGroupId (100);
    m_btnUsingMEM->addListener (this);
    m_btnUsingMEM->setToggleState (true, dontSendNotification);

    addAndMakeVisible (m_txtURI = new TextEditor ("new text editor"));
    m_txtURI->setMultiLine (false);
    m_txtURI->setReturnKeyStartsNewLine (false);
    m_txtURI->setReadOnly (false);
    m_txtURI->setScrollbarsShown (true);
    m_txtURI->setCaretVisible (true);
    m_txtURI->setPopupMenuEnabled (true);
    m_txtURI->setText (String::empty);

    addAndMakeVisible (m_memParams = new PropertyPanel());
    m_memParams->setName ("new component");

    addAndMakeVisible (m_btnOK = new TextButton ("new button"));
    m_btnOK->setButtonText (CharPointer_UTF8 ("\xe7\xa1\xae\xe5\xae\x9a"));
    m_btnOK->addListener (this);

    addAndMakeVisible (m_btnClose = new TextButton ("new button"));
    m_btnClose->setButtonText (CharPointer_UTF8 ("\xe5\x85\xb3\xe9\x97\xad"));
    m_btnClose->addListener (this);

	initParams();

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

settingParams::~settingParams()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    m_btnUsingURI = nullptr;
    m_btnUsingMEM = nullptr;
    m_txtURI = nullptr;
    m_memParams = nullptr;
    m_btnOK = nullptr;
    m_btnClose = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	m_videoSize = nullptr;
    //[/Destructor]
}

//==============================================================================
void settingParams::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::lightgrey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void settingParams::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    m_btnUsingURI->setBounds (32, 8, 150, 24);
    m_btnUsingMEM->setBounds (32, 88, 168, 24);
    m_txtURI->setBounds (32, 48, getWidth() - 64, 24);
    m_memParams->setBounds (32, 120, getWidth() - 64, getHeight() - 168);
    m_btnOK->setBounds (32, getHeight() - 8 - 24, 96, 24);
    m_btnClose->setBounds (144, getHeight() - 8 - 24, 96, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void settingParams::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == m_btnUsingURI)
    {
        //[UserButtonCode_m_btnUsingURI] -- add your button handler code here..
        //[/UserButtonCode_m_btnUsingURI]
    }
    else if (buttonThatWasClicked == m_btnUsingMEM)
    {
        //[UserButtonCode_m_btnUsingMEM] -- add your button handler code here..
        //[/UserButtonCode_m_btnUsingMEM]
    }
    else if (buttonThatWasClicked == m_btnOK)
    {
        //[UserButtonCode_m_btnOK] -- add your button handler code here..
		if (m_pMain)
		{
			m_pMain->paramsChanged();
			setVisible(false);
		}
        //[/UserButtonCode_m_btnOK]
    }
    else if (buttonThatWasClicked == m_btnClose)
    {
        //[UserButtonCode_m_btnClose] -- add your button handler code here..
		setVisible(false);
		//[/UserButtonCode_m_btnClose]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void settingParams::initParams()
{
	Array<PropertyComponent*> arrayParams;
	// video shared memory name;
	m_videoBufferName = new TextPropertyComponent(Value(var(L"TVPS_OUTPUT_VIDEO_REC")), L"video shared memory name", 100, false);
	arrayParams.add(m_videoBufferName);

	// video Size
	StringArray sizeStringArray;
	sizeStringArray.add(L"640 X 480");
	sizeStringArray.add(L"720 x 576");
	sizeStringArray.add(L"1280 X 720");
	sizeStringArray.add(L"1920 X 1080");

	Array<var> sizeVarArray;
	// 640 480
	var size640480;
	size640480.insert(0, var(640));
	size640480.insert(1, var(480));
	sizeVarArray.add(size640480);
	// 720 576
	var size720576;
	size720576.insert(0, var(720));
	size720576.insert(1, var(576));
	sizeVarArray.add(size720576);
	// 1280 720
	var size1280720;
	size1280720.insert(0, var(1280));
	size1280720.insert(1, var(720));
	sizeVarArray.add(size1280720);
	// 1920 1080
	var size19201080;
	size19201080.insert(0, var(1920));
	size19201080.insert(1, var(1080));
	sizeVarArray.add(size19201080);

	m_videoSize = new ChoicePropertyComponent(Value(size1280720), L"video size", sizeStringArray, sizeVarArray);

	arrayParams.add(m_videoSize);

	// video buffers
	m_videoBuffers = new SliderPropertyComponent(Value(var(5)), L"video buffers", 1.0, 20.0, 1.0);
	arrayParams.add(m_videoBuffers);

	// audio shared-memory name
	m_audioBufferName = new TextPropertyComponent(Value(var(L"TVPS_OUTPUT_AUDIO_REC")),L"audio shared memory name",100,false);
	arrayParams.add(m_audioBufferName);

	// audio channels
	m_audioChannels = new SliderPropertyComponent(Value(var(2)), L"audio channels", 1.0, 16.0, 1.0);
	arrayParams.add(m_audioChannels);
	// audio frequency
	StringArray freqStringArray;
	freqStringArray.add(L"8000");
	freqStringArray.add(L"11025");
	freqStringArray.add(L"22050");
	freqStringArray.add(L"32000");
	freqStringArray.add(L"44100");
	freqStringArray.add(L"47250");
	freqStringArray.add(L"48000");
	freqStringArray.add(L"96000");
	freqStringArray.add(L"192000");

	Array<var> freqArray;
	freqArray.add(var(8000));
	freqArray.add(var(11025));
	freqArray.add(var(22050));
	freqArray.add(var(32000));
	freqArray.add(var(44100));
	freqArray.add(var(47250));
	freqArray.add(var(48000));
	freqArray.add(var(96000));
	freqArray.add(var(192000));

	m_audioFreq = new ChoicePropertyComponent(Value(var(44100)), L"audio frequency", freqStringArray, freqArray);
	arrayParams.add(m_audioFreq);

	// audio buffer size
	m_audioBufferSize = new TextPropertyComponent(Value(var(7056)), L"audio buffer size", 10, false);
	arrayParams.add(m_audioBufferSize);

	// audio buffers
	m_audioBuffers = new SliderPropertyComponent(Value(var(10)), L"audio buffers", 1.0, 20.0, 1.0);
	arrayParams.add(m_audioBuffers);

	m_memParams->addProperties(arrayParams);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="settingParams" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TOGGLEBUTTON name="usingURI" id="9a353542464fbf53" memberName="m_btnUsingURI"
                virtualName="" explicitFocusOrder="0" pos="32 8 150 24" buttonText="using URI"
                connectedEdges="0" needsCallback="1" radioGroupId="100" state="0"/>
  <TOGGLEBUTTON name="usingMEM" id="49edd2306408a786" memberName="m_btnUsingMEM"
                virtualName="" explicitFocusOrder="0" pos="32 88 168 24" buttonText="using shared-memory"
                connectedEdges="0" needsCallback="1" radioGroupId="100" state="1"/>
  <TEXTEDITOR name="new text editor" id="10b0dd1fc281795c" memberName="m_txtURI"
              virtualName="" explicitFocusOrder="0" pos="32 48 64M 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <GENERICCOMPONENT name="new component" id="2015fd8d0d67cf4c" memberName="m_memParams"
                    virtualName="PropertyPanel" explicitFocusOrder="0" pos="32 120 64M 168M"
                    class="Component" params=""/>
  <TEXTBUTTON name="new button" id="1f10b0ee451ecac2" memberName="m_btnOK"
              virtualName="" explicitFocusOrder="0" pos="32 8Rr 96 24" buttonText="&#30830;&#23450;"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="1cc3b2a59760878e" memberName="m_btnClose"
              virtualName="" explicitFocusOrder="0" pos="144 8Rr 96 24" buttonText="&#20851;&#38381;"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
