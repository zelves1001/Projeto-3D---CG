#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

GLfloat cameraDistance = 6.0; // Nova distância inicial da câmera
GLfloat rotationAngle = 45.0; // Angulo de rotação inicial

int selectedObjectIndex = -1; // Índice do objeto selecionado para mover

GLfloat objectPositions[3][3] = {{-3.0, 1.5, 0.0}, {1.0, 1.5, -3.5}, {3.0, 0.5, 1.0}}; // Posições iniciais dos objetos

void init() {
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0}; // Iluminação ambiente
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0}; // Iluminação difusa
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0}; // Iluminação especular
    GLfloat position[] = {2.0, 6.0, 3.0, 0.0}; // Posição da luz

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configurando as propriedades de iluminação
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    GLfloat wallAmbientDiffuse[] = {0.8, 0.0, 0.0, 1.0}; // Cor ambiente e difusa das paredes
    GLfloat wallSpecular[] = {1.0, 1.0, 1.0, 1.0}; // Cor especular das paredes
    GLfloat wallShininess[] = {100.0}; // Brilho das paredes

    // Configurando as propriedades de material
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallAmbientDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wallSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, wallShininess);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Definindo a posição da câmera diretamente
    gluLookAt(0.0, cameraDistance, cameraDistance,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Desenhando o chão
    glPushMatrix(); // Salva a matriz de transformação atual
    glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Rotaciona o chão em torno do eixo Y
    glColor3f(0.8, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(-5.0, 0.0, -5.0);
        glVertex3f(-5.0, 0.0, 5.0);
        glVertex3f(5.0, 0.0, 5.0);
        glVertex3f(5.0, 0.0, -5.0);
    glEnd();
    glPopMatrix(); // Restaura a matriz de transformação

    //-------------------------------------------------------------------------------------------------------------

    //Aspecto 3D DO PISO

    glPushMatrix(); // Salva a matriz de transformação atual
    glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Rotaciona as paredes em torno do eixo Y
    glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_QUADS);
        // Paredes laterais

        glVertex3f(-5.0, 0.0, -5.0);
        glVertex3f(-5.0, 0.5, -5.0);
        glVertex3f(-5.0, 0.5, 5.0);
        glVertex3f(-5.0, 0.0, 5.0);

        // Paredes laterais direitas
        glVertex3f(5.0, 0.0, -5.0);
        glVertex3f(5.0, 0.5, -5.0);
        glVertex3f(5.0, 0.5, 5.0);
        glVertex3f(5.0, 0.0, 5.0);

        // Paredes frontais
        glVertex3f(-5.0, 0.0, -5.0);
        glVertex3f(-5.0, 0.5, -5.0);
        glVertex3f(5.0, 0.5, -5.0);
        glVertex3f(5.0, 0.0, -5.0);

        // Paredes traseiras
        glVertex3f(-5.0, 0.0, 5.0);
        glVertex3f(-5.0, 0.5, 5.0);
        glVertex3f(5.0, 0.5, 5.0);
        glVertex3f(5.0, 0.0, 5.0);
    glEnd();
    glPopMatrix(); // Restaura a matriz de transformação

    //-------------------------------------------------------------------------------------------------------------

    // DESENHANDO AS PAREDES E OS ASPECTOS 3D LATERAL DELAS

    glPushMatrix(); // Salva a matriz de transformação atual
    glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Rotaciona as paredes em torno do eixo Y
    glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_QUADS);
        // Paredes laterais

        glVertex3f(5.0, 0.0, -5.0);
        glVertex3f(5.0, 5.0, -5.0);
        glVertex3f(5.0, 5.0, 5.0);
        glVertex3f(5.0, 0.0, 5.0);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(5.5, 0.0, 5.0);
        glVertex3f(5.5, 5.0, 5.0);
        glVertex3f(5.0, 5.0, 5.0);
        glVertex3f(5.0, 0.0, 5.0);
    glEnd();

    glBegin(GL_QUADS);
        // Parede traseira
        glVertex3f(-5.0, 0.0, -5.0);
        glVertex3f(-5.0, 5.0, -5.0);
        glVertex3f(5.0, 5.0, -5.0);
        glVertex3f(5.0, 0.0, -5.0);
    glEnd();

    glBegin(GL_QUADS);
    // Parede lateral direita
        glVertex3f(-5.0, 0.0, -5.5);
        glVertex3f(-5.0, 5.0, -5.5);
        glVertex3f(-5.0, 5.0, -5.0);  // Altura da parede traseira
        glVertex3f(-5.0, 0.0, -5.0);  // Altura da parede traseira
    glEnd();
    glPopMatrix(); // Restaura a matriz de transformação

    //ASPECTOS 3D DA PARTE DE CIMA DAS PAREDES

    glPushMatrix(); // Salva a matriz de transformação atual
    glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Rotaciona o chão em torno do eixo Y
    glColor3f(0.8, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(-5.0, 5.0, -5.0);
        glVertex3f(-5.0, 5.0, -5.5);
        glVertex3f(5.0, 5.0, -5.5);
        glVertex3f(5.0, 5.0, -5.0);
    glEnd();
    glPopMatrix(); // Restaura a matriz de transformação

    glPushMatrix(); // Salva a matriz de transformação atual
    glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Rotaciona o chão em torno do eixo Y
    glColor3f(0.8, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(5.0, 5.0, 5.0);
        glVertex3f(5.5, 5.0, 5.0);
        glVertex3f(5.5, 5.0, -5.5);
        glVertex3f(5.0, 5.0, -5.5);
    glEnd();
    glPopMatrix(); // Restaura a matriz de transformação


    //----------------------------------------------------------------------------------------------------

    //RENDERIZAÇÃO DOS OBJETOS

    // Renderizando o bule
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(-3.0, 1.5, 0.0); // Move o bule para a posição desejada
    glScalef(2.0, 2.0, 2.0);
    glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Rotaciona o bule em torno do eixo Y
    glColor3f(21.0 / 255.0, 167.0 / 255.0, 206.0 / 255.0);
    glutSolidTeapot(1.0);
    glPopMatrix(); // Restaura a matriz de transformação

    // Renderizando a bola
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(1.0, 1.5, -3.5); // Move a bola para a posição desejada
    glScalef(2.0, 2.0, 2.0);
    glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Rotaciona a bola em torno do eixo Y
    glColor3f(255.0 / 255.0, 153.0 / 255.0, 0.0 / 255.0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix(); // Restaura a matriz de transformação

    // Renderizando o toro
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(3.0, 0.5, 1.0); // Move o toro para a posição desejada
    glScalef(2.0, 2.0, 2.0);
    glRotatef(rotationAngle, 0.0, 0.0, 0.0); // Altere esta linha para rotacionar em torno do eixo X
    glRotatef(90.0, 1.0, 0.0, 0.0); // Nova linha para rotacionar em torno do eixo X
    glColor3f(158.0 / 255.0, 250.0 / 255.0, 0.0 / 255.0);
    glutSolidTorus(0.3, 1.0, 20, 20);
    glPopMatrix(); // Restaura a matriz de transformação

    glutSwapBuffers();
}
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            cameraDistance -= 0.1; // Zoom in
            break;
        case GLUT_KEY_DOWN:
            cameraDistance += 0.1; // Zoom out
            break;
    }
    glutPostRedisplay();
}

void moveObject(int index, GLfloat x, GLfloat y, GLfloat z) {
    if (index < 0 || index >= 3) {
        printf("Índice de objeto inválido.\n");
        return;
    }
    objectPositions[index][0] = x;
    objectPositions[index][1] = y;
    objectPositions[index][2] = z;
}

void selectObject(int objectID) {
    selectedObjectIndex = objectID;
    printf("%d", objectID);
}


void selectObjectWithKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 't': // Seleciona o bule
            selectObject(0);
            break;
        case '2': // Seleciona a bola
            selectObject(1);
            break;
        case '3': // Seleciona o toro
            selectObject(2);
            break;
    }
}

void moveObjectWithKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            moveObject(selectedObjectIndex, objectPositions[selectedObjectIndex][0], objectPositions[selectedObjectIndex][1], objectPositions[selectedObjectIndex][2] - 0.1);
            break;
        case 'a':
        case 'A':
            moveObject(selectedObjectIndex, objectPositions[selectedObjectIndex][0] - 0.1, objectPositions[selectedObjectIndex][1], objectPositions[selectedObjectIndex][2]);
            break;
        case 's':
        case 'S':
            moveObject(selectedObjectIndex, objectPositions[selectedObjectIndex][0], objectPositions[selectedObjectIndex][1], objectPositions[selectedObjectIndex][2] + 0.1);
            break;
        case 'd':
        case 'D':
            moveObject(selectedObjectIndex, objectPositions[selectedObjectIndex][0] + 0.1, objectPositions[selectedObjectIndex][1], objectPositions[selectedObjectIndex][2]);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL 3D Scene");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys); // Captura eventos de teclado

    // Adicionando a função de movimento de objetos às teclas 'W', 'A', 'S' e 'D'
    glutKeyboardFunc(selectObjectWithKeys);
    glutKeyboardFunc(moveObjectWithKeys);

    glutMainLoop();
    return 0;
}



