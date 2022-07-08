
This program copies text to a clipboard.

The text can come from `stdin` or a list of files.

Currently, there is no windows or linux support.

# Compiling / Building
## MacOS 
Run `make macos`.

## Windows
Run `make win`.

## Linux 
Run `make linux`.

# Usage
either pipe data to the process and provide no arguments:

`echo -n "add me to the clipboard!" | ./cbcp`

or, provide filename(s) as arguments, and they will be concatenated then copied:

`./cbcp file1.txt file2.txt ...`

