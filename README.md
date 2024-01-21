# UTRA Hacks 2024 - Team Quattro Formaggi
Billions of bacteria and germs claim the surfaces we touch as home, Sanitation John sends them an eviction notice, automatically and efficiently.

Uses 2 buttons to override its state and turn it on/off, in addition to a power switch.
With the Arduino flashed, simply plug it in and turn it on with the button and switch, then watch it go to work.

Find it on the devpost here: https://devpost.com/software/sanitation-john

## Inspiration
Shortening wait times for the emergency room and doctor's office is an [ongoing problem [1]](https://pubmed.ncbi.nlm.nih.gov/27299977/) which was unfortunately evident in the [COVID-19 pandemic [2]](https://www.cbc.ca/news/canada/health-care-how-we-got-here-fix-broken-cracks-billions-canadian-duclos-1.6691196). Our team aimed to develop a robot that could automatically detect and disinfect a dirty surface. With vast numbers of these systems installed in a region, we think the accumulated time savings for disinfection can effectively shorten wait times for patients.
## What it does
Sanitation John is an all-in-one table cleaning, decontaminating, and sanitizing bot for use on any potentially virile or biohazardous surface that may pose a hazard to the individual. Whether it is immunocompromised individuals or just your average person, Sanitation John can guarantee their health and safety with [industry-standard [3]](https://www.publichealthontario.ca/-/media/documents/b/2018/bp-environmental-cleaning.pdf) sterilization techniques. Simply install Sanitation John, and then watch it clean your surface after use.
## How we built it
From our initial paper idea, we slowly started understanding our system's physical and electrical needs. The first step was identifying the locations of different moving parts, and how to secure them there. We gathered materials to secure components and form the structure of the bot. The wiring and interfacing with a microcontroller followed naturally, where we defined a set number of operation states for the robot to be controlled by its various sensors. This was a fairly iterative process as we ran into hardware and software issues that had to be refined and redesigned.
## Challenges we ran into
Driving our motors was a big issue. Our components had large power draws at times that made them difficult to work with, especially with our other, generally low power, hardware.
## Accomplishments that we're proud of
We were able to be resourceful and source various dynamic parts such as motors and servos that we were unfamiliar with while getting them to work from scratch with our circuits.
## What we learned
Sanitation John left the digital and electronic space and stepped into the physical plane, which brought a lot of challenges along with it. Besides getting motors to work with custom drivers we had to design, we also had to figure out the mechanics behind Sanitation John's motion. This along with selecting and operating appropriate sensors and peripherals at the same time provided a significant challenge that we were able to overcome.
## What's next for Sanitation John
Bigger, more robust, with additional features and quality of life improvements. Ideally, we could redesign it to be more lightweight and portable, and more easily transferable to different sizes and types of surfaces. Our design would also benefit from more sensors, as we only had a limited amount during this hackathon. Our design for the spray system was also rather resourcefully improvised and could be designed better with more time.

## References
[1] Moscelli G, Siciliani L, Tonei V. Do waiting times affect health outcomes? Evidence from coronary bypass. Soc Sci Med. 2016 Jul;161:151-9. doi: 10.1016/j.socscimed.2016.05.043. Epub 2016 May 30. PMID: 27299977.
[2] https://www.cbc.ca/news/canada/health-care-how-we-got-here-fix-broken-cracks-billions-canadian-duclos-1.6691196
[3] https://www.publichealthontario.ca/-/media/documents/b/2018/bp-environmental-cleaning.pdf
