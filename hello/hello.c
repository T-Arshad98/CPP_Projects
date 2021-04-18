#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Hello, world!\n"); // Print hello world
    string name = get_string("What is your name?\n"); //Ask for name
    printf("Hello, %s.\n", name); //Print hello, persons name

}