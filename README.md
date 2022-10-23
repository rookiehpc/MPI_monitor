# MPI_monitor: See what your MPI processes do, live #

* [What does it do?](#what-does-it-do)
* [Setup](#setup)
* [Termination](#termination)
* [How does the library work behind the scene?](#how-does-the-library-work-behind-the-scene)
* [Limitations](#limitations)

## What does it do? ##
This mini-library gives you a table reporting the current state of each MPI process live. It is part of the [RookieHPC](https://github.com/rookiehpc/rookiehpc.github.io) project to contribute in making High-Performance Computing easier to learn.

The table below is an example of what you would see in your console:

| Who |         What |              Where |                When |
|----:|-------------:|-------------------:|--------------------:|
|   0 |     MPI_Recv |  myDir/myFile.c:14 | completed 2.01s ago |
|   1 |    MPI_Bcast |  myDir/myFile.c:49 |   started 4.05s ago |
|   2 |    MPI_Bcast |  myDir/myFile.c:49 |   started 3.23s ago |
|   3 |    MPI_Bcast |  myDir/myFile.c:49 |   started 3.79s ago |

In case you prefer to double-check, this is how to read it:
- MPI process 0 has called `MPI_Recv` at line 14 in the file `myDir/myFile.c`, and that call completed about 2.01 seconds ago. Since then, maybe the MPI process 0 has been processing data or doing I/O but it has not issued another MPI call yet.
- MPI processes 1, 2 and 3 have called `MPI_Bcast` from the file `myDir/myFile.c` at line 49. They called it about 3-4 seconds ago and are still waiting for that call to complete.

That's it! If your code has a deadlock, you will now easily see who is responsible, what is the MPI routine involved and where that faulty call comes from.

## Setup ##
This library has been designed to be very quick and convenient to use:
1) Replace all your `#include <mpi.h>` with `#include "mpi_monitor.h"`
1) Add the `mpi_monitor.c` file to your compilation command
1) Run your application as usual

## Termination ##
* If your application has all its MPI processes call `MPI_Finalize`, the monitor will detect successful termination and your application will end its execution like your program would have without the library.
* If your application is having a deadlock, the monitor will see that your application continues to run so it will continue to give you live updates until your interrupt it, typically with `CTRL+C`.

## How does the library work behind the scene? ##

Behind the scene, when the MPI processes issue the `MPI_Init`, two things happen:
1) **MPI process 0** creates a one-sided window, and exposes a buffer that will be used for monitoring
2) **MPI process 0** spawns a thread that will regularly check that buffer and print it out to the console

From that point on, every time an **MPI process X** issues a call to the **MPI routine Y**, it is caught by the `MPI_monitor` library and two messages are sent from **MPI process X** to **MPI process 0** using one-sided communications:
1) One before issuing the MPI routine demanded, so that the monitor buffer on **MPI process 0** is updated and knows that **MPI process X** has started to call **MPI routine Y**.
2) One after the call to **MPI routine Y** has returned so the monitor buffer on **MPI process 0** is updated and knows that **MPI process X** completed its call to **MPI routine Y**.

This design is able to handle deadlocks from any MPI process, even **MPI process 0**, since the monitoring is done via one-sided communications and the actual printing is performed by a child thread on **MPI process 0**.

## Limitations ##
- It is not meant to scale to hundreds of MPI processes or beyond, it is aimed at educational purposes.
- It MPI terms, one could say this library does not provide a thread support beyond `MPI_THREAD_FUNNELED`. In other words, you can have an application that is multithreaded on top of using MPI, for instance with OpenMP, however all MPI calls must be issued by the master thread otherwise they will not be caught by the library nor reported in the live display.
- Not all MPI routines are supported yet. However, this is a temporary limitation as missing MPI routines are being added continuously. The motivation here was: rather than waiting for all routines to be done, let make this tool available as soon as possible. Supporting basic routines will be sufficient for most cases most users will ever encounter. For more advanced users, tell us which missing MPI routines you need, so we can prioritise them.
