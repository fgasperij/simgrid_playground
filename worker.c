#include <msg/msg.h>

XBT_LOG_NEW_DEFAULT_CATEGORY(tuto, "all the info and debug messages of this tutorial");

int worker(int argc, char *argv[]) {
  msg_task_t task; int errcode;
  int id = atoi(argv[1]);
  char mailbox[80];
  sprintf(mailbox,"worker-%d",id);

  while(1) {
    errcode = MSG_task_receive(&task, mailbox);
    xbt_assert(errcode == MSG_OK, "MSG_task_get failed");

    if (!strcmp(MSG_task_get_name(task),"finalize")) {
      MSG_task_destroy(task);
      break;
    }

    XBT_INFO("Processing ’%s’", MSG_task_get_name(task));
    MSG_task_execute(task);
    XBT_INFO("’%s’ done", MSG_task_get_name(task));
    MSG_task_destroy(task);
  }

  XBT_INFO("I’m done. See you!");

  return 0;
}
