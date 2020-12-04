/*
Ejercicio 1
List  information about the FILEs (the current directory by default).  Sort entries alphabeti‐
       cally if none of -cftuvSUX nor --sort is specified.

       Mandatory arguments to long options are mandatory for short options too.

       -a, --all
              do not ignore entries starting with .

        -l     use a long listing format

        -d, --directory
              list directories themselves, not their contents

        -h, --human-readable
              with -l and/or -s, print human readable sizes (e.g., 1K 234M 2G)

		-i, --inode
              print the index number of each file

        -R, --recursive
              list subdirectories recursively

		-1     list one file per line.  Avoid '\n' with -q or -b

		-F, --classify
              append indicator (one of /=>@|) to entries

        --color[=WHEN]
              colorize the output; WHEN can be 'always' (default if  omitted),  'auto',  or  'never';
              more info below

Ejercicio 3
¿Cómo se podrían fijar los permisos rw-r--r-x, de las dos formas?
chmod 645 fichero
chmod u+rw-x,g+r-wx,o+rx-w fichero
*/