# PureNya~
Esoteric language based on Nya~

PureNya~ only accepts expressions containing full "nya\~"s, which means that every expression must contain at least one 'n', at least one 'y', at least one 'a', and any positive number of '\~' at the end, and these characters must occur in the same order as they do in the word "nya\~".

The nya compiler (nyac) first translates the nya file to C++, and then uses g++ (it's required btw) to compile the cpp file into an executable. Afterwards, the cpp file is deleted, and if it isn't, you'll see some garbage C++ code in a .nyac file, enjoy.

The nya converter (nyaconv) takes the input file and saves it in the nya language. It can be used to create .nya files with some actual code in them, but nyancrypted.

The original interpreter can be found [here](https://github.com/sech1p/nya)


## Building
```shell
$ git clone https://github.com/B1rtek/PureNya.git
$ mkdir build
$ cmake ..
$ make
```

## Usage

### nyac

```shell
$ nyac input.nya -o coolname -impure
```

Options:
* `-o <something>` (optional)
  Sets the output file name
* `-impure` (optional)
  Allows for weird "nya~"s like "na~", but still forces the correct characters order

### nyaconv

```shell
$ nyaconv input.nya -o coolname
```

Options:
* `-o <something>` (optional)
  Sets the output file name
