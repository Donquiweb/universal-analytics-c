#include <stdlib.h>
#include "universal-analytics.h"



int main(int argc, char** argv){
  
  /* Static definition of a group of options (in stack space) */
  UASettings settings = {{
      {UA_CUSTOM_DIMENSION, 5, "C library (5)"},
      {UA_CUSTOM_DIMENSION, 7, "Custom Dimension 7"},
      {UA_CUSTOM_METRIC, 5, "55"},
      {UA_CUSTOM_METRIC, 7, "77"},
      {UA_DOCUMENT_PATH, 0, "/virtual/test/C"},
      {UA_DOCUMENT_TITLE, 0, "This is a test in C"}
  }};


  /* createTracker() calls malloc for the entire size required by
   * the tracker; all memory it requires (except for CURL) is
   * allocated within this call. */
  UATracker tracker = createTracker("UA-XXXXX-Y", "abc1234", NULL);
  
  /* Enable queing 
   * This causes all requests to be queued until the "cleanup" phase
   * of the tracker's life (i.e. at removeTracker() below) */
  setTrackerOption(tracker, UA_OPTION_QUEUE, 1);


  /* Store these options permanently (for the lifetime of the tracker) */
  setParameters(tracker, & settings); 

  /* Send a pageview, with no additional options.
   * Processes only the parameters that are set permanently in the 
   * tracker. */
  printf("Sending core pageview\n");
  sendTracking(tracker, UA_PAGEVIEW, NULL);
  
  
  /* Static definition of a group of options (in stack space) */
  UAOptions opts = {{
    {UA_EVENT_CATEGORY, 0, "Event Category"},
    {UA_EVENT_ACTION, 0, "Event Action (C)"},
    {UA_EVENT_LABEL, 0, "Event Label"},
    {UA_CUSTOM_DIMENSION, 3, "Three"}
  }};

  /* Send an event with additional ephemeral options */
  printf("Sending event\n");
  sendTracking(tracker, UA_EVENT, & opts); 

  /* Process the queued tracking, then clear the tracker's memory
   * and deallocate */
  removeTracker(tracker);


  return 0;
}