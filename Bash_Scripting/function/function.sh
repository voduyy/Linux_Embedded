#!/bin/bash
print_function() 
{
    echo "Hello function"
}
print_function 


print_function2()
{
    echo "Hello function $1 $2" #selec single argument
    echo "Hello function $@" #select argument
    return 5
}

print_function2 Vo Duy
echo "Return value $?"

#override command
ls(){
    command ls -lh
} 
ls