/**
\~english

\defgroup APP Applications

\defgroup LIBAPI Libraries

\defgroup LIBAPI_SERVICE Service library
\ingroup LIBAPI
\brief Service library
\details

+ Threading model: A plugin starts a thread to process a service.
    See the specific implementation: CPluginServiceThread and CService
+ Class relationship
  \image html docs/Image/PluginServiceAPI.svg
+ usge:
  - Implement plugin interface:
    + CPluginService: Plugin interface
    + CPluginServiceThread: The default start a new thread. eg. CPluginServiceRabbitVNC
      - Plugin name: This name must be the same as the project name (${PROJECT_NAME}).
        The translation file (${PROJECT_NAME}_*.ts)) name is associated with it. 
        E.g. CPluginServiceRabbitVNC::Name() 
  - Implement CService . Eg. CServiceRabbitVNC


\defgroup LIBAPI_CLIENT Client library
\ingroup LIBAPI
\brief Client library
\details 
- Client plugin interfaces class relationship
  \image html docs/Image/PluginClientAPI.svg
- Sequence diagram
  \image html docs/Image/PluginClientSequenceDiagram.svg


\defgroup CLIENT_API Client application interface
\ingroup LIBAPI_CLIENT
\brief Client application interface
\details
+ Class relationship
  \image html docs/Image/PluginClientAPI.svg
- Sequence diagram
  \image html docs/Image/ClientSequenceDiagram.svg
+ usge:
  - Instance class: CClient m_Client;
    + Handle CClient::Handle::onProcess to get the registered connection plugin
  - Use one of the following methods to create the connecter object:
    + CClient::CreateConnecter
    + CClient::LoadConnecter
  - Connect signal:
    + Connected CConnecter::sigConnected
    + Disconnect CConnecter::sigDisconnect
    + Disconnected CConnecter::sigDisconnected
  - Open the connect: CConnecter::Connect()
  - After receiving the CConnecter::sigConnected signal,
    do connection-related initialization work
  - After receiving the CConnecter::sigDisconnect signal,
    Call CConnecter::DisConnect() to close the connect.
  - Close the connect: CConnecter::DisConnect()
  - After receiving the CConnecter::sigDisconnected signal,
    do connection-related cleanup work,
    and delete the connector object after completion
     (MUST use CConnecter::deleteLater )


\defgroup CLIENT_PLUGIN_API Client plugin interfaces
\ingroup LIBAPI_CLIENT
\brief Client plugin interfaces.
\details
+ Thread module
  - Blocked: Most control protocol implementation library connections are blocking.
    \see CPluginClient CConnecterThread
  - No-blocking: eg: qt event. A thread can handle multiple connections.
    - The plugin does not have a background thread, and all connections use the main thread
    - The plugin has a background thread, and all connections use the same background thread
      \see CPluginClientThread CConnecterDesktop
+ Class relationship
  \image html docs/Image/PluginClientAPI.svg
+ Sequence diagram
  \image html docs/Image/PluginClientSequenceDiagram.svg
+ Write a plugin:
  - The format of the generated plug-in target name is: PluginClient${PROJECT_NAME}
    \include Plugins/FreeRDP/Client/CMakeLists.txt
  - Implement CPluginClient.
    + No background thread or Blocked background thread
      (A background thread handles a connection. The connection is blocked.).
      E.g. FreeRDP
      - Derive from CPluginClient. For example: CPluginFreeRDP 
        + Implement the Qt interface in the class declaration:
          \snippet Plugins/FreeRDP/Client/PluginFreeRDP.h Qt plugin interface
        + Initialize the operation in the constructor.
          For example: initializing resources, loading translation resources, etc.
        + Release resources in the destructor.
        + Implement properties and functions
          - Plugin name: This name must be the same as the project name (${PROJECT_NAME}).
            The translation file (${PROJECT_NAME}_*.ts)) name is associated with it. 
            E.g. CPluginFreeRDP::Name() 
             \include Plugins/FreeRDP/Client/PluginFreeRDP.cpp
    + No-blocking background thread: One background thread handles multiple connections.(Not used yet)
      The connection is non-blocking.
      - Derive from CPluginClientThread.
        + Implement the Qt interface in the class declaration:
          \snippet Plugins/RabbitVNC/Client/PluginRabbitVNC.h Qt plugin interface
        + Initialize the operation in the constructor.
          For example: initializing resources, loading translation resources, etc.
          \snippet Plugins/RabbitVNC/Client/PluginRabbitVNC.cpp Initialize resource
        + Release resources in the destructor.
        + Implement properties and functions
          - Plugin name: This name must be the same as the project name (${PROJECT_NAME}).
            The translation file (${PROJECT_NAME}_*.ts)) name is associated with it. 
            \include Plugins/RabbitVNC/Client/PluginRabbitVNC.cpp
  - Implement \ref CConnecter.
    - Implement remote desktop
      - Blocked: Implements a remote desktop background thread to handle
        a remote desktop connection, which can be derived from CConnecterThread. Eg: CConnecterFreeRDP
        \image html docs/Image/PluginClientBlockSequenceDiagram.svg
      - No-blocking: Implements a background thread to handle multiple remote desktop connections,
        which can be derived from CConnecterDesktop.
        \image html docs/Image/PluginClientNoBlockSequenDiagram.svg
    - Implement remote console, which can be derived from CConnecterTerminal
    - If the above two cannot meet your needs, you  can be derived from CConnecter
  - Implement a specific connection, derived from CConnect. For example: CConnectFreeRDP

\defgroup LIBAPI_THREAD Thread module
\ingroup LIBAPI_CLIENT
\brief Thread module
\details
+ Thread classification
  - Main thread(UI thread)
    - CConnecter
    - CFrmView
    - CParameter
  - Work thread
    - CConnect
+ The module of work thread
  - Blocked: Most control protocol implementation library connections are blocking.
    \see CPluginClient CConnecterThread
  - No-blocking: eg: qt event. A thread can handle multiple connections.
    \see CPluginClientThread CConnecterDesktop
+ Class relationship
  \image html docs/Image/PluginClientAPI.svg

\defgroup LIBAPI_CHANNEL Channel
\brief Stream data channel
\ingroup LIBAPI
\details
+ Class relationship
  \image html docs/Image/Channel.svg
  
\defgroup LIBAPI_ICE ICE
\ingroup LIBAPI_CHANNEL
\details
+ Class relationship
  \image html docs/Image/Channel.svg
  
*/
