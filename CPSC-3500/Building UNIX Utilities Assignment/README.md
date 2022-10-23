wcat
- prints exactly the content of the file
- when passed ono cl args, user is prompted
- in all non-error cases it returns with status 0 and 1 in error cases
- works with multiple files
- works in all cases even with diff command


wgrep
- works in all cases
- returns 1 in cases where exit is needed
- works when only search term is passed in and user input is needed
- works when search term and one file or multiple files are inputted
- matches all lines when empty string is inputted as search term
- works with multiple words as search term
- search term is case-sensitive
- returns 0 if correctly used


wzip
- uses write() to output 4 byte integer and 1 byte char to another file
- counts all consecutive and single characters and does RLE encoding correctly
- works with multiple files being zipped at once
- user needs to add "> file.z" to the end of the command line
- exits with status 1 if anything goes wrong like cannot open file
- user is prompted if no files are specified


wunzip
- uses read() and write() to output a 1 byte character based on the preceding 4 byte integer read from the .z file
- works with multiple zipped files, will output to screen continuously
- returns 0 if correctly executed, returns 1 in all error cases
- user prompted if no files specified

