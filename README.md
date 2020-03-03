# Comp371Project

Anthony Funiciello 40054110
Walid Ennaceur 40060735
Édouard Gagné 40061204
Anthony Vespoli 40042677

Comp 371 Project Implementation Plan


Introduction


        For this term project, we will be implementing option 2. Our idea is to create an astronaut that will walk through a procedurally created world. We plan to create a path in a forest where the character can walk while surrounded by trees and other flora. The environment will be generated at random with models and colors. For example: the trees will always have a random amount of leaves on them to make every tree seem unique. The environment will resemble the character walking on a planet and will be able to see space if they look above them.
Procedurally generated models
Terrain
        The terrain will be a model generated using multiple small cube models next to each other. It will be a finite terrain the same size as our world, and the user will not be allowed to walk past the terrain or through it. The cubes making up the terrain will be generated using three variable properties: a texture, a color and an elevation range. The texture will be randomly picked from a set of textures that we include in the project. A random color will be generated afterward and applied to the texture. Finally, an elevation range will determine the maximum and minimum elevation that the terrain can take in respect to an invisible plane. This will make it so that our terrain can be rocky or smooth. All the cubes in our world will all have the same properties and dimensions, so there will only be one terrain type.
        The elevation of the cube in respect to an invisible plane will be randomized for each cube. However, the cube will not be generated with an elevation less than or higher than the height of a cube in respect to the adjacent cubes. This will make it so there are no holes in our terrain and that we don’t have floating terrain.
Trees
        The trees in our world will be generated using small cubes as well. They will have a few properties that will be randomly generated upon world creation: trunk color and textures, leaves color and texture, tree height range, branches height range, branches number range and leaves per branches range. The trunk and leaves textures will be randomly selected from a set of textures and the colors will be randomly selected and applied to the textures. The height range represents how tall the tree can be and the branches will represent how long their branches can be. These properties represent a species of trees and we will generate 5 different species of tree in our world.
        For each tree in each species, their height, branch length, number of branches and number of leaves per branches will be randomized within the range. The position of the leaves around the branches and branches around the trunk will be randomized as well. Finally, the trees will be positioned randomly in the world, but not clipping with other models.
Rocks
        Finally, the rocks will be models also made with small cubes that will be found across the world. A rock will have a few randomly generated properties, notably texture and color, height range and width. The texture will again be chosen from a set of predefined textures and a random color will be applied to it. The height range and width range will determine how tall or wide the rocks can be. These properties represent a type of rock and we will generate 3 types of rocks. 
Similarly to the trees. The height, width and position of each rock will be randomized within their range. They will be positioned so that they don’t clip with other models as well.
Static models
        Other models that are not procedurally generated will be present in the world. These models will act as alien artifacts for the user to discover in their exploration. They will be models that we find online and will mostly be pop-culture references (for example, one could find the model of the Millenium Falcon[a] randomly in the world). It will be randomly decided which of these models will appear in the world and at which position.
Other features
Movements
        The user will be able to move freely within the world by walking or by flying around. They will be able to switch between the two modes at any time.
Light source
        A single light source acting as the sun will illuminate the scene from one direction. The models will have shadows relative to this light source.


The sky


The sky will be a randomized pattern of colors to provide an atmosphere that fits the context of the project and will emphasize the supernatural aspect of the world.
Seeding
        To generate the properties of our models, we will use a pseudorandom number generator determined by a seed. The user will be given the option to either generate a world using a new seed to generate a world using a specific seed, so that they can generate the same world any number of times.


For source control, we will be using Github to assign tasks and version control our code. The public repository could be found here:
https://github.com/anthroe/Comp371Project


Timeline



Milestone 1
Milestone 2
Milestone 3
Milestone 4
Milestone 5
Complete terrain


Astronaut model


Rock Models


Tree models
	Alien model


Randomly place trees


Randomly place rocks


Movement
	Sky


Light source


Jumping


Flying/ prevent character to go through ground




	Millenium Falcon


Seeding


Shadows
	Optimization


Testing


Finalize


Report
	