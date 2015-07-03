#Big Picture
Develop a distributed platform for device monitoring, control, and automation.

There are many things that can use this, but 2 markets are currently under consideration:
1.) Industrial HVAC control and building automation
2.) Home automation, security and automation

The platform will be a lightweight framework that will be easily extendable by third parties.  The extensions will be packaged in containers.  Extensions can define interfaces that will have auto-generated REST APIs by the framework.  Communication between extensions and the framework will utilize AMQP so that they can location independent for easy distribution and the extensions can be written in a different language than the core framework.


