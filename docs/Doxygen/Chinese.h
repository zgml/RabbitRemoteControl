/**

\~chinese

\defgroup APP 程序

\defgroup LIBAPI 库

\defgroup LIBAPI_SERVICE 服务端库
\ingroup LIBAPI
\brief 服务端库
\details 

+ 线程模型：一个插件启动一个线程处理一个服务。具体实现见： CPluginServiceThread 和 CService
+ 类关系：
  \image html docs/Image/PluginServiceAPI.svg
+ 写一个插件：
  - 实现插件接口:
    + CPluginService 服务插件接口
    + CPluginServiceThread: 默认为每个插件启动一个线程进行处理。例如： CPluginServiceRabbitVNC
      - 插件名：必须与工程名（翻译资源文件名[.ts]）相同。 例如： \ref CPluginServiceRabbitVNC::Name() 
  - 实现服务接口 CService 。支持Qt事件或非Qt事件循环。例如： CServiceRabbitVNC


\defgroup LIBAPI_CLIENT 客户端库
\ingroup LIBAPI
\brief 客户端库
\details 
+ 客户端插件接口类关系：
  \image html docs/Image/PluginClientAPI.svg
+ 序列图：
  \image html docs/Image/PluginClientSequenceDiagram.svg


\defgroup CLIENT_API 客户端应用程序接口
\ingroup LIBAPI_CLIENT
\brief 客户端应用程序接口
\details 
+ 类关系：
  \image html docs/Image/PluginClientAPI.svg
+ 序列图：
  \image html docs/Image/ClientSequenceDiagram.svg
+ 使用：
  - 实例化类： CClient m_Client;
    + 处理 CClient::Handle::onProcess 得到注册的连接插件
  - 使用下面一种方式建立连接者对象：
    + CClient::CreateConnecter
    + CClient::LoadConnecter
  - 关联信号：
    + 连接成功信号： CConnecter::sigConnected
    + 断开连接信号： CConnecter::sigDisconnect
    + 断连成功信号： CConnecter::sigDisconnected
  - 打开连接： CConnecter::Connect()
  - 接收到 CConnecter::sigConnected 信号后，做连接相关初始化工作
  - 接收到 CConnecter::sigDisconnect() 信号后，
    调用 CConnecter::DisConnect() 关闭连接。
  - 关闭连接： CConnecter::DisConnect()
  - 接收到 CConnecter::sigDisconnected 信号后，做连接相关的清理工作，
   完成后并删除此连接者对象 (必须使用 CConnecter::deleteLater )
 

\defgroup CLIENT_PLUGIN_API 客户端插件接口
\ingroup LIBAPI_CLIENT
\brief 客户端插件接口.
\details

+ 线程模型：
  - 阻塞：大多数控制协议实现库连接都是阻塞的。所以需要一个线程处理一个连接。
    \see CPluginClient CConnecterThread
  - 非阻塞：例如Qt事件。一个线程可以处理多个连接。
    - 插件没有后台线程，所有连接使用主线程
    - 插件有一个后台线程，所有连接使用同一个后台线程
    \see CPluginClientThread CConnecterDesktop
+ 类关系：
  \image html docs/Image/PluginClientAPI.svg
+ 序列图：
  \image html docs/Image/PluginClientSequenceDiagram.svg
+ 写一个插件：
  - 生成插件目标名称格式为： PluginClient${PROJECT_NAME}
    \include Plugins/FreeRDP/Client/CMakeLists.txt
  - 实现插件接口 CPluginClient
    + 如果没有后台线程，或者是阻塞线程模型（一个后台线程处理一个连接。连接是阻塞的）。例如：FreeRDP
      - 从 CPluginClient 派生插件。例如： \ref CPluginFreeRDP
        + 在类声明中实现Qt接口:
          \snippet Plugins/FreeRDP/Client/PluginFreeRDP.h Qt plugin interface
        + 在构造函数中初始化操作。例如：初始化资源等
        + 在析构函数中释放资源。
        + 实现属性、函数
          - 插件名：必须与工程名（翻译资源文件名[.ts]）相同。 例如： \ref CPluginFreeRDP::Name() 
            \include Plugins/FreeRDP/Client/PluginFreeRDP.cpp
    + 如果非阻塞线程模型。一个后台线程处理多个连接。连接是非阻塞的。(暂时未用)
      - 从  CPluginClientThread 派生插件。
        + 在类声明中实现Qt接口:
          \snippet Plugins/RabbitVNC/Client/PluginRabbitVNC.h Qt plugin interface
        + 在构造函数中初始化操作。例如：初始化资源等
          \snippet Plugins/RabbitVNC/Client/PluginRabbitVNC.cpp Initialize resource
        + 在析构函数中释放资源。
        + 实现属性、函数
          - 插件名：必须与工程名（翻译资源文件名[.ts]）相同。
            \include Plugins/RabbitVNC/Client/PluginRabbitVNC.cpp
  - 实现连接者接口 \ref CConnecter 。
    + 实现远程桌面
      - 如果是阻塞线程模型。实现一个后台线程处理一个远程连接，连接是阻塞的。
        可以从 \ref CConnecterThread 派生。例如：\ref CConnecterFreeRDP
        \image html docs/Image/PluginClientBlockSequenceDiagram.svg
      - 如果没有后台线程，或者是非阻塞线程模型(实现一个后台线程处理多个远程连接，连接是非阻塞的)。
        可以从 \ref CConnecterDesktop 派生。
        \image html docs/Image/PluginClientNoBlockSequenDiagram.svg
    + 实现远程控制台，可以从 \ref CConnecterTerminal 派生
    + 如果上面两个不能满足你的需要，你可以直接从 \ref CConnecter 派生
  - 实现具体的连接，从 \ref CConnect 派生 。例如：\ref CConnectFreeRDP

\defgroup LIBAPI_THREAD 线程模型
\ingroup LIBAPI_CLIENT
\brief 线程模型
\details
+ 线程分类
  - 主线程（UI线程）。以下类在主线程中：
    - CConnecter
    - CFrmView
    - CParameter
  - 工作线程。以下类在工作线程中：
    - CConnect

+ 工作线程模型
  - 阻塞：大多数控制协议实现库连接都是阻塞的。所以需要一个线程处理一个连接。
         每个连接者启动一个后台线程。
    \see CPluginClient CConnecterThread
  - 非阻塞：例如Qt事件。一个线程可以处理多个连接。
    插件启动一个线程，连接者重用此线程，它不再启动线程。
    \see CPluginClientThread CConnecterDesktop

+ 类关系：
  \image html docs/Image/PluginClientAPI.svg

\defgroup LIBAPI_CHANNEL 通道
\ingroup LIBAPI
\brief 流式数据通道
\details
+ 类关系图
  \image html docs/Image/Channel.svg

\defgroup LIBAPI_ICE ICE
\ingroup LIBAPI_CHANNEL
\details
+ 类关系图
  \image html docs/Image/Channel.svg

*/
