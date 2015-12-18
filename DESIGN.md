#TODO
- [ ] Begin data sizing
- [ ] Begin database design
- [ ] Add sequence diagram for adding new device/plugin
- [ ] Add flow chart for data distribution
- [ ] Begin interface definitions for plugin framework
    - [ ] How to package for easy 3rd party integration
    - [ ] Make sure headers are easy to export and license is friendly
- [ ] How to allow third party, OEM branding

#Design
##Controller
The system is designed around small controllers that interact with a variety of hardware devices and can run any of a number of software services.  The controller design is initially focused on the BeagleBone Black.  The GPIO pins will be used to interact with raw devices.  It can also interact with network based systems via ethernet and WiFi.

The initial controller will run Ubuntu 14.04 and transition to Ubuntu Snappy Core.

The controller will have a few different services:
- Device plugin framework: interacts directly with hardware, written in C++
- REST API front end: control interface, written in go
  - Each controller has a REST API
  - Distribute UI service also has a REST API (hosted in same application server)
- Distributed config db: federation config and monitoring, based on Consul
- Distributed time-series db: stores sensor data, likely based on BodyTrack Datastore or maybe Influx db with distribution added
- RabbitMQ: for inter-service communication, multi-language
- Rules engine: plugin based engine for automating actions based on rules, language TBD
- Management interface: web-based UI - mobile and desktop friendly, likely using bootstrap

![Alt text](http://g.gravizo.com/g?
@startuml;
node "Controller" {;
frame "Application server"{;
[REST API];
};
frame "Plugin Framework"{;
[AMQP plugin];
[Device plugin1];
[Device plugin2];
[local task engine];
[local rules engine];
[system monitor];
};
database "Time series"{;
[sensor data];
[event tracking];
[task history];
[audit];
};
database "Consul"{;
[config data];
[service locator];
};
};
cloud "Distributed services"{;
[task engine];
[rules engine];
[UI service];
[user auth];
};
[UI] -down-> [UI service] : HTTPS;
[local task engine] <-up-> [task engine] : AMQP;
[local rules engine] <-up-> [rules engine] : AMQP;
[UI service] <-up- [REST API] : HTTPS;
[REST API] <-- [AMQP plugin] : AMQP;
User -> [UI];
@enduml;
)

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

Plugins will register events it emits, events it wishes to receive, tasks it can run, roles required for each task.

Each plugin instance gets a unique to the federation service locator address.  This is stored in Consul and is used to identify where events came from and where tasks need to be run

#Tasks:
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
- Tasks are run as a user that belongs to a tenant(s)
- Task addressed/named: device.pluginInstance.task

#Events/Alarms:
- Event/Alarm service
- Plugins register for notification (over AMQP?)
  - Framework handles AMQP to event handler translation so plugins dont need to know AMQP
  - Framework registers plugin with rules engine for event notification
- Rules engine is always notified
- Event/Alarm definitions in json
    - delivered with plugin
    - events belong to 1 or more categories (for easy glob registration)
      - arbitrarily defined, with some standard ones (security, occupancy, temp, etc)
    - internationalized - json file per language
    - event addressed/named: device.pluginInstance.event
- Events trigger and clear alarms

#User Multitenancy, RBAC, Audit trail, authentication, permissions
- Should be able to create multiple tenants with access to certain objects
- Users get roles that give access to certain objects
- Plugin framework handles permissions and tenancy
  - Each Task has its own permission created automatically by framework: plugin.taskName
  - Tasks can specify role required to execute it (need to define roles)
    - Makes it easier to set defaults and auto add perms to existing users when adding new device
  - Tenancy fully handled in framework
- OAuth integration?  Users/roles in LDAP?  Something else?  Keystone?
- Change UI view depending on admin vs user?

#Federation authentication
- How to authenticate nodes - cert exchange at join time?
- Is crypto needed?  Certainly for user auth, but normal data?

#Rules engine
- Tiered: first level runs on device, send events to parent (ie- when threshold exceeded)
  - Parent may have another threshold for sending to its parent?  Or is it only 2 levels?
    - Parent could be distributed or single service?  (1 or more parents?)
- Rules/policies stored in Consul
- Rules engine is a plugin - registers for all event categories

![Alt text](http://g.gravizo.com/g?
@startuml;
actor User;
participant "Device Plugin Occ Sensor" as A;
participant "Device framework" as B;
participant "Device Local PolEngine" as C;
participant "Distributed TaskEngine" as D;
participant "Distributed PolEngine" as E;
User -> A: Enter room;
activate A;
deactivate A;
A -> B: Room occupied event;
activate B;
B -> C: Room occupied event;
activate C;
C --> E: Room occupied event;
activate E;
deactivate C;
E --> D: Prepare room task;
activate D;
deactivate E;
D --> B: Turn on lights task;
D --> B: Turn up heat task;
deactivate D;
deactivate B;
@enduml
)

#Upgrade
- OS upgrade
- Core service upgrade (ie- framework)
- Plugin upgrade
- Versioning and interop
  - protocol (AMQP)
  - REST API
  - Database

#Health check
- Integrate with Consul health reporting
- Monitor space, cpu, memory
- Monitor HW health

#Database sizing
- device local
  - granular time-series
- replicated
  - configuration
  - coarse time-series
  - event history
  - audit trail?

#Support info gathering
- Logging and log rotation
  - where do plugins log?
- What to gather?
- Phone home capability?
- Support user access

#Installation
- New device
- New plugin
- Compute only nodes? Just UI and rules engine?

#Configuration export and backup
- Templates?

#Internationalization
- All outward facing strings will be internationlization friendly
  - defined in a json or xml file with canonical name or number
  - strings defined in a file per language
- Debug logs do not need to be internationalized
