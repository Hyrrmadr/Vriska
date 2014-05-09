
#ifndef VRISKA_LIB_NETWORK_SERVER_H_
# define VRISKA_LIB_NETWORK_SERVER_H_

# include <Vriska/Network/SocketServer.h>
# include <Vriska/Network/SimpleClient.h>
# include <Vriska/Core/Data.hpp>

# include <iostream>
# include <list>
# include <algorithm>

namespace Vriska
{
  // Forward declaration of IServerCallable
  class IServerCallable;
  // Forward declaration of IServerCCallable
  class IServerCCallable;
  
  class VRISKA_EXPORT Server: public SocketServer, public Datable
  {
  public:
    class VRISKA_EXPORT Client : public SimpleClient
    {
    public:
      Client(INativeSocket& sysSocket, Server& server, unsigned int n);
      ~Client();

    private:
      Client(Client const & other);
      Client const & operator=(Client const & other);
      
    public:
      unsigned int	getIndex() const;
      void			destroy();
      
      Error::Code		sync(bool send);

    public:
      int			writeOnBuffer(char const *buffer, size_t size);
      INativeSocket const &	getNativeSocket() const;
      
    private:
      Server&			_server;
      unsigned int	_n;
    };
    
  public:
    typedef bool	(*FunctionC)(Server&, Client&);
    typedef bool	(*Function)(Server&);
    
    typedef std::list<Client *>::iterator	Iter;
    typedef std::list<Client *>::const_iterator	CIter;
    
  public:
    Server(Socket::Protocol protocol = Socket::TCP);
    virtual ~Server();
    
  private:
    Server(Server const & other);
    Server const & operator=(Server const & other);
    
  public:
    Error::Code		connect(unsigned int port = Socket::FreePort, std::string const & host = "", bool force = false);
    Error::Code		connect(unsigned int const *ports, std::string const & host = "", bool force = false);
    Error::Code		connect(std::list<unsigned int> const & ports, std::string const & host = "", bool force = false);
    Error::Code		connect(unsigned int port1, unsigned int port2, std::string const & host = "", bool force = false);
    Error::Code		reconnect();
    Error::Code		disconnect();
    Error::Code		launch();
   
    void			setLimit(unsigned int limit);
    
    size_t    broadcast(void const * buffer, size_t size);

    template <class Func>
    size_t          broadcast(void const * buffer, size_t size, Func func)
    {
      size_t        i = 0;

      sysLog("Broadcast: " + StringUtils::escape(std::string(static_cast<char const *>(buffer), size)));
      for (Iter it = _clients.begin(); it != _clients.end(); ++it)
        if ((*func)(*this, *(*it)))
          if ((*it)->write(buffer, size) == static_cast<int>(size))
            ++i;
      return (i);
    }
    
    template <class Func>
    void			forAll(Func func)
    {
      for (Iter it = _clients.begin(); it != _clients.end(); ++it)
        (*func)(*this, *(*it));
    }

  public:
      void  enableLogging(bool logging);
      void  enableSysLogging(bool sysLogging);
      void  setLoggingStream(std::ostream& os);
      void  setLoggingTag(std::string const & tag);

  public:
    
    void			registerOnReceive(FunctionC func);
    void			registerOnReceive(IServerCCallable *call);
    void			unregisterOnReceive();
    void			registerOnSend(FunctionC func);
    void			registerOnSend(IServerCCallable *call);
    void			unregisterOnSend();
    void			registerOnConnect(FunctionC func);
    void			registerOnConnect(IServerCCallable *call);
    void			unregisterOnConnect();
    void			registerOnDisconnect(FunctionC func);
    void			registerOnDisconnect(IServerCCallable *call);
    void			unregisterOnDisconnect();
    void			registerOnStdin(Function func);
    void			registerOnStdin(IServerCallable *call);
    void			unregisterOnStdin();

    void			setTimeout(Time const & t, Function func, bool exact = true);
    void			setTimeout(Time const & t, IServerCallable *call, bool exact = true);
    void			unsetTimeout();
    Time const &	getElapsedTime() const;
    
    void			disconnectMe(Client* client);
    
  public:
    unsigned int	getPort() const;
    
  private:
    bool			hasTimeout() const;
    Time			getTimeout() const;
    bool			watchStdin() const;

    void			addTimeout(Time const & elapsed);
    bool			callbackTimeout();
    
    bool			callbackConnect(Client& client);
    bool			callbackDisconnect(Client& client);
    bool			callbackReceive(Client& client);
    bool			callbackSend(Client& client);
    bool			callbackStdin();
    
    Client			*addNewClient(INativeSocket *sock);
    Client			*getFromSocket(INativeSocket const *sock);
    Error::Code			manageIO();
    void			clearClients();
    void			manageClients(SocketSet& set, bool send);    
  
    static bool			yesMan(Server& server, Client& client);
    
  private:
    std::list<Client *>	_clients;
    unsigned int		_n;
    unsigned int		_limit;
    
    bool			_tried;
    std::string		_host;
    unsigned int	_port;
    
    Time			_timeTarget;
    Time			_timeElapsed;
    bool			_timeExact;
    
    IServerCCallable	*_callConn;
    FunctionC			_funcConn;
    IServerCCallable	*_callDisc;
    FunctionC			_funcDisc;
    IServerCCallable	*_callReceive;
    FunctionC			_funcReceive;
    IServerCCallable	*_callSend;
    FunctionC			_funcSend;
    IServerCallable		*_callStdin;
    Function			_funcStdin;
    IServerCallable		*_callTime;
    Function			_funcTime;
  };
}

#endif // !VRISKA_LIB_NETWORK_SERVER_H_
