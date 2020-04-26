Answer studio 16 questions here
1. Namit Sambare, William Loh

2. In C++, an interface describes the capabilities of a class without actually implementing the class.
The way to do this is to declare a class with virtual methods, but then also we set these methods equal to 0 in the interface. 

3a. This is an example of interface inheritance since we inherit the interface without the implementation of the interface. 
3b. The member variables should definitely be private. By making them private, we restrict the user from being able to modify them directly. 

4. The test cases I ran were as  follows: 
First, I made a vector full of chars and then wrote that vector into my Textfile object. 
I first checked to see if the getName function was working and returned the correct name and it did. 
Next, I checked to see if the getSize function was working and returned the correct size and it did. 
Then, I appended another vector of chars (the same contents as the first vector) and then performed the read function to see if the read function and the append funcrtion was wokring as it was supposed to and it did. 


5. We did this by saving the Textfile object into a pointer to AbstractFile. 