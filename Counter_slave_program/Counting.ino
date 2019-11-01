//============================[COUNT_CHECK]========================
void countCheck() {

  if (oldCount != count) {
    countChanged = true;
    if (oldCount > count) {
      changedCount = oldCount - count;
      //if car in, send -1
      inOut = plusMinus[1];  //-
    }
    else if (oldCount < count) {
      changedCount = count - oldCount;
      //if car out, send +1
      inOut = plusMinus[0];  //+
    }
  }
  else {
    //countChanged = false;
    //if not changed send =
    inOut = plusMinus[2];  //=
  }

}
