/*what each command stands for
   set -> cmd to set the count number
   ask -> enquiry of the current state
   fts -> first time setup configuration
   cfg -> cmd for change configuraton
   dis -> cmd to display a number on the screen
   err -> cmd to set error flag on
      ASCII CHAR| DC1  ENQ   DC2    DC3   DC4   !
             CMD| set  ask   fts    cfg   dis  err */
//char CMDLUT[] = {0x11, 0x05, 0x12, 0x13, 0x14, 0x21}; // a look up table for every command
//char CMDLUT[] = {'Q', 'W', 'E', 'R', 'T', 'Y'}; // a look up table for every command


//==================================[SET]========================
void setCount(int val) {
  count = val;
}

//============================[CONFIG]========================
void cfgCMD(int val) {
  type = val;
  EEPROM[1] = type;
}




//============================[GET_CMD_NAME]========================
// gets the command byte from the message and executes the corresponding func
void getCMD() {

  if (CMD == CMDLUT[0]) {
    // set count
  }

  if (CMD == CMDLUT[1]) { //ask
    //reply with count
  }

  if (CMD == CMDLUT[2]) { //fts
    //gets type data
  }

  if (CMD == CMDLUT[3]) { //cfg
    //any changes after  fts
  }

  if (CMD == CMDLUT[4]) { //dis
    //set num on display
  }

  if (CMD == CMDLUT[5]) { //err
    //error state enable
  }

}
