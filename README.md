# anlcross

## Overview

## Usage 

To begin analysis of DSD, users have to prepare 2 types of ROOT files.

- Data file with `eventtree`
- Database file with `dbtree`
 
## Requirement

- gcc 4.2.1
- GNU Make 3.81
- GNU Readline 7.0.5
- CERN ROOT 6.14.02

All of them can be installed through homebrew.

And, 

- [com_cli](https://github.com/goroyabu/com_cli) 1.0

Option : To produce documentations, 

- graphvis
- doxygen

## Installation

First, 

```
$ git clone https://github.com/goroyabu/anlcross
$ cd anlcross/
$ make 
$ make install
```

Now, write 

```bash
source /path/to/anlcross/this.sh
``` 
on `~/.bash_profile`.

If you want to uninstall, 

```
$ make uninstall
```


 
## Tutorial

After installation, `cd example/dsdana`

```
$ make
$ make install
$ source this.sh
$ cd work/
$ sh run_ana.sh example.root
```
--

For the beginning of your analysis, copy `run.sh` in `example/dsdana` and modify from `database.root` to the name of your database. 
Now, you can run the analysis with typing,

```
$ sh run.sh my_exp_data.root
``` 

in your working directory.

## Data Format

### dbtree

### hittree

### eventtree

## Tools

```
$ cd tools/
$ make
$ make install
$ source this.sh
```

For analysis of DSD, 

- mkdatabase

For developments of more detailed analysis,

- mkanlmodule
- mkanlinit

--

### mkdatabase

### mkanlmodule

```
$ mkanlmodule --read_tree 
```



### mkanlinit


## Documentation
To make a documentation, 

```
$ cd documentation/
$ make
$ open toppage.html
```

Please read [documentation/README](documentation/README.md)

## Licence


## Authors
Goro Yabu 

## References
