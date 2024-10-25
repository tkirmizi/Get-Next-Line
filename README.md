# Get-Next-Line

<img width="474" alt="Screenshot 2024-10-25 at 15 36 22" src="https://github.com/user-attachments/assets/7cf3b727-0d40-4f61-ac42-48f776124065">


The "Get Next Line" (GNL) function is a utility used in C programming for reading text input from a file or a file descriptor, such as standard input or a file. It reads the input line by line, where each line is terminated by a newline character ('\n'). The function returns a pointer to a dynamically allocated string containing the contents of the next line read from the input stream.

The challenging aspect of this function is that the size read by the `read` function is provided as input and is unknown. The `read` function, as a feature, remembers where it left off when called again and continues reading from there. However, since the input size is unknown, the information read by `read` may include data from one line below the end, which needs to be trimmed. When `read` is called again, the trimmed portion should be added to the new buffer for new line which will be first chars of next line. I used dynamic variables to achieve it.
