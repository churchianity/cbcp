
This program copies text to a clipboard.

The text can come from `stdin` or a list of files.

# Usage
either pipe data to the process and provide no arguments:
`echo -n "add me to the clipboard!" | ./clipcp`

or, provide filename(s) as arguments, and they will be concatenated then copied:
`./clipcp file1.txt file2.txt ...`

