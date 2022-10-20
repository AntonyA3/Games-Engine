
# Object Name

## Summary 
A class to create a opengl shader program and also get the details related tothe status of loading the shader

| Property | Description |
| --- | --- |
| mesh_data_converter | It stores the mesh data output generated from a rectangle that was generated with this |
| mesh_generator | It stores the mesh generator to use to generate the Mesh from rectangle |

## Dependancies
| Dependancy | Explaination |
| --- | --- |
| Rect | The rectangle to be used to generate the mesh |

## Functions
| Function | Description |
| --- | --- |
| generate | Given a rect, get the data from the mesh then usde this data to generate the mesh|


## Test Cases
- Given a valid rectangle a anticlockwise ordered mesh should be generated to represent the rectangle