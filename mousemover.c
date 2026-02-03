/* MouseMover licensed under the GPL v3.0 license
   Inspired from Daniel Hirish
   Although this might seem like I just copied and pasted it
   I didn't, I watched the video and learned everything from the video
   That's why it seems so similiar but thanks Daniel :)
*/

#include <linux/input-event-codes.h>
#include <stdio.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <libevdev-1.0/libevdev/libevdev-uinput.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int errcode = 0; // Determines the return value of the functions to check if they failed or not

void cleanup(struct libevdev *dev, struct libevdev_uinput *udev) {  
  libevdev_uinput_destroy(udev);
  libevdev_free(dev);
}

int main() {
  srand(time(NULL)); // Seed rand() so it generates a new number every time
  
  struct libevdev *dev; // device
  struct libevdev_uinput *udev; // uinput-device
  
  dev = libevdev_new(); // Create a new device

  if (dev == NULL) {
    perror("Error");
    cleanup(dev, udev);
    return -1;
  }

  libevdev_set_name(dev, "Fake device made by MouseMover"); // Set the name of the device

  // Define what the mouse can do

  libevdev_enable_event_type(dev, EV_REL); // Enable relative movement for the mouse
  libevdev_enable_event_code(dev, EV_REL, REL_X, NULL); // Enable relative X movement for the mouse
  libevdev_enable_event_code(dev, EV_REL, REL_Y, NULL);
  libevdev_enable_event_type(dev, EV_KEY); // The kernel wouldn't make the thing work without making the mouse able to click so I did it
  libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, NULL); // Enable the left button for the mouse
  libevdev_enable_event_type(dev, EV_SYN); // Enable relative movement for the mouse
  libevdev_enable_event_code(dev, EV_SYN, SYN_REPORT, NULL); // Make sure the movements actually get accepted by the kernel (I think?)

  
  errcode = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &udev); 
  
  if (errcode != 0) {
    perror("Error");
    cleanup(dev, udev);
  }

  while (1) {
    usleep(15000);
    
    int movement = rand() % 41 - 20; // A range from -20 to 20
    int direction = rand() % 2; // From 0 to 1. Where 0 represents X movement and 1 represents Y movement
    
    errcode = libevdev_uinput_write_event(udev, EV_REL, direction, movement);

    if (errcode != 0) {
      perror("Error");
      cleanup(dev, udev);
      return -1;
    }

    errcode = libevdev_uinput_write_event(udev, EV_SYN, SYN_REPORT, 0); // Make sure the kernel processes the request

    if (errcode != 0) {
      perror("Error");
      return -1;
    }        
  }

  return 0;
}
