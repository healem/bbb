#Plugin Framework
The intent is to make everything a plugin.  The framework exists only to support plugins and enable them to interact with each other.  There shall be no functionality implemented in the framework itself.

The framework is written in C++ as a series of shared libraries. 

The framework will manage a thread pool which is used to execute routines in the plugins.  There also need to be a mechanism to control the memory and CPU footprint of plugins.  Can cgroups work per thread?  If not, maybe a custom memory allocator?

#Plugins
Plugins are also written in C++.  They are stored in a sub-directory that will be scanned on startup.  All plugins present will be loaded (or should it be driven by config file?).  Plugins can be added and removed at run time.

Plugins must implement the plugin interface, which defines their behavior.  Plugins will be single threaded and the thread pool is managed by the framework.  Plugins will also have events and tasks, which will also have an interface that must be implemented (if the plugin has events and/or tasks)

#Plugin Interface
##Init
Init registers events and tasks with the framework

##Load
Loads the plugin and enables it

##Unload
Unload disables the plugin and frees its memory, unregistering tasks and events.

##Events
Events are signals from the plugin to the framework that something interesting has occurred.

Event registration info:
- Name
- Description (must support internationalization)
- Visible
- Type (enum - INFO, CRIT, etc)

##Tasks
Tasks are actions the framework asks the plugin to perform

Task registration info:
- Name
- Description (must support internationalization)
- Callback Method pointer
- Timeout

Task instance methods:
- Init
- Execute (can be called multiple times)
- getStatus
- getId
- Cancel

Multi-stage tasks shall be re-entrant.  Tasks need to track their own status internally (or should there be a template or struct that can be passed to the framework for safe keeping until the next execute call - which would pass the struct back in?)
