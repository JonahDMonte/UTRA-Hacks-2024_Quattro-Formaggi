# UTRA Hacks 2024 - Team Quattro Formaggi
Billions of bacteria and germs claim the surfaces we touch as home, Sanitation John sends them an eviction notice, automatically and efficiently.

Find it on the devpost here: https://devpost.com/software/sanitation-john

## Inspiration
Infectious and contaminated surfaces and their consequences.

## What it does
Sanitation John is an all-in-one table cleaning, decontaminating, and sanitizing bot for use on any potentially virile or biohazardous surface that may pose a hazard to the individual. Whether it is immunocompromised individuals or just your average person, Sanitation John can guarantee their health and safety with industry-standard sterilization techniques. Simply install Sanitation John, and then watch it clean your surface after use.

## How we built it
From our initial paper idea, we slowly started understanding the physical and electrical needs of our system. The first step was identifying the locations of different moving parts, and how to secure them there. We gathered materials to secure components and form the structure of the bot. The wiring and interfacing with a microcontroller followed naturally, where we defined a set number of operation states for the robot to be controlled by its various sensors. This was a fairly iterative process as we ran into hardware and software issues that had to be refined and redesigned.

## Challenges we ran into
Driving our motors was a big issue. Our components had large power draws at times that made them difficult to work with, especially with our other, generally low power, hardware.

## Accomplishments that we're proud of
Being able to source a variety of dynamic parts such as motors and servos that we are unfamiliar with, and getting them to work from scratch with our own circuits.

## What we learned
Sanitation John left the digital and electronic space and stepped into the physical plane, which brought a lot of challenges along with it. Besides getting motors to work with custom drivers we had to design, we also had to figure out the mechanics behind Sanitation John's motion. This along with interfacing a variety of sensors and peripherals at the same time provided a significant challenge that we were able to overcome.

## What's next for Sanitation John
Bigger, more robust, with additional features and quality of life improvements. Ideally, we could redesign it to be more lightweight and portable, and more easily transferable to different sizes and types of surfaces. Our design would also benefit from more sensors, as we only had a limited amount during this hackathon. Our design for the spray system was also rather resourcefully improvised and could be designed better with more time.
