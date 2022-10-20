
# Polygon Batcher

## Summary 
A class to 
| Property | Description |
| --- | --- |
| m_vertex_array | A floats of the vertex data of the mesh that is currently being built |
| m_index_array | The index data of the mesh that is currently being built |
| m_index_offset | The oindex offset of the mesh that is currenly being built |
| Mesh_Data_Converter | Delegates the operation of generating a mesh to this |

## Dependancies
| Dependancy | Explaination |
| --- | --- |
| Rect | A rectangle can be added to the batched polygon |


## Functions
| Function | Description |
| --- | --- |
| addRect | Adds a rectangle to the vertex data, adds 4 to the index offset to represent 4 new verticies |
| clear | Clears the vertes_array, index_array and resets_index offset to 0, for usage in building another mesh |  

## Test Cases
- add a rectangle expect correct index and vertex data
- add 2 rectangles expect correct index and vertex data