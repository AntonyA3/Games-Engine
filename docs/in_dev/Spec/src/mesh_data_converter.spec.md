
# MeshDataConverter

## Summary 
A class to create a opengl shader program and also get the details related tothe status of loading the shader

| Property | Description |
| --- | --- |
| vertex_array | It stores the vertex data for a rectangle |
| index_array | It stores the index data for the rectangle |

## Dependancies
| Dependancy | Explaination |
| --- | --- |
| Rect | The rectangle that is used to generate the mesh |

## Functions
| Function | Description |
| --- | --- |
| generate(stride) | Generates the vertex data of the rect and index data of the rect and adds the stride to all indicies |
| generate() | generates with an index stride of  0|
| clear | Clears the vertex data of the batch and resers the index offset of the buffer|



## Test Cases
- It should produce the correct vertex_array values and index array values given the rect that it was using