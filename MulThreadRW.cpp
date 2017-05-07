
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <iostream>

const int BUF_SIZE = 10;
const int MAX_WRITE_NUM = 300;
static int number = 0;

boost::mutex io_mutex;

class buffer
{
  public:
    typedef boost::mutex::scoped_lock scoped_lock;

    buffer()
        : p(0), c(0), full(0)
    {

    }

    void put(int threadid)
    {
        while (number <= MAX_WRITE_NUM)
        {
            scoped_lock lk_put(mutex);
            if (full == BUF_SIZE)
            {
                {
                    boost::mutex::scoped_lock lk_put_io(io_mutex);
                    std::cout << "W Theadid " << threadid << ":Buffer is full. Waiting..." << std::endl;
                }
                while (full == BUF_SIZE)
                    cond_put.wait(lk_put);
            }
            
            buf[p] = number;

            {
                boost::mutex::scoped_lock lk_put_io(io_mutex);
                std::cout << "W Theadid " << threadid << ":sending: " << buf[p] << std::endl;
            }

            
            p = (p + 1) % BUF_SIZE;
            ++full;
            ++number;

            cond_get.notify_one();
        }
    }

    void get(int threadid)
    {
        while (full > 0 || number <= MAX_WRITE_NUM)
        {
            scoped_lock lk_get(mutex);
            if (full == 0)
            {
                {
                    boost::mutex::scoped_lock lk_get_io(io_mutex);
                    std::cout << "R Theadid " << threadid << ":Buffer is empty. Waiting..." << std::endl;
                }
                while (full == 0)
                    cond_get.wait(lk_get);
            }

            int i = buf[c];
            {
                boost::mutex::scoped_lock lk_get_io(io_mutex);
                std::cout << "R Theadid " << threadid << ":received: " << i << std::endl;
            }

            c = (c + 1) % BUF_SIZE;
            --full;

            cond_put.notify_one();
        }
    }

  private:
    boost::mutex mutex;
    boost::condition cond_put, cond_get;
    unsigned int p, c, full;
    int buf[BUF_SIZE];
};

buffer buf;

void writer(int threadid)
{

    buf.put(threadid);
}

void reader(int threadid)
{
    buf.get(threadid);
}

int main(int argc, char *argv[])
{
    boost::thread thrdR1(boost::bind(&reader, 1));
    boost::thread thrdW1(boost::bind(&writer, 1));
    boost::thread thrdW2(boost::bind(&writer, 2));
    boost::thread thrdR2(boost::bind(&reader, 2));

    thrdR1.join();
    thrdW1.join();
    thrdW2.join();
    thrdR2.join();

    return 0;
}
