
# File Reader

## Summary 
Reads the text content of a file, when given a filename to be read,


| Property | Description | 
| --- | --- |
| content | Stores the content of the file after read has been **invoked** |
| file_read_status | Stores whether the file was successfully read, or unsuccessfully read after read has been **invoked** |


## Dependencies
| Dependancy | Explaination |
| --- | --- |
| Enum FileReadStatus  | For **this** file read status |
| std::stringstream | To Read a stream of strings from the file, which can then be converted to **this** content |
| std::ifstream | To the file to be read check whether there was a problem opening the file |

## Functions

| Function Name | Explaination |
| --- | --- |
| read | Reads a file based on the given file path |


## Test Cases 
- read non existing file
- read existing file
- read existing file twice
