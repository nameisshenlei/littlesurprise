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

#ifndef __JUCE_HEADER_AB3CEA68DD2F1EB6__
#define __JUCE_HEADER_AB3CEA68DD2F1EB6__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "inVideoShowComponent.h"
#include "inFileVideoShowComponent.h"
#include "outVideoShowComponent.h"
#include "gstRtmpPushBin.h"
#include "gstUriPlayer.h"
#include "gstTestPlayer.h"
#include "rtmpPlayerManager.h"

//[/Headers]
class inVideoSelectedComponent;

class fileProcessComponent : public Slider
{
public:
	fileProcessComponent();
	virtual ~fileProcessComponent();

	virtual String getTextFromValue(double value) override;
};

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class mainShowComponent  : public Component,
                           public ButtonListener,
                           public SliderListener,
						   public rtmpPlayeresManger,
						   public nemoGstBasePlayerCallback,
						   public Timer
{
public:
    //==============================================================================
    mainShowComponent ();
    ~mainShowComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    void sliderValueChanged (Slider* sliderThatWasMoved);
	void sliderDragStarted(Slider* s);
	void sliderDragEnded(Slider* s);

	void setLocalButtonState(bool bPlaying);

	virtual void onBasePlayerError(nemoGstBasePlayer* p);
	virtual void onBasePlayerEOS(nemoGstBasePlayer* p);
	virtual void onBasePlayerRunning(nemoGstBasePlayer* p);
	virtual void onBasePlayerProcess(nemoGstBasePlayer* p, gint64 d, gint64 c);

	void setInVideoPeer();

	void selectedInVideo(Component* who);

	int playLocalFile();
	void stopLocalFile();

	virtual bool keyPressed(const KeyPress& key);

	void timerCallback();
private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	void exchangeSelectedPlayer(nemoGstBasePlayer* newPlayer);
	inVideoSelectedComponent* getOldSelectedIn();

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ImageButton> m_imgM1;
	ScopedPointer<outVideoShowComponent> m_outVideoShow;
    ScopedPointer<Label> label;
    ScopedPointer<ImageButton> m_btnOutStart;
    ScopedPointer<ImageButton> m_btnOutStop;
	ScopedPointer<inFileVideoShowComponent> m_inVideoFile;
    ScopedPointer<Label> label2;
    ScopedPointer<ImageButton> m_btnLocalStart;
    ScopedPointer<ImageButton> m_btnLocalStop;
    ScopedPointer<ImageButton> m_btnLocalPrev;
    ScopedPointer<ImageButton> m_btnLocalNext;
    ScopedPointer<ImageButton> m_btnLocalOpen;
    ScopedPointer<Slider> m_sliderVolume;
    ScopedPointer<ImageButton> m_imgVolume;
    ScopedPointer<Label> label3;

	ScopedPointer<inVideoSelectedComponent> m_selectedInFile;
	ScopedPointer<Slider> m_sliderFileProcess;

	ScopedPointer<ImageButton> m_imgNum1;
	ScopedPointer<ImageButton> m_imgNum2;
	ScopedPointer<ImageButton> m_imgNum3;

	ScopedPointer<nemoGstRtmpPush> m_rtmpPush;
	int m_rtmpPushWidth;
	int m_rtmpPushHeight;
	int m_rtmpPushBr;

	String m_selectedFile;

	ScopedPointer<nemoGstTestPlayer> m_testPlayer;
	ScopedPointer<nemoGstUriPlayer> m_uriLocalFilePlayer;

	nemoGstBasePlayer* m_selectedPlayer;
	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (mainShowComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_AB3CEA68DD2F1EB6__
