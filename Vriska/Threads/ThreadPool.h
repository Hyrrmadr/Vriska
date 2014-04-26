
#ifndef VRISKA_LIB_THREADS_THREADPOOL_H_
# define VRISKA_LIB_THREADS_THREADPOOL_H_

# include <Vriska/Threads/Thread.h>
# include <Vriska/Threads/Mutex.h>
# include <Vriska/Threads/CondVar.h>
# include <Vriska/Threads/SafeList.hpp>
# include <Vriska/Threads/ScopedLock.h>
# include <vector>

#ifdef VRISKA_WINDOWS
# pragma warning( push )
# pragma warning( disable : 4251 )
# pragma warning( disable : 4275 )
#endif

namespace Vriska
{
  class VRISKA_EXPORT ThreadPool : public IRunnable
  {
  private:
    typedef std::vector<Thread *>::iterator Iter;

  public:
    ThreadPool(unsigned int);
    virtual ~ThreadPool();

    virtual bool	execute(IRunnable *run);
    virtual void	run();

  private:
    bool			_end;
    unsigned int		_number;
    CondVar			_cv;
    Mutex			_mutex;
    SafeList<IRunnable*>	_list;
    std::vector<Thread*>	_pool;
  };
}

#ifdef VRISKA_WINDOWS
# pragma warning( pop )
#endif

#endif // !VRISKA_LIB_THREADS_THREADPOOL_H_
