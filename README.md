# anlcross

## Overview

## Usage 

To begin analysis of DSD, users have to prepare 2 types of ROOT files.

- Data file with `eventtree`
- Database file with `dbtree`
 
## Tutorial

After installation, `cd example/dsdana`

Then, `make`

Then, `make install`

Then, `source this.sh`

Then, `cd work/`

Finally, 

```
$ . run.sh example.root
```

--

For the beginning of your analysis, copy `run.sh` in `example/dsdana` and modify from `database.root` to the name of your database. 
Now, you can run the analysis with typing,

```
$ . run.sh my_exp_data.root
``` 

in your working directory.

## Data Format

### dbtree

### hittree

### eventtree

## Tools

For analysis of DSD, 

- mkdatabase

For developments of more detailed analysis,

- mkanlmodule
- mkanlinit

--

### mkdatabase

### mkanlmodule

### mkanlinit

## Requirement

- gcc 4.2.1
- GNU Make 3.81
- GNU Readline 7.0.5
- CERN ROOT 6.14.02
- [com_cli](https://github.com/goroyabu/com_cli) 1.0

Option : To produce documentations, 

- graphvis
- doxygen

All of them can be installed through homebrew.

## Installation

First, 

```
$ git clone https://github.com/goroyabu/anlcross
```

Then, 

```
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


## Documentation

First, `cd documentation/`

Then, `make`

And, `open toppage.html`

Please read [documentation/README](documentation/README.md)

## Licence


## Authors
Goro Yabu 

## References
