Names: Namit Sambare and William Loh
Namit Sambare: Completed the functionality for LScommand, removeCommand, MacroCommands, and renameCommand
Wiliam Loh: Completed the functionality for CopyCommand, DisplayCommand, CatCommand, and modified TouchCommand to support password protected files
All 77 tests pass

Testing and Debugging:

Error 1: The removeCommand initially couldn't support the Abstract Command constructor when adding it to the command prompt in the main. 

Solution: The reason for this was that we forgot to have the removeCommand class inherit the Abstract Command interface. Once we did this,the removeCommand was able to be declared in the main. 

Error 2: The rename test was initially failing after implementing it. 

Solution: The reason for this was that the parse method was executing incorrectly. What happened was that the vector of strings was getting an incorrect first index. 
The first index is supposed to be the first word of the command input and my substring was cutting it short. 

Error 3: The MacroCommand.cpp was throwing an error when I tried declaring the destructor.

Solution: The reason for this was that I was not setting the destructor equal to default. When I set the destructor to default, the error was resolved. 


TESTING Command Prompts Thoroughly: 

Trial 1: In the main, you can see that we added a file called file.txt to the file system. The first command I tested was the LS command. 
This worked perfectly as the ls command output that the files existing in the file system was only the file.txt as it should have been . 

Trial 2: I also tested the ls -m which should have listed the metadata of the file and this is exactly what happened. When I executed the ls -m command, the output was printed correctly. 
The output we saw was the file and the type of file it was as well as the metadata numrical value for that file all in a row. 

Trial 3: The next test I ran was using the remove command, which should delete a file. I called rm on the file.txt using the shell and then after I called this, I made sure to 
call the ls command. And sure enough, the file.txt file was not listed as a file because this means the remove command worked successfully. 

Trial 4: I tested the CatCommand with the -a option  and the contents of the file were displayed I kept going down the list and then I tested the CatCommand. When calling the catcommand, the computer meowed wildly. Just kidding. 
When I called the CatCommand, the user was prompted to input data to append to the file. Then after inputting mock data, I tried testing both ":wq" and ":q" and both commands worked. 
":wq" was used to save and quit and ":q" was used to quit without saving. When I used ":wq" the data up until that point was returned, and when I used ":q" the data 
was not returned. 

Trial 5: I also tested the CatCommand without the -a option and the current contents of the file were not displayed to the user before prompting for input. 
Also, when I supplied ":wq" without the -a option the contents of the file were overwritten with the contents that I supplied instead of being added to the contents to the end of the file. 

Trial 6: Going down the list, I next ran the DisplayCommand command. When I ran this command on the file.txt, the file was opened and the contents of the file were diplayed. 
The contents of the file were formatted in a n by n board fashion.

Trial 7: Next, what I did was use the display command but with the -d option. Using the -d option, the display of the file was the same but it wss unformatted, so it was not in a n by n fashion.

Trial 8: The next command I tested was the CopyCommand. And what happned for this one was what was expected to happen even more. The copy command copied the contents of the file.txt file and then renamed it to a new name
with the same contents. Also, I tested if the prototype pattern worked and it did.

Trial 9: I also tested to see if the copied file was password protected and it was. So, the file was ensured to be copied via the prototype pattern, and the proxy for the file needs to be copied also.

Trial 10: Finally, I wanted to test the rename macro command and ensure that my rename command named the file given in the first string with the name desired by the user in the second string. 

Trial 11: Next, I also decided to test really bad input. So, I tested command that did not exist and was prompted again as was expected. 

Trial 12: Also, I tried to run commands when the file didn't exist and wanted to see if the fileDoesNotExist error was returned and that is what ended up happening, as it should have. 

After doing all this testing, by deductive reasoning it can be assumed that all the functionality for the commands asked to be implemented were implemented successfully. We know this not 
just because the unit tests pass but because the tests actually function 100% correctly in the shell that I actually tested as well. 
