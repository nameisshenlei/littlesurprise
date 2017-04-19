/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
// #include "sharedMemoryGSTBin.h"

// class videoShow : public Component
// {
// public:
// 	void paint(Graphics& g)
// 	{
// 		g.fillAll(Colours::black);
// 	}
// };

//==============================================================================
MainContentComponent::MainContentComponent()
: Thread(L"gstMainLoop")
{
// 	addAndMakeVisible(m_btnSetting = new TextButton());
// 	m_btnSetting->setButtonText(L"ÉèÖÃ");
// 	m_btnSetting->addListener(this);
// 
// 	addAndMakeVisible(m_btnPlay = new TextButton());
// 	m_btnPlay->setButtonText(L"²¥·Å");
// 	m_btnPlay->addListener(this);
// 
// 	addAndMakeVisible(m_videoShow = new videoShow());
// 	m_videoShow->setOpaque(true);
// 
// 	addChildComponent(m_settingComponent = new settingParams(this));
// 	m_settingComponent->setOpaque(true);
// 
// 
// 	triggerAsyncUpdate();
	addAndMakeVisible(m_login = new loginComponent());
    setSize (600, 400);

// 	m_gstMainLoop = g_main_loop_new(nullptr, false);
// 	startThread();

}

MainContentComponent::~MainContentComponent()
{
// 	m_btnSetting = nullptr;
// 	m_btnPlay = nullptr;
// 	m_settingComponent = nullptr;
// 	m_videoShow = nullptr;
// 	if (m_gstSharedMemoryBin)
// 	{
// 		m_gstSharedMemoryBin->freeBin();
// 		m_gstSharedMemoryBin = nullptr;
// 	}

	g_main_loop_quit(m_gstMainLoop);
	stopThread(3000);

	m_login = nullptr;
	m_mainShow = nullptr;
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
}

void MainContentComponent::resized()
{
// 	m_btnSetting->setBounds(32, 8, 96, 24);
// 	m_btnPlay->setBounds(144, 8, 96, 24);
// 	if (getPeer())
// 	{
// 		Point<int> pVideo = getPeer()->globalToLocal(localPointToGlobal(Point<int>(32, 40)));
// 		m_videoShow->setBounds(pVideo.getX(), pVideo.getY(), getWidth() - 64, getHeight() - 48);
// 		Point<int> pSetting = getPeer()->globalToLocal(localPointToGlobal(Point<int>(0, 0)));
// 		m_settingComponent->setBounds(pSetting.getX(), pSetting.getY(), getWidth(), getHeight());
// 	}

	m_login->setBounds(0, 0, getWidth(), getHeight());
	if (m_mainShow)
		m_mainShow->setBounds(0, 0, getWidth(), getHeight());
}
// 
// void MainContentComponent::buttonClicked(Button* btn)
// {
// 	if (btn == m_btnSetting)
// 	{
// 		m_settingComponent->setVisible(true);
// 	}
// 	else if (btn == m_btnPlay)
// 	{
// 		if (m_btnPlay->getToggleState())
// 		{
// 			m_btnPlay->setToggleState(false, dontSendNotification);
// 			m_btnPlay->setButtonText(L"²¥·Å");
// 		}
// 		else
// 		{
// 			if (m_gstSharedMemoryBin)
// 			{
// 				m_gstSharedMemoryBin->freeBin();
// 				m_gstSharedMemoryBin = nullptr;
// 			}
// 
// 			m_gstSharedMemoryBin = new gstSharedMemoryBin();
// 			if (!m_gstSharedMemoryBin->createBin(1280,720,m_videoShow->getPeer()->getNativeHandle()))
// 			{
// 				return;
// 			}
// 
// 			m_btnPlay->setToggleState(true, dontSendNotification);
// 			m_btnPlay->setButtonText(L"Í£Ö¹");
// 		}
// 	}
// }
// 
// void MainContentComponent::paramsChanged()
// {
// 
// }
// 
void MainContentComponent::handleAsyncUpdate()
{
}

void MainContentComponent::showMainshow(bool showMain)
{
	m_login->setVisible(!showMain);

	if (showMain)
	{
		if (!m_mainShow)
		{
			addAndMakeVisible(m_mainShow = new mainShowComponent());
			resized();
			m_mainShow->setInVideoPeer();
		}
	}
	else
	{
		m_mainShow->setVisible(showMain);
	}
}
void MainContentComponent::run()
{
	g_main_loop_run(m_gstMainLoop);
}