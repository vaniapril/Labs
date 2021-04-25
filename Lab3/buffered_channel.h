#include <condition_variable>
#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <queue>

template <typename T>
class Channel{
    int _buffer_size;
    bool _closed = false;

    std::mutex queueMutex;
    std::condition_variable sendCheck;
    std::condition_variable recvCheck;

public:

    std::queue<T> _queue;
    Channel(int buffer_size){
        _buffer_size = buffer_size;
    }

    void Send(T value){
        if (_closed) throw std::runtime_error("error");
        std::unique_lock<std::mutex> locker(queueMutex);
        sendCheck.wait(locker, [&](){return _queue.size() != _buffer_size;});

        _queue.push(value);
        recvCheck.notify_all();
    }

    std::pair<T, bool> Recv(){
        std::unique_lock<std::mutex> locker(queueMutex);
        recvCheck.wait(locker, [&](){return (!_queue.empty()) || _closed;});
        if(!_queue.empty()){
            T elem = _queue.front();
            _queue.pop();
            sendCheck.notify_all();
            return std::pair<T, bool>(elem, true);
        } else {
            sendCheck.notify_all();
            return std::pair<T, bool>(T(), false);
        }
    }
    void Close(){
        _closed = true;
        recvCheck.notify_all();
    }
};