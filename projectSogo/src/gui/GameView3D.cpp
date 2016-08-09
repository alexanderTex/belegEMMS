#include "GameView3D.h"

GameView3D::GameView3D(QWidget *parent) : QOpenGLWidget(parent)
{
    //setFixedSize(1024, 600);
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
    setUpdateBehavior(NoPartialUpdate);
    m_hoveredSlotPosition.X = -1;
    m_hoveredSlotPosition.Y = -1;
    m_castHit = false;
    m_mouseMoved = false;

}


GameView3D::GameView3D(GameManager *gm, QWidget *parent)
    : GameView3D(parent)
{
    this->m_gm = gm;
}



void GameView3D::CleanUp()
{
    Logger::GetLoggerIntance()->LogInfo("GameView 3D Destuctor");
    makeCurrent();

    QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());

    delete(Sphere);
    delete(Cube);
    delete(Kanne);

    f->glDeleteTextures(1, &m_tAffe);

    f->glDeleteTextures(1, &m_tRed);
    f->glDeleteTextures(1, &m_tBlue);
    f->glDeleteTextures(1, &m_tBrown);

    f->glDeleteProgram(programID);

    doneCurrent();
}


void GameView3D::sendMVP(GLuint programID)
{
    QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());
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
void GameView3D::initializeGL()
{

    QObject::connect(QOpenGLContext::currentContext(), &QOpenGLContext::aboutToBeDestroyed, this, &GameView3D::CleanUp);

    QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());


    // Auf Keyboard-Events reagieren
        //glfwSetKeyCallback(window, key_callback);

        // white background
        f->glClearColor(1.0f, 1.0f, 1.0f, 0.0f);


        f->glEnable(GL_DEPTH_TEST);

        // Punkte die kleiner sind kommen durch.
        f->glDepthFunc(GL_LESS);

        Logger::GetLoggerIntance()->LogInfo(QDir::currentPath().toStdString());
        Logger::GetLoggerIntance()->LogInfo(QCoreApplication::applicationDirPath().toStdString());

        std::stringstream vertexShaderPath;
        vertexShaderPath << QCoreApplication::applicationDirPath().toStdString() << "/Shader/StandardShading.vertexshader";

        std::stringstream fragmentShaderPath;
        fragmentShaderPath << QCoreApplication::applicationDirPath().toStdString() << "/Shader/StandardShading.fragmentshader";

        // Create and compile our GLSL program from the shaders
        programID = LoadShaders(vertexShaderPath.str().c_str(), fragmentShaderPath.str().c_str());

        // Shader auch benutzen !
        f->glUseProgram(programID);


        std::stringstream sphereObjectPath;
        sphereObjectPath << QCoreApplication::applicationDirPath().toStdString() << "/Objects/sphere.obj";

        std::stringstream cubeObjectPath;
        cubeObjectPath << QCoreApplication::applicationDirPath().toStdString() << "/Objects/cube.obj";

        std::stringstream teapotObjectPath;
        teapotObjectPath << QCoreApplication::applicationDirPath().toStdString() << "/Objects/teapot.obj";

        Sphere = new Mesh(sphereObjectPath.str().c_str());

        Cube = new Mesh(cubeObjectPath.str().c_str());

        Kanne = new Mesh(teapotObjectPath.str().c_str());

        Logger::GetLoggerIntance()->LogInfo("Meshes loaded", __FILE__, __LINE__);


        std::stringstream affeTexturePath;
        affeTexturePath << QCoreApplication::applicationDirPath().toStdString() << "/Textures/mandrill.bmp";


        std::stringstream grainRedPath;
        grainRedPath << QCoreApplication::applicationDirPath().toStdString() << "/Textures/Maserung298rot.bmp";

        std::stringstream grainBluePath;
        grainBluePath << QCoreApplication::applicationDirPath().toStdString() << "/Textures/Maserung298blau.bmp";

        std::stringstream grainBrownPath;
        grainBrownPath << QCoreApplication::applicationDirPath().toStdString() << "/Textures/Maserung298braun.bmp";

        Logger::GetLoggerIntance()->LogInfo("Textures loading", __FILE__, __LINE__);

        // Load the texture
        m_tAffe = loadBMP_custom(affeTexturePath.str().c_str());

        Logger::GetLoggerIntance()->LogInfo("Mandrill Loaded", __FILE__, __LINE__);
        //Logger::GetLoggerIntance()->LogInfo(grainRedPath.str(), __FILE__, __LINE__);

        //Logger::GetLoggerIntance()->LogInfo(grainRedPath.str(), __FILE__, __LINE__);




        m_tRed = loadBMP_custom(grainRedPath.str().c_str());

        m_tBlue = loadBMP_custom(grainBluePath.str().c_str());

        m_tBrown = loadBMP_custom(grainBrownPath.str().c_str());

        this->setFocus();
        Logger::GetLoggerIntance()->LogInfo("GLInit finishes");

        m_drawUpdate3D = new QTimer(this);
        QObject::connect(this->m_drawUpdate3D, SIGNAL(timeout()), this, SLOT(update()));
        m_drawUpdate3D->setSingleShot(false);
        m_drawUpdate3D->start(2);
}


void GameView3D::paintGL()
{
    if(this->m_gm->GetGameData() == NULL)
    {
        Logger::GetLoggerIntance()->LogInfo("GameData Null", __FILE__, __LINE__);
        return;
    }

    //Logger::GetLoggerIntance()->LogInfo("Paint Loop Start");

    QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());


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

    Model = glm::rotate(Model, x_achse, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, y_achse, glm::vec3(0.0f, 1.0f, 0.0f));
    /*
    // Modellierung mit Pfeiltasten
    Model = glm::rotate(Model, up, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, down, glm::vec3(-1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, left, glm::vec3(0.0f, -1.0f, 0.0f));
    Model = glm::rotate(Model, right, glm::vec3(0.0f, 1.0f, 0.0f));
    */


    Save = Model;
    //drawCube();
    // =========================================================================
    //
    //	Playfield
    //
    // =========================================================================

    int x, y, z;

    // World space offset
    // Verschiebungsweite
    float lookAtPointOffset = ( ( m_gm->GetGameData()->GetField()->GetFieldSize() - 1) * m_kugelRad * 2) / 2;

    OffsetSave = glm::translate(Model, glm::vec3(0, m_kugelRad, 0));





    for (x = 0; x < m_gm->GetGameData()->GetField()->GetFieldSize(); x++)
    {
        for (z = 0; z < m_gm->GetGameData()->GetField()->GetFieldSize(); z++)
        {
            Model = Save;

            Model = glm::translate(Model, glm::vec3(x * (m_kugelRad * 2) - lookAtPointOffset, -lookAtPointOffset, z * (m_kugelRad * 2) - lookAtPointOffset));
            Model = glm::scale(Model, glm::vec3(m_kugelRad, m_kugelRad /4, m_kugelRad));
            // Bind our texture in Texture Unit 0
            f->glActiveTexture(GL_TEXTURE0);				// Die Textturen sind durchnummeriert
            f->glBindTexture(GL_TEXTURE_2D, m_tAffe);		// Verbindet die Textur
                                                            // Set our "myTextureSampler" sampler to user Texture Unit 0
            f->glUniform1i(f->glGetUniformLocation(programID, "myTextureSampler"), 0);

            sendMVP(programID);
            f->glBindVertexArray(Cube->VertexArrayID);
            f->glDrawArrays(GL_TRIANGLES, 0, Cube->vertexCount);
        }
    }


    float closestRayHitDistance = 0;

    // x hori
    // y depth
    // z verti

    for (x = 0; x < m_gm->GetGameData()->GetField()->GetFieldSize(); x++)
    {
        for (y = 0; y < m_gm->GetGameData()->GetField()->GetFieldSize(); y++)
        {
            for (z = 0; z < m_gm->GetGameData()->GetField()->GetFieldSize(); z++)
            {
                Model = OffsetSave;

                Model = glm::translate(Model, glm::vec3(x * (m_kugelRad * 2) - lookAtPointOffset, z * (m_kugelRad * 2) - lookAtPointOffset, y * (m_kugelRad * 2) - lookAtPointOffset));

                if (m_gm->GetGameData()->GetField()->GetSlot(x, y, z)->Occupation == PlayingField::BLUE)
                {

                    Model = glm::scale(Model, glm::vec3(m_kugelRad*2, m_kugelRad*2, m_kugelRad*2));
                    //Model = glm::scale(Model, glm::vec3(1.0 / 1000.0, 1.0 / 1000.0, 1.0 / 1000.0));


                    // Bind our texture in Texture Unit 0
                    f->glActiveTexture(GL_TEXTURE0);				// Die Textturen sind durchnummeriert
                    f->glBindTexture(GL_TEXTURE_2D, m_tBlue);		// Verbindet die Textur
                                                                // Set our "myTextureSampler" sampler to user Texture Unit 0
                    f->glUniform1i(f->glGetUniformLocation(programID, "myTextureSampler"), 0);

                    sendMVP(programID);
                    f->glBindVertexArray(Sphere->VertexArrayID);
                    f->glDrawArrays(GL_TRIANGLES, 0, Sphere->vertexCount);


                }
                else if (m_gm->GetGameData()->GetField()->GetSlot(x, y, z)->Occupation == PlayingField::RED)
                {

                    Model = glm::scale(Model, glm::vec3(m_kugelRad*2, m_kugelRad*2, m_kugelRad*2));
                    //Model = glm::scale(Model, glm::vec3(1.0 / 1000.0, 1.0 / 1000.0, 1.0 / 1000.0));


                    // Bind our texture in Texture Unit 0
                    f->glActiveTexture(GL_TEXTURE0);				// Die Textturen sind durchnummeriert
                    f->glBindTexture(GL_TEXTURE_2D, m_tRed);		// Verbindet die Textur
                                                                // Set our "myTextureSampler" sampler to user Texture Unit 0
                    f->glUniform1i(f->glGetUniformLocation(programID, "myTextureSampler"), 0);

                    sendMVP(programID);
                    f->glBindVertexArray(Sphere->VertexArrayID);
                    f->glDrawArrays(GL_TRIANGLES, 0, Sphere->vertexCount);


                }
                else
                {
                    Model = glm::scale(Model, glm::vec3(m_kugelRad / 5, m_kugelRad * 2, m_kugelRad / 5));


                    // Bind our texture in Texture Unit 0
                    f->glActiveTexture(GL_TEXTURE0);				// Die Textturen sind durchnummeriert
                    f->glBindTexture(GL_TEXTURE_2D, m_tBrown);		// Verbindet die Textur
                                                                    // Set our "myTextureSampler" sampler to user Texture Unit 0
                    f->glUniform1i(f->glGetUniformLocation(programID, "myTextureSampler"), 0);

                    sendMVP(programID);

                    f->glBindVertexArray(Cube->VertexArrayID);
                    f->glDrawArrays(GL_TRIANGLES, 0, Cube->vertexCount);
                }
            }

            //Logger::GetLoggerIntance()->LogInfo("Before draw WireCube", __FILE__, __LINE__);



            //Logger::GetLoggerIntance()->LogInfo("Before draw WireCube", __FILE__, __LINE__);
        }
        Model = Save;

    }

    Model = Save;
    if(CastRay(this->m_currentMousePos))
    {
        Model = OffsetSave;
        float obbSize = m_gm->GetGameData()->GetField()->GetFieldSize() * m_kugelRad;

        Model = glm::translate(Model, glm::vec3(m_hoveredSlotPosition.X * (m_kugelRad * 2) - lookAtPointOffset, (obbSize) - lookAtPointOffset,
                                                m_hoveredSlotPosition.Y * (m_kugelRad * 2) - lookAtPointOffset));
        Model = glm::scale(Model, glm::vec3(m_kugelRad, obbSize, m_kugelRad));


        sendMVP(programID);
        drawWireCube();

    }

    Model = OffsetSave;

    float obbSize = m_gm->GetGameData()->GetField()->GetFieldSize() * m_kugelRad;

    // Lichtposition an der Spitze des letzten Segments
    glm::vec4 lightPos = glm::vec4(0, 10, 0, 1);

    Model = glm::translate(Model, glm::vec3(lightPos.x, lightPos.y, lightPos.z));

    /*
    stringstream s;

    s << " Lightposition from model : " << Model[0].x << " " << Model[1].y * 10 << " " << Model[2].z << std::endl;

    Logger::GetLoggerIntance()->LogInfo(s.str(), __FILE__, __LINE__);
    */

    f->glUniform3f(f->glGetUniformLocation(programID, "LightPosition_worldspace"), Model[0].x, Model[1].y * 9, Model[2].z);

    Model = Save;

    //Logger::GetLoggerIntance()->LogInfo("Paint Loop END");
}




void GameView3D::resizeGL(int w, int h)
{
    //Logger::GetLoggerIntance()->LogInfo("Resize Start");

    Projection = glm::perspective(45.0f, (float)(w / h), 0.1f, 100.0f);

}




bool GameView3D::CastRay(QPoint m_currentMousePos)
{

    this->m_castHit = false;
    float closestRayHitDistance = 100000;

    bool objectHit = false;

    // World space offset
    // Verschiebungsweite
    float lookAtPointOffset = ( ( m_gm->GetGameData()->GetField()->GetFieldSize() - 1) * m_kugelRad * 2) / 2;

    float currentRayHitDist = -2;

    glm::vec3 rayOrigin;
    glm::vec3 rayDir;

    ScreenPosToWorldRay((&m_currentMousePos)->x() , (&m_currentMousePos)->y(), this->width(), this->height(), View, Projection, rayOrigin, rayDir);

    // Dumb tutorial
    rayDir = glm::vec3(rayDir.x, -rayDir.y, rayDir.z);

    float obbSize = m_gm->GetGameData()->GetField()->GetFieldSize() * m_kugelRad;

    //glm::vec3 minaabb(-m_kugelRad / 2, -obbSize / 2, -m_kugelRad / 2);
    //glm::vec3 maxaabb(m_kugelRad / 2, obbSize / 2, m_kugelRad / 2);

    glm::vec3 minaabb(-m_kugelRad, -obbSize * 5, -m_kugelRad);
    glm::vec3 maxaabb( m_kugelRad, obbSize * 5, m_kugelRad);

    for(int x = 0; x < m_gm->GetGameData()->GetField()->GetFieldSize(); x++)
    {
        for(int z = 0; z < m_gm->GetGameData()->GetField()->GetFieldSize(); z++)
        {
            Model = OffsetSave;

            Model = glm::translate(Model, glm::vec3(x * (m_kugelRad * 2) - lookAtPointOffset, (obbSize) - lookAtPointOffset, z * (m_kugelRad * 2) - lookAtPointOffset));
            Model = glm::scale(Model, glm::vec3(m_kugelRad, obbSize, m_kugelRad));

            /*

            // Debug Cubes
            sendMVP(programID);
            drawWireCube();

            */

            if(TestRayOBBIntersection(rayOrigin, rayDir, minaabb, maxaabb, Model, currentRayHitDist))
            {
                if((currentRayHitDist < closestRayHitDistance))
                {
                    // don't know why Y is (fieldsize - 1) - z but it seems to be :S
                    // somewhat not coherend / connected in the right way ... :/
                    m_hoveredSlotPosition.X = x;
                    m_hoveredSlotPosition.Y = z;

                    m_castHit = true;
                    objectHit = true;

                    /*
                    std::stringstream s;
                    s << x << " : " << z;
                    Logger::GetLoggerIntance()->LogInfo(s.str(), __FILE__, __LINE__);
                    */
                    /*
                    std::stringstream s;
                    s << "Hit detected ( " << x << " , " << z << " )" << "distance: closest:" << closestRayHitDistance << " |to| current : " << currentRayHitDist << std::endl;
                    Logger::GetLoggerIntance()->LogInfo(s.str(), __FILE__, __LINE__);
                    */
                    closestRayHitDistance = currentRayHitDist;

                    //cout << currentRayHitDist << endl;




                }
                else
                {
                    /*
                    std::stringstream s;
                    s << "Hit but not closest";
                    s << "Hit detected ( " << x << " , " << z << " )" << "distance: closest:" << closestRayHitDistance << " |to| current : " << currentRayHitDist << std::endl
                         << " z: " << z << std::endl;
                    Logger::GetLoggerIntance()->LogInfo(s.str(), __FILE__, __LINE__);
                    */
                }
            }
            else
            {
                //Logger::GetLoggerIntance()->LogInfo("No hit detected", __FILE__, __LINE__);
            }

        }

    }
    Model = Save;
    return objectHit;

}


void GameView3D::CreateLine(glm::vec3 start, glm::vec3 end, GLuint &VertexArrayIDLine)
{
    QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());
    // Vertexarrays kapseln ab OpenGL3 Eckpunkte, Texturen und Normalen
    f->glGenVertexArrays(1, &VertexArrayIDLine);
    f->glBindVertexArray(VertexArrayIDLine);

    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
        start.x,start.y,start.z, end.x,end.y, end.z,
    };

    // Vertexbuffer-Daten z.B. auf Grafikkarte kopieren
    GLuint vertexbuffer;
    f->glGenBuffers(1, &vertexbuffer);
    f->glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Erklaeren wie die Vertex-Daten zu benutzen sind
    f->glEnableVertexAttribArray(0); // Kein Disable ausfuehren !
    f->glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    f->glBindVertexArray(0);
}


void GameView3D::DrawLine(glm::vec3 start, glm::vec3 end)
{
    Model = Save;
    GLuint VertexArrayIDLine;

    CreateLine(start, end, VertexArrayIDLine);

    QOpenGLFunctions_3_3_Core *f = (QOpenGLFunctions_3_3_Core*)(QOpenGLContext::currentContext()->versionFunctions());

    f->glBindVertexArray(VertexArrayIDLine);
    f->glDrawArrays(GL_LINES, 0, 24); // 12 Linien haben 24 Punkte

    f->glDeleteVertexArrays(2, &VertexArrayIDLine);
    Model = Save;
}



void GameView3D::ScreenPosToWorldRay(
    int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
    int screenWidth, int screenHeight,  // Window size, in pixels
    glm::mat4 ViewMatrix,               // Camera position and orientation
    glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
    glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
    glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
){

    // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
    glm::vec4 lRayStart_NDC(
        ((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
        ((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
        -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
        1.0f
    );
    glm::vec4 lRayEnd_NDC(
        ((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
        ((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
        0.0,
        1.0f
    );


    // The Projection matrix goes from Camera Space to NDC.
    // So inverse(ProjectionMatrix) goes from NDC to Camera Space.
    glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

    // The View Matrix goes from World Space to Camera Space.
    // So inverse(ViewMatrix) goes from Camera Space to World Space.
    glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

    glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
    glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
    glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
    glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;


    // Faster way (just one inverse)
    //glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
    //glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
    //glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;


    glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
    lRayDir_world = glm::normalize(lRayDir_world);


    out_origin = glm::vec3(lRayStart_world);
    out_direction = glm::normalize(lRayDir_world);
}


bool GameView3D::TestRayOBBIntersection(
    glm::vec3 ray_origin,        // Ray origin, in world space
    glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
    glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
    glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
    glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
    float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
){

    // Intersection method from Real-Time Rendering and Essential Mathematics for Games

    float tMin = 0.0f;
    float tMax = 100000.0f;

    glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

    glm::vec3 delta = OBBposition_worldspace - ray_origin;

    // Test intersection with the 2 planes perpendicular to the OBB's X axis
    {
        glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
        float e = glm::dot(xaxis, delta);
        float f = glm::dot(ray_direction, xaxis);

        if ( fabs(f) > 0.001f ){ // Standard case

            float t1 = (e+aabb_min.x)/f; // Intersection with the "left" plane
            float t2 = (e+aabb_max.x)/f; // Intersection with the "right" plane
            // t1 and t2 now contain distances betwen ray origin and ray-plane intersections

            // We want t1 to represent the nearest intersection,
            // so if it's not the case, invert t1 and t2
            if (t1>t2){
                float w=t1;t1=t2;t2=w; // swap t1 and t2
            }

            // tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
            if ( t2 < tMax )
                tMax = t2;
            // tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
            if ( t1 > tMin )
                tMin = t1;

            // And here's the trick :
            // If "far" is closer than "near", then there is NO intersection.
            // See the images in the tutorials for the visual explanation.
            if (tMax < tMin )
                return false;

        }else{ // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
            if(-e+aabb_min.x > 0.0f || -e+aabb_max.x < 0.0f)
                return false;
        }
    }


    // Test intersection with the 2 planes perpendicular to the OBB's Y axis
    // Exactly the same thing than above.
    {
        glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
        float e = glm::dot(yaxis, delta);
        float f = glm::dot(ray_direction, yaxis);

        if ( fabs(f) > 0.001f ){

            float t1 = (e+aabb_min.y)/f;
            float t2 = (e+aabb_max.y)/f;

            if (t1>t2){float w=t1;t1=t2;t2=w;}

            if ( t2 < tMax )
                tMax = t2;
            if ( t1 > tMin )
                tMin = t1;
            if (tMin > tMax)
                return false;

        }else{
            if(-e+aabb_min.y > 0.0f || -e+aabb_max.y < 0.0f)
                return false;
        }
    }


    // Test intersection with the 2 planes perpendicular to the OBB's Z axis
    // Exactly the same thing than above.
    {
        glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
        float e = glm::dot(zaxis, delta);
        float f = glm::dot(ray_direction, zaxis);

        if ( fabs(f) > 0.001f ){

            float t1 = (e+aabb_min.z)/f;
            float t2 = (e+aabb_max.z)/f;

            if (t1>t2){float w=t1;t1=t2;t2=w;}

            if ( t2 < tMax )
                tMax = t2;
            if ( t1 > tMin )
                tMin = t1;
            if (tMin > tMax)
                return false;

        }else{
            if(-e+aabb_min.z > 0.0f || -e+aabb_max.z < 0.0f)
                return false;
        }
    }

    intersection_distance = tMin;
    return true;

}
