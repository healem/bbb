#Design
##Controller
The system is designed around small controllers that interact with a variety of hardware devices and can run any of a number of software services.  The controller design is initially focused on the BeagleBone Black.  The GPIO pins will be used to interact with raw devices.  It can also interact with network based systems via ethernet and WiFi.

The initial controller will run Ubuntu 14.04 and transition to Ubuntu Snappy Core.

The controller will have a few different services:
- Device plugin framework: interacts directly with hardware, written in C++
- REST API front end: control interface, written in go
- Distributed config db: federation config and monitoring, based on Consul
- Distributed time-series db: stores sensor data, likely based on BodyTrack Datastore or maybe Influx db with distribution added
- RabbitMQ: for inter-service communication, multi-language
- Rules engine: plugin based engine for automating actions based on rules, language TBD
- Management interface: web-based UI - mobile and desktop friendly, likely using bootstrap

##Features to enable third-party integration
There are a few different features planned to enable easy integration with third-party devices, controllers, and management systems.

###Third-party devices
Devices can be added by developing a plugin.  The plan is to create an SDK with a sample plugin and build script.  This will enable partners to add devices to a controller.  The intent is to allow a new type device to be added with only a few days of development.  Provided the template is followed, the REST API for the device will be automatically created by the framework.  This will enable easy integration into the rules engine and the rest of the system.

###Third-party controllers
Controllers can be added by developing a plugin that gives access to the controller.  It will behave similarly to a device, though will also have access to the rules engine APIs available via REST.  If the controller wants to participate in the federation, it will also need to implement Consul and RabittMQ for service integration.

###Third-party management systems
Management systems, such as Niagara, will be able to integrate with the REST API.  This will give full access to sensor data and control actions.

##Device Plugin framework
The core of the bbb service is a plugin framework written in C++.  Plugins will be dynamically loaded at startup and on demand.  There will be a core set of plugins for system control (reboot, shutdown, upgrade, load/unload plugin, etc).  The core plugins are always loaded at start time.  There will also be device plugins for interacting with specific devices (temperature sensors, bacnet devices, relay boards, etc).  These will be loaded at startup time according to configuration and eventually autodetection.  They can also be loaded later, on demand.

The plugin framework will also integrate with the REST frontend.  Plugins will register themselves with the framework.  As part of registration, the plugin will define public methods with defined types as input and output.  These definitions will be used to auto generate the REST API for the plugin.  The code generator will also be a plugin, itself.  It will be one of the core plugins always loaded.  

#TODO
Tasks:
- Tasks that target a specific device
- Tasks that target a specific service (that can run on any node)
- Tasks that are user visible
- Tasks that are hidden
- Tasks registered with plugin
- Maybe in C++ and core service
  - Distribution could still be a separate service
  - Or is it better to separate tasks as its own service?
    - Would need multiple plugin frameworks?
- Need to be re-entrant to allow for asynchronous task execution

Events/Alarms:
- Event/Alarm service
- Plugins register for notification (over AMQP?)
- Rules engine is always notified
- Event/Alarm definitions in json, delivered with plugin?

User Multitenancy, RBAC, Audit trail, authentication, permissions
- Should be able to create multiple tenants with access to certain objects
- Users get roles that give access to certain objects
- OAuth integration?
- Change UI view depending on admin vs user?

Federation authentication
- How to authenticate nodes - cert exchange at join time?
- Is crypto needed?  Certainly for user auth, but normal data?
