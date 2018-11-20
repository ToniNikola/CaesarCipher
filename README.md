## CaesarCipher
#### CaesarCipher I made for a Job interview. 

 - Environment: Custom Arch Linux distro + VS Code. 
 - Language: C


##### Goal: 

The program should implement a file encryption/decryption with the Caesar Cipher. 
The main program takes two argument: First, the file name. Second, the cipher offset. 

After the arguments are inputed, the main program should make a child process and start the encryption. 
If the encryption is successful, the child process should return to the main program and start a new 
child process that will process the decritpion. Should the decryption be successful, the child process should return
to the main program, and the main program should check the origin file and the decripted-file.
