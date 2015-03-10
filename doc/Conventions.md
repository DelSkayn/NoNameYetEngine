### Coding style
These are the coding style rules I try to use. Although currently there are probebly a lot of files which don't follow these rules. 

These are also kinda temperary and prone to change and expansion when nessesary

 | Thing                  | Style                    | explanation                                                                                                                                                        |
 |------------------------|--------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------| 
 | Class names            | FirstSecond()            | Just a basic way of writing Class names so they can be distinguishable from other identifiers                                                                      |
 | function name          | first_second()           | This is more distinguishable then firstSecond when you compare to a class which can look really simular, example: Foo foo = FirstSecond(), Foo foo = firstSecond() |
 | member variables       | firstSecond              | This way variables are again easy distinguishable from functions.                                                                                                  | 
 | Temp Variables (word?) | first_second             | Temp variables are hard to confuse with functions because of there definition inside functions                                                                     |
 | Global Variable        | gFirstSecond             | Please refrain from using global variables but incase there necessary pre-append with g for readablity                                                             |
 | Interfaces             | AbstractFirstSecond      | Classes which should not be instancied should be pre-appended whit Abstract to reflect that (Delete instancetion (Word?) operator)                                 |
 |------------------------|--------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------|
 | Pointers and refences  | type * name              | I find this way quicker to see when an type is a pointer. In type* name one can miss the *.                                                                        |
 | templates              | template<>:\n:definition | Again the extra line makes punctuats the template<>.                                                                                                               |
 | acolades               | if(statement):\n:	{    | This way trades some clearity on what belongs to what for a beter clearity on scope. I prefer the second.                                                          | 

That is it for basic style rules. Only thing left is that I prefer to put things on a newline when they go on for to long. 
Example: 
'''
void foo(arg1, arg2, arg3,
		 arg4, arg5, arg6)
		{
		}
'''

Too long is kinda objective and I dont really have a clear rule for this.
    
