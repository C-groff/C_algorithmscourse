***** Text editor using text-based commands ******

This is my first big project and its a simple model of a text editor.
Its supposed to run on terminal, I used gcc to compile and ran with "gcc -o editor.exe editor.c", but Ill put an .exe file if that helps.
To use it, you need to type a command from the table bellow:

*****************************************************************************************************************************************************************
***************************TABLE OF COMMANDS AVAILABLE***********************************************************************************************************
I<string N> 		; Insert the followed string at the actual cursor position.
A<string N> 		; Loads the text content of the file named N.
E<string N> 		; Overwerite the text content from the text editor to the file named N.
command F   		; Move the cursor one char to the right.
command T   		; Move the cursor one char to the left.
command O   		; Move the cursor to position 0 of the current line.
command P   		; Move the cursor to the beggining of the next word (on the current line).
command Q   		; Move the cursor to the beggining of the current word.
command $   		; Move the cursor to the end of the current line.
:<int x>    		; Move the cursor to the beggining of the line x.
command :F  		; Move the cursor to the beggining of the last line.
command D   		; Erases char at current position. 
command M   		; Add a mark at the current position. 
command C   		; Copy everything from the current position to the marked position.
command X   		; Same as command C, but it erases everything it copies.
command Z   		; Shows the "copied text stack" memory that can be pasted.
command V   		; Paste the top of the memory stack.
B<string s> 		; Jump to the next occurrence of the string s.
S<string s/string r>    ; Overwrites every occurence of s by r, begins at the current possition. Character '/' is required.
command N   		; Split line, same as 'enter' on the keyboard.
command U   		; Concatenates current line and next.
command !   		; Ends the program.
command J   		; Goes to the next line ( at the same collum, if possible).
command H   		; Goes to previus line  ( at the same collum, if possible).
****************************************************************************************************************************************************************
****************************************************************************************************************************************************************

IMPORTANT NOTES:
Every other command except Insert, move cursor and Erase may crash the program when used on line 0, and I dont really know why this happens.
Command X and C, equivalent to control x and contrl c, may crash the program if M is located at the position 0 of any line.
