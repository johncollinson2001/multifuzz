# Introduction

Multifuzz is a multiband distortion unit, for use in hosts that support VST technology, such as Cubase and Ableton. The plugin contains three distortion bands, which allow you to fine tune the frequency ranges using a band pass filter technique. You can then apply different types of overdrive and saturation to the filtered signal and mix them back together at the end. It leads to some highliy interesting textures and sounds, often allowing you to warp a sound in new and exciting ways.

# User Interface

The interface looks like....

![multifuzz-ui](https://raw.githubusercontent.com/johncollinson2001/multifuzz/master/design/GUI_Mockup.jpg)

The in/outs are on the left, with a wet/dry mix. The three distortion bands are on the right, complete with bypass, frequency and resonance of the band pass, overdrive and distortion type and a mix volume control.

# Technical stuff

The project was built using Visual C++ and a VST library called wdl-ol. Pull the repository and open the solution file in VC++. Build the solution which will place a dll in a folder called build-win, with a build for both VST2 and VST3 platforms. 

As mentioned above the plugin will open in any host that supports VST technology, but included in the repo for testing purposes is a free lightweight host called savihost. Open savihost and you will be prompted for the dll of the plugin to test - so navigate to the VST2 sub folder of the build-win directory and find the built dll. You may need to search the web for some instructions on savihost, but essentially you can play a wave file through the plugin and wire up your PC's microphone in order to test it out.