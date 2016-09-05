# echo
Realtime twitter bot sonification based on [anon](https://github.com/edsu/anon) &amp; SodaLib

## Status
Unfinished code, getting closer .....    .. ... ...  ...

## Software Components
Built with OpenFrameworks 0.9.3. Targeted OS-es: OSX, Raspbian Jessie (Linux Arm)
OF dependencies (addons): [ofxJSON](https://github.com/jefftimesten/ofxJSON), [ofxPd](https://github.com/danomatika/ofxPd), [ofxSodaLib](https://github.com/stc/ofxSodaLib), [ofxFontStash](https://github.com/armadillu/ofxFontStash)
System dependency: ruby 1.9.3+ (this needs to be installed manually on the PI), [twurl](https://github.com/twitter/twurl)
Raspberry GPIO reading (of Rotary Encoder) library: [py-gaugette](https://github.com/guyc/py-gaugette) which is based on WiringPi (see repository's readme for details)

##Installation (on Raspberry PI / Jessie Light OS) :
Needed for getting twitter timelines:
- Update Ruby (1.9.3+) > [as described here](http://elinux.org/RPi_Ruby)
- [Install twurl](https://github.com/twitter/twurl) (and needed dependencies as indicated)

For Rotary encoder:
- Install Adafruit's [pygaugette lib](https://github.com/guyc/py-gaugette) (and needed dependencies as indicated)

##Note

For exhibiting echo in Sept of 2016, an instance of anon bot has been set up that is listening Hungarian Gov related ip numbers, named [@_EchoBot](https://twitter.com/_EchoBot) 

#License
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)