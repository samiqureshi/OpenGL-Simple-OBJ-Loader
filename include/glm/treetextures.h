//Textures and Texture Tree
GLuint texture;
Texture treeTexture;

bool LoadTreeTextures(char* texturename, int textureID)
{

    // first of all we call the tga file loader. It doesn't do anything special: it fills the Texture struct with information about
    // the image (height, width, bits per pixel). You can easily replace it with a function to load bmps or jpegs.
    // The important thing is do load the image corectly in the structure you give it
    if (LoadTGA(&treeTexture, texturename))
    {

        // This tells opengl to create 1 texture and put it's ID in the given integer variable
        // OpenGL keeps a track of loaded textures by numbering them: the first one you load is 1, second is 2, ...and so on.
        glGenTextures(textureID, &treeTexture.texID);
        // Binding the texture to GL_TEXTURE_2D is like telling OpenGL that the texture with this ID is now the current 2D texture in use
        // If you draw anything the used texture will be the last binded texture
        glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
        // This call will actualy load the image data into OpenGL and your video card's memory. The texture is allways loaded into the current texture
        // you have selected with the last glBindTexture call
        // It asks for the width, height, type of image (determins the format of the data you are giveing to it) and the pointer to the actual data
        glTexImage2D(GL_TEXTURE_2D, 0, treeTexture.bpp / 8, treeTexture.width, treeTexture.height, 0, treeTexture.type, GL_UNSIGNED_BYTE, treeTexture.imageData);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glEnable(GL_TEXTURE_2D);
        if (treeTexture.imageData)
        {

            // You can now free the image data that was allocated by LoadTGA
            // You don't want to keep a few Mb of worthless data on heap. It's worthless because OpenGL stores the image someware else after
            // you call glTexImage2D (usualy in you video card)
            free(treeTexture.imageData); 

        }

        return true;

    } // Return The Status
    else return false;

}
