# Intel Smart Caching Tests for Skylake Processors

## What is the Project About?
Project for CSE 221 Spring 2018. Excerpt from project paper Introduction:
>Intel boasts caching system called smart cache within Intel Skylake processors. Smart cache is a way, as Intel claims, to share cache memory between other cores. Thus a single core can have access to the entire level 2 and level 3 cache if needed. In theory, this leads to lower cache misses and thus higher speeds per processor. However, due to the physical architecture of Intel Skylake processor, the theory may not do as well as the implementation. Skylake consists of a ring architecture for sharing memory. As a result, a core that is using memory from one end of the ring may have high latency if the core uses cache on the other end of the ring.
Furthermore, on top of a heavy operating system like Windows, this system may not be taken advantage fully as Windows may take up space within L2 cache and utilize multiple threads that may cause disproportionate sharing of the caches within the ring.

## Usage
> make main

## Resources
* [Prof. Voelker Time Measuring](http://cseweb.ucsd.edu/classes/wi17/cse221-a/timing.html)

## Required Libraries
* None