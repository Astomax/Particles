#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <random>
#include <vector>
#include <math.h>
#include <array>
#include <thread>


const float PI = 3.14159265359f;
const int window_size_x = 700;
const int window_size_y = 700;
const int particle_count = 100000;
const float g = 2;
const float max_vel = 20.0f;
double x_pos, y_pos;

int RandomMinPlus() {
    if (rand() % 3 == 0) {
        return -1;
    }
    return 1;
}

float RandomFloat(float Max) {
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / Max));
}

class Particle {

public: float angle;
public: float force;
public: float pos[2] = { 0, 0 };


      void Draw() {
          glColor4f(1, 1, 1, 0.1f);
          glVertex2f(pos[0], pos[1]);



      }

      void AddForce(float force_angle, float strength) {
          float Xa = cos(force_angle) * strength;
          float Ya = sin(force_angle) * strength;

          float Aa = atan2(Xa, Ya);

          float Xab = force * cos(angle) + Xa;
          float Yab = force * sin(angle) + Ya;

          float new_force = sqrt((Xab * Xab) + (Yab * Yab));
          force = new_force;

          float new_angle = atan2(Yab, Xab);// + RandomFloat(0.1 * PI);
          angle = new_angle;

      }

      void UpdatePos() {
          pos[0] += cos(angle) * force + RandomFloat(0.5);
          pos[1] += sin(angle) * force + RandomFloat(0.5);;

          //angle = 2 * PI - (angle - PI);
          if (force > max_vel) {
              force = max_vel;
          }

          if (pos[1] > window_size_y - 1) {

              pos[1] -= window_size_y;
          }
          else if (pos[1] < 0) {

              pos[1] += window_size_y;
          }

          if (pos[0] > window_size_x - 1) {

              pos[0] -= window_size_x;
          }
          else if (pos[0] < 0) {

              pos[0] += window_size_x;
          }
      }

};


Particle* particles = new Particle[particle_count];

void ThreadFunction(int thread) {
    int A = (particle_count / 20) * thread;
    int B = (particle_count / 20) * (thread + 1);
    for (int i = A; i < B; i++) {




        float angle = atan2(y_pos - particles[i].pos[1], x_pos - particles[i].pos[0]);
        float angle2 = atan2((window_size_y - y_pos) - particles[i].pos[1], (window_size_x - x_pos) - particles[i].pos[0]);
        float angle3 = atan2(y_pos - particles[i].pos[1], (window_size_x - x_pos) - particles[i].pos[0]);
        float angle4 = atan2((window_size_y - y_pos) - particles[i].pos[1], x_pos - particles[i].pos[0]);


        particles[i].AddForce(angle, g);
        //particles[i].AddForce(angle2, g);
        //particles[i].AddForce(angle3, g);
        //particles[i].AddForce(angle4, g);
        particles[i].UpdatePos();
       


    }
}



int main(void)
{

    std::srand(time(NULL));
    GLFWwindow* window;



    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_size_x, window_size_y, "enge dingen", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    gluOrtho2D(0.0, window_size_x, window_size_y, 0.0);




    
   
    for (int i = 0; i < particle_count; i++) {
        Particle new_particle = Particle();

        new_particle.pos[0] = rand() % window_size_x;
        new_particle.pos[1] = rand() % window_size_y;
        new_particle.angle = RandomFloat(2 * PI);
        new_particle.force = 1;

        particles[i] = new_particle;
    }


    int a = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */


        glClear(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        a++;
        

        glClearColor(0, 0, 0, 1);

        
        glfwGetCursorPos(window, &x_pos, &y_pos);


        std::thread t0(ThreadFunction, 0);
        std::thread t1(ThreadFunction, 1);
        std::thread t2(ThreadFunction, 2);
        std::thread t3(ThreadFunction, 3);
        std::thread t4(ThreadFunction, 4);
        std::thread t5(ThreadFunction, 5);
        std::thread t6(ThreadFunction, 6);
        std::thread t7(ThreadFunction, 7);
        std::thread t8(ThreadFunction, 8);
        std::thread t9(ThreadFunction, 9);

        std::thread t10(ThreadFunction, 10);
        std::thread t11(ThreadFunction, 11);
        std::thread t12(ThreadFunction, 12);
        std::thread t13(ThreadFunction, 13);
        std::thread t14(ThreadFunction, 14);
        std::thread t15(ThreadFunction, 15);
        std::thread t16(ThreadFunction, 16);
        std::thread t17(ThreadFunction, 17);
        std::thread t18(ThreadFunction, 18);
        std::thread t19(ThreadFunction, 19);



        t0.join();
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();

        t10.join();
        t11.join();
        t12.join();
        t13.join();
        t14.join();
        t15.join();
        t16.join();
        t17.join();
        t18.join();
        t19.join();

        glBegin(GL_POINTS);
        for (int i = 0; i < particle_count; i++) {
            particles[i].Draw();
        }
       
        glEnd();




        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
