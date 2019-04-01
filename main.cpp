#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "stb_image.hpp"
#include "Image.hpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Particle.hpp"


/*

The program first asks the user whether to import his or her own image, and the path if the answer is yes. Then, it asks if the user wishes to suppress the splash created at the bottom of the waterfall.

This program reads in a JPEG image using stb_lib, then we try to locate the waterfall in that image. After we get the information about the waterfall, we texture map the image, and create a particle simulator on where the waterfall is to simulate a moving waterfall.

Author: Fabio von Schelling Goldman and Harry Zhou

Collaborators:

 Sean Barrett for writing stb_image.h and providing the source code on Github


*/

using namespace std;
vector<Particle*> particles;
static float tm = 0; //time
unsigned int texture;
Image image;
int par_amt = 250;
vector<Color> average;
bool lock_splash = false;

void init( void ){//create the base line particles and set various GL properties
    float corrective_factor = 6*image.get_waterfall()->get_waterfall_height()/image.get_height();
    for(int i = 0; i < 250; i++){
        Particle *p = new Particle(image.get_waterfall()->get_waterfall_begin(), image.get_waterfall()->get_waterfall_top(),image.get_waterfall()->get_waterfall_width(), image.get_waterfall()->get_waterfall_height(), corrective_factor, lock_splash);
        particles.push_back(p);
        vector<Particle*> t = particles;
    }

    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    
}

//Increase the time to create movement based on the curve of particles
void idle( void ){
    tm += 0.005;
    glutPostRedisplay();
}

void display(void){
    float corrective_factor = 6*image.get_waterfall()->get_waterfall_height()/image.get_height(); //Loosen delimiters of top and bottom a bit
    if(par_amt <= 2500){ //generate 20 new Particles if not at 2500 yet, 2500 is an arbitrary value and can be increased based on PC performance
        for(int i = 0; i < 20; i++){
            particles.push_back(new Particle(tm, image.get_waterfall()->get_waterfall_begin(), image.get_waterfall()->get_waterfall_top(),image.get_waterfall()->get_waterfall_width(), image.get_waterfall()->get_waterfall_height(), corrective_factor, lock_splash));
        }
    }
    par_amt += 20;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-image.get_width()/2, image.get_width()/2, -image.get_height()/2, image.get_height()/2, -400, 400);
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_LINE, GL_FILL);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture( GL_TEXTURE_2D, 0);
    
    for(Particle* p : particles){
        float vert = p->get_location_vert(tm, image.get_waterfall()->wat_widening_factor()); //move the particle vertically
        if (vert > image.get_waterfall()->get_waterfall_bot() - corrective_factor) {
            p->setup(tm, false, image.get_waterfall()->get_waterfall_begin(), image.get_waterfall()->get_waterfall_top(),image.get_waterfall()->get_waterfall_width(), image.get_waterfall()->get_waterfall_height(), corrective_factor, lock_splash);
        }
        glPushMatrix();
        glTranslatef(p->get_location_hori(tm) - image.get_width()/2, image.get_height()/2-vert, 0); //move origin to desired location for GluDisk to draw at that place
        GLUquadric* quadric = gluNewQuadric();
        Color color = average[(int) vert]; //Adapt color slightly to surroundings
        glColor3f(color.x()/255 ,color.y()/255, color.z()/255);
        gluDisk(quadric, 0, p->get_radius(), 10, 10);
        glPopMatrix();
    }

    //Texture mapping
    glBindTexture( GL_TEXTURE_2D, texture);
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-image.get_width()/2, -image.get_height()/2, 0);

    glBegin(GL_QUADS);
    glTexCoord2f(1.0,0.0); glVertex3f(image.get_width(), image.get_height(), 0);
    glTexCoord2f(0.0,0.0); glVertex3f(0, image.get_height(), 0);
    glTexCoord2f(0.0,1.0); glVertex3f(0, 0, 0);
    glTexCoord2f(1.0,1.0); glVertex3f(image.get_width(), 0, 0);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ) {
    switch(key) {
        case 27: // Escape key
            for(Particle* p : particles){ //free the used memory upon exit
                delete(p);
                particles.pop_back();
            }
            exit(0);
    }
    glutPostRedisplay();
}

/*
 * This function looks over each row in the waterfall and calculates the average pixel color
 */
void fill_average(){
    int start_loop_i = image.get_waterfall()->get_waterfall_top();
    int end_loop_i = image.get_waterfall()->get_waterfall_bot();
    int start_loop_j = (int) image.get_waterfall()->get_waterfall_begin();
    int end_loop_j = (int) image.get_waterfall()->get_waterfall_end();
    vector<vector<Color>> tmp_image = image.get_image();
    for (int i = 0; i <= image.get_height(); i++){
        if (i < start_loop_i||i > end_loop_i){
            average.push_back(Color(0,0,0));
            continue;
        }
        Color sum = Color(0,0,0);
        int cnt = 0;
        for (int j = start_loop_j; j <= end_loop_j; j++){
            sum = sum + tmp_image[j][i];
            cnt++;
        }
        Color tmp_sum = (sum/cnt) + Color(255, 255, 255);
        average.push_back(tmp_sum/2);
    }
    return;
}

int main(int argc,char **argv)

{
    string own_image;
    cout << "Would you like to use your own image? For any answer that is not yes we will randomly use one of our preconfigured images." << endl;
    cin >> own_image;
    if (own_image == "yes"){
        int fails = 0;
        do {
            fails++;
            string path;
            printf("Please type the full path of the image.\n");
            cin >> path;
            image = Image(&path[0u]);
            if (fails >= 4){
                printf("Failed to provide a valid image. Ending program.\n");
                exit(-1);
            }
        } while (image.get_data() == NULL);
    }
    
    cout << "Do you wish to suppress the splash at the bottom of waterfall? Please type yes or no. Default is no." << endl;
    string no_splash;
    cin >> no_splash;
    if (no_splash == "yes") lock_splash = true;

    int pot_images = 5;
    srand(time(NULL)); //Seed the random generator
    string potential[pot_images] = {"/home/fabio/cg/particle_falls/wf0.jpeg", "/home/fabio/cg/particle_falls/wf1.jpeg", "/home/fabio/cg/particle_falls/wf2.jpeg", "/home/fabio/cg/particle_falls/wf3.jpeg","/home/fabio/cg/particle_falls/wf4.jpeg"};
    int selector = rand() % pot_images;
    image = Image(&potential[1][0u]);

    fill_average();

    glutInit( &argc, argv );
    
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(image.get_width(), image.get_height());
    
    glutCreateWindow("Waterfall");
    
    init();
    
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );
    glEnable(GL_TEXTURE_2D);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    if (image.get_data())
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.get_width(), image.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.get_data());
    }
    else
    {
        perror("Failed to load texture");
        stbi_image_free(image.get_data());
        exit(-1);
    }
    glutMainLoop();
    
    stbi_image_free(image.get_data());
    return 0;
}
