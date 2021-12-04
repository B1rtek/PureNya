# PureNya~
Esoteric language based on Nya~

PureNya~ only accepts expressions containing full "nya\~"s, which means that every expression must contain at least one 'n', at least one 'y', at least one 'a', and any positive number of '\~' at the end, and these characters must occur in the same order as they do in the word "nya\~".

The nya compiler (nyac) first translates the nya file to C++, and then uses g++ (it's required btw) to compile the cpp file into an executable. Afterwards, the cpp file is deleted, and if it isn't, you'll see some garbage code in a .nyac file, enjoy.

The original interpreter can be found [here](https://github.com/sech1p/nya)
