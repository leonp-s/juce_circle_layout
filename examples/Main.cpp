#include "CircleLayoutExamples.h"

#include <juce_gui_basics/juce_gui_basics.h>

class CircleLayoutExamplesApp : public juce::JUCEApplication
{
public:
    CircleLayoutExamplesApp ()
    {
    }

    const juce::String getApplicationName () override
    {
        return "circle_layout_examples";
    }

    const juce::String getApplicationVersion () override
    {
        return "1.0.0";
    }

    bool moreThanOneInstanceAllowed () override
    {
        return true;
    }

    void initialise (const juce::String & commandLine) override
    {
        juce::ignoreUnused (commandLine);
        mainWindow.reset (new MainWindow (getApplicationName ()));
    }

    void shutdown () override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit () override
    {
        quit ();
    }

    void anotherInstanceStarted (const juce::String & commandLine) override
    {
        juce::ignoreUnused (commandLine);
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
        explicit MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance ().getDefaultLookAndFeel ().findColour (
                                  ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setColour (juce::ResizableWindow::ColourIds::backgroundColourId, juce::Colours::white);
            setUsingNativeTitleBar (true);
            setContentOwned (new CircleLayoutExamples (), true);
            setResizable (true, true);
            centreWithSize (getWidth (), getHeight ());
            setVisible (true);
        }

        void closeButtonPressed () override
        {
            JUCEApplication::getInstance ()->systemRequestedQuit ();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (CircleLayoutExamplesApp)