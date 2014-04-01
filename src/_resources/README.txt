Do not change resource files: it is useless.
They are compiled into .cpp files.

The bin2c utility should be used to recompile files into .cpp files.

For example, if you changed the bg.jpg file then you should run
`bin2c bg.jpg` and it will generate the bg.jpg.cpp file.
