# The ERNEST simulation framework
The ERNEST framework (EaRly verification and validation of Networked Embedded SysTems) is an open platform developed by Fraunhofer ESK for the early-stage analysis of component-based software in networked embedded systems. The aim is to allow the validation of non-functional requirements while the system is still being modelled and designed. To do this ERNEST links an in-house developed simulation framework with the Eclipse development environment, which offers the flexibility to use the platform in model-driven design processes.

# Download Ready-to-Use Eclipse Platform
Although ERNEST is open source and can be downloaded from GitHub, the simplest way to test ERNEST is the ready-to-use Eclipse, with ERNEST, an example Model and a tutorial, available at:
http://s.fhg.de/ERNEST-en

# Integration and adaptability
One of the primary design goals of the ERNEST platform is its broad utility. For this reason the engineers focused on ensuring the analysis runs independent of the language used to model the system architecture. This is achieved by means of a proprietary meta model that makes it possible to represent the simulation-relevant information and extract it from an output model. ERNEST currently features a transformation function that supports models based on the EAST-ADL architecture description language. EAST-ADL is prevalent in the automobile industry where it is used to describe relevant hardware and software relationships. Additional transformation processes are also possible for other modelling languages, such as UML/MARTE and AUTOSAR/Artop, and have been implemented prototypically

# Simulation-based analysis
The core of the ERNEST platform is a simulation-based analysis created on the foundation of a simulation framework developed with the SystemC system description language. The framework helps to simulate the hardware, software and communications behaviour of the modelled embedded system as accurately as possible. C++ source code is generated using a model-to-text transformation, which forms the executable simulation together with ERNEST. While the simulation is being executed, the system records trace activity on the ports of components that contain definitions for non-functional requirements.

The tracing data is fed back into the ERNEST model in order to analyze it. The simulation process then writes this information in a so-called change model, a mechanism set up by the Eclipse modelling framework. Modifications to individual model elements can thus be described and automatically adopted by the original model. This makes it possible to allocate the tracing data captured during the simulation to the respective element of the ERNEST model.

# Expandable analysis tool
The utilization of an open framework approach and the Eclipse development environment transforms ERNEST into a flexible, easily-expandable analysis platform. The ERNEST Eclipse extension provides a starting point for adding custom analyses, which can then be applied to the ERNEST models. The tracing data acquired in the model also allows the results to be evaluated in a variety of ways. The Eclipse modelling framework thus offers sufficient opportunity to extract the results of the analysis from the model and display it in the desired form. The system is currently capable of visualizing adherence to existing timing requirements.
