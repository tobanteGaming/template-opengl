# OpenGL

## Draw Lines

```cpp
// Draw lines
glUseProgram(NULL);
glLoadIdentity();  // load identity matrix

// glTranslatef(0.0f, 0.0f, -4.0f);  // move forward 4 units
glColor3f(0.0f, 1.0f, 1.0f);  // blue color

glLineWidth(10.0f);
glBegin(GL_LINES);  // starts drawing of points
glVertex3f(-0.6f, 1.0f, 0.0f);
glVertex3f(-0.5f, -1.0f, 0.0f);

glVertex3f(0.6f, 1.0f, 0.0f);
glVertex3f(0.5f, -1.0f, 0.0f);
glEnd();  // end drawing of points
```
