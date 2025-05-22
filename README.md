# Philosophers

<p align="center">
  <a href="https://github.com/Albertoocbs/Philosophers">
    <img src="https://github.com/Albertoocbs/Philosophers/blob/main/philo.png" width="110"/>
  </a>
</p>

This project is based in the basics of threading a process. We learn how to create threads and explore the use of mutexes.

---
**Status**

Finished: 2025-06-12. Grade: 100/100.

-------
**Overview**

The "philosophers' dinner" problem is a classic thought experiment and a well-known problem in computer science and distributed systems.

The problem is typically presented in the context of five philosophers who are sitting around a circular table, with a plate of spaghetti in front of each of them, and a single fork between each pair of adjacent philosophers. The goal of each philosopher is to eat the spaghetti, but in order to do so, they must each use two forks.

The problem is to design a protocol that allows each philosopher to pick up the two forks to their sides without causing a deadlock, where every philosopher is waiting for a fork that is currently being held by their neighbor. The protocol must ensure that no philosopher goes hungry, and that no two adjacent philosophers hold the same fork at the same time.

The philosophers' dinner problem is an example of a concurrency problem in computer science and distributed systems, and it has been used as a case study in various fields, including operating systems, distributed algorithms, and concurrent programming. It highlights the importance of designing protocols that can handle concurrent access to shared resources without causing deadlocks or other issues.

-------

Here is a useful guide to understand this project: https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
