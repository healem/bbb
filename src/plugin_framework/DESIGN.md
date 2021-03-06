#Plugin Framework
The intent is to make everything a plugin.  The framework exists only to support plugins and enable them to interact with each other.  There shall be no functionality implemented in the framework itself.

The framework is written in C++ as a series of shared libraries. 

The framework will manage a thread pool which is used to execute routines in the plugins.  There also need to be a mechanism to control the memory and CPU footprint of plugins.  Can cgroups work per thread?  If not, maybe a custom memory allocator?

#Plugin Manager
The plugin manager is a core part of the plugin framework - it basically is the framework.  The plugin manager is what accepts plugin registration and deregistration requests.  It is responsible for loading and unloading plugins.  It is also what routes events to the event manager plugin, tasks to the task manager plugin, and logging requests to the logging plugin.  These 3 plugins are also core plugins.  While the plugin framework will run just fine without them, the system won't function very well without them.  This is so that they can be replaced during runtime.

The plugin manager must be coded such that it can deal with a poorly coded plugin.  Should a plugin experience a "fatal" or critical event, the plugin manager will simply unload it and allow other plugins to run unaffected.

##Startup
The plugin manager is the first to load.  It starts the core framework, then it begins to enumerate the core plugin directory.  It loads the logging, event manager, and task manager plugins - in that order.  Their order is determined by config file.  Their can be more than one logger, event manager, and task manager.

Once the core plugins are loaded, it enumerates the add-on plugin directories.  Their order can be specified by config file or by default they will be loaded per directory enumeration.

When it first brings up a plugin, the manager will call the plugins init method.  The plugins init method will register its events and tasks.  Once registration (init) is complete, the plugin manager will call the plugin's load method.  This is what "turns on" the plugin and enables it.

#Plugin Manager Interface
##Discover
Method that triggers plugin discovery.  Newly discovered plugins will be init'd once discovery completes.

##Register
Is called when a plugin wants to register all of its events and tasks

##Unregister
Is called when a plugin wants to unregister all of its events and tasks

##Alert
Is called when a plugin wants to notify the plugin manager that an event occurred.  The event will be sent to all registered event managers.

##Execute
Is called when a plugin wants a task to be run.  The task will be sent to all registered task amangers.

##Log
Is called when a plugin wants to log a message to the frameworks log file.

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
- Type - UUID for the event class - of the form <plugin_name>.<event_name> - does not need to match event Name field
- Visible
- Scope (enum - node, peer, cluster, fed)
- Level (enum - INFO, CRIT, etc)
- Category (same as plugin category?)

Events are encapsulated in an object that is derived from the base event class.  This object must be serializable as it will likely be sent to other nodes via AMQP or stored in a database.  The event object:

- Id - UID of the event on the node it originated on
- NodeId - UID of the node the event originated on
- Name
- Description
- Visible
- Level
- Scope (enum - node, peer, cluster, fed)
- Category
- Time - time the event was generated, UTC

##Tasks
Tasks are actions the framework asks the plugin to perform

Task registration info:
- Name
- Description (must support internationalization)
- Type - UUID of the task class, of the form <plugin_name>.<task_name> - task name does not need to match the Name field
- Scope (enum - node, peer, cluster, fed)
- Parameters (vector of tuples: name, type, bool required)
- Timeout

Task instance methods:
- Init
- Execute (can be called multiple times)
  - This is the callback that executes the task - the name, type, parameters, and timeout will be passed in
  - The execute method will likely be a dispatch table inside the plugin
- getStatus
- getId
- Cancel

Tasks are encapsulated in an object that is derived from the base task class.  This object must be serializable as it will likely be sent to other nodes via AMQP and or stored in a database.  The task object:

- Id - UID of the task instance, generated by the target node
- NodeId - UID of the node to execute the task
- Name
- Description
- Type
- Scope (enum - node, peer, cluster, fed)
- ScopeId (Id of node, peer group, cluster, or fed)
- Parameters
- Timeout
- StartTime - time the task is started, UTC
- EndTime - time the task is completed, UTC
- Duration - the time it took to execute the task
- Status - descriptive enum for what it is currently doing
- State - enum of its current state (running, waiting, complete, error, etc)

Multi-stage tasks shall be re-entrant.  Tasks need to track their own status internally (or should there be a template or struct that can be passed to the framework for safe keeping until the next execute call - which would pass the struct back in?)

When creating a task for execution: Name, Type, Parameters, and Timeout must be defined.  If a specific node must execute the task then NodeId must be filled in.  The other fields will be filled in during task execution.
