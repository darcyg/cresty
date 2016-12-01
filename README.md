cresty
======

Very simple RESTful server implemented in C.  Mainly for the purposes of getting
reacquainted with doing server development (primarily network based) in C after
a few years.

building
--------
Currently, there are no real dependencies (other than the basic build tools).

```shell
$ ./autogen.sh # to get autotools ready to go
$ ./configure
$ make
```

The executable will be at `src/cresty`.  It's not super useful yet.

License
-------
cresty is released under the [MIT License](http://www.opensource.org/licenses/MIT).
