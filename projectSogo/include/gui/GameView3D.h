#ifndef GAMEVIEW3D_H
#define GAMEVIEW3D_H

#include <typeinfo>
#include <sstream>

// Include GLM
#include "../external/glm-0.9.4.0/glm/glm.hpp"
#include "../external/glm-0.9.4.0/glm/gtc/matrix_transform.hpp"

#include "../external/objloader.hpp"
#include "../external/shader.hpp"
#include "../external/objects.hpp"
#include "../external/texture.hpp"

#include <QApplication>
#include <QWidget>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QKeyEvent>
#include <QTimer>

#include "Logger.h"
#include "GameManagerThread.h"


class GameView3D : public QOpenGLWidget
{
    /*
        Dient zur Darstellung eines 3D Modells.
    */
    struct Mesh
    {
        /*
            filename	Übergabe der pbj Datei
        */
        Mesh(std::string fileName)
        {
            Logger::GetLoggerIntance()->LogInfo("Mesh Const");
            QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());
            // --- Kannenmodell
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec2> uvs;
            std::vector<glm::vec3> normals;
            // Laden der Objektdatei
            Logger::GetLoggerIntance()->LogInfo("before LoadObj");

            bool res = loadOBJ(fileName.c_str(), vertices, uvs, normals);
            if(!res)
                Logger::GetLoggerIntance()->LogError("Load OBJ Failed");
            else
                Logger::GetLoggerIntance()->LogInfo("Obj loaded");

            // Jedes Objekt eigenem VAO zuordnen, damit mehrere Objekte moeglich sind
            // VAOs sind Container fuer mehrere Buffer, die zusammen gesetzt werden sollen.
            f->glGenVertexArrays(1, &VertexArrayID);
            f->glBindVertexArray(VertexArrayID);

            // Ein ArrayBuffer speichert Daten zu Eckpunkten (hier xyz bzw. Position)
            f->glGenBuffers(1, &vertexbuffer); // Kennung erhalten
            f->glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // Daten zur Kennung definieren
                                                         // Buffer zugreifbar für die Shader machen
            f->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

            // Erst nach glEnableVertexAttribArray kann DrawArrays auf die Daten zugreifen...
            f->glEnableVertexAttribArray(0); // siehe layout im vertex shader: location = 0
            f->glVertexAttribPointer(0,  // location = 0
                3,  // Datenformat vec3: 3 floats fuer xyz
                GL_FLOAT,
                GL_FALSE, // Fixedpoint data normalisieren ?
                0, // Eckpunkte direkt hintereinander gespeichert
                (void*)0); // abweichender Datenanfang ?


                           // Aufgabe 6 // Hier alles analog für Normalen in location == 2
            f->glGenBuffers(1, &normalbuffer);
            f->glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
            f->glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
            f->glEnableVertexAttribArray(2); // siehe layout im vertex shader
            f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

            // Aufgabe 7 // Hier alles analog für Texturkoordinaten in location == 1 (2 floats u und v!)
            f->glGenBuffers(1, &uvbuffer);
            f->glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            f->glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
            f->glEnableVertexAttribArray(1); // siehe layout im vertex shader
            f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

            vertexCount = vertices.size();

            Logger::GetLoggerIntance()->LogInfo("Mesh successfully created! Yeah");
        }

        virtual ~Mesh()
        {
            Logger::GetLoggerIntance()->LogInfo("Mesh destrS");
            QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());

            f->glDeleteBuffers(1, &vertexbuffer);

            f->glDeleteBuffers(1, &normalbuffer);

            f->glDeleteBuffers(1, &uvbuffer);
        }

        GLuint VertexArrayID;

        GLuint vertexbuffer;
        GLuint normalbuffer;
        GLuint uvbuffer;

        int vertexCount;

    };

    Q_OBJECT
public:



    explicit GameView3D(QWidget *parent = 0);
    GameView3D(GameManager *gm, QWidget *parent = 0);

    virtual inline ~GameView3D()
    {

    }

    void CleanUp();

protected:

    void sendMVP(GLuint programID);


    //this is where all the code before the graphics loop goes
    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int w, int h);



    inline void keyPressEvent(QKeyEvent *event)
    {
        switch(event->key())
        {
            case Qt::Key_A:
                y_achse -= 1;
            break;
            case Qt::Key_D:
                y_achse += 1;
            break;
            case Qt::Key_W:
                x_achse += 1;
            break;
            case Qt::Key_S:
                x_achse -= 1;
            break;
        }
    }

    inline void mousePressEvent(QMouseEvent *event)
    {
        Logger::GetLoggerIntance()->LogInfo("Mouse Button Pressed");

        if(m_castHit)
        {
            Vector2 v(this->m_hoveredSlotPosition.X, this->m_hoveredSlotPosition.Y);

            InputSubmit(v);
            Logger::GetLoggerIntance()->LogInfo("Mouse Button Input go");
        }
    }

    inline void mouseMoveEvent(QMouseEvent *event)
    {
        m_currentMousePos = event->pos();

        this->m_mouseMoved = true;
    }


    // works finally
    bool CastRay(QPoint m_currentMousePos);

    void CreateLine(glm::vec3 start, glm::vec3 end, GLuint &VertexArrayIDLine);

    void DrawLine(glm::vec3 start, glm::vec3 end);


    //Source : https://github.com/opengl-tutorials/ogl/blob/master/misc05_picking/misc05_picking_custom.cpp
    //         http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/



    void ScreenPosToWorldRay(
        int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
        int screenWidth, int screenHeight,  // Window size, in pixels
        glm::mat4 ViewMatrix,               // Camera position and orientation
        glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
        glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
        glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
    );


    bool TestRayOBBIntersection(
        glm::vec3 ray_origin,        // Ray origin, in world space
        glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
        glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
        glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
        glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
        float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
    );
signals:

    void InputSubmit(Vector2 pos);

public slots:


private :
    QTimer *m_drawUpdate3D;

    GameManager *m_gm;


    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 Save;
    glm::mat4 OffsetSave;

    float winkel = 0;
    float x_achse = 0;
    float y_achse = 0;
    float z_achse = 0;

    float left = 0;
    float right = 0;
    float up = 0;
    float down = 0;

    Vector2 m_hoveredSlotPosition;
    QPoint m_currentMousePos;
    bool m_mouseMoved;

    bool m_castHit;

    //KugelRadius
    float m_kugelRad = 1.0f;

    // will be playingfield->size
    int playfieldSize = 3;

    /***
     * Ressources
     */
    GLuint programID;
    GLuint m_tAffe;
    GLuint m_tRed;
    GLuint m_tBlue;
    GLuint m_tBrown;

    Mesh *Sphere;
    Mesh *Cube;
    Mesh *Kanne;





};

#endif // GAMEVIEW3D_H
