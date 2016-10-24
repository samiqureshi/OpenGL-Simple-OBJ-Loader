// Here are the fonts:
LPVOID glutFonts[7] = {
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_8_BY_13,
    GLUT_BITMAP_TIMES_ROMAN_10,
    GLUT_BITMAP_TIMES_ROMAN_24,
    GLUT_BITMAP_HELVETICA_10,
    GLUT_BITMAP_HELVETICA_12,
    GLUT_BITMAP_HELVETICA_18
};

//glutPrint(-1.5f, 1.0f, glutFonts[1], s, 1.0f, 0.0f, 0.0f, 0.5f);

// Here is the function
void glutPrint(float x, float y, LPVOID font, char* text, float r, float g, float b, float a)
{
    if(!text || !strlen(text)) return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glColor4f(r,g,b,a);
    glRasterPos2f(x,y);
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
    if(!blending) glDisable(GL_BLEND);
}  
