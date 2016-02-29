#include <msg/msg.h>
#include <./master.c>
#include <./worker.c>

int main(int argc, char *argv[]) {
  MSG_init(&argc,argv);
  /* Declare all existing agent, binding their name to their function */
  MSG_function_register("master", &master);
  MSG_function_register("worker", &worker);
  /* Load a platform instance */
  MSG_create_environment("platform.xml"); // we could take the names of XML files as argv
  /* Load a deployment file */
  MSG_launch_application("deployment.xml");
  /* Launch the simulation (until its end) */
  MSG_main();
  XBT_INFO("Simulation took %g seconds", MSG_get_clock());
}
