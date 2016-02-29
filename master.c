#include <msg/msg.h>

XBT_LOG_NEW_DEFAULT_CATEGORY(tuto, "all the info and debug messages of this tutorial");

int master(int argc, char *argv[]) {
  int number_of_tasks = atoi(argv[1]);
  double task_comp_size = atof(argv[2]);
  double task_comm_size = atof(argv[3]);
  int workers_count = atoi(argv[4]);
  char mailbox[80]; char buff[64];
  int i; 
  msg_task_t task;

  /* Dispatching (dumb round-robin algorithm) */
  for (i = 0; i < number_of_tasks; i++) {
    sprintf(buff, "Task_%d", i);
    task = MSG_task_create(buff, task_comp_size, task_comm_size, NULL);
    sprintf(mailbox,"worker-%d",i % workers_count);
    XBT_INFO("Sending \"%s\" to mailbox \"%s\"", task->name, mailbox);
    MSG_task_send(task, mailbox);
  }
  /* Send finalization message to workers */
  XBT_INFO("All tasks dispatched. Let’s stop workers");
  for (i = 0; i < workers_count; i++) {
    sprintf(mailbox,"worker-%d",i % workers_count);
    MSG_task_send(MSG_task_create("finalize", 0, 0, 0), mailbox);
  }

  XBT_INFO("Goodbye now!");

  return 0;
}
