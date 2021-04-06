# rayCppaster
A Raycaster renderer in C++.

## Raymark
This branch is a benchmarking program - should only take about two minutes tops (unless your machine is really slow). Just download the `Raymark.zip`, extract, and run `run.bat` and you will get results!

It's based off the multithreaded renderer from the master branch which has it's quirks to say the least (notably higher frametimes and surprisingly dismal performance) but nevertheless is steady enough to use as a benchmark. This will test across a few numbers of threads, higher physically threaded systems are likely to see better performance out of the higher thread run modes (don't be alarmed if 64T runs slower than 16T for example, this is quite typical at least on my system).

**An installation of Python is required to run Raymark.**
