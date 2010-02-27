#include "glwidget.h"

GLWidget::GLWidget()
{
    cellCount = 10;
    startTimer( TIMER_INTERVAL );
    rotX = rotY = rotZ = 0.f;
    col = 0;
}

void GLWidget::initializeGL()
{
    // Create a new unit (for gl debug purposes).
    unit[0].actionTime = 10;
    unit[0].actionRate = 150;
    unit[0].hitPoints = 80;
    unit[0].totalHitPoints = 100;
    unit[0].image.load("sprites/wizard.png");
    unit[0].mask_image.load("sprites/mask_wizard.png");
    unit[0].status = UNIT_OK;
    unit[0].xLocation = 1;
    unit[0].yLocation = 1;
    unit[0].leftTeam = true;

    // Create a new unit (for gl debug purposes).
    unit[1].actionTime = 10;
    unit[1].actionRate = 200;
    unit[1].hitPoints = 40;
    unit[1].totalHitPoints = 100;
    unit[1].image.load("sprites/buddhist.png");
    unit[1].mask_image.load("sprites/mask_buddhist.png");
    unit[1].status = UNIT_OK;
    unit[1].xLocation = 3;
    unit[1].yLocation = 4;
    unit[1].leftTeam = true;

    // Create a new unit (for gl debug purposes).
    unit[2].actionTime = 40;
    unit[2].actionRate = 100;
    unit[2].hitPoints = 10;
    unit[2].totalHitPoints = 100;
    unit[2].image.load("sprites/bard.png");
    unit[2].mask_image.load("sprites/mask_bard.png");
    unit[2].status = UNIT_OK;
    unit[2].xLocation = 4;
    unit[2].yLocation = 5;
    unit[2].leftTeam = true;

    // Create a new unit (for gl debug purposes).
    unit[3].actionTime = 40;
    unit[3].actionRate = 100;
    unit[3].hitPoints = 10;
    unit[3].totalHitPoints = 100;
    unit[3].image.load("sprites/desertsoldier.png");
    unit[3].mask_image.load("sprites/mask_desertsoldier.png");
    unit[3].status = UNIT_OK;
    unit[3].xLocation = 2;
    unit[3].yLocation = 9;
    unit[3].leftTeam = false;

    // Create a new unit (for gl debug purposes).
    unit[4].actionTime = 40;
    unit[4].actionRate = 100;
    unit[4].hitPoints = 10;
    unit[4].totalHitPoints = 100;
    unit[4].image.load("sprites/merchant.png");
    unit[4].mask_image.load("sprites/mask_merchant.png");
    unit[4].status = UNIT_OK;
    unit[4].xLocation = 3;
    unit[4].yLocation = 7;
    unit[4].leftTeam = false;

    // Create a new unit (for gl debug purposes).
    unit[5].actionTime = 40;
    unit[5].actionRate = 100;
    unit[5].hitPoints = 10;
    unit[5].totalHitPoints = 100;
    unit[5].image.load("sprites/priestess.png");
    unit[5].mask_image.load("sprites/mask_priestess.png");
    unit[5].status = UNIT_OK;
    unit[5].xLocation = 2;
    unit[5].yLocation = 6;
    unit[5].leftTeam = false;

    for( int i = 6; i < MAX_UNITS; i++ )
    {
        // Tell OpenGL whether or not the unit exists.
        unit[i].status = NO_UNIT;
    }

    // Load a background image (debug).
    bkImage.load("backgrounds/beach.png");
    bkImage = bkImage.scaled(GLWidget::width(), GLWidget::height(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    glBkImage = QGLWidget::convertToGLFormat(bkImage);

    glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);							// Depth Buffer Setup
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);				// Set Line Antialiasing
    glEnable(GL_BLEND);                                                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Type Of Blending To Use
    glEnable(GL_TEXTURE_2D);
    return;								// Initialization Went OK
}

void GLWidget::paintGL()
{
    // (Re)Calculate the OpenGL object dimensions.
    fullWidth = GLWidget::width();
    fullHeight = GLWidget::height();
    statusWidth = (fullWidth / cellCount) * 0.1f;
    cellWidth = fullWidth / cellCount;
    cellHeight = fullHeight / cellCount;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw the background.
    glDrawPixels(glBkImage.width(), glBkImage.height(), GL_RGBA, GL_UNSIGNED_BYTE, glBkImage.bits());

    // Draw all units.
    for( int i = 0; i < MAX_UNITS; i++ )
    {
        drawUnit(unit[i]);
        if( unit[i].actionTime >= 100 )
        {
            //killTimer(1);
            unit[i].actionTime = 0;
        }
        unit[i].actionTime += 0.005 * unit[i].actionRate;
    }
    
    // Make the grid lines white.
    qglColor(Qt::white);

    // Draw the grid lines.
    glBegin(GL_LINES);
    for (int i = 1; i <= cellCount + 2; i++)
    {
        // Vertical lines.
        glVertex3f(fullWidth/cellCount * i, 0.0f, 0.0f); // Origin of the line.
        glVertex3f(fullWidth/cellCount * i , fullHeight, 0.0f); // Ending point of the line.
    }
    for (int i = 1; i <= 12; i++)
    {
        // Horizontal lines.
        glVertex3f(0.0f, fullHeight/cellCount * i, 0.0f); // Origin of the line.
        glVertex3f(fullWidth, fullHeight/cellCount * i, 0.0f); // Ending point of the line.
    }
    glEnd( );

    // Write some text.
    //qglColor(Qt::white);
    //renderText(330, 310, 0.0, "Tom text!");
}

bool GLWidget::drawUnit(characterUnit myUnit)
{
    if( myUnit.status == NO_UNIT )
    {
        return( false );
    }

    // Calculate the action and hit point bars as a percentage.
    float actionTime = (float)myUnit.actionTime / (float)100;
    float hitPoints = (float)myUnit.hitPoints / (float)myUnit.totalHitPoints;

    // Dynamically define the height and width of the sprite.
    float widthRation = (float)myUnit.image.width() / (float)myUnit.image.height();
    int spriteHeight = cellHeight + 1, spriteWidth = cellHeight * widthRation;

    // Dynamically define the OpenGL location of the sprite.
    int bottomEdge = myUnit.xLocation * cellHeight;
    int leftEdge = myUnit.yLocation * cellWidth + (cellWidth / 2) - (spriteWidth / 2);
    int rightEdge = leftEdge + spriteWidth;

    glColor4f(1.0f,1.0f,1.0f,0.5f);
    glBlendFunc(GL_DST_COLOR,GL_ZERO);

    glEnable(GL_TEXTURE_2D);
    GLuint textureMask = bindTexture( myUnit.mask_image, GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, textureMask );

    // Draw the sprite facing left or right.
    if( !myUnit.leftTeam )
    {
        glBegin (GL_QUADS);
            // Bottom left.
            glTexCoord2f (0.0, 0.0);
            glVertex3f (leftEdge, bottomEdge, 0.0);

            // Bottom right.
            glTexCoord2f (1.0, 0.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge, 0.0);

            // Top right.
            glTexCoord2f (1.0, 1.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge + spriteHeight, 0.0);

            // Top left.
            glTexCoord2f (0.0, 1.0);
            glVertex3f (leftEdge, bottomEdge + spriteHeight, 0.0);
        glEnd ();
    }
    else
    {
        glBegin (GL_QUADS);
            // Bottom left.
            glTexCoord2f (1.0, 0.0);
            glVertex3f (leftEdge, bottomEdge, 0.0);

            // Bottom right.
            glTexCoord2f (0.0, 0.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge, 0.0);

            // Top right.
            glTexCoord2f (0.0, 1.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge + spriteHeight, 0.0);

            // Top left.
            glTexCoord2f (1.0, 1.0);
            glVertex3f (leftEdge, bottomEdge + spriteHeight, 0.0);
        glEnd ();
    }

    glBlendFunc(GL_ONE, GL_ONE);
    GLuint textureValue = bindTexture( myUnit.image, GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, textureValue );

    // Draw the sprite facing left or right.
    if( !myUnit.leftTeam )
    {
        glBegin (GL_QUADS);
            // Bottom left.
            glTexCoord2f (0.0, 0.0);
            glVertex3f (leftEdge, bottomEdge, 0.0);

            // Bottom right.
            glTexCoord2f (1.0, 0.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge, 0.0);

            // Top right.
            glTexCoord2f (1.0, 1.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge + spriteHeight, 0.0);

            // Top left.
            glTexCoord2f (0.0, 1.0);
            glVertex3f (leftEdge, bottomEdge + spriteHeight, 0.0);
        glEnd ();
    }
    else
    {
        glBegin (GL_QUADS);
            // Bottom left.
            glTexCoord2f (1.0, 0.0);
            glVertex3f (leftEdge, bottomEdge, 0.0);

            // Bottom right.
            glTexCoord2f (0.0, 0.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge, 0.0);

            // Top right.
            glTexCoord2f (0.0, 1.0);
            glVertex3f (leftEdge + spriteWidth, bottomEdge + spriteHeight, 0.0);

            // Top left.
            glTexCoord2f (1.0, 1.0);
            glVertex3f (leftEdge, bottomEdge + spriteHeight, 0.0);
        glEnd ();
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_TEXTURE_2D);

    // Show unit's health.
    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f( leftEdge - statusWidth, bottomEdge + cellHeight * hitPoints, 0.0f );	// Top Left
        glVertex3f( leftEdge, bottomEdge + cellHeight * hitPoints, 0.0f );	// Top Right
        glVertex3f( leftEdge,  bottomEdge, 0.0f );	// Bottom Right
        glVertex3f( leftEdge - statusWidth, bottomEdge, 0.0f );	// Bottom Left
    glEnd();

    // Show unit's action points.
    glColor3f(0.0f, 0.0f, actionTime);
    glBegin(GL_QUADS);
        glVertex3f( rightEdge, bottomEdge + cellHeight * actionTime, 0.0f );	// Top Left
        glVertex3f( rightEdge + statusWidth, bottomEdge + cellHeight * actionTime, 0.0f );	//Top Right
        glVertex3f( rightEdge + statusWidth, bottomEdge, 0.0f );	// Bottom Right
        glVertex3f( rightEdge, bottomEdge, 0.0f );	// Bottom Left
    glEnd();
    return( true );
}

void GLWidget::resizeGL(int width, int height)
{
    // Never divide by zero.
    if (height==0)
    {
        height=1;
    }

    // Setup the new viewport.
    glViewport (0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width,0,height,-1,1);
    glMatrixMode (GL_MODELVIEW);

    updateGL();

    // Reload and resize the background image.
    bkImage.load("backgrounds/beach.png");
    bkImage = bkImage.scaled(fullWidth, fullHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    glBkImage = QGLWidget::convertToGLFormat(bkImage);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  //proces mouse events for rotate/move inside 3D scene
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Process mouse stuff...
}

void GLWidget::timerEvent(QTimerEvent *event)
{
    updateGL();
}
