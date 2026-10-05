# Multithreaded Order Processing System

A C++ multithreaded order processing system that demonstrates concurrent order processing using a thread-safe task queue.

## Features

- Multiple worker threads for concurrent order processing
- Thread-safe order queue using `std::mutex`
- Efficient worker synchronization using `std::condition_variable`
- Producer-consumer architecture
- Graceful worker shutdown
- Processes pending orders before stopping

## Concepts Used

- `std::thread`
- `std::mutex`
- `std::lock_guard`
- `std::unique_lock`
- `std::condition_variable`
- Producer-Consumer Pattern
- Thread-safe Queue
- Graceful Shutdown

## Architecture

```text
             Producer
                 |
                 v
        Thread-Safe Task Queue
           /             \
          /               \
     Worker 1           Worker 2
        |                   |
        v                   v
   Process Order       Process Order
