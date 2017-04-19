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

#include "mainShowComponent.h"
#include "stopOutComponent.h"
#include "outParamsComponent.h"
#include "inVideoSelectedComponent.h"
#include "gstUriPlayer.h"

//////////////////////////////////////////////////////////////////////////

fileProcessComponent::fileProcessComponent() { };
fileProcessComponent::~fileProcessComponent() {};

String fileProcessComponent::getTextFromValue(double value)
{
	return gstHelpProcessToString((int)value, (int)getMaximum());
}

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
mainShowComponent::mainShowComponent ()
: m_selectedPlayer(nullptr)
{
	String strImagesPath = File::getSpecialLocation(File::currentApplicationFile).getParentDirectory().getFullPathName();
	strImagesPath += L"\\images\\";

	addAndMakeVisible(m_imgM1 = new ImageButton("new button"));
    m_imgM1->addListener (this);

	Image imgM1 = ImageFileFormat::loadFrom(File(strImagesPath + L"m1.png"));
	m_imgM1->setImages(false, true, true,
		imgM1, 1.000f, Colour(0x00000000),
		imgM1, 1.000f, Colour(0x00000000),
		imgM1, 1.000f, Colour(0x00000000));
	addAndMakeVisible(m_outVideoShow = new outVideoShowComponent());
    m_outVideoShow->setName ("new component");

    addAndMakeVisible (label = new Label ("new label",
                                          CharPointer_UTF8 ("\xe7\x9b\xb4\xe6\x92\xad\xe8\xa7\x86\xe9\xa2\x91")));
    label->setFont (Font (24.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xfff33b72));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_btnOutStart = new ImageButton ("new button"));
    m_btnOutStart->addListener (this);

    m_btnOutStart->setImages (false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"startNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"startOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"startDown.png")), 1.000f, Colour(0x00000000));
    addAndMakeVisible (m_btnOutStop = new ImageButton ("new button"));
    m_btnOutStop->addListener (this);

    m_btnOutStop->setImages (false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"stopNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"stopOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"stopDown.png")), 1.000f, Colour(0x00000000));
	m_btnOutStop->setEnabled(false);

	addAndMakeVisible(m_inVideoFile = new inFileVideoShowComponent(this));
	m_inVideoFile->setName("new component");

    addAndMakeVisible (label2 = new Label ("new label",
                                           CharPointer_UTF8 ("\xe6\x9c\xac\xe5\x9c\xb0\xe8\xa7\x86\xe9\xa2\x91")));
    label2->setFont (Font (24.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colour (0xfff33b72));
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_btnLocalStart = new ImageButton ("new button"));
    m_btnLocalStart->addListener (this);

    m_btnLocalStart->setImages (false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"startNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"startOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"startDown.png")), 1.000f, Colour(0x00000000));
	addAndMakeVisible(m_btnLocalStop = new ImageButton("new button"));
    m_btnLocalStop->addListener (this);

    m_btnLocalStop->setImages (false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"stopNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"stopOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"stopDown.png")), 1.000f, Colour(0x00000000));
	addAndMakeVisible(m_btnLocalPrev = new ImageButton("new button"));
    m_btnLocalPrev->addListener (this);

    m_btnLocalPrev->setImages (false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"prevNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"prevOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"prevDown.png")), 1.000f, Colour(0x00000000));
	addAndMakeVisible(m_btnLocalNext = new ImageButton("new button"));
    m_btnLocalNext->addListener (this);

    m_btnLocalNext->setImages (false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"nextNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"nextOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"nextDown.png")), 1.000f, Colour(0x00000000));
	addAndMakeVisible(m_btnLocalOpen = new ImageButton("new button"));
    m_btnLocalOpen->addListener (this);

    m_btnLocalOpen->setImages (false, true, true,
		ImageFileFormat::loadFrom(File(strImagesPath + L"openFileNormal.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"openFileOver.png")), 1.000f, Colour(0x00000000),
		ImageFileFormat::loadFrom(File(strImagesPath + L"openFileDown.png")), 1.000f, Colour(0x00000000));
	addAndMakeVisible(m_sliderVolume = new Slider("new slider"));
    m_sliderVolume->setRange (0, 10, 0);
    m_sliderVolume->setSliderStyle (Slider::LinearHorizontal);
    m_sliderVolume->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
	m_sliderVolume->setColour(Slider::thumbColourId, Colour(0xfff33b72));
	m_sliderVolume->setColour(Slider::rotarySliderFillColourId, Colour(0x7ff33b72));
	m_sliderVolume->addListener(this);

    addAndMakeVisible (m_imgVolume = new ImageButton ("new button"));
    m_imgVolume->addListener (this);

	Image imgVolume = ImageFileFormat::loadFrom(File(strImagesPath + L"volume.png"));
	m_imgVolume->setImages(false, true, true,
		imgVolume, 1.000f, Colour(0x00000000),
		imgVolume, 1.000f, Colour(0x00000000),
		imgVolume, 1.000f, Colour(0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           CharPointer_UTF8 ("\xe6\x9c\xba\xe4\xbd\x8d\xe6\x8b\x8d\xe6\x91\x84\xe8\xa7\x86\xe9\xa2\x91")));
    label3->setFont (Font (24.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colour (0xfff33b72));
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	String strIp;
	{
		Array<IPAddress> allIp;
		IPAddress::findAllAddresses(allIp);
		for (int i = 0; i < allIp.size(); ++i)
		{
			if (allIp[i] != IPAddress::local())
			{
				strIp << L"rtmp://" << allIp[i].toString() << L":1935/live/";
				break;
			}
		}
	}

	initManager(strIp);

	for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
	{
		addAndMakeVisible(m_rtmpPlayerInfo[i].videoShowComponent);
		m_rtmpPlayerInfo[i].videoShowComponent->setName("rtmpVideoShow");
		m_rtmpPlayerInfo[i].videoShowComponent->showQRcode(true);

		addAndMakeVisible(m_rtmpPlayerInfo[i].selectedComponent);
		m_rtmpPlayerInfo[i].selectedComponent->setInterceptsMouseClicks(false, false);
	}

	addAndMakeVisible(m_selectedInFile = new inVideoSelectedComponent());
	m_selectedInFile->setInterceptsMouseClicks(false, false);

	addAndMakeVisible(m_sliderFileProcess = new fileProcessComponent());
	m_sliderFileProcess->setRange(0, 10, 0);
	m_sliderFileProcess->setSliderStyle(Slider::LinearHorizontal);
	m_sliderFileProcess->setTextBoxStyle(Slider::TextBoxBelow, true, 240, 20);
	m_sliderFileProcess->setColour(Slider::thumbColourId, Colours::white);
	m_sliderFileProcess->setColour(Slider::rotarySliderFillColourId, Colour(0x7ff33b72));
	m_sliderFileProcess->setColour(Slider::textBoxTextColourId, Colours::white);
	m_sliderFileProcess->setColour(Slider::textBoxBackgroundColourId, Colour(0x00ffffff));
	m_sliderFileProcess->setColour(Slider::textBoxOutlineColourId, Colour(0x00808080));
	m_sliderFileProcess->addListener(this);

	addAndMakeVisible(m_imgNum1 = new ImageButton("new button"));
	m_imgNum1->addListener(this);
	Image imgNum1 = ImageFileFormat::loadFrom(File(strImagesPath + L"num1.png"));
	m_imgNum1->setImages(false, true, true,
		imgNum1, 1.000f, Colour(0x00000000),
		imgNum1, 1.000f, Colour(0x00000000),
		imgNum1, 1.000f, Colour(0x00000000));

	addAndMakeVisible(m_imgNum2 = new ImageButton("new button"));
	m_imgNum2->addListener(this);
	Image imgNum2 = ImageFileFormat::loadFrom(File(strImagesPath + L"num2.png"));
	m_imgNum2->setImages(false, true, true,
		imgNum2, 1.000f, Colour(0x00000000),
		imgNum2, 1.000f, Colour(0x00000000),
		imgNum2, 1.000f, Colour(0x00000000));

	addAndMakeVisible(m_imgNum3 = new ImageButton("new button"));
	m_imgNum3->addListener(this);
	Image imgNum3 = ImageFileFormat::loadFrom(File(strImagesPath + L"num3.png"));
	m_imgNum3->setImages(false, true, true,
		imgNum3, 1.000f, Colour(0x00000000),
		imgNum3, 1.000f, Colour(0x00000000),
		imgNum3, 1.000f, Colour(0x00000000));

	setLocalButtonState(false);

	//[UserPreSize]
	startTimer(500);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
// 	triggerAsyncUpdate();
    //[/Constructor]
}

mainShowComponent::~mainShowComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	stopTimer();
    //[/Destructor_pre]

	stopLocalFile();
	if (m_testPlayer)
	{
		m_testPlayer->stop();
		m_testPlayer = nullptr;
	}

	if (m_rtmpPush)
	{
		m_rtmpPush->stop();
		m_rtmpPush = nullptr;
	}

    m_imgM1 = nullptr;
    m_outVideoShow = nullptr;
    label = nullptr;
    m_btnOutStart = nullptr;
    m_btnOutStop = nullptr;
	m_inVideoFile = nullptr;
    label2 = nullptr;
    m_btnLocalStart = nullptr;
    m_btnLocalStop = nullptr;
    m_btnLocalPrev = nullptr;
    m_btnLocalNext = nullptr;
    m_btnLocalOpen = nullptr;
    m_sliderVolume = nullptr;
    m_imgVolume = nullptr;
    label3 = nullptr;

	m_selectedInFile = nullptr;
	m_sliderFileProcess = nullptr;

	m_imgNum1 = nullptr;
	m_imgNum2 = nullptr;
	m_imgNum3 = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void mainShowComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff1b1b1b));
    g.fillRect (0, 0, getWidth() - 0, getHeight() - 0);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void mainShowComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
	m_selectedInFile->setBounds(proportionOfWidth(0.5625f) + -8, proportionOfHeight(0.0667f) + -8, 494, 286);
	m_imgM1->setBounds(16, 0, 60, 163);
	m_outVideoShow->setBounds(proportionOfWidth(0.0625f), proportionOfHeight(0.0667f), 576, 324);
	label->setBounds(proportionOfWidth(0.0625f) + 0, proportionOfHeight(0.0667f) + -8 - 32, 176, 32);
	m_btnOutStart->setBounds(proportionOfWidth(0.0625f) + 0, proportionOfHeight(0.0667f) + 324 - -16, 38, 38);
	m_btnOutStop->setBounds((proportionOfWidth(0.0625f) + 0) + 38 - -16, proportionOfHeight(0.0667f) + 324 - -16, 38, 38);
	m_inVideoFile->setBounds(proportionOfWidth(0.5625f), proportionOfHeight(0.0667f), 480, 270);
	label2->setBounds(proportionOfWidth(0.5625f) + 0, proportionOfHeight(0.0667f) + -8 - 32, 176, 32);
	m_btnLocalStart->setBounds(proportionOfWidth(0.5625f) + 0, (proportionOfHeight(0.0667f) + 324 - -16) + 0, 38, 38);
	m_btnLocalStop->setBounds((proportionOfWidth(0.5625f) + 0) + 38 - -16, ((proportionOfHeight(0.0667f) + 324 - -16) + 0) + 0, 38, 38);
	m_btnLocalPrev->setBounds(((proportionOfWidth(0.5625f) + 0) + 38 - -16) + 38 - -16, (((proportionOfHeight(0.0667f) + 324 - -16) + 0) + 0) + 0, 38, 38);
	m_btnLocalNext->setBounds((((proportionOfWidth(0.5625f) + 0) + 38 - -16) + 38 - -16) + 38 - -16, ((((proportionOfHeight(0.0667f) + 324 - -16) + 0) + 0) + 0) + 0, 38, 38);
	m_btnLocalOpen->setBounds(proportionOfWidth(0.5625f) + 480 - 8 - 169, (((((proportionOfHeight(0.0667f) + 324 - -16) + 0) + 0) + 0) + 0) + 0, 169, 35);
	m_sliderVolume->setBounds(proportionOfWidth(0.0625f) + 576 - 240, proportionOfHeight(0.0667f) + 324 - -16, 240, 38);
	m_imgVolume->setBounds((proportionOfWidth(0.0625f) + 576 - 240) + -16 - 26, proportionOfHeight(0.0667f) + 324 - -24, 26, 23);
	label3->setBounds(proportionOfWidth(0.0625f) + 0, proportionOfHeight(0.6889f) + -8 - 32, 192, 32);
	m_sliderFileProcess->setBounds(proportionOfWidth(0.5625f) + 0, proportionOfHeight(0.0667f) + 270 - -8, 480, 40);
	m_imgNum1->setBounds((proportionOfWidth(0.0625f) + 0) + 384 - 16 - 36, proportionOfHeight(0.6889f) + 0 - 36, 36, 36);
	m_imgNum2->setBounds(proportionOfWidth(0.3489f) + 384 - 16 - 36, (proportionOfHeight(0.6889f) + 0) + 0 - 36, 36, 36);
	m_imgNum3->setBounds(proportionOfWidth(0.6354f) + 384 - 16 - 36, ((proportionOfHeight(0.6889f) + 0) + 0) + 0 - 36, 36, 36);

	m_inVideoFile->setBounds(getTopLevelComponent()->getLocalArea(this, Rectangle<int>(proportionOfWidth(0.5625f), proportionOfHeight(0.0667f), 480, 270)));
	m_outVideoShow->setBounds(getTopLevelComponent()->getLocalArea(this, Rectangle<int>(proportionOfWidth(0.0625f), proportionOfHeight(0.0667f), 576, 324)));

// 	m_inVideo1->setBounds(proportionOfWidth(0.0625f) + 0, proportionOfHeight(0.6889f), 384, 216);
// 	m_inVideo2->setBounds(proportionOfWidth(0.3489f), proportionOfHeight(0.6889f) + 0, 384, 216);
// 	m_inVideo3->setBounds(proportionOfWidth(0.6354f), (proportionOfHeight(0.6889f) + 0) + 0, 384, 216);
	m_rtmpPlayerInfo[0].selectedComponent->setBounds((proportionOfWidth(0.0625f) + 0) + -8, proportionOfHeight(0.6889f) + 216 - -8 - 232, 400, 232);
	m_rtmpPlayerInfo[1].selectedComponent->setBounds(proportionOfWidth(0.3489f) + -8, (proportionOfHeight(0.6889f) + 0) + -8, 400, 232);
	m_rtmpPlayerInfo[2].selectedComponent->setBounds(proportionOfWidth(0.6354f) + -8, ((proportionOfHeight(0.6889f) + 0) + 0) + -8, 400, 232);
	m_rtmpPlayerInfo[0].videoShowComponent->setBounds(getTopLevelComponent()->getLocalArea(this, Rectangle<int>(proportionOfWidth(0.0625f) + 0, proportionOfHeight(0.6889f), 384, 216)));
	m_rtmpPlayerInfo[1].videoShowComponent->setBounds(getTopLevelComponent()->getLocalArea(this, Rectangle<int>(proportionOfWidth(0.3489f), proportionOfHeight(0.6889f) + 0, 384, 216)));
	m_rtmpPlayerInfo[2].videoShowComponent->setBounds(getTopLevelComponent()->getLocalArea(this, Rectangle<int>(proportionOfWidth(0.6354f), (proportionOfHeight(0.6889f) + 0) + 0, 384, 216)));

	//[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void mainShowComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == m_imgM1)
    {
        //[UserButtonCode_m_imgM1] -- add your button handler code here..
        //[/UserButtonCode_m_imgM1]
    }
    else if (buttonThatWasClicked == m_btnOutStart)
    {
        //[UserButtonCode_m_btnOutStart] -- add your button handler code here..
		outParamsComponent* pOutParams = new outParamsComponent();
		int ret = DialogWindow::showModalDialog(L"提示", pOutParams, m_outVideoShow, Colours::lightgrey.withAlpha(0.4f), true);
		deleteAndZero(pOutParams);
		if (ret == 720)
		{
			// 720P
			m_rtmpPushWidth = 1280;
			m_rtmpPushHeight = 720;
			m_rtmpPushBr = 1000;
		}
		else if (ret == 360)
		{
			// 360P
			m_rtmpPushWidth = 480;
			m_rtmpPushHeight = 360;
			m_rtmpPushBr = 500;
		}
		else if (ret == 270)
		{
			// 270P
			m_rtmpPushWidth = 360;
			m_rtmpPushHeight = 270;
			m_rtmpPushBr = 200;
		}
		else
		{
			// cancel
			return;
		}

		m_rtmpPush = new nemoGstRtmpPush();
		if (m_rtmpPush->initPush(L"rtmp://localhost:1935/live/test1", m_rtmpPushWidth, m_rtmpPushHeight, m_rtmpPushBr) != 0)
		{
			return;
		}

		if (m_rtmpPush->play() != 0)
		{
			m_rtmpPush = nullptr;
			return;
		}
		m_rtmpPush->setNewSrc();

		
		m_selectedPlayer->linkConvertElementsForRtmp(m_rtmpPushWidth, m_rtmpPushHeight);
		m_selectedPlayer->linkRtmpPush(m_rtmpPush);

		m_btnOutStart->setEnabled(false);
		m_btnOutStop->setEnabled(true);
		//[/UserButtonCode_m_btnOutStart]
    }
    else if (buttonThatWasClicked == m_btnOutStop)
    {
        //[UserButtonCode_m_btnOutStop] -- add your button handler code here..
		stopOutComponent* pStopOut = new stopOutComponent();
		int ret = DialogWindow::showModalDialog(L"提示", pStopOut, m_outVideoShow, Colours::lightgrey.withAlpha(0.4f), true);
		deleteAndZero(pStopOut);
		if (ret == 1)
		{
			// OK
		}
		else
		{
			// cancle
			return;
		}

		m_btnOutStart->setEnabled(true);
		m_btnOutStop->setEnabled(false);

		m_selectedPlayer->brokenRtmpPush();

		if (m_rtmpPush)
		{
			m_rtmpPush->stop();
		}
		m_rtmpPush = nullptr;

        //[/UserButtonCode_m_btnOutStop]
    }
    else if (buttonThatWasClicked == m_btnLocalStart)
    {
        //[UserButtonCode_m_btnLocalStart] -- add your button handler code here..
		if (m_selectedFile.isNotEmpty())
		{
			if (playLocalFile() == 0)
			{
				setLocalButtonState(true);
			}
		}
		//[/UserButtonCode_m_btnLocalStart]
    }
    else if (buttonThatWasClicked == m_btnLocalStop)
    {
        //[UserButtonCode_m_btnLocalStop] -- add your button handler code here..
		stopLocalFile();
		m_testPlayer->linkMainPreview(m_outVideoShow->getPeer()->getNativeHandle());
		setLocalButtonState(false);
		//[/UserButtonCode_m_btnLocalStop]
    }
    else if (buttonThatWasClicked == m_btnLocalPrev)
    {
        //[UserButtonCode_m_btnLocalPrev] -- add your button handler code here..
		m_uriLocalFilePlayer->seekBack();
		//[/UserButtonCode_m_btnLocalPrev]
    }
    else if (buttonThatWasClicked == m_btnLocalNext)
    {
        //[UserButtonCode_m_btnLocalNext] -- add your button handler code here..
		m_uriLocalFilePlayer->seekForward();
		//[/UserButtonCode_m_btnLocalNext]
    }
    else if (buttonThatWasClicked == m_btnLocalOpen)
    {
        //[UserButtonCode_m_btnLocalOpen] -- add your button handler code here..
		FileChooser myChooser(L"请选择需要播放的文件",
			File::getSpecialLocation(File::userHomeDirectory),
			"*.mkv;*.mp4;*.avi;*.mov;*.mpg");

		if (myChooser.browseForFileToOpen())
		{
			stopLocalFile();
			setLocalButtonState(false);

			File selectedFile(myChooser.getResult());
			m_selectedFile = selectedFile.getFullPathName();

			if (playLocalFile() == 0)
			{
// 				setLocalButtonState(true);
			}
		}
        //[/UserButtonCode_m_btnLocalOpen]
    }
    else if (buttonThatWasClicked == m_imgVolume)
    {
        //[UserButtonCode_m_imgVolume] -- add your button handler code here..
        //[/UserButtonCode_m_imgVolume]
    }
	else if (buttonThatWasClicked == m_imgNum1)
	{
		//[UserButtonCode_m_imgNum1] -- add your button handler code here..
		createRtmpPlayer(0,this);
		//[/UserButtonCode_m_imgNum1]
	}
	else if (buttonThatWasClicked == m_imgNum2)
	{
		//[UserButtonCode_m_imgNum2] -- add your button handler code here..
		createRtmpPlayer(1,this);
		//[/UserButtonCode_m_imgNum2]
	}
	else if (buttonThatWasClicked == m_imgNum3)
	{
		//[UserButtonCode_m_imgNum3] -- add your button handler code here..
		createRtmpPlayer(2,this);
		//[/UserButtonCode_m_imgNum3]
	}

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

bool mainShowComponent::keyPressed(const KeyPress& key)
{
	if (key == KeyPress('1', ModifierKeys(ModifierKeys::ctrlModifier),'1')
		|| key == KeyPress(KeyPress::numberPad1, ModifierKeys(ModifierKeys::noModifiers), '1'))
	{
		selectedInVideo(m_rtmpPlayerInfo[0].videoShowComponent);
		return true;
	}
	else if (key == KeyPress('2', ModifierKeys(ModifierKeys::ctrlModifier), '2')
		|| key == KeyPress(KeyPress::numberPad2, ModifierKeys(ModifierKeys::noModifiers), '2'))
	{
		selectedInVideo(m_rtmpPlayerInfo[1].videoShowComponent);
		return true;
	}
	else if (key == KeyPress('3', ModifierKeys(ModifierKeys::ctrlModifier), '3')
		|| key == KeyPress(KeyPress::numberPad3, ModifierKeys(ModifierKeys::noModifiers), '3'))
	{
		selectedInVideo(m_rtmpPlayerInfo[2].videoShowComponent);
		return true;
	}
	else if (key == KeyPress('4', ModifierKeys(ModifierKeys::ctrlModifier), '4')
		|| key == KeyPress(KeyPress::numberPad4, ModifierKeys(ModifierKeys::noModifiers), '4'))
	{
		selectedInVideo(m_inVideoFile);
		return true;
	}

	return false;
}

int mainShowComponent::playLocalFile()
{
	m_uriLocalFilePlayer = new nemoGstUriPlayer();
	if (m_uriLocalFilePlayer->playerInit(m_mainClock, this, m_selectedFile, m_inVideoFile->getPeer()->getNativeHandle()) != 0)
	{
		return -1;
	}

	if (m_uriLocalFilePlayer->play(true) != 0)
	{
		return -1;
	}

	return 0;
}

void mainShowComponent::stopLocalFile()
{
	if (m_uriLocalFilePlayer)
	{
		m_uriLocalFilePlayer->stop();
		m_uriLocalFilePlayer = nullptr;
	}
}

void mainShowComponent::setLocalButtonState(bool bPlaying)
{
	m_btnLocalStart->setEnabled(!bPlaying);
	m_btnLocalStop->setEnabled(bPlaying);
	m_btnLocalPrev->setEnabled(bPlaying);
	m_btnLocalNext->setEnabled(bPlaying);
}

void mainShowComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == m_sliderVolume)
    {
        //[UserSliderCode_m_sliderVolume] -- add your slider handling code here..
        //[/UserSliderCode_m_sliderVolume]
    }
	else if (sliderThatWasMoved == m_sliderFileProcess)
	{
	}

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void mainShowComponent::sliderDragStarted(Slider* s)
{
	if (s == m_sliderFileProcess)
	{
		if (m_uriLocalFilePlayer)
		{
			m_uriLocalFilePlayer->stopTimer();
		}
	}
}

void mainShowComponent::sliderDragEnded(Slider* s)
{
	if (s == m_sliderFileProcess)
	{
		if (m_uriLocalFilePlayer)
		{
			gint64 seekTime = (gint64)m_sliderFileProcess->getValue();
			seekTime *= 1000000000;

			m_uriLocalFilePlayer->seek(seekTime);
			m_uriLocalFilePlayer->startTimer(500);
		}
	}
}

void mainShowComponent::onBasePlayerError(nemoGstBasePlayer* p)
{
	if (p == m_uriLocalFilePlayer)
	{
		setLocalButtonState(false);
		m_uriLocalFilePlayer->stop();
		m_uriLocalFilePlayer = nullptr;
		if (m_selectedInFile->isSelected())
		{
			exchangeSelectedPlayer(m_testPlayer);
		}
	}
	else
	{
		for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
		{
			if (m_rtmpPlayerInfo[i].rtmpPlayer == p)
			{
				m_rtmpPlayerInfo[i].rtmpPlayer->stop();
				m_rtmpPlayerInfo[i].rtmpPlayer = nullptr;
				m_rtmpPlayerInfo[i].timeoutCheck = (Time::getCurrentTime() + RelativeTime::seconds(2));
				m_rtmpPlayerInfo[i].videoShowComponent->showQRcode(true);

				if (m_rtmpPlayerInfo[i].selectedComponent->isSelected())
				{
					exchangeSelectedPlayer(m_testPlayer);
				}
			}
		}
	}
}
void mainShowComponent::onBasePlayerEOS(nemoGstBasePlayer* p)
{
	if (p == m_uriLocalFilePlayer)
	{
		setLocalButtonState(false);
		m_uriLocalFilePlayer->seek(0);
// 		m_uriLocalFilePlayer->play(true);
	}
	else
	{
		for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
		{
			if (m_rtmpPlayerInfo[i].rtmpPlayer == p)
			{
				m_rtmpPlayerInfo[i].rtmpPlayer->stop();
				m_rtmpPlayerInfo[i].rtmpPlayer = nullptr;
				m_rtmpPlayerInfo[i].timeoutCheck = Time::getCurrentTime() + RelativeTime::seconds(2);
				m_rtmpPlayerInfo[i].videoShowComponent->showQRcode(true);

				if (m_rtmpPlayerInfo[i].selectedComponent->isSelected())
				{
					exchangeSelectedPlayer(m_testPlayer);
				}
			}
		}
	}
}
void mainShowComponent::onBasePlayerRunning(nemoGstBasePlayer* p)
{
	if (p == m_uriLocalFilePlayer)
	{
		setLocalButtonState(true);
		if (m_selectedInFile->isSelected())
		{
			exchangeSelectedPlayer(m_uriLocalFilePlayer);
		}
	}
	else
	{
		for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
		{
			if (m_rtmpPlayerInfo[i].rtmpPlayer == p)
			{
				m_rtmpPlayerInfo[i].videoShowComponent->showQRcode(false);
				if (m_rtmpPlayerInfo[i].selectedComponent->isSelected())
				{
					exchangeSelectedPlayer(m_rtmpPlayerInfo[i].rtmpPlayer);
				}
			}
		}
	}
}
void mainShowComponent::onBasePlayerProcess(nemoGstBasePlayer* p, gint64 d, gint64 c)
{
	if (p == m_uriLocalFilePlayer)
	{
		d /= 1000000000;
		c /= 1000000000;

		// 	String processInfo = gstHelpProcessToString((int)c, (int)d);
		// 	m_inVideoFile->setProcessInfo(processInfo);

		m_sliderFileProcess->setRange(0.0, (double)d);
		m_sliderFileProcess->setValue((double)c, dontSendNotification);
	}
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void mainShowComponent::exchangeSelectedPlayer(nemoGstBasePlayer* newPlayer)
{
	if (!newPlayer)
		return;

	if (m_selectedPlayer != newPlayer)
	{
		if (m_rtmpPush)
		{
			newPlayer->linkConvertElementsForRtmp(m_rtmpPushWidth, m_rtmpPushHeight);
			m_selectedPlayer->brokenRtmpPush();
			newPlayer->linkRtmpPush(m_rtmpPush);
			m_selectedPlayer->brokenConvertElementsForRtmp();
		}
		m_selectedPlayer->brokenMainPreview();
		newPlayer->linkMainPreview(m_outVideoShow->getPeer()->getNativeHandle());


		m_selectedPlayer = newPlayer;
	}
}

inVideoSelectedComponent* mainShowComponent::getOldSelectedIn()
{
	if (m_selectedInFile->isSelected())
	{
		return m_selectedInFile;
	}
	for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
	{
		if (m_rtmpPlayerInfo[i].selectedComponent->isSelected())
		{
			return m_rtmpPlayerInfo[i].selectedComponent;
		}
	}

	return nullptr;
}

void mainShowComponent::selectedInVideo(Component* who)
{
	inVideoSelectedComponent* oldSel = getOldSelectedIn();

	inVideoSelectedComponent* nowSel = nullptr;
	nemoGstUriPlayer* nowP = nullptr;


	if (who == m_inVideoFile)
	{
		nowSel = m_selectedInFile;
		nowP = m_uriLocalFilePlayer;
	}
	for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
	{
		if (m_rtmpPlayerInfo[i].videoShowComponent == who)
		{
			nowSel = m_rtmpPlayerInfo[i].selectedComponent;
			nowP = m_rtmpPlayerInfo[i].rtmpPlayer;
		}
	}

	if (oldSel)
	{
		oldSel->setSelected(false);
		if (oldSel == nowSel)
		{
			exchangeSelectedPlayer(m_testPlayer);
		}
		else
		{
			nowSel->setSelected(true);
			exchangeSelectedPlayer(nowP);
		}
	}
	else
	{
		nowSel->setSelected(true);
		exchangeSelectedPlayer(nowP);
	}
}

void mainShowComponent::setInVideoPeer()
{
	m_inVideoFile->addToDesktop(0, getPeer()->getNativeHandle());
	for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
	{
		m_rtmpPlayerInfo[i].videoShowComponent->addToDesktop(0, getPeer()->getNativeHandle());
	}
	m_outVideoShow->addToDesktop(0, getPeer()->getNativeHandle());

	if (!m_testPlayer)
	{
		m_testPlayer = new nemoGstTestPlayer();
		m_testPlayer->initPlayer(m_mainClock,this);
		m_testPlayer->play();

		m_selectedPlayer = m_testPlayer;
		m_testPlayer->linkMainPreview(m_outVideoShow->getPeer()->getNativeHandle());
	}

	resized();
}

void mainShowComponent::timerCallback()
{
	checkAndRestartRtmpPlayer(this);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="mainShowComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff">
    <RECT pos="0 0 0M 0M" fill="solid: ff1b1b1b" hasStroke="0"/>
  </BACKGROUND>
  <IMAGEBUTTON name="new button" id="35f627fbb3fb596f" memberName="m_imgM1"
               virtualName="" explicitFocusOrder="0" pos="32 0 120 326" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <GENERICCOMPONENT name="new component" id="624c3c2c2d8d144f" memberName="m_outVideoShow"
                    virtualName="" explicitFocusOrder="0" pos="216 128 480 360" class="Component"
                    params=""/>
  <LABEL name="new label" id="a5d11aed80711e52" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="216 80 176 40" textCol="fff33b72"
         edTextCol="ff000000" edBkgCol="0" labelText="&#30452;&#25773;&#35270;&#39057;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="32" bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="new button" id="2cbf1588c58c5398" memberName="m_btnOutStart"
               virtualName="" explicitFocusOrder="0" pos="216 512 38 38" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="65b20b870e1b475b" memberName="m_btnOutStop"
               virtualName="" explicitFocusOrder="0" pos="280 512 38 38" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <GENERICCOMPONENT name="new component" id="b1bb22d14287f465" memberName="component"
                    virtualName="" explicitFocusOrder="0" pos="500R 128 400 300"
                    class="Component" params=""/>
  <LABEL name="new label" id="5dd386996ef53bba" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="500R 80 176 40" textCol="fff33b72"
         edTextCol="ff000000" edBkgCol="0" labelText="&#26412;&#22320;&#35270;&#39057;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="32" bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="new button" id="ccee80ee110d2785" memberName="m_btnLocalStart"
               virtualName="" explicitFocusOrder="0" pos="500R 448 38 38" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="ee1b9bb7cdc1153e" memberName="m_btnLocalStop"
               virtualName="" explicitFocusOrder="0" pos="436R 448 38 38" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="6a87501fd1356043" memberName="m_btnLocalPrev"
               virtualName="" explicitFocusOrder="0" pos="372R 448 38 38" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="670f8715ba6b4faa" memberName="m_btnLocalNext"
               virtualName="" explicitFocusOrder="0" pos="308R 448 38 38" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="cfb4e393cfca58a9" memberName="m_btnLocalOpen"
               virtualName="" explicitFocusOrder="0" pos="372R 512 169 35" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <SLIDER name="new slider" id="efc0b931b4963cc5" memberName="m_sliderVolume"
          virtualName="" explicitFocusOrder="0" pos="432 512 262 38" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <IMAGEBUTTON name="new button" id="ffbaac03bb47f025" memberName="m_imgVolume"
               virtualName="" explicitFocusOrder="0" pos="384 520 26 23" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <GENERICCOMPONENT name="new component" id="86f2079a034c7885" memberName="m_inVideo1"
                    virtualName="" explicitFocusOrder="0" pos="216 264R 320 240"
                    class="Component" params=""/>
  <LABEL name="new label" id="56a4f8385fe39c33" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="216 320R 192 40" textCol="fff33b72"
         edTextCol="ff000000" edBkgCol="0" labelText="&#26426;&#20301;&#25293;&#25668;&#35270;&#39057;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="32" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="new component" id="a59e3ba8d86d2805" memberName="m_inVideo2"
                    virtualName="" explicitFocusOrder="0" pos="-98C 264R 320 240"
                    class="Component" params=""/>
  <GENERICCOMPONENT name="new component" id="aacfe24fa65a992f" memberName="m_inVideo3"
                    virtualName="" explicitFocusOrder="0" pos="412R 264R 320 240"
                    class="Component" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
