# echo
Realtime twitter bot sonification based on [anon](https://github.com/edsu/anon) &amp; SodaLib

## Concept
Echo is a listening machine. It represents anonymous Wikipedia edits made by governmental institutes of different countries. A few twitter bots are observing the IP addresses of Wikipedia article editors and once these edits are made from governmental addresses, the system notifies this event to the audience: it makes a sound along a visual sign on a map. The title of the installation reflects onto these - originally unintended - sounds made by the editors, but Echo is also the name of a basic command in different operating systems that is used to display textual content on the screen, or save it to a file. The visual appearance of the installation is inspired by early radio systems that have names of cities and different frequency ranges indicated on them. It also merits from the activities of amateur (and pirate) radio activities by transforming those concepts into the digital domain. Users can “tune” between different bot sonifications by rotating a knob, this act is similar to the search for meaningful information on those original radio appliances.

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