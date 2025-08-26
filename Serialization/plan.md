- Serializable Interface 
    - Has Serialize function. 
- Deserializable Interface 
    - Has Deserialize function 


- Each Routines members conform to both

- `returntype` `name` `arguments` 
- `returntype` : Enumeration, only fixed amount of types, tells us whether or not we have to send back a response through the channel.
- `name` : Makes calling the actual routine more explicit. 
- `arguments`: agregate -> prefix number of arguments. With these threee we can specify whichfunction exactly we wish to call and then we can memcpy the arguments in. 

- Serialize(): Allocate enough memory for the entire struct ( fixed size ) and simply write the values from there. Returns how many bytes have been serialized.

- Pointer to blob in memory where there is an underlying array


- Aggregate Types: Arrays, Strings, nested objects
- Numeric Types: Floats, Integers, Bool. 
