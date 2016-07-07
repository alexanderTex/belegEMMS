#ifndef GAMEVIEW3D_H
#define GAMEVIEW3D_H

#include <typeinfo>


// Include GLM
#include "../external/glm-0.9.4.0/glm/glm.hpp"
#include "../external/glm-0.9.4.0/glm/gtc/matrix_transform.hpp"

#include "../external/objloader.hpp"
#include "../external/shader.hpp"
#include "../external/objects.hpp"

#include <QApplication>
#include <QWidget>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QFile>
#include <QFileInfo>
#include <QDir>

#include "Logger.h"
#include <sstream>

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
            QOpenGLFunctions_4_5_Core *f = (QOpenGLFunctions_4_5_Core*)(QOpenGLContext::currentContext()->versionFunctions());
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
            QOpenGLFunctions_4_5_Core *f = (QOpenGLFunctions_4_5_Core*)(QOpenGLContext::currentContext()->versionFunctions());

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

protected:

    void sendMVP(GLuint programID)
    {
        QOpenGLFunctions_4_5_Core *f = (QOpenGLFunctions_4_5_Core*)(QOpenGLContext::currentContext()->versionFunctions());
        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP = Projection * View * Model;
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform, konstant fuer alle Eckpunkte
        f->glUniformMatrix4fv(f->glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        f->glUniformMatrix4fv(f->glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
        f->glUniformMatrix4fv(f->glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
        f->glUniformMatrix4fv(f->glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);
    }


    //this is where all the code before the graphics loop goes
    inline virtual void initializeGL()
    {

        QOpenGLFunctions_4_5_Core *f = (QOpenGLFunctions_4_5_Core*)(QOpenGLContext::currentContext()->versionFunctions());


        // Auf Keyboard-Events reagieren
            //glfwSetKeyCallback(window, key_callback);

            // white background
            f->glClearColor(1.0f, 1.0f, 1.0f, 0.0f);


            f->glEnable(GL_DEPTH_TEST);

            // Punkte die kleiner sind kommen durch.
            f->glDepthFunc(GL_LESS);
            Logger::GetLoggerIntance()->Log("before shader");

            Logger::GetLoggerIntance()->Log(QDir::currentPath().toStdString());
            Logger::GetLoggerIntance()->Log(QCoreApplication::applicationDirPath().toStdString());

            std::stringstream vertexShaderPath;
            vertexShaderPath << QCoreApplication::applicationDirPath().toStdString() << "/Shader/StandardShading.vertexshader";

            std::stringstream fragmentShaderPath;
            fragmentShaderPath << QCoreApplication::applicationDirPath().toStdString() << "/Shader/StandardShading.fragmentshader";

            // Create and compile our GLSL program from the shaders
            programID = LoadShaders(vertexShaderPath.str().c_str(), fragmentShaderPath.str().c_str());

            Logger::GetLoggerIntance()->Log("after shaderload");


            std::stringstream sphereObjectPath;
            sphereObjectPath << QCoreApplication::applicationDirPath().toStdString() << "/Objects/sphere.obj";

            std::stringstream cubeObjectPath;
            cubeObjectPath << QCoreApplication::applicationDirPath().toStdString() << "/Objects/cube.obj";

            std::stringstream teapotObjectPath;
            teapotObjectPath << QCoreApplication::applicationDirPath().toStdString() << "/Objects/teapot.obj";

            Sphere = new Mesh(sphereObjectPath.str().c_str());

            Cube = new Mesh(cubeObjectPath.str().c_str());

            Kanne = new Mesh(teapotObjectPath.str().c_str());


            std::stringstream affeTexturePath;
            affeTexturePath << QCoreApplication::applicationDirPath().toStdString() << "/Textures/mandrill.bmp";

            std::stringstream loeweTexturePath;
            loeweTexturePath << QCoreApplication::applicationDirPath().toStdString() << "/Textures/mandrill.bmp";


            // Load the texture
            m_tAffe = new QOpenGLTexture(QImage(affeTexturePath.str().c_str()));
            m_tLoewe = new QOpenGLTexture(QImage(loeweTexturePath.str().c_str()));

            Logger::GetLoggerIntance()->LogInfo("GLInit finishes");

            setAutoFillBackground(false);
    }

    inline virtual void paintGL()
    {

        Logger::GetLoggerIntance()->LogInfo("Paint Loop Start");

        QOpenGLFunctions_4_5_Core *f = (QOpenGLFunctions_4_5_Core*)(QOpenGLContext::currentContext()->versionFunctions());

        // Shader auch benutzen !
        f->glUseProgram(programID);

        // Clear the screen
        //glClear(GL_COLOR_BUFFER_BIT);
        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

        // =========================================================================
        //
        //	Cam View
        //
        // =========================================================================
        View = glm::lookAt(glm::vec3(0, 0, -20), // Camera is at (0,0,-5), in World Space
            glm::vec3(0, 0, 0),  // and looks at the origin
            glm::vec3(0, 1, 0)); // Head is up (set to 0,-1,0 to look upside-down)


        // Model matrix : an identity matrix (model will be at the origin)
        Model = glm::mat4(1.0f);


        // Modellierung mit Pfeiltasten
        Model = glm::rotate(Model, up, glm::vec3(1.0f, 0.0f, 0.0f));
        Model = glm::rotate(Model, down, glm::vec3(-1.0f, 0.0f, 0.0f));
        Model = glm::rotate(Model, left, glm::vec3(0.0f, -1.0f, 0.0f));
        Model = glm::rotate(Model, right, glm::vec3(0.0f, 1.0f, 0.0f));

        Save = Model;
        drawCube();
        // =========================================================================
        //
        //	Playfield
        //
        // =========================================================================

        int x, y, z;

        // World space offset
        // Verschiebungsweite
        float lookAtPoint = (koord1 * kugelRad * 2) / 2;

        glm::mat4 offsetSaves = glm::translate(Model, glm::vec3(0, kugelRad, 0));





  ///*
        for (x = 0; x <= koord1; x++)
        {
            for (z = 0; z <= koord1; z++)
            {
                Model = Save;

                Model = glm::translate(Model, glm::vec3(x * (kugelRad * 2) - lookAtPoint, -lookAtPoint, z * (kugelRad * 2) - lookAtPoint));
                Model = glm::scale(Model, glm::vec3(kugelRad * 2, kugelRad /4, kugelRad * 2));
                // Bind our texture in Texture Unit 0
                f->glActiveTexture(GL_TEXTURE0);				// Die Textturen sind durchnummeriert
                f->glBindTexture(GL_TEXTURE_2D, m_tAffe->textureId());		// Verbindet die Textur
                                                                // Set our "myTextureSampler" sampler to user Texture Unit 0
                f->glUniform1i(f->glGetUniformLocation(programID, "myTextureSampler"), 0);

                sendMVP(programID);
                f->glBindVertexArray(Cube->VertexArrayID);
                f->glDrawArrays(GL_TRIANGLES, 0, Cube->vertexCount);
            }
        }

        for (y = 0; y <= koord1; y++)
        {
            for (x = 0; x <= koord1; x++)
            {
                for (z = 0; z <= koord1; z++)
                {
                    Model = offsetSaves;

                    Model = glm::translate(Model, glm::vec3(x * (kugelRad * 2) - lookAtPoint, y * (kugelRad * 2) - lookAtPoint, z * (kugelRad * 2) - lookAtPoint));

                    if (x == 1 && z == 3 && y == 0 )
                    {

                        Model = glm::scale(Model, glm::vec3(kugelRad*2, kugelRad*2, kugelRad*2));
                        //Model = glm::scale(Model, glm::vec3(1.0 / 1000.0, 1.0 / 1000.0, 1.0 / 1000.0));


                        // Bind our texture in Texture Unit 0
                        f->glActiveTexture(GL_TEXTURE0);				// Die Textturen sind durchnummeriert
                        f->glBindTexture(GL_TEXTURE_2D, m_tAffe->textureId());		// Verbindet die Textur
                                                                    // Set our "myTextureSampler" sampler to user Texture Unit 0
                        f->glUniform1i(f->glGetUniformLocation(programID, "myTextureSampler"), 0);

                        sendMVP(programID);
                        f->glBindVertexArray(Sphere->VertexArrayID);
                        f->glDrawArrays(GL_TRIANGLES, 0, Sphere->vertexCount);


                    }
                    else
                    {
                        Model = glm::scale(Model, glm::vec3(kugelRad / 5, kugelRad * 2, kugelRad / 5));


                        // Bind our texture in Texture Unit 0
                        f->glActiveTexture(GL_TEXTURE0);				// Die Textturen sind durchnummeriert
                        f->glBindTexture(GL_TEXTURE_2D, m_tAffe->textureId());		// Verbindet die Textur
                                                                        // Set our "myTextureSampler" sampler to user Texture Unit 0
                        f->glUniform1i(f->glGetUniformLocation(programID, "myTextureSampler"), 0);

                        sendMVP(programID);

                        drawCube();

                        f->glBindVertexArray(Cube->VertexArrayID);
                        f->glDrawArrays(GL_TRIANGLES, 0, Cube->vertexCount);
                    }
                }

            }
        }
//*/
        Model = Save;


        // Lichtposition an der Spitze des letzten Segments
        glm::vec4 lightPos = glm::vec4(8, 3, 0, 1);
        f->glUniform3f(f->glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z);

        //QOpenGLContext::currentContext()->swapBuffers(QOpenGLContext::currentContext()->surface());

        Logger::GetLoggerIntance()->LogInfo("Paint Loop END");


    }


    inline virtual void resizeGL(int w, int h)
    {
        Logger::GetLoggerIntance()->LogInfo("Resize Start");

        Projection = glm::perspective(45.0f, (float)(w / h), 0.1f, 100.0f);

    }


    inline bool RayCast()
    {
        float interDistance = 0;

        return false;


    }

    inline bool RayIntersection(glm::vec3 ray_origin, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, float &intersectionDistance)
    {
        float tMin = 0.0f;
        float tMax = 100000.0f;


        glm::vec3 OBBposition_worldspace(Model[3].x, Model[3].y, Model[3].z);

        glm::vec3 delta = OBBposition_worldspace - ray_origin;

        glm::vec3 xaxis(Model[0].x, Model[0].y, Model[0].z);
        float e = glm::dot(xaxis, delta);
        float f = glm::dot(ray_direction, xaxis);

        // Beware, don't do the division if f is near 0 ! See full source code for details.
        float t1 = (e+aabb_min.x)/f; // Intersection with the "left" plane
        float t2 = (e+aabb_max.x)/f; // Intersection with the "right" plane

        if (t1>t2){ // if wrong order
            float w=t1;t1=t2;t2=w; // swap t1 and t2
        }

        // tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
        if ( t2 < tMax ) tMax = t2;
        // tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
        if ( t1 > tMin ) tMin = t1;

        if (tMax < tMin )
            return false;
    }

signals:

public slots:


private :
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 Save;

    float winkel = 0;
    float x_achse = 0;
    float y_achse = 0;
    float z_achse = 0;

    float left = 0;
    float right = 0;
    float up = 0;
    float down = 0;





    //KugelRadius
    float kugelRad = 1.0f;

    // will be playingfield->size
    int koord1 = 3;

    /***
     * Ressources
     */
    GLuint programID;
    QOpenGLTexture *m_tAffe;
    QOpenGLTexture *m_tLoewe;

    Mesh *Sphere;
    Mesh *Cube;
    Mesh *Kanne;





};

#endif // GAMEVIEW3D_H
